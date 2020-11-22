//
// Created by liuyuelin on 10/21/20.
//

#ifndef PGROUP_04_COUNTQUERY_H
#define PGROUP_04_COUNTQUERY_H
#include "../Query.h"

class CountQuery : public ComplexQuery {
    static constexpr const char *qname = "COUNT";
public:
    using ComplexQuery::ComplexQuery;

    QueryResult::Ptr execute() override;

    std::string toString() override;
};
#endif //PGROUP_04_COUNTQUERY_H
