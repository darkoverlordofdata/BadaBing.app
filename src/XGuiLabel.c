#include "XGuiLabel.h"

XGuiLabel* XGuiLabel_New(int x, int y, char* text, XGuiFont* font) {

    XGuiLabel* this  = (XGuiLabel*)malloc(sizeof(XGuiLabel));
    this->x = x;
    this->y = y;
    this->text = strdup(text);
    this->font = font;
    return this;
}

void XGuiLabel_SetText(XGuiLabel* this, char* text) {

}

void XGuiLabel_SetPos(XGuiLabel* this, int x, int y) {

}

void XGuiLabel_Draw(XGuiLabel* this) {

}

void XGuiLabel_Dispose(XGuiLabel* this) {
    if (this->text != NULL) free(this->text);
    XGuiFont_Dispose(this->font);
}