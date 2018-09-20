//
// Created by Han Pengfei on 2018/9/17.
//

#ifndef C_ALGORITHM_COLLECTION_H
#define C_ALGORITHM_COLLECTION_H

#include "boolean.h"
#include "iterator.h"
#include "exception.h"

typedef struct __collection *collection;

struct __collection {

    void *__expander;

    void (*add)(collection, void *);

    void (*add_all)(collection, collection);

    void (*clear)(collection);

    boolean (*contains)(collection, void *);

    boolean (*contains_all)(collection, collection);

    boolean (*is_empty)(collection);

    iterator (*iterator)(collection);

    void (*remove)(collection, void *);

    void (*remove_all)(collection, collection);

    int (*size)(collection);

    void **(*to_array)(collection);
};

/* Default implementation */

collection new_collection();

void unmodifiable_collection(collection col);

void default_collection_add_all(collection, collection);

boolean default_collection_contains(collection, void *);

boolean default_collection_contains_all(collection, collection);

void default_collection_remove_all(collection, collection);

boolean default_collection_is_empty(collection);

void **default_collection_to_array(collection);

void default_collection_clear(collection);

#endif //C_ALGORITHM_COLLECTION_H
