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
#include <stdint.h>

#include "CFObject.h"
#include "CFArray.h"
#include "CFHash.h"

struct __CFArray {
	struct __CFObject obj;
	void **data;
	size_t size;
};

static struct __CFClass class = {
	.name = "CFArray",
	.size = sizeof(struct __CFArray),
	.ctor = CFArrayCreate,
	.dtor = CFArrayFinalize,
	.equal = CFArrayEqual,
	.hash = CFArrayHash,
	.copy = CFArrayCopy,
	.class = CFClass
};
CFClassRef CFArrayClass = &class;

typedef CFArrayRef (*CFAlloc_t)(CFTypeRef cf, ...);

CFArrayRef 
CFArrayNew(CFAlloc_t f, va_list args)
{
	CFArrayRef o = f(CFArrayClass);
	CFArrayCreate(o, args);
	return o;
}
// x = CFArrayCreate(CFNew, a, b, c);

Boolean 
CFArrayCreate(CFTypeRef self, va_list args)
{
	CFArrayRef this = self;
	void *obj;

	this->data = NULL;
	this->size = 0;

	while ((obj = va_arg(args, void*)) != NULL)
		if (!CFArrayPush(this, obj))
			return false;

	return true;
}

void 
CFArrayFinalize(CFTypeRef self)
{
	CFArrayRef this = self;
	size_t i;

	for (i = 0; i < this->size; i++)
		CFUnref(this->data[i]);

	if (this->data != NULL)
		free(this->data);
}

Boolean 
CFArrayEqual(CFTypeRef ptr1, CFTypeRef ptr2)
{
	CFObjectRef obj2 = ptr2;
	CFArrayRef array1, array2;
	size_t i;

	if (obj2->cls != CFArrayClass)
		return false;

	array1 = ptr1;
	array2 = ptr2;

	if (array1->size != array2->size)
		return false;

	for (i = 0; i < array1->size; i++)
		if (CFEqual(array1->data[i], array2->data[i]))
			return false;

	return true;
}

CFHashCode 
CFArrayHash(CFTypeRef self)
{
	CFArrayRef this = self;
	size_t i;
	uint32_t hash;

	CF_HASH_INIT(hash);

	for (i = 0; i < this->size; i++)
		CF_HASH_ADD_HASH(hash, CFHash(this->data[i]));

	CF_HASH_FINALIZE(hash);

	return hash;
}

CFTypeRef 
CFArrayCopy(CFTypeRef self)
{
	CFArrayRef this = self;
	CFArrayRef new;
	size_t i;

	if ((new = CFNew(CFArrayClass, (void*)NULL)) == NULL)
		return NULL;

	if ((new->data = malloc(sizeof(void*) * this->size)) == NULL) {
		CFUnref(new);
		return NULL;
	}
	new->size = this->size;

	for (i = 0; i < this->size; i++)
		new->data[i] = CFRef(this->data[i]);

	return new;
}

CFTypeRef
CFArrayGet(CFArrayRef this, size_t index)
{
	if (index >= this->size)
		return NULL;

	return this->data[index];
}

CFSize
CFArraySize(CFArrayRef this)
{
	return this->size;
}

Boolean
CFArraySet(CFArrayRef this, size_t index, CFTypeRef self)
{
	CFObjectRef obj = self;
	CFObjectRef old;

	if (index >= this->size)
		return false;

	CFRef(obj);
	old = this->data[index];
	this->data[index] = obj;
	CFUnref(old);

	return true;
}

Boolean
CFArrayPush(CFArrayRef this, CFTypeRef self)
{
	CFObjectRef obj = self;
	void **new;

	if (this->data == NULL)
		new = malloc(sizeof(void*));
	else
		new = realloc(this->data, sizeof(void*) * (this->size + 1));

	if (new == NULL)
		return false;

	new[this->size] = CFRef(obj);

	this->data = new;
	this->size++;

	return true;
}

CFTypeRef
CFArrayLast(CFArrayRef this)
{
	if (this->size == 0)
		return NULL;

	return this->data[this->size - 1];
}

Boolean
CFArrayPop(CFArrayRef this)
{
	void **new;
	void *last;

	if (this->size == 0)
		return NULL;

	if (this->size == 1) {
		CFUnref(this->data[0]);
		free(this->data);
		this->data = NULL;
		this->size = 0;
		return true;
	}

	last = this->data[this->size - 1];

	new = realloc(this->data, sizeof(void*) * (this->size - 1));
	if (new == NULL)
		return false;

	CFUnref(last);

	this->data = new;
	this->size--;

	return true;
}

Boolean
CFArrayContains(CFArrayRef this, CFTypeRef self)
{
	size_t i;

	for (i = 0; i < this->size; i++)
		if (CFEqual(this->data[i], self))
			return true;

	return false;
}

Boolean
CFArrayContainsPtr(CFArrayRef this, CFTypeRef self)
{
	size_t i;

	for (i = 0; i < this->size; i++)
		if (this->data[i] == self)
			return true;

	return false;
}

CFSize
CFArrayFind(CFArrayRef this, CFTypeRef self)
{
	size_t i;

	for (i = 0; i < this->size; i++)
		if (CFEqual(this->data[i], self))
			return i;

	return SIZE_MAX;
}

CFSize
CFArrayFindPtr(CFArrayRef this, CFTypeRef self)
{
	size_t i;

	for (i = 0; i < this->size; i++)
		if (this->data[i] == self)
			return i;

	return SIZE_MAX;
}


