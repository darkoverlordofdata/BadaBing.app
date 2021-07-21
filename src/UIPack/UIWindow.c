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
#include <sys/time.h>
#include <unistd.h>
#include <time.h>
#include "UIWindow.h"

#define DTIME           20

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_IMPLEMENTATION
#define NK_XLIB_IMPLEMENTATION

#include "nuklear.h"
#include "nuklear_xlib.h"
#include "style.c"

#define THEME_DEFAULT THEME_DARK

#include "UILabel.h"

static long
timestamp(void)
{
    struct timeval tv;
    if (gettimeofday(&tv, NULL) < 0) return 0;
    return (long)((long)tv.tv_sec * 1000 + (long)tv.tv_usec/1000);
}

static void
sleep_for(long t)
{
    struct timespec req;
    const time_t sec = (int)(t/1000);
    const long ms = t - (sec * 1000);
    req.tv_sec = sec;
    req.tv_nsec = ms * 1000000L;
    while(-1 == nanosleep(&req, &req));
}

/**
 *	UIWindow Instance
 */
struct __UIWindow
{
	struct __CFObject obj;
    UIWindow parent;
    CFArray children;
    NKContext ctx;
    UIWidgetVtbl vtbl;

    UIApplication app;
    CFString title;
    int x;
    int y;
    uint width;
    uint height; 

    Display *display;
    Window root;
    Visual *visual;
    Colormap cmap;
    XWindowAttributes attr;
    XSetWindowAttributes swa;
    Window window;
    int screen;
    XFont *font;
    Atom wm_delete_window;
    Boolean wm_delete_window_triggered;
    int depth;

};

static CFTypeID _kUIWindowTypeID = 0;
static CFClass UIWindowClass;

static struct __UIWidgetVtbl vtbl = {
    .Draw = UIWindowDraw
};

Boolean
/**
 * Constructor
 */
UIWindowConstructor(CFType self, va_list args)
{
    UIWindow this = self;

    this->vtbl = &vtbl;
    this->app = va_arg(args, UIApplication);
    char* title = va_arg(args, char*);
    UIRect bounds = va_arg(args, UIRect);
    
    this->wm_delete_window_triggered = false;
    this->title = CFStringCreate(title);
    this->x = bounds.x;
    this->y = bounds.y;
    this->width = bounds.width;
    this->height = bounds.height;
    this->children = CFArrayCreate();

    this->display = XOpenDisplay(NULL);

	return true;
}

void 
/**
 * Finalize
 */
UIWindowFinalize(CFType self)
{
    CFLog("UIWindow::dtor\n");
    static bool done = false;
    if (done) return;
    done = true;

    UIWindow this = self;

    nk_xfont_del(this->display, this->font);
    nk_xlib_shutdown();
    XUnmapWindow(this->display, this->window);
    XFreeColormap(this->display, this->cmap);
    XDestroyWindow(this->display, this->window);
    if (this->wm_delete_window_triggered) {
        CFLog("WTF!\n");
        XCloseDisplay(this->display);
    }
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


NKContext
UIWindownnNKCtx(UIWindow this) { return this->ctx; }

CFString
UIWindowTitle(UIWindow this) { return this->title; }

int
UIWindowX(UIWindow this) { return this->x; }

int
UIWindowY(UIWindow this) { return this->y; }

int
UIWindowWidth(UIWindow this) { return this->width; }

int
UIWindowHeight(UIWindow this) { return this->height; }

void 
/**
 * Show
 */
UIWindowShow(UIWindow this)
{
    this->root = DefaultRootWindow(this->display);
    this->screen = XDefaultScreen(this->display);
    this->visual = XDefaultVisual(this->display, this->screen);
    this->cmap = XCreateColormap(this->display,this->root,this->visual,AllocNone);

    this->swa.colormap = this->cmap;
    this->swa.event_mask =
        ExposureMask | KeyPressMask | KeyReleaseMask |
        ButtonPress | ButtonReleaseMask| ButtonMotionMask |
        Button1MotionMask | Button3MotionMask | Button4MotionMask | Button5MotionMask|
        PointerMotionMask | KeymapStateMask;
    this->window = XCreateWindow(this->display, this->root, 
        this->x, this->y, this->width, this->height, 0,
        XDefaultDepth(this->display, this->screen), InputOutput,
        this->visual, CWEventMask | CWColormap, &this->swa);

    XStoreName(this->display, this->window, "X11");
    XMapWindow(this->display, this->window);
    this->wm_delete_window = XInternAtom(this->display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(this->display, this->window, &this->wm_delete_window, 1);
    XGetWindowAttributes(this->display, this->window, &this->attr);
    this->width = (unsigned int)this->attr.width;
    this->height = (unsigned int)this->attr.height;


    this->font = nk_xfont_create(this->display, "Roboto");
    this->ctx = nk_xlib_init(this->font, this->display, 
            this->screen, this->window,
            this->visual, this->cmap,
            this->width, this->height);


    set_style(this->ctx, THEME_DEFAULT);

}


void 
/**
 * Run
 */
UIWindowRun(UIWindow this, long panelFlag)
{
    long dt;
    long started;
    Boolean running = true;

    while(running)
    {
        /* Input */
        XEvent evt;
        started = timestamp();


        //================== e v e n t s =============================
        nk_input_begin(this->ctx);
        while (XPending(this->display)) {
            XNextEvent(this->display, &evt);                

            if ((evt.type == ClientMessage) && 
                (evt.xclient.data.l[0] == this->wm_delete_window)) {
                    this->wm_delete_window_triggered = true;
                    return;
                }
            if (XFilterEvent(&evt, this->window)) continue;
            nk_xlib_handle_event(this->display, this->screen, this->window, &evt);
        }
        nk_input_end(this->ctx);

        if (nk_begin(this->ctx, CFStringC(this->title), 
            nk_rect(0, 0, this->width, this->height),
            panelFlag ))
        {
            for (var i=0; i<CFArraySize(this->children); i++) {
                UIWidget widget = CFArrayGet(this->children, i);
                widget->vtbl->Draw(widget);
            }

            nk_end(this->ctx);
        }

        this->vtbl->Draw(this);

        /* Timing */
        dt = timestamp() - started;
        if (dt < DTIME)
            sleep_for(DTIME - dt);
    }
}

void 
/**
 * Show
 */
UIWindowDraw(void* self)
{
    UIWindow this = self;
    if (nk_window_is_hidden(this->ctx, CFStringC(this->title))) return;

    XClearWindow(this->display, this->window);
    nk_xlib_render(this->window, nk_rgb(30,30,30));
    XFlush(this->display);
}

void
UIWindowAdd(UIWindow this, CFType control)
{
    CFArrayPush(this->children, control);
    UIWidgetParent(control, this, this->ctx);
}

void
UIWidgetParent(UIWidget this, UIWindow parent, NKContext ctx)
{
    this->parent = parent;
    this->ctx = ctx;
}
