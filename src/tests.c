/*
 * Copyright (c) 2012, Jonathan Schleifer <js@webkeks.org>
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
 */

#include <stdio.h>

#include "CFObject.h"
#include "CFRefpool.h"
#include "CFString.h"
#include "CFInt.h"
#include "CFArray.h"
#include "CFMap.h"

static void
print_map(CFMapRef map)
{
	CFMapIter_t iter;

	CFMapIter(map, &iter);

	fputs("{\n", stdout);

	while (iter.key != NULL) {
		printf("\t%s = ", CFStringC(iter.key));

		if (CFIs(iter.obj, CFStringClass))
			printf("%s\n", CFStringC(iter.obj));
		else if (CFIs(iter.obj, CFIntClass))
			printf("%jd\n", CFIntValue(iter.obj));

		CFMapIterNext(&iter);
	}

	fputs("}\n", stdout);
}

int
main()
{
	CFRefpoolRef pool;
	CFArrayRef array;
	CFStringRef str, str2;
	CFMapRef map;
	size_t i;

	pool = CFNew(CFRefpoolClass);

	array = CFCreate(CFArrayClass,
	    CFStringCreate("Hallo"),
	    CFStringCreate(" Welt"),
	    CFStringCreate("!"), NULL);

	str = CFStringNew(NULL);

	for (i = 0; i < CFArraySize(array); i++)
		CFStringAppend(str, CFArrayGet(array, i));

	CFUnref(pool);

	puts(CFStringC(str));

	pool = CFNew(CFRefpoolClass);
	str2 = CFStringCreate("ll");
	printf("%zd\n", CFStringFind(str, str2, CFRangeAll));

	CFUnref(pool);
	CFUnref(str);

	pool = CFNew(CFRefpoolClass);

	map = CFCreate(CFMapClass,
	    CFStringCreate("Hallo"),
	    CFStringCreate("Welt!"),
	    CFStringCreate("Test"),
	    CFStringCreate("success!"),
	    CFStringCreate("int"),
	    CFCreate(CFIntClass, INTMAX_C(1234)), NULL);

	print_map(map);

	CFMapSet(map,
	    CFStringCreate("Hallo"),
	    CFStringCreate("Test"));

	print_map(map);

	CFMapSet(map, CFStringCreate("Hallo"), NULL);
	print_map(map);

	CFUnref(pool);

	return 0;
}
