//
// Created by liuyuelin on 10/21/20.
//

#ifndef PGROUP_04_MINQUERY_H
#define PGROUP_04_MINQUERY_H
#include "../Query.h"

class MinQuery : public ComplexQuery {
    static constexpr const char *qname = "MIN";
public:
    using ComplexQuery::ComplexQuery;

    QueryResult::Ptr execute() override;

    std::string toString() override;
};
#endif //PGROUP_04_MINQUERY_H
