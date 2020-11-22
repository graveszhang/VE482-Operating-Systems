//
// Created by liuyuelin on 11/21/20.
//

#ifndef PGROUP_04_R_W_MUTEX_H
#define PGROUP_04_R_W_MUTEX_H

#include <mutex>


static std::mutex db_lock;
static std::mutex count_lock;

void write_unlock();

void write_lock();

void read_unlock();

void read_lock();

#endif //PGROUP_04_R_W_MUTEX_H
