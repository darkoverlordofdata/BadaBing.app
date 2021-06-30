#pragma once
#include "main.h"
#include "helpers.h"
#include "XGuiTypes.h"
#include "XGuiApplication.h"


XGuiWindow* XGuiWindow_New(XGuiApplication* app);

void XGuiWindow_Dispose(XGuiWindow* this);
void XGuiWindow_Show(XGuiWindow* this);
