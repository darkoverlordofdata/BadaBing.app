/*
 * Copyright (c) 2012, Jonathan Schleifer <js@webkeks.org>
 * Copyright (c) 2021 Dark Overlord of Data
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>

#include "CFObject.h"
#include "CFMap.h"
#include "CFHash.h"
#include "CFString.h"

static struct bucket {
	CFObjectRef key, obj;
	uint32_t hash;
} deleted = { NULL, NULL, 0 };

struct __CFMap {
	struct __CFObject obj;
	struct bucket **data;
	uint32_t size;
	size_t items;
};

static struct __CFClass class = {
	.name = "CFMap",
	.size = sizeof(struct __CFMap),
	.ctor = CFMapCreate,
	.dtor = CFMapFinalize,
	.equal = CFMapEqual,
	.hash = CFMapHash,
	.copy = CFMapCopy
};
CFClassRef CFMapClass = &class;


Boolean 
CFMapCreate(CFTypeRef self, va_list args)
{
	CFMapRef this = self;
	void *key;

	this->data = NULL;
	this->size = 0;
	this->items = 0;

	while ((key = va_arg(args, void*)) != NULL)
		if (!CFMapSet(this, key, va_arg(args, void*)))
			return false;

	return true;
}

void 
CFMapFinalize(CFTypeRef self)
{
	CFMapRef this = self;
	uint32_t i;

	for (i = 0; i < this->size; i++) {
		if (this->data[i] != NULL && this->data[i] != &deleted) {
			CFUnref(this->data[i]->key);
			CFUnref(this->data[i]->obj);
			free(this->data[i]);
		}
	}

	if (this->data != NULL)
		free(this->data);
}

Boolean 
CFMapEqual(CFTypeRef ptr1, CFTypeRef ptr2)
{
	CFObjectRef obj2 = ptr2;
	CFMapRef map1, map2;
	uint32_t i;

	if (obj2->cls != CFMapClass)
		return false;

	map1 = ptr1;
	map2 = ptr2;

	if (map1->items != map2->items)
		return false;

	for (i = 0; i < map1->size; i++)
		if (map1->data[i] != NULL && map1->data[i] != &deleted &&
		    !CFEqual(CFMapGet(map2, map1->data[i]->key),
		    map1->data[i]->obj))
			return false;

	return true;
}

CFHashCode 
CFMapHash(CFTypeRef self)
{
	CFMapRef this = self;
	uint32_t i, hash = 0;

	for (i = 0; i < this->size; i++) {
		if (this->data[i] != NULL && this->data[i] != &deleted) {
			hash += this->data[i]->hash;
			hash += CFHash(this->data[i]->obj);
		}
	}

	return hash;
}

CFTypeRef 
CFMapCopy(CFTypeRef self)
{
	CFMapRef this = self;
	CFMapRef new;
	uint32_t i;

	if ((new = CFNew(CFMapClass, (void*)NULL)) == NULL)
		return NULL;

	if ((new->data = malloc(sizeof(*new->data) * this->size)) == NULL)
		return NULL;
	new->size = this->size;

	for (i = 0; i < this->size; i++) {
		if (this->data[i] != NULL && this->data[i] != &deleted) {
			struct bucket *bucket;

			if ((bucket = malloc(sizeof(*bucket))) == NULL)
				return NULL;

			bucket->key = CFRef(this->data[i]->key);
			bucket->obj = CFRef(this->data[i]->obj);
			bucket->hash = this->data[i]->hash;

			new->data[i] = bucket;
		} else
			new->data[i] = NULL;
	}

	return new;
}

bool
resize(CFMapRef this, uint32_t items)
{
	size_t fullness = items * 4 / this->size;
	struct bucket **ndata;
	uint32_t i, nsize;

	if (items > UINT32_MAX)
		return false;

	if (fullness >= 3)
		nsize = this->size << 1;
	else if (fullness <= 1)
		nsize = this->size >> 1;
	else
		return true;

	if (nsize == 0)
		return false;

	if ((ndata = malloc(nsize * sizeof(*ndata))) == NULL)
		return false;

	for (i = 0; i < nsize; i++)
		ndata[i] = NULL;

	for (i = 0; i < this->size; i++) {
		if (this->data[i] != NULL && this->data[i] != &deleted) {
			uint32_t j, last;

			last = nsize;

			j = this->data[i]->hash & (nsize - 1);
			for (; j < last && ndata[j] != NULL; j++);

			/* In case the last bucket is already used */
			if (j >= last) {
				last = this->data[i]->hash & (nsize - 1);

				for (j = 0; j < last && ndata[j] != NULL; j++);
			}

			if (j >= last) {
				free(ndata);
				return false;
			}

			ndata[j] = this->data[i];
		}
	}

	free(this->data);
	this->data = ndata;
	this->size = nsize;

	return true;
}

