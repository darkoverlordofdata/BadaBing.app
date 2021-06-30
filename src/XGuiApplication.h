#pragma once
#include "main.h"
#include "helpers.h"
#include "XGuiTypes.h"
#include "XGuiWindow.h"

XGuiApplication* XGuiApplication_New();//int verbosity, char* calendar, char* theme_name, char* font_name, bool scrot, char* pin, int tz);
void XGuiApplication_Init(XGuiApplication* this);//, int argc, char **argv);
void XGuiApplication_Run(XGuiApplication* this);
void XGuiApplication_Dispose(XGuiApplication* this);
