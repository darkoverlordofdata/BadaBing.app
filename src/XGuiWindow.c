#include "XGuiWindow.h"

XGuiWindow* XGuiWindow_New(XGuiApplication* app) {

    XGuiWindow* this = (XGuiWindow*)malloc(sizeof(XGuiWindow));
    this->app = app;

    Display *display = this->app->display;
    int screen = this->app->screen;


    this->depth = DefaultDepth(display, screen);
    this->root = RootWindow(display, screen);

    this->width = DisplayWidth(display, screen);
    this->height = DisplayHeight(display, screen);

    this->cm = DefaultColormap(display, screen);

    XColor bg = { 0, 0, 0, 0 }; // black
    XColor fg = { 0, 65535, 65535, 65535 }; // white

    XAllocColor(display, this->cm, &bg);
    XAllocColor(display, this->cm, &fg);

    return this;
}

void XGuiWindow_Dispose(XGuiWindow* this)
{
    XDestroyWindow(this->app->display, this->top);
}

void XGuiWindow_Show(XGuiWindow* this)
{
    Display *display = this->app->display;
    int screen = this->app->screen;

    this->top = XCreateSimpleWindow(display, RootWindow(display, screen), 
                            10, 10, 100, 100, 1,
                            BlackPixel(display, screen), WhitePixel(display, screen));
    XSelectInput(display, this->top, ExposureMask | KeyPressMask);
    XMapWindow(display, this->top);
}
