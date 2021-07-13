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
#include "CFBox.h"

struct __CFBox {
	struct __CFObject obj;
	void *self;
	uint32_t type;
	bool free;
};

static struct __CFClass class = {
	.name = "CFBox",
	.size = sizeof(struct __CFBox),
	.ctor = CFBoxCreate,
	.dtor = CFBoxFinalize
};
CFClassRef CFBoxClass = &class;

Boolean 
CFBoxCreate(CFTypeRef self, va_list args)
{
	CFBoxRef this = self;

	this->self = va_arg(args, void*);
	this->type = va_arg(args, uint32_t);
	this->free = va_arg(args, int);

	return true;
}

void 
CFBoxFinalize(CFTypeRef self)
{
	CFBoxRef this = self;

	if (this->free)
		free(this->self);
}

void*
CFBoxPtr(CFBoxRef this)
{
	return this->self;
}

uint32_t
CFBoxType(CFBoxRef this)
{
	return this->type;
}
