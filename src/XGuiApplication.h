#pragma once
#include "main.h"
#include "helpers.h"
#include "XGuiParams.h"
#include "XGuiWindow.h"
#include "corefw.h"

typedef struct XGuiWindow XGuiWindow;
typedef struct XGuiApplication XGuiApplication;
extern CFWClass *xgui_application;

CFWString* XGuiApplication_GetCwd(XGuiApplication* this);
XGuiWindow* XGuiApplication_GetWindow(XGuiApplication* this);
XGuiParams* XGuiApplication_GetParams(XGuiApplication* this);

