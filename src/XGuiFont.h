#pragma once
#include "main.h"
#include "XGuiTypes.h"

XGuiFont* XGuiFont_New(char* name, int size);

void XGuiFont_Dispose(XGuiFont* this);