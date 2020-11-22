//
// Created by liuyuelin on 11/9/20.
//

#ifndef PGROUP_04_LISTEN_H
#define PGROUP_04_LISTEN_H
#include "Query.h"

class ListenQuery : public Query {
    static constexpr const char *qname = "LISTEN";

public:
    explicit ListenQuery (std::string filename):dir(std::move(filename)){}

    const std::string dir;

    QueryResult::Ptr execute() override;

    std::string toString() override;
};

#endif //PGROUP_04_LISTEN_H
