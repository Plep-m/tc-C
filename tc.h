#ifndef TC_H
#define TC_H

#include <stdio.h>
#include <setjmp.h>
#include <string.h>

typedef struct {
    int code;
    char message[256];
} Exception;

static jmp_buf global_env;
static Exception global_exception;

#define throw(error_code, error_message) \
    do { \
        global_exception.code = (error_code); \
        snprintf(global_exception.message, sizeof(global_exception.message), "%s", error_message); \
        longjmp(global_env, 1); \
    } while (0)

#define try if (!setjmp(global_env))

int is_in_list(int code, int* codes, int length) {
    for (int i = 0; i < length; i++) {
        if (codes[i] == code) {
            return 1;
        }
    }
    return 0;
}

#define IS_IN_LIST(code, ...) \
    (is_in_list((code), (int[]){__VA_ARGS__}, sizeof((int[]){__VA_ARGS__}) / sizeof(int)))

#define catch(name, ...) \
    else if (IS_IN_LIST(global_exception.code, __VA_ARGS__)) \
        for (Exception* name = &global_exception; name != NULL; name = NULL)

#define otherwise else

#endif
