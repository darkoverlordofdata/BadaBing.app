#include "XGuiApplication.h"


XGuiApplication* XGuiApplication_New()//int verbosity, char* calendar, char* theme_name, char* font_name, bool scrot, char* pin, int tz) 
{
    XGuiApplication* this = (XGuiApplication*)malloc(sizeof(XGuiApplication));
    return this;
}

void XGuiApplication_Init(XGuiApplication* this) 
{
    this->display = XOpenDisplay(NULL);

    if (this->display == NULL) {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }

    this->screen = DefaultScreen(this->display);

    this->window = XGuiWindow_New(this);

}

void XGuiApplication_Run(XGuiApplication* this)
{
    XEvent e;
    // XGuiApplication_Print(this);
    bool done = false;
    while (done == false) {
        XNextEvent(this->display, &e);
        if (e.type == KeyPress)
            break;
    }

}

void XGuiApplication_Dispose(XGuiApplication* this)
{
    XGuiWindow_Dispose(this->window);
    XCloseDisplay(this->display);
}

