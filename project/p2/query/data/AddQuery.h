//
// Created by liuyuelin on 10/21/20.
//

#ifndef PGROUP_04_ADDQUERY_H
#define PGROUP_04_ADDQUERY_H
#include "../Query.h"

class AddQuery : public ComplexQuery {
    static constexpr const char *qname = "ADD";
public:
    using ComplexQuery::ComplexQuery;

    QueryResult::Ptr execute() override;

    std::string toString() override;
};
#endif //PGROUP_04_ADDQUERY_H
