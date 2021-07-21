/* ******************************************************************************
 * Copyright 2020 bruce davidson <darkoverlordofdata@gmail.com>.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/
#include <CoreFX/CoreFX.h>
#include <UIPack/UIPack.h>
#include "main.h"

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
// #define NK_IMPLEMENTATION
// #define NK_XLIB_IMPLEMENTATION

#include "UIPack/nuklear.h"
#include "UIPack/nuklear_xlib.h"
// #include "UIPack/style.c"


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


int main(int argc, char **argv)
{


	var pool = CFRefPoolNew(); 
    var app = UIApplicationCreate(argc, argv, longopts);
    var parm = UIApplicationGetParams(app);

    if (CFEqual($("YES"), CFMapGet(parm, $("version")))) {
        printf("catlock v0.1.0, © 2020 Dark Overlord of Data\n");
        printf("inspired by metalock © 2012 Timothy Beyer\n");
    	CFUnRef(pool);
        return 0;
    }

    if (CFEqual($("YES"), CFMapGetC(parm, "help"))) {
        printf("Usage: catlock [option]\n");
        printf("\n");
        printf("-h / --help               help (self)\n");
        printf("-V / --version            version information\n");
        printf("-s / --scrot              take screen pics\n");
        printf("-c / --calendar           calendar app, such as \"orage\"\n");
        printf("-v n / --verbosity n      verbosity level (default: 0)\n");
        printf("-f name / --font name     X11 font name\n");
        printf("-t name / --theme name    theme name (default: badabing)\n");
        printf("\n");
        printf("https://github.com/darkoverlordofdata/kitty-cat-lock\n" );
    	CFUnRef(pool);
        return 0;
    }

    CFLog("CWD: %@\n", UIApplicationGetCwd(app));

    UIWindow win = UIWindowCreate(app, "BadaBing", (UIRect){ 100, 100, 400, 300});

    UIWindowShow(win);
    
    UILabel label1 = UILabelCreate("Label aligned left", NK_TEXT_LEFT);

    UIWindowAdd(win, label1);

    UIWindowRun(win, NK_WINDOW_NO_SCROLLBAR);
    
	CFUnRef(pool);
    return 0;
    
}

