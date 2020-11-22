//
// Created by liuyuelin on 10/21/20.
//

#ifndef PGROUP_04_SUBQUERY_H
#define PGROUP_04_SUBQUERY_H
#include "../Query.h"

class SubQuery : public ComplexQuery {
    static constexpr const char *qname = "SUB";
public:
    using ComplexQuery::ComplexQuery;

    QueryResult::Ptr execute() override;

    std::string toString() override;
};
#endif //PGROUP_04_SUBQUERY_H
