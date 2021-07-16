/*******************************************************************
** This code is part of the Dark Framework.
**
*
* Copyright (c) 2018 Dark Overlord of Data
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
*
******************************************************************/
#pragma once

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>

typedef bool Boolean;
typedef int8_t Int8;
typedef uint8_t UInt8;
typedef int16_t Int16;
typedef uint16_t UInt16;
typedef int32_t Int32;
typedef uint32_t UInt32;
typedef int64_t Int64;
typedef uint64_t UInt64;
typedef float Float32;
typedef double Float64;
typedef uint32_t CFHashCode;
typedef uint32_t CFTypeID;
typedef void* CFType;
typedef size_t CFSize;
typedef size_t CFIndex;

extern CFTypeID CFArrayTypeID;
extern CFTypeID CFBitVectorTypeID;
extern CFTypeID CFBoolTypeID;
extern CFTypeID CFBoxTypeID;
extern CFTypeID CFClassTypeID;
extern CFTypeID CFDateTypeID;
extern CFTypeID CFDoubleTypeID;
extern CFTypeID CFFileTypeID;
extern CFTypeID CFIntTypeID;
extern CFTypeID CFListTypeID;
extern CFTypeID CFMapTypeID;
extern CFTypeID CFObjectTypeID;
extern CFTypeID CFRangeTypeID;
extern CFTypeID CFRefPoolTypeID;
extern CFTypeID CFSocketTypeID;
extern CFTypeID CFStreamTypeID;
extern CFTypeID CFStringTypeID;
extern CFTypeID CFUUIDTypeID;

/**
 *  MACRO Min
 *      cache results of calculation in pocket scope 
 */
#define Min(a, b)                                                       \
({                                                                      \
    const __auto_type _a = a;                                                         \
    const __auto_type _b = b;                                                         \
    (_a < _b) ? _a : _b;                                                \
})

/**
 *  MACRO Max
 *      cache results of calculation in pocket scope 
 */
#define Max(a, b)                                                       \
({                                                                      \
    const __auto_type _a = a;                                                         \
    const __auto_type _b = b;                                                         \
    (_a > _b) ? _a : _b;                                                \
})


#undef true
#undef false
#define true (_Bool)1
#define false (_Bool)0
#define YES true
#define NO false


#define CFCreate(T, args...) CFCreateObject(CFRegisterGet(T##GetTypeID()), ## args)
#define CFNew(T, args...) CFNewObject(CFRegisterGet(T##GetTypeID()), ## args)
/**
 *
 * Advanced Mode includes  type inference
 *
 */
#ifdef __CoreFX_Advanced_Mode__


#define var __auto_type
#define let const var



#endif