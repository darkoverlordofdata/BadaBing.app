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

typedef struct __CFString *CFString;
extern CFClass CFStringClass;

extern CFString 
CFStringNew(const char*);

extern CFString
CFStringCreate(const char*);

extern Boolean 
CFStringConstructor(CFType, va_list);

extern void 
CFStringFinalize(CFType);

extern Boolean 
CFStringEqual(CFType, CFType);

extern CFHashCode 
CFStringHash(CFType);

extern CFType 
CFStringCopy(CFType);

extern CFSize 
CFStrnlen(const char*, CFSize);

extern char* 
CFStrdup(const char*);

extern char* 
CFStrndup(const char*, CFSize);

extern char* 
CFStringC(CFString);

extern CFSize 
CFStringLength(CFString);

extern Boolean 
CFStringSet(CFString, const char*);

extern void 
CFStringSetNocopy(CFString, char*, CFSize);

extern Boolean 
CFStringAppend(CFString, CFString);

extern Boolean 
CFStringAppendC(CFString, const char*);

extern Boolean 
CFStringHasPrefix(CFString, CFString);

extern Boolean 
CFStringHasPrefixC(CFString, const char*);

extern Boolean 
CFStringHasSuffix(CFString, CFString);

extern Boolean 
CFStringHasSuffixC(CFString, const char*);

extern CFSize 
CFStringFind(CFString, CFString, CFRange_t);

extern CFSize 
CFStringFindC(CFString, const char*, CFRange_t);

extern char*
CFStringToString(CFType);

extern CFTypeID
CFStringGetTypeID (void);
