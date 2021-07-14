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
#include <stdio.h> 
#include <stdlib.h> 
#include <stdarg.h>
#include <math.h> 
#include <string.h>
#include <time.h>
#import <sys/time.h>



    // time_t now = time(NULL);
    // struct tm *t = localtime(&now);

    // strftime(this->tline, BUFLEN-1, "%l:%M", t);


static inline void CFLog (char* format, ...);

// static inline __attribute__((__format__ (__printf__, 1, 2))) 
static inline char* CFsprintf(const char* format, ...);
static inline void CFvfprintf(FILE*, const char*, va_list);
static inline int CFSvsnprintf(char*, size_t, const char*, va_list);
static inline int CFvsnprintf(char*, size_t, const char*, va_list);

// void
// CFLogv(char* format, va_list args)
// {

// }

// void
// CFLog(char* format, ...)
// {
//   va_list ap;

//   va_start(ap, format);
//   CFLogv(format, ap);
//   va_end(ap);
// }

static inline uint64_t GetTicks() { 
    static struct timeval t = { .tv_sec = 0, .tv_usec = 0 };
    
    gettimeofday(&t, NULL);
    // uint64_t ts = t.tv_sec;
    // uint64_t us = t.tv_usec;
    // return ((ts * 1000000L) + us) * 10;
    return t.tv_sec;
}

/**
 * Log
 * 
 * Writes output to stderr, with end of line.
 */
// __attribute__((__format__ (__printf__, 1, 2)))
static inline void CFLog (char* format, ...) {

    time_t now = time(NULL) - (60*60*3);
    struct tm *t = localtime(&now);
    char buf[256]; 

    // static struct timeval ts = { .tv_sec = 0, .tv_usec = 0 };
    // gettimeofday(&ts, NULL);
    // fprintf(stderr, "[%s:%lu] ", buf, ts.tv_usec / 1000L );
    
    strftime(buf, 255, "%Y-%m-%d %H:%M:%S", t);
    fprintf(stderr, "[%s] ", buf );

    va_list args;
    va_start(args, format);
    CFvfprintf(stderr, format, args);
    va_end(args);
    // fprintf(stderr, "\n");
}


static inline __attribute__((__format__ (__printf__, 1, 2)))                          
char* CFsprintf(const char* format, ...) 
{
    va_list args1;
    va_list args2;
    
    va_start(args1, format);
    va_copy(args2, args1);  

    int len = CFvsnprintf(NULL, 0, format, args1);
    va_end(args1);
    if (len == 0) return "";
    //FiX!!!
    char* str = (char*)calloc((len+1), sizeof(char));
    len = CFvsnprintf(str, len+1, format, args2);
    va_end(args2);
    return str;
}

static inline void CFvfprintf(FILE* stream, const char* format, va_list _args) 
{
    va_list args1;
    va_list args2;
    
    va_copy(args1, _args);
    va_copy(args2, _args);  

    int len = CFvsnprintf(NULL, 0, format, args1);
    va_end(args1);
    //FiX!!!
    char* str = (char*)calloc((len+1), sizeof(char));
    len = CFvsnprintf(str, len+1, format, args2);
    va_end(args2);
    fputs(str, stream);
    free(str);
    return;
}

static inline int CFvsnprintf(char* str, size_t n, const char* format, va_list _args)  
{
    const char *current; 
    char result[40];
    char spec[40];
    int i;
    int l;
    int c;
    char *s;
    CFObjectRef object;
    char *dst = str;
    bool update = (str != NULL);
    int length = 0;
    char* types = "diuoxXfFeEgGaAcspn$@";
    va_list arg; 
    va_copy(arg, _args);
    
    /**
     * decompose the format string into specifiers.
     * call sprintf for standard specifiers, and handle
     * new specifiers.
     */
    for (current = format; *current != '\0'; current++) { 

        while ( *current != '%' ) { 
            if (*current == '\0') return length;
            if (update) *dst++ = *current;
            current++; 
            length++;
        } 
        c = 0;
        memset(spec, 0, 40);
        spec[c++] = *current;
        current++;

        /** 
         * collect the specifier 
         * 
         *  %[flags][width][.precision][length]specifier 
         * 
         * Everything between the leading % and the specifier is collected
         * and passed on to stdlib sprintf. This is done to add a new
         * specifier, '$' for DaRKSTEP objects.
         * 
         */
        while ((*current != '\0') 
            && (strchr(types, *current) != NULL)) {
            spec[c++] = *current;
            current++;
        }
        /** Back up one, and point to the specifier */
        current--;

        switch (*current) { 
        case 'c' :  /** char */
            i = va_arg(arg, int);    
            if (update) *dst++ = i;
            length++;
            break; 
                    
        case 'f' :  /** float */
        case 'F' : 
        case 'e' : 
        case 'E' : 
        case 'g' : 
        case 'G' : 
        case 'a' : 
        case 'A' : 
            l = sprintf(result, spec, va_arg(arg, double));
            if (update) dst = strncpy(dst, result, l) + l;
            length += l;
            break;

        case 'u':   /** unsigned */
            l = sprintf(result, spec, va_arg(arg, unsigned int));
            if (update) dst = strncpy(dst, result, l) + l;
            length += l;
            break;

        case 'd':   /** integer */
        case 'i': 
            l = sprintf(result, spec, va_arg(arg, int));
            if (update) dst = strncpy(dst, result, l) + l;
            length += l;
            break;

        case 'o':   /** octal */
            l = sprintf(result, spec, va_arg(arg, unsigned int));
            if (update) dst = strncpy(dst, result, l) + l;
            length += l;
            break;
                    
        case 's':   /** string */
            s = va_arg(arg, char *);       
            l = strlen(s);
            if (update) dst = strncpy(dst, s, l) + l;
            length += l;
            break; 
                    
        case 'x':   /** hex */
        case 'X':
            l = sprintf(result, spec, va_arg(arg, unsigned int));
            if (update) dst = strncpy(dst, result, l) + 1;
            length += l;
            break;

        case '$':   /** DaRKSTEP object */
        case '@':   /** DaRKSTEP object */
            object = va_arg(arg, CFObjectRef);   
            l = strlen(object->cls->tostr(object));
            if (update) dst = strncpy(dst, object->cls->tostr(object), l) + l;
            length += l;
            break;
        }   
    } 
    va_end(arg); 
    return 0;
}

