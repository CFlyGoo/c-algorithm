//
// Created by Han Pengfei on 2018/9/17.
//

#include "collection.h"
#include <stdlib.h>

boolean default_collection_is_empty(collection col) {
    return col->size(col) == 0;
}

void default_collection_add_all(collection first, collection second) {
    iterator it = second->iterator(second);
    while (it->has_next(it))
        first->add(first, it->next(it));
}

boolean default_collection_contains_all(collection first, collection second) {
    iterator it = second->iterator(second);
    while (it->has_next(it))
        if (!first->contains(first, it->next(it)))
            return false;
    return true;
}

void default_collection_clear(collection this) {
    this->remove_all(this, this);
}

boolean default_collection_contains(collection col, void *elem) {
    iterator it = col->iterator(col);
    while (it->has_next(it))
        if (elem == it->next(it))
            return true;
    return false;
}

void default_collection_remove_all(collection first, collection second) {
    iterator it = second->iterator(second);
    while (it->has_next(it))
        first->remove(first, it->next(it));
}

void **default_collection_to_array(collection col) {
    void **array = malloc(sizeof(void *) * col->size(col));
    iterator it = col->iterator(col);
    for (int i = 0; it->has_next(it); ++i)
        array[i] = it->next(it);
    return array;
}

collection new_collection() {
    collection this = malloc(sizeof(struct __collection));
    this->is_empty = default_collection_is_empty;
    this->add_all = default_collection_add_all;
    this->contains_all = default_collection_contains_all;
    this->clear = default_collection_clear;
    this->contains = default_collection_contains;
    this->remove_all = default_collection_remove_all;
    this->to_array = default_collection_to_array;
    this->__expander = NULL;
    return this;
}

void unsupported_collection_add_or_remove(collection this, void *e) {
    throw(UNSUPPORTED_OPTIONAL);
}

void unsupported_collection_add_all_or_remove_all(collection first, collection second) {
    throw(UNSUPPORTED_OPTIONAL);
}

void unsupported_collection_clear(collection this) {
    throw(UNSUPPORTED_OPTIONAL);
}

void unmodifiable_collection(collection this) {
    this->add = unsupported_collection_add_or_remove;
    this->add_all = unsupported_collection_add_all_or_remove_all;
    this->remove = unsupported_collection_add_or_remove;
    this->remove_all = unsupported_collection_add_all_or_remove_all;
    this->clear = unsupported_collection_clear;
}
