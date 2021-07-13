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

#include "CFClass.h"
#include "CFRange.h"

typedef struct __CFString *CFStringRef;
extern CFClassRef CFStringClass;

extern CFStringRef 
CFStringNew(const char*);

extern CFStringRef
CFStringCreate(const char*);

extern Boolean 
CFStringConstructor(CFTypeRef, va_list);

extern void 
CFStringFinalize(CFTypeRef);

extern Boolean 
CFStringEqual(CFTypeRef, CFTypeRef);

extern CFHashCode 
CFStringHash(CFTypeRef);

extern CFTypeRef 
CFStringCopy(CFTypeRef);

extern CFSize 
CFStrnlen(const char*, CFSize);

extern char* 
CFStrdup(const char*);

extern char* 
CFStrndup(const char*, CFSize);

extern char* 
CFStringC(CFStringRef);

extern CFSize 
CFStringLength(CFStringRef);

extern Boolean 
CFStringSet(CFStringRef, const char*);

extern void 
CFStringSetNocopy(CFStringRef, char*, CFSize);

extern Boolean 
CFStringAppend(CFStringRef, CFStringRef);

extern Boolean 
CFStringAppendC(CFStringRef, const char*);

extern Boolean 
CFStringHasPrefix(CFStringRef, CFStringRef);

extern Boolean 
CFStringHasPrefixC(CFStringRef, const char*);

extern Boolean 
CFStringHasSuffix(CFStringRef, CFStringRef);

extern Boolean 
CFStringHasSuffixC(CFStringRef, const char*);

extern CFSize 
CFStringFind(CFStringRef, CFStringRef, CFRange_t);

extern CFSize 
CFStringFindC(CFStringRef, const char*, CFRange_t);

extern char*
CFStringToString(CFTypeRef);
