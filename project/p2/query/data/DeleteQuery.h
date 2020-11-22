//
// Created by liuyuelin on 10/20/20.
//

#ifndef PGROUP_04_DELETEQUERY_H
#define PGROUP_04_DELETEQUERY_H
#include "../Query.h"

class DeleteQuery : public ComplexQuery {
    static constexpr const char *qname = "DELETE";
public:
    using ComplexQuery::ComplexQuery;

    QueryResult::Ptr execute() override;

    std::string toString() override;
};
#endif //PGROUP_04_DELETEQUERY_H
