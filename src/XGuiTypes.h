#pragma once

typedef struct XGuiWindow XGuiWindow;
typedef struct XGuiApplication XGuiApplication;
typedef struct XGuiFont XGuiFont;
typedef struct XGuiLabel XGuiLabel;

typedef struct XGuiApplication
{
    Display *display;      // application display
    int screen;
    XGuiWindow* window;


} XGuiApplication;

typedef struct XGuiFont 
{
    char* name;
    int size;
    XftFont *obj;
    Display *disp;      // application display
    int screen;
} XGuiFont;

typedef struct XGuiLabel 
{
    int x;
    int y;
    char* text;
    XGuiFont* font;

} XGuiLabel;

typedef struct XGuiWindow
{

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
