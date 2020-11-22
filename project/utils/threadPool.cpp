//
// Created by liuyuelin on 11/2/20.
//

#include "threadPool.h"

extern bool W_Waiting;
extern bool R_Waiting;

void threadPool::stop() {
    while (!queries.empty());
    for (unsigned i = 1; i <= this->counter; i++) {
        std::cout << i << "\n" << std::flush;
        if (this->output[i])
            std::cout << *output[i] << std::flush;
    }
    this->stopped = true;
    for (unsigned i = 0; i < threadAvai; i++) {
        this->pool[i].join();
    }
}


void threadPool::execute(Query::Ptr query, unsigned count) {
    auto q = query->toString();
    if (!(q.find("SELECT") == std::string::npos && q.find("SUM") == std::string::npos &&
          q.find("COUNT") == std::string::npos &&
          q.find("MAX") == std::string::npos && q.find("MIN") == std::string::npos))
        read_lock();
    QueryResult::Ptr result = query->execute();

    if (this->output.size() <= count)
        this->output.resize(2 * count);
    if (result->success()) {
        if (result->display()) {
            this->output[count] = std::move(result);
        } else {
            this->output[count] = nullptr;
#ifndef NDEBUG
            std::cout.flush();
            std::cerr << *result;
#endif
        }
    } else {
        std::cout.flush();
        std::cerr << "QUERY FAILED:\n\t" << *result;
    }
    if (q.find("SELECT") == std::string::npos && q.find("SUM") == std::string::npos &&
        q.find("COUNT") == std::string::npos &&
        q.find("MAX") == std::string::npos && q.find("MIN") == std::string::npos)
        write_unlock();
    else
        read_unlock();
}

void threadPool::run() {
    while (!this->stopped) {
        qMutex.lock();
        if (queries.empty() && !this->stopped) {
            qMutex.unlock();
            continue;
        }
        if (this->stopped) {
            qMutex.unlock();
            return;
        }
        auto query = std::move(this->queries.front());
        queries.pop();
        unsigned c = ++this->counter;
        std::string q = query->toString();
        if (q.find("SELECT") == std::string::npos && q.find("SUM") == std::string::npos &&
            q.find("COUNT") == std::string::npos &&
            q.find("MAX") == std::string::npos && q.find("MIN") == std::string::npos) {
            while (W_Waiting || R_Waiting);
            write_lock();
        }
        qMutex.unlock();
        execute(std::move(query), c);
    }
}

void threadPool::getTask(Query::Ptr ptr) {
    queries.push(std::move(ptr));
}

threadPool::threadPool(unsigned threadNum) : threadAvai(threadNum > 1 ? threadNum : 1), counter(0), stopped(false) {
    for (unsigned i = 0; i < threadAvai; i++) {
        this->pool.emplace_back(std::thread(&threadPool::run, this));
    }
}