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

/**
 *	UILabel
 */
struct __UILabel 
{
	struct __CFObject obj;
    int x;
    int y;
    char* text;
    UIFont font;
};

static CFTypeID _kUILabelTypeID = 0;
static CFClass UILabelClass;



static Boolean
UILabelConstructor(CFType self, va_list args)
{
    UILabel this = self;
    const int x = va_arg(args, int);
    const int y = va_arg(args, int);
	const char* text = va_arg(args, char*);
    UIFont font = va_arg(args, UIFont);

    this->x = x;
    this->y = y;
    this->text = strdup(text);
    this->font = font;
	return true;
}

static void 
UILabelFinalize(CFType self)
{
    UILabel this = self;
    if (this->text != NULL) free(this->text);
    printf("UILabel::dtor\n");
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
    CFClass UILabelClass = &__UILabelClass;
	UILabelClass = &__UILabelClass;
	_kUILabelTypeID = CFRegisterClass(UILabelClass);
}


UILabel
UILabelCreate(int x, int y, char* text)
{
	return CFCreateObject(UILabelClass, x, y, text);
}

UILabel
UILabelNew(int x, int y, char* text)
{
	return CFNewObject(UILabelClass, x, y, text);
}

void 
UILabelSetText(UILabel this, char* text) {
    this->text = text;
}

void 
UILabelSetPos(UILabel this, int x, int y) {
    this->x = x;
    this->y = y;
}

void 
UILabelDraw(UILabel this) {
}

