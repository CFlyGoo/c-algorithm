#ifndef Test_h
#define Test_h

#include <stdio.h>
#include "_test.h"

typedef struct __test_env *test_env;
typedef struct __test_case *test_case;

#define test_failure(__c) {__c->success = false;printf("[Failure]\n");}
#define test_success(__c) {__c->success = true;printf("[Success]\n");}

struct __test_env {

    void *__expander;

    void (*add_test_case)(test_env, void(*)(void *), char *, void *);

    void (*add_test_case_with_exception)(test_env, void(*)(void *), char *, void *, int);

    void (*run)(test_env);
};

test_env new_test_env(char *);

#endif /* Test_h */
