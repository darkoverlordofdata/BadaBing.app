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
#include "CFInt.h"

struct __CFInt {
	struct __CFObject obj;
	intmax_t value;
};

static struct __CFClass class = {
	.name = "CFInt",
	.size = sizeof(struct __CFInt),
	.ctor = CFIntCreate,
	.equal = CFIntEqual,
	.hash = CFIntHash,
	.copy = CFIntCopy
};
CFClassRef CFIntClass = &class;

Boolean 
CFIntCreate(CFTypeRef self, va_list args)
{
	CFIntRef this = self;

	this->value = va_arg(args, intmax_t);

	return true;
}

Boolean 
CFIntEqual(CFTypeRef ptr1, CFTypeRef ptr2)
{
	CFObjectRef obj2 = ptr2;
	CFIntRef int1, int2;

	if (obj2->cls != CFIntClass)
		return false;

	int1 = ptr1;
	int2 = ptr2;

	return (int1->value == int2->value);
}

CFHashCode 
CFIntHash(CFTypeRef self)
{
	CFIntRef this = self;

	return (uint32_t)this->value;
}

CFTypeRef 
CFIntCopy(CFTypeRef self)
{
	return CFRef(self);
}

intmax_t 
CFIntValue(CFIntRef this)
{
	return this->value;
}

