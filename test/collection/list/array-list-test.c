//
// Created by Han Pengfei on 2018/9/17.
//

#include <stdlib.h>
#include "array-list-test.h"
#include "exception.h"

jmp_buf e_env = {};

int main(int argc, char **argv) {
    test_env t_env = new_test_env("array list");
    t_env->add_test_case(t_env, test_new_array_list, "new array list", new_array_list());
    t_env->add_test_case(t_env, test_add, "add", array_list_to_collection(new_array_list()));
    t_env->add_test_case(t_env, test_size, "size", array_list_to_collection(new_array_list()));
    t_env->add_test_case(t_env, test_clear, "clear", array_list_to_collection(new_array_list()));
    t_env->add_test_case(t_env, test_remove, "remove", array_list_to_collection(new_array_list()));
    t_env->add_test_case(t_env, test_contains, "contains", array_list_to_collection(new_array_list()));
    t_env->add_test_case(t_env, test_is_empty, "is empty", array_list_to_collection(new_array_list()));
    t_env->add_test_case(t_env, test_iterator, "iterator", array_list_to_collection(new_array_list()));
    t_env->add_test_case(t_env, test_to_array, "to array", array_list_to_collection(new_array_list()));
    t_env->add_test_case_with_exception(t_env, test_insert_out_of_bounds, "insert out of bounds",
                                        array_list_to_list(new_array_list()), INDEX_OUT_OF_BOUNDS);
    t_env->run(t_env);
    return 0;
}

void test_new_array_list(void *al) {
    assert(al != NULL);
}
