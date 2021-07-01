#include "XGuiLabel.h"

typedef struct XGuiLabel 
{
	CFWObject obj;
    int x;
    int y;
    char* text;
    XGuiFont* font;
} XGuiLabel;

void XGuiLabel_SetText(XGuiLabel* this, char* text) {

}

void XGuiLabel_SetPos(XGuiLabel* this, int x, int y) {

}

void XGuiLabel_Draw(XGuiLabel* this) {

}


static bool ctor(void *ptr, va_list args)
{
    XGuiLabel* this = ptr;
    const int x = va_arg(args, int);
    const int y = va_arg(args, int);
	const char* text = va_arg(args, char*);
    XGuiFont* font = va_arg(args, XGuiFont*);

    this->x = x;
    this->y = y;
    this->text = strdup(text);
    this->font = font;
	return true;
}

static void dtor(void *ptr)
{
    XGuiLabel* this = ptr;
    if (this->text != NULL) free(this->text);
    printf("XGuiLabel::dtor\n");
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
	.name = "XGuiLabel",
	.size = sizeof(XGuiLabel),
	.ctor = ctor,
	.dtor = dtor,
	.equal = equal,
	.hash = hash,
	.copy = copy
};
CFWClass *xgui_label = &class;
