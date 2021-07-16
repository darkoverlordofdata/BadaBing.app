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
#include <string.h>

#include "CFStream.h"

#define BUFFER_SIZE 4096

static CFTypeID _kCFStreamTypeID = 0;

static Boolean 
CFStreamConstructor(CFType self, va_list args)
{
	CFStream this = self;

	this->ops = NULL;
	this->cache = NULL;
	this->cache_len = 0;

	return true;
}

static void 
CFStreamFinalize(CFType self)
{
	CFStreamClose(self);
}

static struct __CFClass class = {
	.name = "CFStream",
	.size = sizeof(struct __CFStream),
	.ctor = CFStreamConstructor,
	.dtor = CFStreamFinalize
};
CFClass CFStreamClass = &class;

CFTypeID
CFStreamGetTypeID (void)
{
  return _kCFStreamTypeID;
}

void CFStreamClassInitialize()
{
	_kCFStreamTypeID = CFRegisterClass(&class);
}

CFStream
CFStreamCreate()
{
	return CFCreateObject(CFStreamClass);
}

CFStream
CFStreamNew()
{
	return CFNewObject(CFStreamClass);
}

CFSize
CFStreamRead(CFType self, CFType buf, CFSize len)
{
	CFStream this = self;
	CFSize ret;

	if (this == NULL || this->ops == NULL)
		return -1;

	if (this->cache == NULL) {
		if ((ret = this->ops->read(this, buf, len)) < -1)
			ret = -1;

		return ret;
	}

	if (len >= this->cache_len) {
		ret = this->cache_len;

		memcpy(buf, this->cache, this->cache_len);

		free(this->cache);
		this->cache = NULL;
		this->cache_len = 0;

		return ret;
	} else {
		char *tmp;

		if ((tmp = malloc(this->cache_len - len)) == NULL)
			return -1;
		memcpy(tmp, this->cache + len, this->cache_len - len);
		memcpy(buf, this->cache, len);

		free(this->cache);
		this->cache = tmp;
		this->cache_len -= len;

		return len;
	}
}

CFString
CFStreamReadLine(CFType self)
{
	CFStream this = self;
	CFString ret;
	char *buf, *ret_str, *new_cache;
	ssize_t buf_len;
	size_t i, ret_len;

	/* Look if there is a line or \0 in our cache */
	if (this->cache != NULL) {
		for (i = 0; i < this->cache_len; i++) {
			if (this->cache[i] == '\n' ||
			    this->cache[i] == '\0') {
				ret_len = i;
				if (i > 0 && this->cache[i - 1] == '\r')
					ret_len--;

				ret_str = CFStrndup(this->cache, ret_len);
				if (ret_str == NULL)
					return NULL;

				ret = CFStringCreate((void*)NULL);
				if (ret == NULL) {
					free(ret_str);
					return NULL;
				}
				CFStringSetNocopy(ret, ret_str, ret_len);

				if (this->cache_len > i + 1) {
					if ((new_cache = malloc(
					    this->cache_len - i - 1)) == NULL)
						return NULL;
					memcpy(new_cache, this->cache + i + 1,
					    this->cache_len - i - 1);
				} else
					new_cache = CFStrdup("");

				free(this->cache);
				this->cache = new_cache;
				this->cache_len -= i + 1;

				return ret;
			}
		}
	}

	/* Read and see if we get a newline or \0 */

	if ((buf = malloc(BUFFER_SIZE)) == NULL)
		return NULL;

	for (;;) {
		if (this->ops->at_end(this)) {
			free(buf);

			if (this->cache == NULL)
				return NULL;

			ret_len = this->cache_len;

			if (ret_len > 0 && this->cache[ret_len - 1] == '\r')
				ret_len--;

			ret_str = CFStrndup(this->cache, ret_len);
			if (ret_str == NULL)
				return NULL;

			ret = CFStringCreate((void*)NULL);
			if (ret == NULL) {
				free(ret_str);
				return NULL;
			}
			CFStringSetNocopy(ret, ret_str, ret_len);

			free(this->cache);
			this->cache = NULL;
			this->cache_len = 0;

			return ret;
		}

		buf_len = this->ops->read(this, buf, BUFFER_SIZE);
		if (buf_len == -1) {
			free(buf);
			return NULL;
		}

		/* Look if there's a newline or \0 */
		for (i = 0; i < buf_len; i++) {
			if (buf[i] == '\n' || buf[i] == '\0') {
				ret_len = this->cache_len + i;

				if ((ret_str = malloc(ret_len + 1)) == NULL) {
					/*
					 * FIXME: We lost the current buffer.
					 *	  Mark the this as broken?
					 */
					free(buf);
					return NULL;
				}
				memcpy(ret_str, this->cache,
				    this->cache_len);
				memcpy(ret_str + this->cache_len, buf, i);
				if (ret_len > 0 && ret_str[ret_len - 1] == '\r')
					ret_len--;
				ret_str[ret_len] = '\0';

				ret = CFStringCreate((void*)NULL);
				if (ret == NULL) {
					free(buf);
					free(ret_str);
					return NULL;
				}
				CFStringSetNocopy(ret, ret_str, ret_len);

				if (buf_len > i + 1) {
					new_cache = malloc(buf_len - i - 1);
					if (new_cache == NULL) {
						free(buf);
						return NULL;
					}
					memcpy(new_cache, buf + i + 1,
					    buf_len - i - 1);
				} else
					new_cache = CFStrdup("");

				free(this->cache);
				this->cache = new_cache;
				this->cache_len = buf_len - i - 1;

				free(buf);
				return ret;
			}
		}

		/* There was no newline or \0 */
		if (this->cache_len + buf_len > 0) {
			new_cache = realloc(this->cache,
			    this->cache_len + buf_len);
			if (new_cache == NULL) {
				free(buf);
				return NULL;
			}
			memcpy(new_cache + this->cache_len, buf, buf_len);
		} else {
			free(this->cache);
			new_cache = CFStrdup("");
		}

		this->cache = new_cache;
		this->cache_len += buf_len;
	}
}

Boolean
CFStreamWrite(CFType self, const CFType buf, CFSize len)
{
	CFStream this = self;

	if (this == NULL || this->ops == NULL)
		return false;

	return this->ops->write(this, buf, len);
}

Boolean
CFStreamWriteString(CFType self, const char *str)
{
	return CFStreamWrite(self, (const CFType)str, strlen(str));
}

Boolean
CFStreamWriteLine(CFType self, const char *str)
{
	char *tmp;
	size_t len;

	len = strlen(str);

	if ((tmp = malloc(len + 2)) == NULL)
		return false;

	memcpy(tmp, str, len);
	tmp[len] = '\n';
	tmp[len + 1] = '\0';

	if (!CFStreamWrite(self, tmp, len + 1)) {
		free(tmp);
		return false;
	}

	free(tmp);
	return true;
}

Boolean
CFStreamAtEnd(CFType self)
{
	CFStream this = self;

	if (this == NULL || this->ops == NULL)
		return true;

	if (this->cache != NULL)
		return false;

	return this->ops->at_end(this);
}

void
CFStreamClose(CFType self)
{
	CFStream this = self;

	if (this == NULL || this->ops == NULL)
		return;

	this->ops->close(this);
}

