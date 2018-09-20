#include <stdlib.h>
#include <assert.h>

#include "test.h"
#include "exception.h"

typedef struct __array_test_runner *array_test_runner;

#define test_env_to_array_test_runner(env) ((array_test_runner)(env->__expander))
#define print_start_info(__env)  printf("Starting test %s\n", (test_env_to_array_test_runner(__env))->name);

static void array_test_runner_add_test_case(test_env, void(*)(void *), char *, void *);

static void array_test_runner_add_test_case_with_exception(test_env, void(*)(void *), char *, void *, int);

static void array_test_runner_run(test_env);

// Inner

static int run_case_with_exception(test_case);

static int run_case_non_exception(test_case);

static void test_end(test_env);

struct __array_test_runner {
    test_env __prototype;
    char *name;
    test_case *cases;
    int count;
};

test_env new_test_env(char *name) {
    array_test_runner this = malloc(sizeof(struct __array_test_runner));
    this->__prototype = malloc(sizeof(struct __test_env));
    this->name = name;
    this->count = 0;
    this->cases = NULL;
    this->__prototype->__expander = this;
    this->__prototype->add_test_case = array_test_runner_add_test_case;
    this->__prototype->add_test_case_with_exception = array_test_runner_add_test_case_with_exception;
    this->__prototype->run = array_test_runner_run;
    return this->__prototype;
}

static void array_test_runner_add_test_case(test_env env, void(*func)(void *), char *name, void *args) {
    array_test_runner runner = test_env_to_array_test_runner(env);
    runner->cases = (runner->count == 0) ?
                    malloc(sizeof(struct __test_case) * ++runner->count) :
                    realloc(runner->cases, sizeof(struct __test_case) * ++runner->count);
    test_case c = runner->cases[runner->count - 1] = malloc(sizeof(struct __test_case));
    c->name = name;
    c->args = args;
    c->func = func;
    c->throw_e = false;
    c->e_code = 0;
}

static int run_case_with_exception(test_case c) {
    assert(c->throw_e);
    try c->func(c->args);
    catch(c->e_code)return 0;
    return __e_code;
}

static int run_case_non_exception(test_case c) {
    assert(!c->throw_e);
    try {
        c->func(c->args);
        return 0;
    }
    return __e_code;
}

static void array_test_runner_add_test_case_with_exception(
        test_env env, void(*func)(void *), char *name, void *args, int e) {
    array_test_runner_add_test_case(env, func, name, args);
    array_test_runner runner = test_env_to_array_test_runner(env);
    test_case c = runner->cases[runner->count - 1];
    c->throw_e = true;
    c->e_code = e;
}

static void start_test_case(int i, test_env env, test_case c) {
    printf("[%d/%d] %-16.16s\t", i + 1, (test_env_to_array_test_runner(env))->count, c->name);
    printf(" .................................. ");
    int code = c->throw_e ? run_case_with_exception(c) : run_case_non_exception(c);
    if (code == 0) {test_success(c); }
    else {test_failure(c); }
}

static void array_test_runner_run(test_env env) {
    array_test_runner runner = test_env_to_array_test_runner(env);
    test_case *cases = runner->cases;
    print_start_info(env);
    for (int i = 0; i < runner->count; ++i) {
        start_test_case(i, env, cases[i]);
    }
    test_end(env);
}

void test_end(test_env env) {
    array_test_runner runner = test_env_to_array_test_runner(env);
    printf("Test %s - Count: %d\t", runner->name, runner->count);
    int success = 0;
    for (int i = 0; i < runner->count; ++i)
        if (runner->cases[i]->success)
            ++success;
    printf("Success: %d\tFailure: %d\n", success, runner->count - success);
}