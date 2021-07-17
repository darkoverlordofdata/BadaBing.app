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
#include <stdio.h> 
#include "CFObject.h"
#include "CFArray.h"
#include "CFHash.h"

struct __CFArray {
	struct __CFObject obj;
	void **data;
	size_t size;
};

static CFTypeID _kCFArrayTypeID = 0;
static CFClass CFArrayClass;

static Boolean 
CFArrayConstructor(CFType self, va_list args)
{
	CFArray this = self;

	this->data = NULL;
	this->size = 0;

	return true;
}

static void 
CFArrayFinalize(CFType self)
{
	CFArray this = self;
	size_t i;

	for (i = 0; i < this->size; i++)
		CFUnRef(this->data[i]);

	if (this->data != NULL)
		free(this->data);
}

static Boolean 
CFArrayEqual(CFType ptr1, CFType ptr2)
{
	CFObject obj2 = ptr2;
	CFArray array1, array2;
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

static CFHashCode 
CFArrayHash(CFType self)
{
	CFArray this = self;
	size_t i;
	uint32_t hash;

	CF_HASH_INIT(hash);

	for (i = 0; i < this->size; i++)
		CF_HASH_ADD_HASH(hash, CFHash(this->data[i]));

	CF_HASH_FINALIZE(hash);

	return hash;
}

static CFType 
CFArrayCopy(CFType self)
{
	CFArray this = self;
	CFArray new;
	size_t i;

	if ((new = CFArrayNew()) == NULL)
		return NULL;

	if ((new->data = malloc(sizeof(void*) * this->size)) == NULL) {
		CFUnRef(new);
		return NULL;
	}
	new->size = this->size;

	for (i = 0; i < this->size; i++)
		new->data[i] = CFRef(this->data[i]);

	return new;
}


// static struct __CFClass __CFArrayClass = {
// 	.name = "CFArray",
// 	.size = sizeof(struct __CFArray),
// 	.ctor = CFArrayConstructor,
// 	.dtor = CFArrayFinalize,
// 	.equal = CFArrayEqual,
// 	.hash = CFArrayHash,
// 	.copy = CFArrayCopy,
// 	.class = CFGetClass,
// 	.tostr = CFArrayToString

// };
// CFClass CFArrayClass = &__CFArrayClass;

CFTypeID
CFArrayGetTypeID (void)
{
  return _kCFArrayTypeID;
}

void CFArrayClassInitialize()
{
	static struct __CFClass __CFArrayClass = {
		.name 	= "CFArray",
		.size 	= sizeof(struct __CFArray),
		.ctor 	= CFArrayConstructor,
		.dtor 	= CFArrayFinalize,
		.equal 	= CFArrayEqual,
		.hash 	= CFArrayHash,
		.copy 	= CFArrayCopy,
		.class 	= CFGetClass,
		.tostr 	= CFArrayToString

	};
	CFArrayClass = &__CFArrayClass;
	_kCFArrayTypeID = CFRegisterClass(CFArrayClass);
}

CFArray 
CFArrayCreate()
{
	return CFCreateObject(CFArrayClass);
}

CFArray 
CFArrayNew()
{
	return CFNewObject(CFArrayClass);
}

CFArray 
CFArrayCreateWith(CFType first, ...)
{
	CFArray this = CFCreateObject(CFArrayClass);
	
	va_list args;
	va_start(args, first);

	CFArrayPush(this, first);
	void *obj;
	while ((obj = va_arg(args, void*)) != NULL)
		CFArrayPush(this, obj);

	va_end(args);
	return this;
}

CFArray 
CFArrayNewWith(CFType first, ...)
{
	CFArray this = CFNewObject(CFArrayClass);

	va_list args;
	va_start(args, first);

	CFArrayPush(this, first);
	void *obj;
	while ((obj = va_arg(args, void*)) != NULL)
		CFArrayPush(this, obj);

	va_end(args);
	return this;
}

CFType
CFArrayGet(CFArray this, size_t index)
{
	if (index >= this->size)
		return NULL;

	return this->data[index];
}

CFSize
CFArraySize(CFArray this)
{
	return this->size;
}

Boolean
CFArraySet(CFArray this, size_t index, CFType self)
{
	CFObject obj = self;
	CFObject old;

	if (index >= this->size)
		return false;

	CFRef(obj);
	old = this->data[index];
	this->data[index] = obj;
	CFUnRef(old);

	return true;
}

Boolean
CFArrayPush(CFArray this, CFType self)
{
	CFObject obj = self;
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

CFType
CFArrayLast(CFArray this)
{
	if (this->size == 0)
		return NULL;

	return this->data[this->size - 1];
}

Boolean
CFArrayPop(CFArray this)
{
	void **new;
	void *last;

	if (this->size == 0)
		return NULL;

	if (this->size == 1) {
		CFUnRef(this->data[0]);
		free(this->data);
		this->data = NULL;
		this->size = 0;
		return true;
	}

	last = this->data[this->size - 1];

	new = realloc(this->data, sizeof(void*) * (this->size - 1));
	if (new == NULL)
		return false;

	CFUnRef(last);

	this->data = new;
	this->size--;

	return true;
}

Boolean
CFArrayContains(CFArray this, CFType self)
{
	size_t i;

	for (i = 0; i < this->size; i++)
		if (CFEqual(this->data[i], self))
			return true;

	return false;
}

Boolean
CFArrayContainsPtr(CFArray this, CFType self)
{
	size_t i;

	for (i = 0; i < this->size; i++)
		if (this->data[i] == self)
			return true;

	return false;
}

CFSize
CFArrayFind(CFArray this, CFType self)
{
	size_t i;

	for (i = 0; i < this->size; i++)
		if (CFEqual(this->data[i], self))
			return i;

	return SIZE_MAX;
}

CFSize
CFArrayFindPtr(CFArray this, CFType self)
{
	size_t i;

	for (i = 0; i < this->size; i++)
		if (this->data[i] == self)
			return i;

	return SIZE_MAX;
}


char* 
CFArrayToString(CFType self)
{
	static char str[64]; 

	CFArray this = self;
	snprintf(str, 63, "CFArray: %li", this->size);
	return str;
}

#ifdef __CoreFX_Advanced_Mode__

void __attribute__((overloadable))
CFForEach(CFArray const this, void (^each)(int, CFType))
{
	for (int i=0; i<this->size; i++) 
	{
		each(i, this->data[i]);
	}
}

void __attribute__((overloadable))
CFForEach(CFArray const this, void (*each)(int, CFType))
{
	for (int i=0; i<this->size; i++) 
	{
		each(i, this->data[i]);
	}
}

#endif