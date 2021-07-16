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

#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "CFObject.h"
#include "CFRefPool.h"

static CFTypeID _kCFObjectTypeID = 0;
void CFArrayClassInitialize();
void CFBoolClassInitialize();
void CFBoxClassInitialize();
void CFDoubleClassInitialize();
void CFFileClassInitialize();
void CFIntClassInitialize();
void CFMapClassInitialize();
void CFObjectClassInitialize();
void CFRefPoolClassInitialize();
void CFSocketClassInitialize();
void CFStreamClassInitialize();
void CFStringClassInitialize();
void CFInitialize (void) __attribute__ ((constructor));

void
CFInitialize()
{
	CFArrayClassInitialize();
	CFBoolClassInitialize();
	CFBoxClassInitialize();
	CFDoubleClassInitialize();
	CFFileClassInitialize();
	CFIntClassInitialize();
	CFMapClassInitialize();
	CFObjectClassInitialize();
	CFRefPoolClassInitialize();
	CFSocketClassInitialize();
	CFStreamClassInitialize();
	CFStringClassInitialize();
}

static struct __CFClass class = {
	.name = "CFObject",
	.size = sizeof(struct __CFObject),
};
CFClass CFObjectClass = &class;

static CFClass ClassRegistry[256];
static int classRegistrySize = 0;

void CFObjectClassInitialize()
{
	_kCFObjectTypeID = CFRegisterClass(&class);
}

CFTypeID
CFObjectGetTypeID (void)
{
  return _kCFObjectTypeID;
}

CFTypeID
CFRegisterClass(CFClass cls)
{
	classRegistrySize += 1;
	ClassRegistry[classRegistrySize] = cls;
	return classRegistrySize;
}

CFClass 
CFRegisterGet(CFTypeID index)
{
	return ClassRegistry[index];
}


CFClass 
CFRegisterFind(char* name)
{
	for (int i=0; i<classRegistrySize; i++) {
		if (strcmp(name, ClassRegistry[i]->name) == 0) {
			return ClassRegistry[i];
		}
	}
	return NULL;
}

CFType
CFNewObject(CFClass class, ...)
{
	CFObject this;

	if ((this = malloc(class->size)) == NULL)
		return NULL;

	this->cls = class;
	this->ref_cnt = 1;

	if (class->ctor != NULL) {
		va_list args;
		va_start(args, class);

		if (!class->ctor(this, args)) {
			CFUnRef(this);
			return NULL;
		}

		va_end(args);
	}

	return this;
}

CFType
CFCreateObject(CFClass class, ...)
{
	CFObject this;

	assert(class != CFRefPoolClass);

	if ((this = malloc(class->size)) == NULL)
		return NULL;

	this->cls = class;
	this->ref_cnt = 1;

	if (class->ctor != NULL) {
		va_list args;
		va_start(args, class);

		if (!class->ctor(this, args)) {
			CFUnRef(this);
			return NULL;
		}

		va_end(args);
	}

	if (!CFRefPoolAdd(this)) {
		CFUnRef(this);
		return NULL;
	}

	return this; 
}

CFType
CFRef(CFType self)
{
	CFObject this = self;

	if (this == NULL)
		return NULL;

	this->ref_cnt++;

	return this;
}

void
CFUnRef(CFType self)
{
	CFObject this = self;

	if (this == NULL)
		return;

	if (--this->ref_cnt == 0)
		CFFree(this);
}

void
CFFree(CFType self)
{
	CFObject this = self;

	if (this == NULL)
		return;

	if (this->cls->dtor != NULL)
		this->cls->dtor(this);

	free(this);
}

CFClass
CFGetClass(CFType self)
{
	CFObject this = self;

	if (this == NULL)
		return NULL;

	return this->cls;
}

Boolean
CFIsa(CFType self, CFClass cls)
{
	CFObject this = self;

	if (this == NULL || cls == NULL)
		return false;

	return (this->cls == cls);
}

Boolean
CFEqual(CFType ptr1, CFType ptr2)
{
	CFObject obj1 = ptr1, obj2 = ptr2;

	if (obj1 == obj2)
		return true;

	if (obj1 == NULL || obj2 == NULL)
		return false;

	if (obj1->cls->equal != NULL) {
		return obj1->cls->equal(obj1, obj2);
	} else
		return (obj1 == obj2);
}

CFHashCode
CFHash(CFType self)
{
	CFObject this = self;

	if (this == NULL)
		return 0;

	if (this->cls->hash != NULL)
		return this->cls->hash(this);

	return (uint32_t)(uintptr_t)self;
}

CFType
CFCopy(CFType self)
{
	CFObject this = self;

	if (this == NULL)
		return NULL;

	if (this->cls->copy != NULL)
		return this->cls->copy(this);

	return NULL;
}

CFString 
ToString(CFType self)
{
	return NULL;
}
