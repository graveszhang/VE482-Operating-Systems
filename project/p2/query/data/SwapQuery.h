//
// Created by liuyuelin on 10/21/20.
//

#ifndef PGROUP_04_SWAPQUERY_H
#define PGROUP_04_SWAPQUERY_H
#include "../Query.h"

class SwapQuery : public ComplexQuery {
    static constexpr const char *qname = "SWAP";
public:
    using ComplexQuery::ComplexQuery;

    QueryResult::Ptr execute() override;

    std::string toString() override;
};
#endif //PGROUP_04_SWAPQUERY_H
