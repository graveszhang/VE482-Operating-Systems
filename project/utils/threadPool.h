//
// Created by liuyuelin on 11/2/20.
//

#ifndef PGROUP_04_THREADPOOL_H
#define PGROUP_04_THREADPOOL_H

#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <iostream>
#include <string>
#include "../query/QueryParser.h"


class threadPool{
    unsigned threadAvai; // avalable thread number
    std::vector<std::thread> pool;
    std::queue<Query::Ptr> queries;
    std::mutex dbMutex;
    std::mutex qMutex;
    size_t counter;
    bool stopped;
    std::vector<QueryResult::Ptr> output;
    void execute(Query::Ptr query, unsigned count);
public:
    explicit threadPool(unsigned threadNum);
    void getTask(Query::Ptr);
    void run();
    void stop();
};

#endif //PGROUP_04_THREADPOOL_H
