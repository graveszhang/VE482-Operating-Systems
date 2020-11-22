//
// Created by liuyuelin on 11/21/20.
//

#include "R_W_Mutex.h"

static unsigned counter = 0;

bool W_Waiting = false;
bool R_Waiting = false;

void write_unlock(){
    W_Waiting = false;
    db_lock.unlock();
}

void write_lock(){
    W_Waiting = true;
    db_lock.lock();
}

void read_unlock(){
    count_lock.lock();
    counter--;
    if (counter == 0) {
        R_Waiting = false;
        db_lock.unlock();
    }
    count_lock.unlock();
}

void read_lock(){
    count_lock.lock();
    if (counter == 0) {
        R_Waiting = true;
        db_lock.lock();
    }
    counter++;
    count_lock.unlock();
}