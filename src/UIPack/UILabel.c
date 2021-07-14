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
    UIFontRef font;
};

static struct __CFClass class = {
	.name = "UILabel",
	.size = sizeof(struct __UILabel),
	.ctor = UILabelConstructor,
	.dtor = UILabelFinalize
};
CFClassRef UILabelClass = &class;


void 
UILabelSetText(UILabelRef this, char* text) {
}

void 
UILabelSetPos(UILabelRef this, int x, int y) {
}

void 
UILabelDraw(UILabelRef this) {
}

Boolean
UILabelConstructor(CFTypeRef self, va_list args)
{
    UILabelRef this = self;
    const int x = va_arg(args, int);
    const int y = va_arg(args, int);
	const char* text = va_arg(args, char*);
    UIFontRef font = va_arg(args, UIFontRef);

    this->x = x;
    this->y = y;
    this->text = strdup(text);
    this->font = font;
	return true;
}

void 
UILabelFinalize(CFTypeRef self)
{
    UILabelRef this = self;
    if (this->text != NULL) free(this->text);
    printf("UILabel::dtor\n");
}

