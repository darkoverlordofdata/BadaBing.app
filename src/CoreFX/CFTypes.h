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

#define CFNew(T, args...) CFNewObject(T##Class, ## args)
#define CFCreate(T, args...) CFCreateObject(T##Class, ## args)


/**
 *
 * Advanced Mode includes  type inference
 *
 */
#ifdef __CoreFX_Advanced_Mode__


#define var __auto_type
#define let const var

// static inline Boolean* NewBoolean(bool const value){
//     return CFCreate(CFBooleanClass, value);
// }
// static inline Char* NewChar(char const value) {
//     return CFCreate(CFBooleanClass, value);
// }
// static inline String* NewString(char* const value) {
//     return CFCreate(CFBooleanClass, value);
// }

// static inline Short* NewShort(short const value) {
//     return CFCreate(CFBooleanClass, value);
// }

// static inline Integer* NewInteger(int const value) {
//     return CFCreate(CFBooleanClass, value);
// }

// static inline Long* NewLong(long const value) {
//     return CFCreate(CFBooleanClass, value);
// }

// static inline Float* NewFloat(float const value) {
//     return CFCreate(CFBooleanClass, value);
// }

// static inline Double* NewDouble(double const value) {
//     return CFCreate(CFBooleanClass, value);
// }

// /**
//  *  MACRO $
//  *      Wrap a primitive type in a Object*
//  */
// #define _(T) _Generic((T),                                              \
//                                                                         \
//         _Bool:              NewBoolean,                                 \
//         char:               NewChar,                                    \
//         signed char:        NewChar,                                    \
//         const char *:       NewString,                                  \
//         char *:             NewString,                                  \
//         short int:          NewShort,                                   \
//         unsigned short int: NewShort,                                   \
//         unsigned int:       NewInteger,                                 \
//         long int:           NewLong,                                    \
//         unsigned long int:  NewLong,                                    \
//         int:                NewInteger,                                 \
//         float:              NewFloat,                                   \
//         double:             NewDouble,                                  \
//         default:            NewString)(T)



/**
 *  MACRO typeof
 *      return the typename of T
 */
#define typeof(T) \
    _Generic((T),        /* wrap a primitive type */                    \
                                                                        \
        _Bool: "bool",                                                  \
        unsigned char: "unsigned char",                                 \
        char: "char",                                                   \
        signed char: "signed char",                                     \
        short int: "short int",                                         \
        unsigned short int: "unsigned short int",                       \
        int: "int",                                                     \
        unsigned int: "unsigned int",                                   \
        long int: "long int",                                           \
        unsigned long int: "unsigned long int",                         \
        long long int: "long long int",                                 \
        unsigned long long int: "unsigned long long int",               \
        float: "float",                                                 \
        double: "double",                                               \
        long double: "long double",                                     \
        char *: "pointer to char",                                      \
        void *: "pointer to void",                                      \
        int *: "pointer to int",                                        \
        const char *: "const pointer to char",                          \
        CFObject *: "Object",                                           \
        CFBoolean *: "Boolean",                                         \
        CFDouble *: "Double",                                           \
        CFInt *: "Integer",                                             \
        CFString *: "String",                                           \
        CFArray *: "Array",                                             \
        CFMap *: "Map",                                                 \
        default: "unknown")


#endif