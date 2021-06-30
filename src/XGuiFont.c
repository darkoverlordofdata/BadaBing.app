#include "XGuiFont.h"

    // char* name;
    // int size;
    // XftFont *obj;
    // Display *disp;      // application display
    // int screen;


XGuiFont* XGuiFont_New(char* name, int size) {
    XGuiFont* this = (XGuiFont*)malloc(sizeof(XGuiFont));
    this->name = strdup(name);
    this->size = size;


//    app->font_small = XftFontOpenName(app->disp, app->screen, app->fontname_small);
    return this;

}

void XGuiFont_Dispose(XGuiFont* this) {
    if (this->name != NULL) free(this->name);
}