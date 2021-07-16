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
#include <CoreFX/CoreFX.h>

void Each(CFType key, CFType obj) 
{
	CFLog("\t%@ = %@\n", key, obj);
}

int
main()
{
	CFRefPool pool;
	CFArray array;
	CFString str, str2;
	CFMap map;

	pool = CFRefPoolNew();

	array = CFArrayCreateWith(
	    $("Hallo"),
	    $(" Welt"),
	    $("!"), 
		NULL);

	CFForEach(array, ^(int index, CFType obj) {
		CFLog("\t%i: %@\n", index, obj);

	});

	str = CFStringNew(NULL);

	for (var i = 0; i < CFArraySize(array); i++)
		CFStringAppend(str, CFArrayGet(array, i));

	CFUnRef(pool);

	CFLog("%s\n", CFStringC(str));

	pool = CFRefPoolNew();
	str2 = $("ll");
	CFLog("%i\n", CFStringFind(str, str2, CFRangeAll));

	CFUnRef(pool);
	CFUnRef(str);

	pool = CFRefPoolNew();

	map = CFMapCreateWith(
	    $("Hallo"),	$("Welt!"),
	    $("Test"),	$("success!"),
	    $("int"), 	$(1234),
		NULL);

	CFLog("{\n");
	CFForEach(map, Each);
	CFLog("}\n");

	CFMapSet(map, $("Hallo"), $("Test"));

	CFLog("{\n");
	CFForEach(map, ^(CFType key, CFType obj) {
		CFLog("\t%@ = %@\n", key, obj);
	});
	CFLog("}\n");

	CFMapSet(map, $("Hallo"), NULL);

	CFLog("{\n");
	CFForEach(map, ^(CFType key, CFType obj) {
		CFLog("\t%@ = %@\n", key, obj);
	});
	CFLog("}\n");

	let bb = $(true);

	CFLog("bb = %$\n", bb);

	let ff = $(3.1415);

	CFLog("ff = %$\n", ff);

	CFInt ii = $(1000L);

	CFLog("ii = %@\n", ii);
	
	CFLog("hash = %i\n", CFHash(ii));

	CFLog("%s\n", CFGetClass(ii)->name);

	CFLog("StdIn = %@\n", CFStdIn);


	CFUnRef(pool);
	return 0;
}
