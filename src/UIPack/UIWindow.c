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
#include "UIWindow.h"

/**
 *	UIWindow Instance
 */
struct __UIWindow
{
	struct __CFObject obj;
    Display *display;      // application display
    int screen;
    UIApplicationRef app;
    int width;
    int height;
    Window root;
    int depth;
    Window active;      // the active window
    Window top;         // top level window
    Window panel;       // drawing panel
    XftDraw *draw;      // drawable
    XftColor color;     // color to draw
    XftColor bgcolor;   // color tp draw
    Colormap cm;
    Cursor invisible;
};

/**
 *	UIWindow Class
 */
static struct __CFClass class = 
{
	.name = "UIWindow",
	.size = sizeof(struct __UIWindow),
	.ctor = UIWindowConstructor,
	.dtor = UIWindowFinalize
};

CFClass UIWindowClass = &class;

Boolean
/**
 * Constructor
 */
UIWindowConstructor(CFType self, va_list args)
{
    UIWindowRef this = self;

    this->app = va_arg(args, UIApplicationRef);

    this->display = XOpenDisplay(NULL);
    if (this->display == NULL) {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }

    this->screen = DefaultScreen(this->display);

    this->depth = DefaultDepth(this->display, this->screen);
    this->root = RootWindow(this->display, this->screen);

    this->width = DisplayWidth(this->display, this->screen);
    this->height = DisplayHeight(this->display, this->screen);

    this->cm = DefaultColormap(this->display, this->screen);

    XColor bg = { 0, 0, 0, 0 }; // black
    XColor fg = { 0, 65535, 65535, 65535 }; // white

    XAllocColor(this->display, this->cm, &bg);
    XAllocColor(this->display, this->cm, &fg);

	return true;
}

void 
/**
 * Finalize
 */
UIWindowFinalize(CFType self)
{
    UIWindowRef this = self;
    XDestroyWindow(this->display, this->top);
    XCloseDisplay(this->display);
    CFLog("UIWindow::dtor\n");
}


void 
/**
 * Run
 */
UIWindowRun(UIWindowRef this)
{
    XEvent e;
    bool done = false;
    while (done == false) {
        XNextEvent(this->display, &e);
        if (e.type == KeyPress)
            break;
    }

}

void 
/**
 * Show
 */
UIWindowShow(UIWindowRef this)
{
    Display *display = this->display;
    int screen = this->screen;

    this->top = XCreateSimpleWindow(display, RootWindow(display, screen), 
                            10, 10, 600, 400, 1,
                            BlackPixel(display, screen), WhitePixel(display, screen));
    XSelectInput(display, this->top, ExposureMask | KeyPressMask);
    XMapWindow(display, this->top);
}




