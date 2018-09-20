//
// Created by Han Pengfei on 2018/9/17.
//

#include <stdlib.h>
#include "boolean.h"
#include "list.h"
#include "exception.h"

static void assert_is_modifiable(list_iterator);

boolean list_iterator_has_next(iterator it) {
    list_iterator this = iterator_to_list_iterator(it);
    return this->__index + 1 < list_to_collection(this->__list)->size(list_to_collection(this->__list));
}

void *list_iterator_next(iterator it) {
    list_iterator this = iterator_to_list_iterator(it);
    return this->__list->get(this->__list, ++this->__index);
}

void list_iterator_remove(iterator it) {
    list_iterator this = iterator_to_list_iterator(it);
    assert_is_modifiable(this);
    collection col = list_to_collection(this->__list);
    col->remove(col, this->__list->get(this->__list, this->__index));
}

void list_iterator_add(list_iterator it, void *elem) {
    list_iterator this = iterator_to_list_iterator(it);
    assert_is_modifiable(this);
    collection col = list_to_collection(this->__list);
    col->add(col, elem);
}

boolean list_iterator_has_previous(list_iterator this) {
    return this->__index > 0;
}

int list_iterator_next_index(list_iterator this) {
    return this->__index + 1;
}

list_iterator new_list_iterator(list list, boolean modifiable) {
    list_iterator this = malloc(sizeof(struct __list_iterator));
    this->__prototype_iterator = malloc(sizeof(struct __iterator));
    this->__index = -1;
    this->__list = list;
    this->__modifiable = modifiable;
    list_iterator_to_iterator(this)->has_next = list_iterator_has_next;
    list_iterator_to_iterator(this)->next = list_iterator_next;
    list_iterator_to_iterator(this)->remove = list_iterator_remove;
    this->add = list_iterator_add;
    this->has_previous = list_iterator_has_previous;
    this->next_index = list_iterator_next_index;
    this->__prototype_iterator->__expander = this;
    return this;
}

static void assert_is_modifiable(list_iterator this) {
    if (!this->__modifiable)
        throw(UNSUPPORTED_OPTIONAL);
}