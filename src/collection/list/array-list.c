//
// Created by Han Pengfei on 2018/9/17.
//

#include <stdlib.h>
#include <string.h>
#include "array-list.h"

static void array_list_remove(collection, void *);

static int array_list_size(collection);

static void array_list_insert(list, int i, void *);

static void *array_list_get(list, int);

static void **array_list_to_array(collection c);

static void array_list_retain_all(list, collection);

static void *array_list_set(list, int, void *);

static void array_list_sort(list, int (*)(void *, void *));

static list array_list_sub_list(list, int, int);

static void array_list_trim_to_size(array_list);

static void init_array_list_func(array_list);

static void init_array_list_attrs(array_list);

static void assert_not_index_of_bounds(collection, int);

static void assert_not_index_of_bounds_excepted_last(collection, int);

array_list new_array_list() {
    array_list this = malloc(sizeof(struct __array_list));
    this->__prototype_list = new_list();
    init_array_list_func(this);
    init_array_list_attrs(this);
    this->__prototype_list->__expander = this;
    return this;
}

void unmodifiable_array_list(array_list this) {
    unmodifiable_list(array_list_to_list(this));
    this->trim_to_size(this);
}

static void array_list_retain_all(list l, collection c) {
    // TODO implement
}

static void array_list_sort(list l, int (*comparator)(void *, void *)) {
    void **array = list_to_collection(l)->to_array(list_to_collection(l));
    // TODO sort
    list_to_array_list(l)->__array = array;
}

static void init_array_list_func(array_list this) {
    this->trim_to_size = array_list_trim_to_size;
    array_list_to_list(this)->get = array_list_get;
    array_list_to_list(this)->set = array_list_set;
    array_list_to_list(this)->sort = array_list_sort;
    array_list_to_list(this)->insert = array_list_insert;
    array_list_to_list(this)->sub_list = array_list_sub_list;
    array_list_to_list(this)->retain_all = array_list_retain_all;
    array_list_to_collection(this)->to_array = array_list_to_array;
    array_list_to_collection(this)->remove = array_list_remove;
    array_list_to_collection(this)->size = array_list_size;
}

static void init_array_list_attrs(array_list this) {
    this->__size = 0;
    this->__capacity = DEFAULT_CAPACITY;
    this->__load_factor = DEFAULT_LOAD_FACTOR;
    this->__array = malloc(sizeof(void *) * DEFAULT_CAPACITY);
}

static void array_list_remove(collection c, void *e) {
    array_list this = collection_to_array_list(c);
    int count = 0;
    for (int i = 0; i < this->__size; ++i) {
        if (this->__array[i] != e)
            continue;
        for (int j = i; j < this->__size; ++j)
            this->__array[j] = this->__array[j + 1];
        ++count;
    }
    this->__size -= count;
}

static int array_list_size(collection c) {
    return collection_to_array_list(c)->__size;
}

static void array_list_insert(list l, int i, void *e) {
    assert_not_index_of_bounds_excepted_last(list_to_collection(l), i);
    array_list this = list_to_array_list(l);
    if (this->__size >= this->__capacity * this->__load_factor) {
        this->__capacity *= 2;
        this->__array = realloc(this->__array, this->__capacity);
    }
    for (int j = this->__size; j >= i && j > 0; --j)
        this->__array[j] = this->__array[j - 1];
    this->__array[i] = e;
    ++this->__size;
}

static void *array_list_get(list l, int i) {
    assert_not_index_of_bounds(list_to_collection(l), i);
    array_list this = list_to_array_list(l);
    return this->__array[i];
}

static void **array_list_to_array(collection c) {
    void **array = malloc(sizeof(void *) * c->size(c));
    memcpy(array, collection_to_array_list(c)->__array, sizeof(void *) * c->size(c));
    return array;
}

static void *array_list_set(list l, int i, void *e) {
    assert_not_index_of_bounds_excepted_last(list_to_collection(l), i);
    array_list this = list_to_array_list(l);
    void *value = this->__array[i];
    this->__array[i] = e;
    return value;
}

static void array_list_trim_to_size(array_list this) {
    this->__array = realloc(this->__array, sizeof(void *) * this->__size);
}

static void assert_not_index_of_bounds_excepted_last(collection c, int i) {
    if (i > c->size(c) || i < 0)
        throw(INDEX_OUT_OF_BOUNDS);
}

static void assert_not_index_of_bounds(collection c, int i) {
    if (i >= c->size(c) || i < 0)
        throw(INDEX_OUT_OF_BOUNDS);
}

static list array_list_sub_list(list l, int form, int to) {
    int size = form - to;
    void **array = malloc(sizeof(void *) * size);
    array_list this = list_to_array_list(l);
    memcpy(array, this->__array[form], size);
    array_list nl = new_array_list();
    nl->__capacity = (unsigned int) size;
    nl->__size = (unsigned int) size;
    nl->__array = array;
    nl->__load_factor = DEFAULT_LOAD_FACTOR;
    return array_list_to_list(nl);
};
