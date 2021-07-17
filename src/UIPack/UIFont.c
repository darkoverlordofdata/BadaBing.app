/* ******************************************************************************
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
*
******************************************************************/
#import <Imlib2.h>
#import <X11/Xlib.h>
#import <X11/Xutil.h>
#import <X11/xpm.h>
#import <X11/extensions/dpms.h>
#import <X11/keysym.h>
#import <Xft/Xft.h>
#include "UIFont.h"


/**
 *	UIFont
 */
struct __UIFont 
{
	struct __CFObject obj;
    char* name;
    int size;
    XftFont *font;
    Display *disp;      // application display
    int screen;
};

static CFTypeID _kUIFontTypeID = 0;
static CFClass UIFontClass;

static Boolean
UIFontConstructor(CFType self, va_list args)
{
    UIFont this = self;
	const char* name = va_arg(args, char*);
	const int size = va_arg(args, int);

    this->name = strdup(name);
    this->size = size;
	return true;
}

static void 
UIFontFinalize(CFType self)
{
    UIFont this = self;
    if (this->name != NULL) free(this->name);
    printf("UIFont::dtor\n");
}

CFTypeID
UIFontGetTypeID (void)
{
  return _kUIFontTypeID;
}

void UIFontClassInitialize()
{
    static struct __CFClass __UIFontClass = {
        .name = "UIFont",
        .size = sizeof(struct __UIFont),
        .ctor = UIFontConstructor,
        .dtor = UIFontFinalize
    };
	UIFontClass = &__UIFontClass;
	_kUIFontTypeID = CFRegisterClass(UIFontClass);
}


extern UIFont 
UIFontCreate(char* name, int size)
{
	return CFCreateObject(UIFontClass, name, size);
}

extern UIFont 
UIFontNew(char* name, int size)
{
	return CFNewObject(UIFontClass, name, size);
}
