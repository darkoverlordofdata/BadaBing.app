#include "XGuiWindow.h"

/**
 *	XGuiWindow
 */
typedef struct XGuiWindow
{
	CFWObject obj;
    Display *display;      // application display
    int screen;
    XGuiApplication* app;
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
} XGuiWindow;

/**
 * Run
 */
void XGuiWindow_Run(XGuiWindow* this)
{
    XEvent e;
    bool done = false;
    while (done == false) {
        XNextEvent(this->display, &e);
        if (e.type == KeyPress)
            break;
    }

}

/**
 * Show
 */
void XGuiWindow_Show(XGuiWindow* this)
{
    Display *display = this->display;
    int screen = this->screen;

    this->top = XCreateSimpleWindow(display, RootWindow(display, screen), 
                            10, 10, 100, 100, 1,
                            BlackPixel(display, screen), WhitePixel(display, screen));
    XSelectInput(display, this->top, ExposureMask | KeyPressMask);
    XMapWindow(display, this->top);
}



static bool ctor(void *ptr, va_list args)
{
    XGuiWindow* this = ptr;

    this->app = va_arg(args, XGuiApplication*);

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

static void dtor(void *ptr)
{
    XGuiWindow* this = ptr;
    XDestroyWindow(this->display, this->top);
    XCloseDisplay(this->display);
    printf("XGuiWindow::dtor\n");
}

static bool equal(void *ptr1, void *ptr2)
{
    return false;
}

static uint32_t hash(void *ptr)
{
	return (uint32_t)ptr;
}

static void* copy(void *ptr)
{
	return NULL;
}


static CFWClass class = {
	.name = "XGuiWindow",
	.size = sizeof(XGuiWindow),
	.ctor = ctor,
	.dtor = dtor,
	.equal = equal,
	.hash = hash,
	.copy = copy
};
CFWClass *xgui_window = &class;
