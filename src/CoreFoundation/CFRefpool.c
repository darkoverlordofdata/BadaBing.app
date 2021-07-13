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
#include <assert.h>

#include "CFObject.h"
#include "CFRefpool.h"
#include "CFArray.h"

struct __CFRefpool {
	struct __CFObject obj;
	void **data;
	CFSize size;
	CFRefpoolRef prev, next;
};

static CFRefpoolRef top;

static struct __CFClass class = {
	.name = "CFRefPool",
	.size = sizeof(struct __CFRefpool),
	.ctor = CFRefpoolCreate,
	.dtor = CFRefpoolFinalize
};
CFClassRef CFRefpoolClass = &class;


Boolean 
CFRefpoolCreate(CFTypeRef self, va_list args)
{
	CFRefpoolRef this = self;

	this->data = NULL;
	this->size = 0;

	if (top != NULL) {
		this->prev = top;
		top->next = this;
	} else
		this->prev = NULL;
	this->next = NULL;

	top = this;

	return true;
}

void 
CFRefpoolFinalize(CFTypeRef self)
{
	CFRefpoolRef this = self;
	size_t i;

	if (this->next != NULL)
		CFUnref(this->next);

	for (i = 0; i < this->size; i++)
		CFUnref(this->data[i]);

	if (this->data != NULL)
		free(this->data);

	top = this->prev;

	if (top != NULL)
		top->next = NULL;
}

Boolean
CFRefpoolAdd(CFTypeRef self)
{
	void **ndata;

	assert(top != NULL);

	if (top->data != NULL)
		ndata = realloc(top->data, (top->size + 1) * sizeof(void*));
	else
		ndata = malloc((top->size + 1) * sizeof(void*));

	if (ndata == NULL)
		return false;

	ndata[top->size++] = self;

	top->data = ndata;

	return true;
}

