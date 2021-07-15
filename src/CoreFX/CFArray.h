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

typedef struct __CFArray *CFArray;

extern CFClass CFArrayClass;

extern Boolean 
CFArrayCreate(CFType self, va_list args);

extern void 
CFArrayFinalize(CFType);

extern Boolean 
CFArrayEqual(CFType, CFType);

extern CFHashCode 
CFArrayHash(CFType);

extern CFType 
CFArrayCopy(CFType);

extern CFSize 
CFArraySize(CFArray);

extern CFType 
CFArrayGet(CFArray, CFSize);

extern Boolean 
CFArraySet(CFArray, CFSize, CFType);

extern Boolean 
CFArrayPush(CFArray, CFType);

extern CFType 
CFArrayLast(CFArray);

extern Boolean 
CFArrayPop(CFArray);

extern Boolean 
CFArrayContains(CFArray, CFType);

extern Boolean 
CFArrayContainsPtr(CFArray, CFType);

extern CFSize 
CFArrayFind(CFArray, CFType);

extern CFSize 
CFArrayFindPtr(CFArray, CFType);

extern char* 
CFArrayToString(CFType self);

extern CFTypeID
CFArrayGetTypeID (void);

#ifdef __CoreFX_Advanced_Mode__

void __attribute__((overloadable))
CFForEach(CFArray const this, void (^each)(int, CFType));

void __attribute__((overloadable))
CFForEach(CFArray const this, void (*each)(int, CFType));

#endif