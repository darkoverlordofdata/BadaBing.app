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
#include "UIParams.h"

static struct __CFClass class = {
	.name = "UIParams",
	.size = sizeof(struct __UIParams),
	.ctor = UIParamsConstructor,
	.dtor = UIParamsFinalize
};
CFClassRef UIParamsClass = &class;

/**
 * Constructor
 *
 * make a new Params object using command line params
 */
Boolean
UIParamsConstructor(CFTypeRef self, va_list args)
{
    UIParamsRef this = self;
	int argc = va_arg(args, int);
    char **argv = va_arg(args, char **);
    UIParamsParse(this, argc, argv);

	return true;
}

/**
 * Destructor
 *
 * dispose of strings
 */
void 
UIParamsFinalize(CFTypeRef self)
{
    UIParamsRef this = self;
    free(this->calendar);
    free(this->font_name);
    free(this->theme_name);
    free(this->pin);
    CFLog("UIParams::dtor\n");
}


void 
UIParamsParse(UIParamsRef this, int argc, char **argv) 
{
    static struct option longopts[] = {
        {"help", no_argument, NULL, 'h'},
        {"version", no_argument, NULL, 'V'},
        {"scrot", no_argument, NULL, 's'},
        {"calendar", required_argument, NULL, 'c'},
        {"pin", required_argument, NULL, 'p'},
        {"verbosity", required_argument, NULL, 'v'},
        {"font", required_argument, NULL, 'f'},
        {"theme", required_argument, NULL, 't'},
        {"tz", required_argument, NULL, 'z'}
    };

    int longindex = -1;
    int opt = 0;

    while ((opt = getopt_long(argc, argv, "oshVt:v:f:a:c:p:", longopts, &longindex))!= -1) {
        switch (opt) {
        case 's':
            this->scrot = true;
            break;
        case 'h':
            this->help = true;
            break;
        case 'V':
            this->version = true;
            break;
        case 'c':
            if (this->calendar != NULL) {
                free(this->calendar);
            }
            this->calendar = strdup(optarg);
            break;
        case 'p':
            if (this->pin != NULL) {
                free(this->pin);
            }
            this->pin = strdup(optarg);
            break;
        case 'f':
            if (this->font_name != NULL) {
                free(this->font_name);
            }
            this->font_name = strdup(optarg);
            break;
        case 't':
            if (this->theme_name != NULL) {
                free(this->theme_name);
            }
            this->theme_name = strdup(optarg);
            break;
        case 'v':
            this->verbosity = atoi(optarg);
            break;
        case 'z':
            this->tz = atoi(optarg);
            break;
        default:
            break;
        }
    }

    if (this->verbosity > 0) {
        printf("font: \"%s\"\n", this->font_name);
        printf("verbosity: %d\n", this->verbosity);
    }

    if (this->version) {
        puts("catlock v0.1.0, © 2020 Dark Overlord of Data");
        puts("inspired by metalock © 2012 Timothy Beyer");
        exit(0);
    }

    if (this->help) {
        puts("Usage: catlock [option]\n");

        puts("-h / --help               help (this)");
        puts("-V / --version            version information");
        puts("-s / --scrot              take screen pics");
        puts("-c / --calendar           calendar app, such as \"orage\"");
        puts("-v n / --verbosity n      verbosity level (default: 0)");
        puts("-f name / --font name     X11 font name");
        puts("-t name / --theme name    theme name (default: badabing)");

        puts("\nhttps://github.com/darkoverlordofdata/kitty-cat-lock" );
        exit(0);
    }


}


void 
UIParamsPrint(UIParamsRef this)
{
    CFLog("tz adjustment %d\n", this->tz);
    CFLog("verbosity %d\n", this->verbosity);
    CFLog("calendar %s\n", this->calendar ? this->calendar : "(null)");
    CFLog("theme_name %s\n", this->theme_name ? this->theme_name : "(null)");
    CFLog("font_name %s\n", this->font_name ? this->font_name : "(null)");
    CFLog("pin %s\n", this->pin ? this->pin : "(null)");
    CFLog("scrot %x\n", this->scrot);
    CFLog("help %x\n", this->help);
    CFLog("version %x\n", this->version);
}

