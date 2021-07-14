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

#pragma once

#include <unistd.h>

#include "CFClass.h"
#include "CFObject.h"
#include "CFString.h"

struct CFStreamOps {
	ssize_t (*read)	(CFTypeRef , CFTypeRef , CFSize);
	bool (*write) 	(CFTypeRef, const void *, CFSize);
	bool (*at_end)	(CFTypeRef );
	void (*close)	(CFTypeRef );
};

struct __CFStream {
	struct __CFObject obj;
	struct CFStreamOps *ops;
	char *cache;
	CFSize cache_len;
};

typedef struct __CFStream *CFStreamRef;

extern CFClassRef CFStreamClass;

extern Boolean 
CFStreamCreate(CFTypeRef, va_list);

extern void 
CFStreamFinalize(CFTypeRef);

extern CFSize 
CFStreamRead(CFTypeRef , CFTypeRef , CFSize);

extern CFStringRef 
CFStreamReadLine(CFTypeRef );

extern Boolean 
CFStreamWrite(CFTypeRef , const CFTypeRef , CFSize);

extern Boolean 
CFStreamWriteString(CFTypeRef , const char*);

extern Boolean 
CFStreamWriteLine(CFTypeRef , const char*);

extern Boolean 
CFStreamAtEnd(CFTypeRef );

extern void 
CFStreamClose(CFTypeRef );

