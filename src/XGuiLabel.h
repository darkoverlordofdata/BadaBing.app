#pragma once
#include "main.h"
#include "XGuiFont.h"
#include "corefw.h"

typedef struct XGuiLabel XGuiLabel;
extern CFWClass *xgui_label;

void XGuiLabel_SetText(XGuiLabel* this, char* text);
void XGuiLabel_SetPos(XGuiLabel* this, int x, int y);
void XGuiLabel_Draw(XGuiLabel* this);

