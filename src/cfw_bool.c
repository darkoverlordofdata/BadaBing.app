/*
 * Copyright (c) 2012, Jonathan Schleifer <js@webkeks.org>
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

#include "cfw_object.h"
#include "cfw_bool.h"

struct CFWBool {
	CFWObject obj;
	bool value;
};

static bool
ctor(void *ptr, va_list args)
{
	CFWBool *boolean = ptr;

	boolean->value = va_arg(args, int);

	return true;
}

static bool
equal(void *ptr1, void *ptr2)
{
	CFWObject *obj2 = ptr2;
	CFWBool *boolean1, *boolean2;

	if (obj2->cls != cfw_bool)
		return false;

	boolean1 = ptr1;
	boolean2 = ptr2;

	return (boolean1->value == boolean2->value);
}

static uint32_t
hash(void *ptr)
{
	CFWBool *boolean = ptr;

	return (uint32_t)boolean->value;
}

static void*
copy(void *ptr)
{
	return cfw_ref(ptr);
}

bool
cfw_bool_value(CFWBool *boolean)
{
	return boolean->value;
}

static CFWClass class = {
	.name = "CFWBool",
	.size = sizeof(CFWBool),
	.ctor = ctor,
	.equal = equal,
	.hash = hash,
	.copy = copy
};
CFWClass *cfw_bool = &class;
