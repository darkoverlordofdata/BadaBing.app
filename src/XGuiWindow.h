#pragma once
#include "main.h"
#include "helpers.h"
#include "XGuiApplication.h"
#include "corefw.h"

typedef struct XGuiWindow XGuiWindow;
extern CFWClass *xgui_window;

void XGuiWindow_Show(XGuiWindow* this);
void XGuiWindow_Run(XGuiWindow* this);

typedef struct XGuiApplication XGuiApplication;
