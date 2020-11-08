//
// Created by grave on 2020/11/8.
//

#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include "plugin.h"

int main(int argc, char *argv[]) {
    char filetype[100];
    scanf("%s", &filetype)
    void *handle;
    dll p;
    void (*init)(dll *p);

    handle = dlopen(filetype, RTLD_LAZY);
    char *error_msg;
    error_msg = dlerror();

    if (error_msg) {
       exit(1);
    }

    if( NULL == handle) {
        printf("%s\n", dlerror());
        exit(1);
    }

    fildInType = dlsym(handle, "fileInType");
    if( NULL == fildInType) {
        printf("%s\n", dlerror());
        exit(1);
    }

    fileInType(&p);

    return 0;
}