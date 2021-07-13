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
#include "CFDouble.h"

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
	.copy = CFDoubleCopy
};
CFClassRef CFDoubleClass = &class;

Boolean 
CFDoubleCreate(CFTypeRef self, va_list args)
{
	CFDoubleRef this = self;

	this->value = va_arg(args, double);

	return true;
}

Boolean 
CFDoubleEqual(CFTypeRef ptr1, CFTypeRef ptr2)
{
	CFObjectRef obj2 = ptr2;
	CFDoubleRef double1, double2;

	if (obj2->cls != CFDoubleClass)
		return false;

	double1 = ptr1;
	double2 = ptr2;

	return (double1->value == double2->value);
}

CFHashCode 
CFDoubleHash(CFTypeRef self)\
{
	CFDoubleRef this = self;

	/* FIXME: Create a proper hash! */
	return (CFHashCode)this->value;
}

CFTypeRef 
CFDoubleCopy(CFTypeRef self)
{
	return CFRef(self);
}

double
CFDoubleValue(CFDoubleRef this)
{
	return this->value;
}

