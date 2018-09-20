//
// Created by Han Pengfei on 2018/9/19.
//

#include "collection-test.h"

void test_add(void *args) {
    collection col = args;
    assert(col->size(col) == 0);
    col->add(col, (void *) 1);
    assert(col->contains(col, (void *) 1));
}

void test_add_all(void *args) {
}

void test_clear(void *args) {
    collection col = args;
    assert(col->size(col) == 0);
    col->add(col, (void *) 1);
    assert(col->size(col) == 1);
    col->clear(col);
    assert(col->size(col) == 0);
}

void test_contains(void *args) {
    collection col = (collection) args;
    col->add(col, (void *) 1);
    assert(col->contains(col, (void *) 1));
}

void test_contains_all(void *args) {
}

void test_is_empty(void *args) {
    collection col = (collection) args;
    assert(col->size(col) == 0);
    assert(col->is_empty(col));
    col->add(col, (void *) 1);
    assert(!col->is_empty(col));
    col->remove(col, (void *) 1);
    assert(col->is_empty(col));
}

void test_iterator(void *args) {}

void test_remove(void *args) {}

void test_remove_all(void *args) {}

void test_size(void *args) {
}

void test_to_array(void *args) {}

