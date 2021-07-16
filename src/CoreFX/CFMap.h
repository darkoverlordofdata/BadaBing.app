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

typedef struct __CFMap *CFMap;

typedef struct CFMapIter_t {
	void *key, *obj;
	/* private */
	CFMap _map;
	uint32_t _pos;
} CFMapIter_t;

extern CFClass CFMapClass;

extern CFMap
CFMapCreate();

extern CFMap
CFMapNew();

extern CFMap
CFMapCreateWith(CFType, ...);

extern CFMap
CFMapNewWith(CFType, ...);

extern CFSize 
CFMapSize(CFMap);

extern CFType 
CFMapGet(CFMap, CFType);

extern CFType 
CFMapGetC(CFMap, const char*);

extern Boolean 
CFMapSet(CFMap, CFType, CFType);

extern Boolean 
CFMapSetC(CFMap, const char*, CFType);

extern void 
CFMapIter(CFMap, CFMapIter_t*);

extern void 
CFMapIterNext(CFMapIter_t*);

extern CFTypeID
CFMapGetTypeID (void);

#ifdef __CoreFX_Advanced_Mode__

void __attribute__((overloadable))
CFForEach(CFMap const this, void (^each)(CFType, CFType));

void __attribute__((overloadable))
CFForEach(CFMap const this, void (*each)(CFType, CFType));

#endif