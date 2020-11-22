//
// Created by liuyuelin on 10/29/20.
//

#ifndef P2_TRUNCATETABLEQUERY_H
#define P2_TRUNCATETABLEQUERY_H

#include "../Query.h"

class TruncateTableQuery : public Query {
    static constexpr const char *qname = "TRUNCATE";
public:
    using Query::Query;

    QueryResult::Ptr execute() override;

    std::string toString() override;
};


#endif //P2_TRUNCATETABLEQUERY_H
