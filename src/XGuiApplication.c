#include "XGuiApplication.h"

/**
 *	XGuiApplication
 */
typedef struct XGuiApplication
{
	CFWObject obj;
    XGuiWindow* window;
    XGuiParams* params;
    CFWString* cwd;
} XGuiApplication;

/**
 *	XGuiApplication GetCwd
 */
CFWString* XGuiApplication_GetCwd(XGuiApplication* this) {
	return this->cwd;
}

/**
 *	XGuiApplication GetWindow
 */
XGuiWindow* XGuiApplication_GetWindow(XGuiApplication* this) {
	return this->window;
}

/**
 *	XGuiApplication GetParams
 */
XGuiParams* XGuiApplication_GetParams(XGuiApplication* this) {
	return this->params;
}

static bool ctor(void *ptr, va_list args)
{
    XGuiApplication* this = ptr;
	int argc = va_arg(args, int);
    char **argv = va_arg(args, char **);

	this->params = cfw_create(xgui_params, argc, argv);
	this->window = cfw_create(xgui_window, this);

	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	this->cwd = cfw_create(cfw_string, cwd);

	return true;
}

static void dtor(void *ptr)
{
    printf("XGuiApplication::dtor\n");
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
	.name = "XGuiApplication",
	.size = sizeof(XGuiApplication),
	.ctor = ctor,
	.dtor = dtor,
	.equal = equal,
	.hash = hash,
	.copy = copy
};
CFWClass *xgui_application = &class;
