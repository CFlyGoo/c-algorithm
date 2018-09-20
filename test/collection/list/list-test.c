//
// Created by Han Pengfei on 2018/9/20.
//

#include "list-test.h"

void test_insert_out_of_bounds(void *args) {
    list l = (list) args;
    l->insert(l, 1, (void *) 1);
}

