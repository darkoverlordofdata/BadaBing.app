/*
 * Copyright (c) 2012, Jonathan Schleifer <js@webkeks.org>
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
 */

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#include "CFObject.h"
#include "CFString.h"
#include "CFHash.h"

struct __CFString {
	struct __CFObject obj;
	char *data;
	CFSize len;
};


static struct __CFClass class = {
	.name = "CFString",
	.size = sizeof(struct __CFString),
	.ctor = CFStringConstructor,
	.dtor = CFStringFinalize,
	.equal = CFStringEqual,
	.hash = CFStringHash,
	.copy = CFStringCopy,
	.tostr = CFStringToString
};
CFClassRef CFStringClass = &class;


CFStringRef 
CFStringNew(const char* value)
{
	return CFNew(CFStringClass, value);
}

CFStringRef 
CFStringCreate(const char* value)
{
	return CFCreate(CFStringClass, value);
}


CFSize
CFStrnlen(const char *s, CFSize max)
{
	CFSize i = 0;

	for (i = 0; i < max && *s != '\0'; s++)
		i++;

	return i;
}

char*
CFStrdup(const char *s)
{
	char *copy;
	CFSize len;

	len = strlen(s);

	if ((copy = malloc(len + 1)) == NULL)
		return NULL;

	memcpy(copy, s, len + 1);

	return copy;
}

char*
CFStrndup(const char *s, CFSize max)
{
	char *copy;
	CFSize len;

	len = CFStrnlen(s, max);

	if ((copy = malloc(len + 1)) == NULL)
		return NULL;

	memcpy(copy, s, len);
	copy[len] = 0;

	return copy;
}

Boolean 
CFStringConstructor(CFTypeRef self, va_list args)
{
	CFStringRef this = self;
	const char *cstr = va_arg(args, const char*);

	if (cstr != NULL) {
		this->data = NULL;
		if ((this->data = CFStrdup(cstr)) == NULL)
			return false;

		this->len = strlen(cstr);
	} else {
		this->data = NULL;
		this->len = 0;
	}

	return true;
}

void 
CFStringFinalize(CFTypeRef self)
{
	CFStringRef this = self;

	if (this->data != NULL)
		free(this->data);
}

Boolean 
CFStringEqual(CFTypeRef ptr1, CFTypeRef ptr2)
{
	CFObjectRef obj2 = ptr2;
	CFStringRef str1, str2;

	if (obj2->cls != CFStringClass)
		return false;

	str1 = ptr1;
	str2 = ptr2;

	if (str1->len != str2->len)
		return false;

	return !memcmp(str1->data, str2->data, str1->len);
}

CFHashCode 
CFStringHash(CFTypeRef self)
{
	CFStringRef this = self;
	CFSize i;
	uint32_t hash;

	CF_HASH_INIT(hash);

	for (i = 0; i < this->len; i++)
		CF_HASH_ADD(hash, this->data[i]);

	CF_HASH_FINALIZE(hash);

	return hash;
}

CFTypeRef 
CFStringCopy(CFTypeRef self)
{
	CFStringRef this = self;
	CFStringRef new;

	if ((new = CFNew(CFStringClass, (void*)NULL)) == NULL)
		return NULL;

	if ((new->data = malloc(this->len + 1)) == NULL) {
		CFUnref(new);
		return NULL;
	}
	new->len = this->len;

	memcpy(new->data, this->data, this->len + 1);

	return new;
}

char*
CFStringToString(CFTypeRef self)
{
	
	return ((CFStringRef)self)->data;
}

char*
CFStringC(CFStringRef this)
{
	return this->data;
}

CFSize
CFStringLength(CFStringRef string)
{
	return string->len;
}

Boolean
CFStringSet(CFStringRef this, const char *cstr)
{
	char *copy;
	CFSize len;

	if (this != NULL) {
		if ((copy = CFStrdup(cstr)) == NULL)
			return false;

		len = strlen(copy);
	} else {
		copy = NULL;
		len = 0;
	}

	if (this->data != NULL)
		free(this->data);

	this->data = copy;
	this->len = len;

	return true;
}

void
CFStringSetNocopy(CFStringRef this, char *cstr, CFSize len)
{
	if (this->data != NULL)
		free(this->data);

	this->data = cstr;
	this->len = len;
}

Boolean
CFStringAppend(CFStringRef this, CFStringRef append)
{
	char *new;

	if (append == NULL)
		return true;

	if ((new = realloc(this->data, this->len + append->len + 1)) == NULL)
		return false;

	memcpy(new + this->len, append->data, append->len);
	new[this->len + append->len] = 0;

	this->data = new;
	this->len += append->len;

	return true;
}

Boolean
CFStringAppendC(CFStringRef this, const char *append)
{
	char *new;
	CFSize append_len;

	if (append == NULL)
		return true;

	append_len = strlen(append);

	if ((new = realloc(this->data, this->len + append_len + 1)) == NULL)
		return false;

	memcpy(new + this->len, append, append_len);
	new[this->len + append_len] = 0;

	this->data = new;
	this->len += append_len;

	return true;
}

Boolean
CFStringHasPrefix(CFStringRef this, CFStringRef prefix)
{
	if (prefix->len > this->len)
		return false;

	return !memcmp(this->data, prefix->data, prefix->len);
}

Boolean
CFStringHasPrefixC(CFStringRef this, const char *prefix)
{
	CFSize prefix_len = strlen(prefix);

	if (prefix_len > this->len)
		return false;

	return !memcmp(this->data, prefix, prefix_len);
}

Boolean
CFStringHasSuffix(CFStringRef this, CFStringRef suffix)
{
	if (suffix->len > this->len)
		return false;

	return !memcmp(this->data, suffix->data, suffix->len);
}

Boolean
CFStringHasSuffixC(CFStringRef this, const char *suffix)
{
	CFSize suffix_len = strlen(suffix);

	if (suffix_len > this->len)
		return false;

	return !memcmp(this->data, suffix, suffix_len);
}

CFSize
CFStringFind(CFStringRef this, CFStringRef substr, CFRange_t range)
{
	CFSize i;

	if (range.start > this->len)
		return SIZE_MAX;

	if (range.length == SIZE_MAX)
		range.length = this->len - range.start;

	if (range.start + range.length > this->len || substr->len > range.length)
		return SIZE_MAX;

	for (i = range.start; i <= range.start + range.length - substr->len;
	    i++)
		if (!memcmp(this->data + i, substr->data, substr->len))
			return i;

	return SIZE_MAX;
}

CFSize
CFStringFindC(CFStringRef this, const char *substr, CFRange_t range)
{
	CFSize substr_len = strlen(substr);
	CFSize i;

	if (range.start > this->len)
		return SIZE_MAX;

	if (range.length == SIZE_MAX)
		range.length = this->len - range.start;

	if (range.start + range.length > this->len || substr_len > range.length)
		return SIZE_MAX;

	for (i = range.start; i <= range.start + range.length - substr_len;
	    i++)
		if (!memcmp(this->data + i, substr, substr_len))
			return i;

	return SIZE_MAX;
}

