/**
 *
 *     
 *
 *        ________                __   _______________  ___
 *        \______ \ _____ _______|  | _\_   _____/\   \/  /
 *        |    |  \\__  \\_  __ \  |/ /|    __)   \     / 
 *        |    `   \/ __ \|  | \/    < |     \    /     \ 
 *        /_______  (____  /__|  |__|_ \\___  /   /___/\  \
 *                \/     \/           \/    \/          \_/
 * 
 *            DarkCF Copyright 2018 BSD License Dark Overlord of Data         
 * 
 *                        oop framework for c        
 */
/* ******************************************************************************
* Copyright (c) 2012, Jonathan Schleifer <js@webkeks.org>
* Copyright (c) 2018 - 2021 Dark Overlord of Data
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

#include "CFTypes.h"
#include "CFClass.h"
#include "CFObject.h"
#include "CFLog.h"
#include "CFArray.h"
#include "CFBool.h"
#include "CFBox.h"
#include "CFDouble.h"
#include "CFFile.h"
#include "CFHash.h"
#include "CFInt.h"
#include "CFMap.h"
#include "CFRange.h"
#include "CFRefPool.h"
#include "CFStream.h"
#include "CFString.h"
#include "CFSocket.h"


#ifdef __CoreFX_Advanced_Mode__


static inline CFString __attribute__((overloadable))$(char* str)
{
	return CFStringCreate(str);
}

static inline CFBool __attribute__((overloadable))$(_Bool b)
{
	return CFBoolCreate(b);
}


static inline CFInt __attribute__((overloadable))$(int i)
{
	return CFIntCreate(i);
}

static inline CFInt __attribute__((overloadable))$(long i)
{
	return CFIntCreate(i);
}

static inline CFDouble __attribute__((overloadable))$(double f)
{
	return CFDoubleCreate(f);
}

static inline CFType __attribute__((overloadable))$(CFType o)
{
	return o;
	
}

#endif



