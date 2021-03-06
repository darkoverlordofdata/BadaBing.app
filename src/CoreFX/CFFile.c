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

#include <string.h>
#include <limits.h>
#include <stdio.h> 
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "CFStream.h"
#include "CFFile.h"

#ifndef O_BINARY
# define O_BINARY 0
#endif

#ifndef S_IRGRP
# define S_IRGRP 0
#endif
#ifndef S_IROTH
# define S_IROTH 0
#endif
#ifndef S_IWGRP
# define S_IWGRP 0
#endif
#ifndef S_IWOTH
# define S_IWOTH 0
#endif

#define DEFAULT_MODE S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH

static int parse_mode(const char *mode);
static ssize_t file_read(CFType self, CFType buf, CFSize len);
static bool file_write(CFType self, const void* buf, CFSize len);
static bool file_at_end(CFType self);
static void file_close(CFType self);

static struct CFStreamOps stream_ops = {
	.read = file_read,
	.write = file_write,
	.at_end = file_at_end,
	.close = file_close
};




static CFTypeID _kCFFileTypeID = 0;

struct __CFFile {
	struct __CFStream stream;
	char* path; 
	int fd;
	bool at_end;
	bool useCtor;
};

static Boolean 
CFFileConstructor(CFType self, va_list args)
{
	CFFile this = self;
	const char *path = va_arg(args, const char*);
	const char *mode = va_arg(args, const char*);
	int flags;

	this->path = CFStrdup(path);
	this->useCtor = true;
	/* Make sure we have a valid file in case we error out */
	CFStreamClass->ctor(self, args);
	this->at_end = false;

	if ((flags = parse_mode(mode)) == -1)
		return false;

	if ((this->fd = open(path, flags, DEFAULT_MODE)) == -1)
		return false;

	this->stream.ops = &stream_ops;

	return true;
}

static void 
CFFileFinalize(CFType self)
{
	CFFile this = self;
	if (this->useCtor) {
		free(this->path);
	}
	CFStreamClass->dtor(self);
}

static char* 
CFFileToString(CFType self)
{
	static char str[64]; 

	CFFile this = self;
	snprintf(str, 63, "CFFile: %s", this->path);
	return str;
}

static struct __CFClass class = {
	.name = "CFFile",
	.size = sizeof(struct __CFFile),
	.ctor = CFFileConstructor,
	.dtor = CFFileFinalize,
	.tostr = CFFileToString
};
CFClass CFFileClass = &class;



CFTypeID
CFFileGetTypeID (void)
{
  return _kCFFileTypeID;
}

void CFFileClassInitialize()
{
	_kCFFileTypeID = CFRegisterClass(&class);
}

CFFile 
CFFileCreate(char* path, char* mode)
{
	return CFCreateObject(CFFileClass, path, mode);
}

CFFile 
CFFileNew(char* path, char* mode)
{
	return CFNewObject(CFFileClass, path, mode);
}

static int
parse_mode(const char *mode)
{
	if (!strcmp(mode, "r"))
		return O_RDONLY;
	if (!strcmp(mode, "rb"))
		return O_RDONLY | O_BINARY;
	if (!strcmp(mode, "r+"))
		return O_RDWR;
	if (!strcmp(mode, "rb+") || !strcmp(mode, "r+b"))
		return O_RDWR | O_BINARY;
	if (!strcmp(mode, "w"))
		return O_WRONLY | O_CREAT | O_TRUNC;
	if (!strcmp(mode, "wb"))
		return O_WRONLY | O_CREAT | O_TRUNC | O_BINARY;
	if (!strcmp(mode, "w+"))
		return O_RDWR | O_CREAT | O_TRUNC;
	if (!strcmp(mode, "wb+") || !strcmp(mode, "w+b"))
		return O_RDWR | O_CREAT | O_TRUNC | O_BINARY;
	if (!strcmp(mode, "a"))
		return O_WRONLY | O_CREAT | O_APPEND;
	if (!strcmp(mode, "ab"))
		return O_WRONLY | O_CREAT | O_APPEND | O_BINARY;
	if (!strcmp(mode, "a+"))
		return O_RDWR | O_CREAT | O_APPEND;
	if (!strcmp(mode, "ab+") || !strcmp(mode, "a+b"))
		return O_RDWR | O_CREAT | O_APPEND | O_BINARY;

	return -1;
}

static ssize_t
file_read(CFType self, CFType buf, CFSize len)
{
	CFFile this = self;
	CFSize ret;

	if ((ret = read(this->fd, buf, len)) == 0)
		this->at_end = true;

	return ret;
}

static bool
file_write(CFType self, const void* buf, CFSize len)
{
	CFFile this = self;
	CFSize ret;

	if ((ret = write(this->fd, buf, len)) < len)
		return false;

	return true;
}

static bool
file_at_end(CFType self)
{
	CFFile this = self;

	return this->at_end;
}

static void
file_close(CFType self)
{
	CFFile this = self;

	close(this->fd);
}



static struct __CFFile CFStdIn_ = {
	.path = "stdin:",
	.stream = {
		.obj = {
			.cls = &class,
			.ref_cnt = INT_MAX
		},
		.ops = &stream_ops
	},
	.fd = 0,
	.at_end = false
};

static struct __CFFile CFStdOut_ = {
	.path = "stdout:",
	.stream = {
		.obj = {
			.cls = &class,
			.ref_cnt = INT_MAX
		},
		.ops = &stream_ops
	},
	.fd = 1,
	.at_end = false
};

static struct __CFFile CFStdErr_ = {
	.path = "stderr:",
	.stream = {
		.obj = {
			.cls = &class,
			.ref_cnt = INT_MAX
		},
		.ops = &stream_ops
	},
	.fd = 2,
	.at_end = false
};

CFFile CFStdIn = &CFStdIn_;
CFFile CFStdOut = &CFStdOut_;
CFFile CFStdErr = &CFStdErr_;

