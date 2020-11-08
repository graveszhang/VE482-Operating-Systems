//
// Created by grave on 2020/11/8.
//

#ifndef L6_PLUGIN_H
#define L6_PLUGIN_H

typedef struct _plugin{
    char name[64];
    char path[256];
    char entry[128];
}dll;

#endif //L6_PLUGIN_H
