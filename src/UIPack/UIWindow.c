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
    UIApplication app;
    int x;
    int y;
    uint width;
    uint height; 
    CFString title;
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

static CFTypeID _kUIWindowTypeID = 0;
static CFClass UIWindowClass;

static Atom WM_DELETE_WINDOW;

Boolean
/**
 * Constructor
 */
UIWindowConstructor(CFType self, va_list args)
{
    UIWindow this = self;

    this->app = va_arg(args, UIApplication);
    char* title = va_arg(args, char*);
    UIRect bounds = va_arg(args, UIRect);
    
    this->title = CFStringCreate(title);
    this->x = bounds.x;
    this->y = bounds.y;
    this->width = bounds.width;
    this->height = bounds.height;

    this->display = XOpenDisplay(NULL);
    if (this->display == NULL) {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }

    this->screen = DefaultScreen(this->display);

    this->depth = DefaultDepth(this->display, this->screen);
    this->root = RootWindow(this->display, this->screen);

    // full screen:
    // this->width = DisplayWidth(this->display, this->screen);
    // this->height = DisplayHeight(this->display, this->screen);

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
    static bool done = false;
    if (done) return;
    done = true;

    CFLog("UIWindow::dtor\n");
    UIWindow this = self;
    XCloseDisplay(this->display);
}


CFTypeID
UIWindowGetTypeID (void)
{
  return _kUIWindowTypeID;
}

void UIWindowClassInitialize()
{
    static struct __CFClass __UIWindowClass = 
    {
        .name = "UIWindow",
        .size = sizeof(struct __UIWindow),
        .ctor = UIWindowConstructor,
        .dtor = UIWindowFinalize
    };

    UIWindowClass = &__UIWindowClass;
	_kUIWindowTypeID = CFRegisterClass(UIWindowClass);
}

UIWindow
UIWindowCreate(UIApplication app, char* title, UIRect bounds)
{
	return CFCreateObject(UIWindowClass, app, title, bounds);
}

UIWindow
UIWindowNew(UIApplication app, char* title, UIRect bounds)
{
	return CFNewObject(UIWindowClass, app, title, bounds);
}

void 
/**
 * Run
 */
UIWindowRun(UIWindow this)
{
    XEvent e;
    bool done = false;
    int i;
    char text[10];
    KeySym key;

    while (done == false) {
        XNextEvent(this->display, &e);
        if (e.type == KeyPress) {
            i = XLookupString((XKeyEvent*)&e, text, 10, &key, 0);
            if (i==1 && text[0]=='q') done = true;
        }  else if (e.type == Expose) {
            UIWindowDraw(this);
        } else if (UIWindowCheckEvent(this, &e, "WM_DELETE_WINDOW")) {
            done = true;
        }
    }

}

void 
/**
 * Show
 */
UIWindowDraw(UIWindow this)
{

}
void 
/**
 * Show
 */
UIWindowShow(UIWindow this)
{
    Display *display = this->display;
    int screen = this->screen;

    this->top = XCreateSimpleWindow(display, RootWindow(display, screen), 
                            0, 0, 1, 1, 1,
                            // 100, 100, 300, 300, 1,
                            BlackPixel(display, screen), WhitePixel(display, screen));
    XSelectInput(display, this->top, ExposureMask | KeyPressMask);
    XStoreName(display, this->top, CFStringC(this->title));
    XMapWindow(display, this->top);

    XMoveResizeWindow(this->display, this->top, this->x, this->y, this->width, this->height);
    WM_DELETE_WINDOW = XInternAtom(this->display, "WM_DELETE_WINDOW", false); 
    XSetWMProtocols(this->display, this->top, &WM_DELETE_WINDOW, 1);  
    
}

Boolean
UIWindowCheckEvent(UIWindow this, XEvent* event, char* name)
{
    if (strcmp("WM_DELETE_WINDOW", name) == 0) {
        if ((event->type == ClientMessage) && 
            (event->xclient.data.l[0] == WM_DELETE_WINDOW))
                return true;
    }
    return false;
}


