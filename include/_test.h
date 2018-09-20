//
// Created by Han Pengfei on 2018/9/19.
//

#ifndef C_ALGORITHM_TEST_H
#define C_ALGORITHM_TEST_H

#include "boolean.h"

struct __test_case {

    char *name;
    int e_code;
    void *args;
    boolean throw_e;
    boolean success;

    void (*func)(void *);
};

#endif //C_ALGORITHM_TEST_H
