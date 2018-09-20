//
// Created by Han Pengfei on 2018/9/18.
//

#ifndef C_ALGORITHM_EXCEPTION_H
#define C_ALGORITHM_EXCEPTION_H

#include <setjmp.h>

extern jmp_buf e_env;

#define try  int __e_code = setjmp(e_env); if (__e_code == 0)
#define catch(__cache_e_code) else if (__e_code == __cache_e_code)
#define throw(e) longjmp(e_env, e)

#define UNSUPPORTED_OPTIONAL -16

#define INDEX_OUT_OF_BOUNDS -32

#endif //C_ALGORITHM_EXCEPTION_H
