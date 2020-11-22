//
// Created by liuyuelin on 10/20/20.
//

#ifndef PGROUP_04_SELECTQUERY_H
#define PGROUP_04_SELECTQUERY_H
#include "../Query.h"

class SelectQuery : public ComplexQuery {
    static constexpr const char *qname = "SELECT";
public:
    using ComplexQuery::ComplexQuery;

    QueryResult::Ptr execute() override;

    std::string toString() override;
};
#endif //PGROUP_04_SELECTQUERY_H
