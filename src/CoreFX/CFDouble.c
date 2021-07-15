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

#include <stdio.h> 
#include "CFObject.h"
#include "CFDouble.h"

static CFTypeID _kCFDoubleTypeID = 0;

struct __CFDouble {
	struct __CFObject obj;
	double value;
};

static struct __CFClass class = {
	.name = "CFDouble",
	.size = sizeof(struct __CFDouble),
	.ctor = CFDoubleCreate,
	.equal = CFDoubleEqual,
	.hash = CFDoubleHash,
	.copy = CFDoubleCopy,
	.tostr = CFDoubleToString
};
CFClass CFDoubleClass = &class;

CFTypeID
CFDoubleGetTypeID (void)
{
  return _kCFDoubleTypeID;
}

void CFDoubleClassInitialize()
{
	_kCFDoubleTypeID = CFRegisterClass(&class);
}

Boolean 
CFDoubleCreate(CFType self, va_list args)
{
	CFDouble this = self;
	this->value = va_arg(args, double);
	return true;
}

Boolean 
CFDoubleEqual(CFType ptr1, CFType ptr2)
{
	CFObject obj2 = ptr2;
	CFDouble double1, double2;

	if (obj2->cls != CFDoubleClass)
		return false;

	double1 = ptr1;
	double2 = ptr2;

	return (double1->value == double2->value);
}

CFHashCode 
CFDoubleHash(CFType self)\
{
	CFDouble this = self;

	/* FIXME: Create a proper hash! */
	return (CFHashCode)this->value;
}

CFType 
CFDoubleCopy(CFType self)
{
	return CFRef(self);
}

double
CFDoubleValue(CFDouble this)
{
	return this->value;
}

char* 
CFDoubleToString(CFType self)
{
	static char str[64]; 

	CFDouble this = self;
	snprintf(str, 63, "%f", this->value);
	return str;
}

