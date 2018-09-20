//
// Created by Han Pengfei on 2018/9/17.
//

#include "list.h"
#include <stdlib.h>
#include <string.h>

list new_list() {
    list this = malloc(sizeof(struct __list));
    this->__prototype_collection = new_collection();
    this->__expander = NULL;
    this->list_iterator = default_list_list_iterator;
    this->index_of = default_list_index_of;
    this->last_index_of = default_list_last_index_of;
    this->list_iterator_form = default_list_list_iterator_form;
    this->insert_all = default_list_insert_all;
    list_to_collection(this)->iterator = default_list_iterator;
    list_to_collection(this)->add = default_list_add;
    this->__prototype_collection->__expander = this;
    return this;
}

list_iterator unmodifiable_list_iterator(list this) {
    return new_list_iterator(this, false);
}

void unsupported_list_insert(list l, int i, void *e) {
    throw(UNSUPPORTED_OPTIONAL);
}

void *unsupported_list_set(list l, int i, void *e) {
    throw(UNSUPPORTED_OPTIONAL);
}

void unsupported_list_insert_all(list l, int i, collection c) {
    throw(UNSUPPORTED_OPTIONAL);
}

void unsupported_retain_all(list l, collection c) {
    throw(UNSUPPORTED_OPTIONAL);
}

void unsupported_sort(list l, int(*func)(void *, void *)) {
    throw(UNSUPPORTED_OPTIONAL);
}

void unmodifiable_list(list this) {
    unmodifiable_collection(list_to_collection(this));
    this->insert = unsupported_list_insert;
    this->insert_all = unsupported_list_insert_all;
    this->set = unsupported_list_set;
    this->retain_all = unsupported_retain_all;
    this->sort = unsupported_sort;
    this->list_iterator = unmodifiable_list_iterator;
}

int default_list_last_index_of(list l, void *e) {
    for (int i = list_to_collection(l)->size(list_to_collection(l)) - 1; i >= 0; --i)
        if (l->get(l, i) == e)
            return i;
    return -1;
}

list_iterator default_list_list_iterator(list this) {
    return new_list_iterator(this, true);
}

iterator default_list_iterator(collection col) {
    list this = collection_to_list(col);
    return list_iterator_to_iterator((this->list_iterator(this)));
}

int default_list_index_of(list this, void *elem) {
    iterator it = list_to_collection(this)->iterator(list_to_collection(this));
    for (int i = -1; it->has_next(it); ++i)
        if (it->next(it) == elem)
            return i;
    return -1;
}

list_iterator default_list_list_iterator_form(list this, int idx) {
    list sub = this->sub_list(this, idx, list_to_collection(this)->size(list_to_collection(this)) - 1);
    return sub->list_iterator(sub);
}

void default_list_insert_all(list this, int idx, collection col) {
    iterator it = col->iterator(col);
    for (int step = 0; it->has_next(it); ++step)
        this->insert(this, idx + step, it->next(it));
}

void default_list_add(collection col, void *elem) {
    list this = collection_to_list(col);
    this->insert(this, col->size(col), elem);
}