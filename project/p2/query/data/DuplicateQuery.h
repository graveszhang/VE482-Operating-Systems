//
// Created by liuyuelin on 10/21/20.
//

#ifndef PGROUP_04_DUPLICATEQUERY_H
#define PGROUP_04_DUPLICATEQUERY_H
#include "../Query.h"

class DuplicateQuery : public ComplexQuery {
    static constexpr const char *qname = "DUPLICATE";
public:
    using ComplexQuery::ComplexQuery;

    QueryResult::Ptr execute() override;

    std::string toString() override;
};
#endif //PGROUP_04_DUPLICATEQUERY_H
