/*******************************************************************
** This code is part of the Dark Framework.
**
MIT License

Copyright (c) 2018 Dark Overlord of Data

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************/
#pragma once
#include <signal.h>
#include <dark/core/object.h>

type (Option) {
	bool none;
	Object* value;
};

static Option* None;


/**
 * Option `monad`
 * 
 * A container/collection that can hold either 0 or 1 object
 * 
 */
static inline Option* NewOption(Object* value) {
    if (value == nullptr) {
        printf("Invalid - Option cannot be null\n");
        raise(SIGSEGV);
    }
    const auto self = alloc(Option);
    self->value = value;
    return self;
}

method Object* Some(Option* self) {
    return self->value;
}

method int Length(Option* self) {
    return self->value != nullptr ? 1 : 0;
}

method void ForEach(Option* const self, void (^iter)(Object*)) {
    iter(self->value);
}

method bool IsEmpty(Option* self) {
    return self->value == nullptr ? true : false;
}
 
method Object* Bind(Option* self, Option* (^func)(Option*)) {
    return self->value != nullptr ? func(self->value) : None; 
}

method Object* Bind(Option* self, Option* (*func)(Option*)) {
    return self->value != nullptr ? func(self->value) : None; 
}

static inline Object* Return(Option* self) {
    return self->value != nullptr ? NewOption(self->value) : None;
}

static void __attribute__((constructor())) OptionBoot() {
    None = alloc(Option);
    None->value = nullptr;
}

