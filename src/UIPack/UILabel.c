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
#include "UILabel.h"
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR

#include "nuklear.h"
#include "nuklear_xlib.h"


/**
 *	UILabel
 */
struct __UILabel 
{
	struct __CFObject obj;
    UIWindow parent;
    CFArray children;
    NKContext ctx;
    UIWidgetVtbl vtbl;

    CFString text;
    long format; //enum nk_text_alignment
};

static CFTypeID _kUILabelTypeID = 0;
static CFClass UILabelClass;

static struct __UIWidgetVtbl vtbl = {
    // .Draw = (void(*)(void*))UILabelDraw
    .Draw = UILabelDraw
};

static Boolean
UILabelConstructor(CFType self, va_list args)
{
    UILabel this = self;
    this->vtbl = &vtbl;
    this->text = CFStringCreate(va_arg(args, char*));
    this->format = va_arg(args, long);
	return true;
}

static void 
UILabelFinalize(CFType self)
{
    CFLog("UILabel::dtor %s \n");
}

CFTypeID
UILabelGetTypeID (void)
{
  return _kUILabelTypeID;
}

void UILabelClassInitialize()
{
    static struct __CFClass __UILabelClass = {
        .name = "UILabel",
        .size = sizeof(struct __UILabel),
        .ctor = UILabelConstructor,
        .dtor = UILabelFinalize
    };
	UILabelClass = &__UILabelClass;
	_kUILabelTypeID = CFRegisterClass(UILabelClass);
}

UILabel
UILabelCreate(char* text, long format)
{
	return CFCreateObject(UILabelClass, text, format);
}

void
UILabelDraw(void* self)
{
    UILabel this = self;
    nk_layout_row_dynamic(this->ctx, 30, 3);
    nk_label(this->ctx, CFStringC(this->text), this->format);
}

void
UILabelParent(UILabel this, UIWindow parent, NKContext ctx)
{
    this->parent = parent;
    this->ctx = UIWindownnNKCtx(parent);
}



void
UILabelRun(UILabel this)
{
}
