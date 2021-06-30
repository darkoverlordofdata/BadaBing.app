#pragma once
#include "main.h"
#include "XGuiTypes.h"
#include "XGuiFont.h"


XGuiLabel* XGuiLabel_New(int x, int y, char* text, XGuiFont* font);

void XGuiLabel_SetText(XGuiLabel* this, char* text);
void XGuiLabel_SetPos(XGuiLabel* this, int x, int y);
void XGuiLabel_Draw(XGuiLabel* this);
void XGuiLabel_Dispose(XGuiLabel* this);