CFSize
CFMapSize(CFMapRef this)
{
	return this->items;
}

CFTypeRef
CFMapGet(CFMapRef this, CFTypeRef key)
{
	uint32_t i, hash, last;

	if (key == NULL)
		return NULL;

	hash = CFHash(key);
	last = this->size;

	for (i = hash & (this->size - 1);
	    i < last && this->data[i] != NULL; i++) {
		if (this->data[i] == &deleted)
			continue;

		if (CFEqual(this->data[i]->key, key))
			return this->data[i]->obj;
	}

	if (i < last)
		return NULL;

	/* In case the last bucket is already used */
	last = hash & (this->size - 1);

	for (i = 0; i < last && this->data[i] != NULL; i++) {
		if (this->data[i] == &deleted)
			continue;

		if (CFEqual(this->data[i]->key, key))
			return this->data[i]->obj;
	}

	return NULL;
}

CFTypeRef
CFMapGetC(CFMapRef this, const char *key)
{
	CFStringRef str;
	void *ret;

	if ((str = CFNew(CFStringClass, key)) == NULL)
		return NULL;

	ret = CFMapGet(this, str);

	CFUnref(str);

	return ret;
}

Boolean
CFMapSet(CFMapRef this, CFTypeRef key, CFTypeRef obj)
{
	uint32_t i, hash, last;

	if (key == NULL)
		return false;

	if (this->data == NULL) {
		if ((this->data = malloc(sizeof(*this->data))) == NULL)
			return false;

		this->data[0] = NULL;
		this->size = 1;
		this->items = 0;
	}

	hash = CFHash(key);
	last = this->size;

	for (i = hash & (this->size - 1);
	    i < last && this->data[i] != NULL; i++) {
		if (this->data[i] == &deleted)
			continue;

		if (CFEqual(this->data[i]->key, key))
			break;
	}

	/* In case the last bucket is already used */
	if (i >= last) {
		last = hash & (this->size - 1);

		for (i = 0; i < last && this->data[i] != NULL; i++) {
			if (this->data[i] == &deleted)
				continue;

			if (CFEqual(this->data[i]->key, key))
				break;
		}
	}

	/* Key not in dictionary */
	if (i >= last || this->data[i] == NULL || this->data[i] == &deleted ||
	    !CFEqual(this->data[i]->key, key)) {
		struct bucket *bucket;

		if (obj == NULL)
			return true;

		if (!resize(this, this->items + 1))
			return false;

		last = this->size;

		for (i = hash & (this->size - 1); i < last &&
		    this->data[i] != NULL && this->data[i] != &deleted; i++);

		/* In case the last bucket is already used */
		if (i >= last) {
			last = hash & (this->size - 1);

			for (i = 0; i < last && this->data[i] != NULL &&
			    this->data[i] != &deleted; i++);
		}

		if (i >= last)
			return false;

		if ((bucket = malloc(sizeof(*bucket))) == NULL)
			return false;

		if ((bucket->key = CFCopy(key)) == NULL) {
			free(bucket);
			return false;
		}

		bucket->obj = CFRef(obj);
		bucket->hash = CFHash(key);

		this->data[i] = bucket;
		this->items++;

		return true;
	}

	if (obj != NULL) {
		void *old = this->data[i]->obj;
		this->data[i]->obj = CFRef(obj);
		CFUnref(old);
	} else {
		CFUnref(this->data[i]->key);
		CFUnref(this->data[i]->obj);

		free(this->data[i]);
		this->data[i] = &deleted;

		this->items--;

		if (!resize(this, this->items))
			return false;
	}

	return true;
}

Boolean
CFMapSetC(CFMapRef this, const char *key, CFTypeRef obj)
{
	CFStringRef str;
	bool ret;

	if ((str = CFNew(CFStringClass, key)) == NULL)
		return false;

	ret = CFMapSet(this, str, obj);

	CFUnref(str);

	return ret;
}

void
CFMapIter(CFMapRef this, CFMapIter_t *iter)
{
	iter->_map = this;
	iter->_pos = 0;

	CFMapIterNext(iter);
}

void
CFMapIterNext(CFMapIter_t *iter)
{
	CFMapRef this = iter->_map;

	for (; iter->_pos < this->size &&
	    (this->data[iter->_pos] == NULL ||
	    this->data[iter->_pos] == &deleted); iter->_pos++);

	if (iter->_pos < this->size) {
		iter->key = this->data[iter->_pos]->key;
		iter->obj = this->data[iter->_pos]->obj;
		iter->_pos++;
	} else {
		iter->key = NULL;
		iter->obj = NULL;
	}
}
