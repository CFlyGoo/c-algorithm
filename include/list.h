//
// Created by Han Pengfei on 2018/9/17.
//

#ifndef C_ALGORITHM_LIST_H
#define C_ALGORITHM_LIST_H

#include "boolean.h"
#include "list.h"
#include "iterator.h"
#include "collection.h"

typedef struct __list *list;

typedef struct __list_iterator *list_iterator;

#define list_to_collection(this) (this->__prototype_collection)

#define collection_to_list(col) ((list)(col->__expander))

struct __list {

    collection __prototype_collection;

    void *__expander;

    void (*insert)(list, int idx, void *);

    void (*insert_all)(list, int idx, collection);

    void *(*get)(list, int);

    int (*index_of)(list, void *);

    int (*last_index_of)(list, void *);

    list_iterator (*list_iterator)(list);

    list_iterator (*list_iterator_form)(list, int);

    void (*retain_all)(list, collection);

    void *(*set)(list, int, void *);

    void (*sort)(list, int(*)(void *, void *));

    list (*sub_list)(list, int, int);
};

/* Default implementation */

list new_list();

void unmodifiable_list(list this);

void default_list_add(collection, void *);

int default_list_index_of(list, void *);

int default_list_last_index_of(list, void *);

iterator default_list_iterator(collection col);

list_iterator default_list_list_iterator(list this);

list_iterator default_list_list_iterator_form(list, int);

void default_list_insert_all(list, int, collection);

#define list_iterator_to_iterator(this) ((iterator)(this->__prototype_iterator))
#define iterator_to_list_iterator(this) ((list_iterator)(this->__expander))

struct __list_iterator {

    iterator __prototype_iterator;
    void *__expander;
    int __index;
    list __list;
    boolean __modifiable;

    void (*add)(list_iterator, void *);

    boolean (*has_previous)(list_iterator);

    int (*next_index)(list_iterator);

    void (*previous)(list_iterator);

    int (*previous_index)(list_iterator);

    void (*set)(list_iterator, void *);
};

list_iterator new_list_iterator(list, boolean);

#endif //C_ALGORITHM_LIST_H

