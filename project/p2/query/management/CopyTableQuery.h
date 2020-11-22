//
// Created by liuyuelin on 10/29/20.
//

#ifndef P2_COPYTABLEQUERY_H
#define P2_COPYTABLEQUERY_H
#include "../Query.h"

class CopyTableQuery : public Query {
    static constexpr const char *qname = "COPY";
    const std::string fileName;
public:
    explicit CopyTableQuery(std::string table, std::string fileName) :
    Query(std::move(table)), fileName(std::move(fileName)) {}

    QueryResult::Ptr execute() override;

    std::string toString() override;
};
#endif //P2_COPYTABLEQUERY_H
