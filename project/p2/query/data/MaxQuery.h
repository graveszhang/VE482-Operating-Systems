//
// Created by liuyuelin on 10/21/20.
//

#ifndef PGROUP_04_MAXQUERY_H
#define PGROUP_04_MAXQUERY_H
#include "../Query.h"

class MaxQuery : public ComplexQuery {
    static constexpr const char *qname = "MAX";
public:
    using ComplexQuery::ComplexQuery;

    QueryResult::Ptr execute() override;

    std::string toString() override;
};
#endif //PGROUP_04_MAXQUERY_H
