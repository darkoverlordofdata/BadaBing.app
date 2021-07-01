#pragma once
#include "main.h"
#include "helpers.h"
#include "corefw.h"

typedef struct XGuiParams XGuiParams;
extern CFWClass *xgui_params;


// Params* Params_New();
void XGuiParams_Parse(XGuiParams* this, int argc, char **argv);
void XGuiParams_Print(XGuiParams* this);

typedef struct XGuiParams
{
	CFWObject obj;
    int tz;
    int verbosity;
    bool scrot;
    bool help;
    bool version;
    char* calendar;
    char* font_name;
    char* theme_name;
    char* pin;
} XGuiParams;
