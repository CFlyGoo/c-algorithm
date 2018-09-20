//
// Created by Han Pengfei on 2018/9/17.
//

#ifndef C_ALGORITHM_ITERABLE_H
#define C_ALGORITHM_ITERABLE_H

#include "boolean.h"

typedef struct __iterator *iterator;

struct __iterator {

    void *__expander;

    boolean (*has_next)(iterator);

    void *(*next)(iterator);

    void (*remove)(iterator);
};

typedef struct __iterable *iterable;

struct __iterable {

    iterator (*iterator)(iterable);
};

#endif //C_ALGORITHM_ITERABLE_H
