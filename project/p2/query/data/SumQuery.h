//
// Created by liuyuelin on 10/21/20.
//

#ifndef PGROUP_04_SUMQUERY_H
#define PGROUP_04_SUMQUERY_H
#include "../Query.h"

class SumQuery : public ComplexQuery {
    static constexpr const char *qname = "SUM";
public:
    using ComplexQuery::ComplexQuery;

    QueryResult::Ptr execute() override;

    std::string toString() override;
};
#endif //PGROUP_04_SUMQUERY_H
