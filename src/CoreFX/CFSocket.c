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

#define _C99_SOURCE
#define _POSIX_SOURCE

#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "CFStream.h"
#include "CFSocket.h"

int snprintf(char *str, size_t size, const char *format, ...);

static CFTypeID _kCFSocketTypeID = 0;

struct __CFSocket {
	struct __CFStream stream;
	int fd;
	bool at_end;
};


static struct __CFClass class = {
	.name = "CFSocket",
	.size = sizeof(struct __CFSocket),
	.ctor = CFSocketCreate,
	.dtor = CFSocketFinalize
};
CFClass CFSocketClass = &class;

CFTypeID
CFSocketGetTypeID (void)
{
  return _kCFSocketTypeID;
}


void CFSocketClassInitialize()
{
	_kCFSocketTypeID = CFRegisterClass(&class);
}

static ssize_t
sock_read(void *self, void *buf, size_t len)
{
	CFSocket this = self;
	ssize_t ret;

	if ((ret = recv(this->fd, buf, len, 0)) == 0)
		this->at_end = true;

	return ret;
}

static bool
sock_write(void *self, const void *buf, size_t len)
{
	CFSocket this = self;
	ssize_t ret;

	if ((ret = send(this->fd, buf, len, 0)) < len)
		return false;

	return true;
}

static bool
sock_at_end(void *self)
{
	CFSocket this = self;

	return this->at_end;
}

static void
sock_close(void *self)
{
	CFSocket this = self;

	if (this->fd != -1)
		close(this->fd);
}

static struct CFStreamOps stream_ops = {
	.read = sock_read,
	.write = sock_write,
	.at_end = sock_at_end,
	.close = sock_close
};

Boolean 
CFSocketCreate(CFType self, va_list args)
{
	CFSocket this = self;

	CFStreamClass->ctor(self, args);

	this->fd = -1;
	this->stream.ops = &stream_ops;
	this->at_end = false;

	return true;
}

void 
CFSocketFinalize(CFType self)
{
	CFStreamClass->dtor(self);
}

Boolean
CFSocketConnect(CFSocket this, const char *host, uint16_t port)
{
	struct addrinfo hints, *res, *res0;
	char portstr[7];

	if (this->fd != -1)
		return false;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	snprintf(portstr, 7, "%" PRIu16, port);

	if (getaddrinfo(host, portstr, &hints, &res0))
		return false;

	for (res = res0; res != NULL; res = res->ai_next) {
		if ((this->fd = socket(res->ai_family, res->ai_socktype,
		    res->ai_protocol)) == -1)
			continue;

		if (connect(this->fd, res->ai_addr, res->ai_addrlen) == -1) {
			close(this->fd);
			this->fd = -1;
			continue;
		}

		break;
	}

	freeaddrinfo(res0);

	return (this->fd != -1);
}

