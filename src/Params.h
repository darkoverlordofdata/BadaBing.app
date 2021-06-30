#pragma once
#include "main.h"
#include "helpers.h"

typedef struct Params
{
    int tz;
    int verbosity;
    char* calendar;
    char* theme_name;
    char* font_name;
    char* pin;
    bool scrot;
    bool help;
    bool version;

} Params;


Params* Params_New();
void Params_Init(Params* this, int argc, char **argv);
void Params_Print(Params* this);
void Params_Dispose(Params* this);
