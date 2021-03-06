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

#include "CFObject.h"
#include "CFBool.h"

static CFTypeID _kCFBoolTypeID = 0;

struct __CFBool {
	struct __CFObject obj;
	bool value;
};

static Boolean 
CFBoolConstructor(CFType self, va_list args)
{
	CFBool this = self;
	this->value = va_arg(args, int);
	return true;
}

static Boolean 
CFBoolEqual(CFType ptr1, CFType ptr2)
{
	CFObject obj2 = ptr2;
	CFBool boolean1, boolean2;

	if (obj2->cls != CFBoolClass)
		return false;

	boolean1 = ptr1;
	boolean2 = ptr2;

	return (boolean1->value == boolean2->value);
}

static char*
CFBoolToString(CFType self)
{
	CFBool this = self;
	
	if (this->value) {
		return "YES";
	}
	else {
		return "NO";
	}
}

static CFHashCode 
CFBoolHash(CFType self)
{
	CFBool this = self;

	return (uint32_t)this->value;
}

static CFType 
CFBoolCopy(CFType self)
{
	return CFRef(self);
}

static struct __CFClass class = {
	.name = "CFBool",
	.size = sizeof(struct __CFBool),
	.ctor = CFBoolConstructor,
	.equal = CFBoolEqual,
	.hash = CFBoolHash,
	.copy = CFBoolCopy,
	.tostr = CFBoolToString
};
CFClass CFBoolClass = &class;

CFTypeID
CFBoolGetTypeID (void)
{
  return _kCFBoolTypeID;
}

void CFBoolClassInitialize()
{
	_kCFBoolTypeID = CFRegisterClass(&class);
}

CFBool
CFBoolCreate(bool value)
{
	return CFCreateObject(CFBoolClass, value);
}

CFBool
CFBoolNew(bool value)
{
	return CFNewObject(CFBoolClass, value);
}

Boolean
CFBoolValue(CFBool this)
{
	return this->value;
}

