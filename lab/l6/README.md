> Name: Liqin Zhang
>
> UID: 517370910123

# VE482 Lab6

## Zathura-txt

### Usage

```shell
 $ cd zathura-txt
 $ mkdir build
 $ meson build
 $ cd build
 $ ninja
 $ ninja install
```

### Implementation

The implementation of zathura-txt plugin is based on the modification of Zathura-CB.

First, I include the ```plugin-api.h``` to load ```zathura_document_t``` and ```zathura_page_t``` and other necessary head files. Next, I register my ```zathura-txt``` in ```ZATHURA_PLUGIN_REGISTER```.

```c
ZATHURA_PLUGIN_REGISTER_WITH_FUNCTIONS(
  "txt",
  VERSION_MAJOR,
  VERSION_MINOR,
  VERSION_REV,
  ZATHURA_PLUGIN_FUNCTIONS({
    .document_open            = txt_document_open,
    .document_free            = txt_document_free,
    .document_index_generate  = txt_document_index_generate,
    .page_init                = txt_page_init,
    .page_clear               = txt_page_clear,
    .page_render_cairo        = txt_page_render_cairo
  }),
  ZATHURA_PLUGIN_MIMETYPES({
    "application/x-cbr",
    "application/x-rar",
    "application/x-cbz",
    "application/zip",
    "application/x-cb7",
    "application/x-7z-compressed",
    "application/x-cbt",
    "application/x-tar"
  })
)
```

All the functions to initializing the pages as well as open the documents are implemented in ```document.c``` and ```page.c```.

## Linked-Filetype

### CSV-plugin Implementation

Given the sample input for example, we have

```csv
rand_int,rand_double,inc_char*
abc=123,bfc=43.5786,aa=cat
asda=54,sdfs=654.1,poi=dog
poqq=3,qa=0.12313,qkm=fish
```

In the ```linked-csv.c```, I implemented my plugin to support reading csv, the API should be the same as for implementing other filetypes, which is defined as ```fileInType```, in case there is need to support other file types.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked-csv.h"

const char* getfield(char* line, int num)
{
    const char* tok;
    for (tok = strtok(line, ",");
         tok && *tok;
         tok = strtok(NULL, ",\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}

void fileInType(){ // General API for multi-filetypes support
    FILE* stream = fopen("input", "r");
    char* data1[64];
    char* data2[64];
    char* data3[64];
    char line[1024];
    int i = 0, j = 0, k = 0;
    while (fgets(line, 1024, stream))
    {
        char* tmp = strdup(line);
        data[i] = getfield(tmp, 1);
        data[j] = getfield(tmp, 2);
        data[k] = getfield(tmp, 3);
        i += 1;
        j += 1;
        k += 1;
        free(tmp);
    }
}
```

### Plugin Structure overview

I designed and implemented my plugin system, which could handle all file-types strictly according to the formal way as follows.

#### Discovering

First, when compiling the program, one has to specify the filetype, such that the handler could have access to the specified ```.so``` library. 

```c
  char filetype[100];
    scanf("%s", &filetype)
    void *handle;
    dll p;
    void (*init)(dll *p);

    handle = dlopen(filetype, RTLD_LAZY);
```

#### Registering

As is the multi-file type support is defined uniformly as ```fileInType```, I've also declared the ```dll``` class to register all the plugin potentially discovered by the main program. Another approach is to define the plugin in ```xml``` file for easy configuration, this could later be parsed by ```libxml2```.

```xml
<plugins>
    <plugin name="linked-csv">
        <library path="./csv.so">
        </library>
        <entry name="csv">
        </entry>
    </plugin>
</plugins>
```

```
typedef struct _plugin{
    char name[64];
    char path[256];
    char entry[128];
}dll;
```

#### Hooking

In order to attach the plugin to the program, ```dlsym``` can be used to load ```fileInType``` in ```csv```.

```
fildInType = dlsym(handle, "fileInType");
if( NULL == fildInType) {
    printf("%s\n", dlerror());
    exit(1);
}
```

#### Exposing

The ```.so``` libraries can be compiled and linked using 

```shell
gcc -rdynamic -o main.c plugin.h -ldl
gcc -shared -o linked-csv.c plugin.h
```

According to the functions in ```plugin.h```, specific functions will be called for library.