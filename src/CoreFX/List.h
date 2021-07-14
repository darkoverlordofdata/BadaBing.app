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
#include <dark/core/object.h>
#include <dark/types/string.h>

#define IsList(object) _Generic((object), List*: true, default: false)
#define AsList(object) _Generic((object),                             \
                            List*: (List *)object,                  \
                            default: nullptr)

typedef int (*List_Compare) (Object*, Object*);
typedef void (^List_Iterator) (Object*);

type (ListNode) {
    Object* data;
    ListNode* next;
};

type (List) {
    Class isa;
    Class typeOf;
    int length;
    ListNode* head;
};

delegate (List, New,        List*,      (List*, Class));
delegate (List, ToString,   char*,      (const List* const) );
delegate (List, Length,     int,        (List* const) );
delegate (List, Add,        Either*,    (List* const, Object*) );
delegate (List, Remove,     Object*,    (List* const) );
delegate (List, Insert,     Either*,    (List* const, Object*, List_Compare) );
delegate (List, Iterate,    void,       (List* const, List_Iterator) );

vtable (List) {
    const ListToString          ToString;
    const ObjectEquals          Equals;
    const ObjectGetHashCode     GetHashCode;
    const ObjectDispose         Dispose;
    const ListLength            Length;
    const ListAdd               Add;
    const ListRemove            Remove;
    const ListInsert            Insert;
    const ListIterate           Iterate;
};

static inline vptr(List);
/**
 * 
 * Class Loader callback
 */
static inline Class ClassLoadList(Class base) 
{
    Class cls = createClass(base, List);
    addMethod(cls, List, ToString);
    addMethod(cls, Object, Equals);
    addMethod(cls, Object, GetHashCode);
    addMethod(cls, Object, Dispose);
    addMethod(cls, List, Length);
    addMethod(cls, List, Add);
    addMethod(cls, List, Remove);
    addMethod(cls, List, Insert);
    addMethod(cls, List, Iterate);
    
    return cls;
}

method List* NewEither(List* const self)
{
    return New(self, nullptr);
}

method List* New(List* self, Class typeOf)
{
    extends(Object);
    self->isa = isa(List);
    self->typeOf = typeOf;
    self->head = nullptr;

    return self;
}

method List* New(List* const self)
{
    return New(self, nullptr);
}


/**
 * Create new ListNode
 * 
 * @param data to add
 * @param next node in list
 * 
 */
static inline ListNode* ListNode_ctor(ListNode* const self, Object* data, ListNode* next)
{
    self->data = data;
    self->next = next;
    return self;
}

static inline ListNode* NewListNode(Object* data, ListNode* next)
{
    return ListNode_ctor(alloc(ListNode), data, next);
}

/**
 * Add to list in sorted order
 * 
 * @param data to insert
 * @param comp function to compare for insertion
 * 
 */
method Either* Insert(List* const self, Object* data, List_Compare comp)
{
    if ((self->typeOf) && !InstanceOf(self->typeOf, data)) 
        return left(new(String, "InvalidType"));

    if (self->head == nullptr) {
        self->head = NewListNode(data, nullptr);
        return right(new(String, "1"));
    }

    // Find spot in linked list to insert new node
    ListNode* prev = nullptr;
    ListNode* curr = self->head;
    while (curr != nullptr && curr->data != nullptr && comp(curr->data, data) < 0) {
        prev = curr;
        curr = curr->next;
    }

    if (prev == nullptr) 
        self->head = NewListNode(data, self->head);
    else 
        prev->next = NewListNode(data, curr);

    self->length++;
    return right(new(String, "1"));
}

/**
 * Add to end of list
 * 
 * @param data to insert
 * 
 */
method Either* Add(List* const self, Object* data)
{
    if ((self->typeOf) && !InstanceOf(self->typeOf, data)) 
        return left(new(String, "InvalidType"));


    if (self->head == nullptr) {
        self->head = NewListNode(data, nullptr);
    }
    else { 
       self->head = NewListNode(data, self->head);
    }
    self->length++;
}

/**
 * Remove item at end of list
 */
method Object* Remove(List* const self)
{
    ListNode* head = self->head;

    Object* popped_data = head->data;
    self->head = head->next;

    // delete(head);
    self->length--;
    return popped_data;
}

/**
 * Iterate over list
 * 
 * @param iter function to call for each iteration
 * 
 */
method void Iterate(List* const self, void (^iter)(Object*))
{
    for (ListNode* curr = self->head; curr != nullptr; curr = curr->next) {
        iter(curr->data);
    }
}

/**
 * Free list
 */
method void Dispose(List* const self)
{
    // ListNode curr = self->head;
    // ListNode next;

    // while (curr != nullptr) {
    //     delete(curr->data);
    //     next = curr->next;
    //     delete(curr);
    //     curr = next;
    // }
}

/**
 * Number of items in vector
 */
method int Length(List* const self)
{
    return self->length;
}

/**
 * ToString
 */
method char* ToString(const List* const self)
{
    return "dark.collections.List";
}

