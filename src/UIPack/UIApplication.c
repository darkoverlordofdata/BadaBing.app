/* ******************************************************************************
* Copyright (c) 2021 Dark Overlord of Data
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice,
*    this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
******************************************************************/
#include <unistd.h>
#include <getopt.h>
#include "UIApplication.h"


/**
 *	UIApplication
 */
struct __UIApplication
{
	struct __CFObject obj;
    UIWindow window;
    CFMap params;
    CFString cwd;
};

static CFTypeID _kUIApplicationTypeID = 0;
static CFClass UIApplicationClass;

void UIApplicationClassInitialize();
void UIFontClassInitialize();
void UILabelClassInitialize();
void UIWindowClassInitialize();

void UIInitialize (void) __attribute__ ((constructor(102) ));

void
UIInitialize()
{
	UIApplicationClassInitialize();
	UIFontClassInitialize();
	UILabelClassInitialize();
	UIWindowClassInitialize();
}
//CFRegisterGet(UIWindowGetTypeID())

static Boolean
UIApplicationConstructor(CFType self, va_list args)
{
    UIApplication this = self;
	int argc = va_arg(args, int);
    char **argv = va_arg(args, char **);
	struct option *longopts = va_arg(args, struct option *);

	char sVal[2];
	sVal[1] = '\0';

	this->window = CFCreateObject(CFRegisterGet(UIWindowGetTypeID()), this);

	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	this->cwd = CFCreateObject(CFStringClass, cwd);

	CFString flags = CFStringCreate("");
	for (int i=0; longopts[i].name != NULL; i++) {
		sVal[0] = longopts[i].val;
		CFStringAppendC(flags, sVal);
		if (longopts[i].has_arg == required_argument) {
			CFStringAppendC(flags, ":");
		}
	}

	this->params = CFMapCreate();
	int longindex = -1;
	int opt = 0;

	while ((opt = getopt_long(argc, argv, CFStringC(flags), longopts, &longindex))!= -1) {

		CFString str = CFStringCreate("");
		sVal[0] = opt;
		CFStringAppendC(str, sVal);
		if (optarg != NULL) {
			CFMapSet(this->params, str, $(optarg));
		}
		for (int i=0; longopts[i].name != NULL; i++) {
			if (longopts[i].val == opt) {
				CFString name = CFStringCreate(longopts[i].name);
				if (longopts[i].has_arg == required_argument) {
					CFMapSet(this->params, name, $(optarg));
				} else {
					CFMapSet(this->params, str, $("YES"));
					CFMapSet(this->params, name, $("YES"));
				}
			}
		}
	}

	return true;
}

static void 
UIApplicationFinalize(CFType self)
{
    CFLog("UIApplication::dtor\n");
}

CFTypeID
UIApplicationGetTypeID (void)
{
  return _kUIApplicationTypeID;
}

void UIApplicationClassInitialize()
{
	static struct __CFClass __UIApplicationClass = {
		.name = "UIApplication",
		.size = sizeof(struct __UIApplication),
		.ctor = UIApplicationConstructor,
		.dtor = UIApplicationFinalize
	};
	UIApplicationClass = &__UIApplicationClass;
	_kUIApplicationTypeID = CFRegisterClass(UIApplicationClass);
}

UIApplication 
UIApplicationCreate(int argc, char** argv, struct option* longopts)
{
	return CFCreateObject(UIApplicationClass, argc, argv, longopts);
}

UIApplication 
UIApplicationNew(int argc, char** argv, struct option* longopts)
{
	return CFNewObject(UIApplicationClass, argc, argv, longopts);
}
/**
 *	UIApplication GetCwd
 */
CFString 
UIApplicationGetCwd(UIApplication this) 
{
	return this->cwd;
}

/**
 *	UIApplication GetWindow
 */
// UIWindowRef 
CFType
UIApplicationGetWindow(UIApplication this) 
{
	return this->window;
}

/**
 *	UIApplication GetParams
 */
CFMap
UIApplicationGetParams(UIApplication this) 
{
	return this->params;
}

