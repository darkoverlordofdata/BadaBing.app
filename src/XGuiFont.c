#include "XGuiFont.h"

typedef struct XGuiFont 
{
	CFWObject obj;
    char* name;
    int size;
    XftFont *font;
    Display *disp;      // application display
    int screen;
} XGuiFont;


static bool ctor(void *ptr, va_list args)
{
    XGuiFont* this = ptr;
	const char* name = va_arg(args, char*);
	const int size = va_arg(args, int);

    this->name = strdup(name);
    this->size = size;
	return true;
}

static void dtor(void *ptr)
{
    XGuiFont* this = ptr;
    if (this->name != NULL) free(this->name);
    printf("XGuiFont::dtor\n");
}

static bool equal(void *ptr1, void *ptr2)
{
    return false;
}

static uint32_t hash(void *ptr)
{
	return (uint32_t)ptr;
}

static void* copy(void *ptr)
{
	return NULL;
}


static CFWClass class = {
	.name = "XGuiFont",
	.size = sizeof(XGuiFont),
	.ctor = ctor,
	.dtor = dtor,
	.equal = equal,
	.hash = hash,
	.copy = copy
};
CFWClass *xgui_font = &class;
