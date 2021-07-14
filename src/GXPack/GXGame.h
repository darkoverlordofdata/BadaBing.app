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
#import <CoreFX/CoreFX.h>
#import <SDL2/SDL.h>
#import <SDL2/SDL_image.h>
#import <time.h>
#import <sys/time.h>
#import "OpenGL.h"

#define TicksPerMillisecond  10000.0
#define MillisecondsPerTick 1.0 / (TicksPerMillisecond)

#define TicksPerSecond TicksPerMillisecond * 1000.0   // 10,000,000
#define SecondsPerTick  1.0 / (TicksPerSecond)         // 0.0001

#define SCAN_MASK 0x1ff

typedef struct __GXGame *GXGameRef;

typedef struct GXGameVTable
{
    void (*Initialize)  (GXGameRef);
    void (*LoadContent) (GXGameRef);
    void (*Update)      (GXGameRef, Float64);
    void (*Draw)        (GXGameRef, Float64);
} GXGameVTable;


extern CFClassRef GXGameClass;

extern Float64
GXGameDelta(CFGameRef);

extern Boolean
GXGameIsRunning(CFGameRef);

extern Boolean
GXGameMouseDown(CFGameRef);

extern Float32
GXGameMouseX(CFGameRef);

extern Float32
GXGameMouseY(CFGameRef);

extern Int32
GXGameWidth(CFGameRef);

extern Int32
GXGameHeight(CFGameRef);

extern SDL_Window*
GXGameWindow(CFGameRef);

extern CFStringRef
GXGameTitle(CFGameRef);

extern Boolean 
GXGameConstructor(CFTypeRef, va_list);

extern GXGameRef 
GXGameNew(char*, int, int);

extern GXGameRef 
GXGameCreate(char*, int, int);

extern CFStringRef 
GXGameToString(CFTypeRef);

extern void
GXGameStart(CFGameRef);

extern void
GXGameStop(CFGameRef);

extern void
GXGameQuit(CFGameRef);

extern void
GXGameRun(CFGameRef);

extern void
GXGameInitialize(CFGameRef);

extern void
GXGameLoadContent(CFGameRef);

extern void
GXGameRunLoop(CFGameRef);

extern void
GXGameUpdate(CFGameRef, Float64);

extern void
GXGameDraw(CFGameRef, Float64);

extern void
GXGameHandleEvents(CFGameRef);

extern void
GXGameTick(CFGameRef);

extern void
GXGameFinalyze(CFGameRef);

extern void
GXGameCreatePlatform(CFGameRef);

extern Boolean
GXGameGetKey(CFGameRef, int);

