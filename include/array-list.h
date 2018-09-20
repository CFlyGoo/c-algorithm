//
// Created by Han Pengfei on 2018/9/17.
//

#ifndef C_ALGORITHM_ARRAY_LIST_H
#define C_ALGORITHM_ARRAY_LIST_H

#include "list.h"

#define array_list_to_list(this) (this->__prototype_list)
#define array_list_to_collection(this) (list_to_collection(array_list_to_list(this)))

#define list_to_array_list(l) ((array_list)(l->__expander))
#define collection_to_array_list(col) (list_to_array_list(collection_to_list(col)))

#define DEFAULT_CAPACITY 16
#define DEFAULT_LOAD_FACTOR 0.75

typedef struct __array_list *array_list;

struct __array_list {

    list __prototype_list;
    unsigned int __capacity;
    double __load_factor;
    void **__array;
    unsigned int __size;

    void (*trim_to_size)(array_list);
};

array_list new_array_list();

void unmodifiable_array_list(array_list);

#endif //C_ALGORITHM_ARRAY_LIST_H
