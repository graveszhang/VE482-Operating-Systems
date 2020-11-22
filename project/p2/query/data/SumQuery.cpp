//
// Created by liuyuelin on 10/21/20.
//

#include "SumQuery.h"
#include "../../db/Database.h"
#include <iostream>

constexpr const char *SumQuery::qname;

QueryResult::Ptr SumQuery::execute() {
    using namespace std;
    string output;
    unsigned rowNum = this->operands.size();
    if (rowNum == 0)
        return make_unique<ErrorMsgResult>(
                qname, this->targetTable.c_str(),
                "Invalid number of operands (? operands)."_f % operands.size()
        );
    Database &db = Database::getInstance();
    try {
        auto &table = db[this->targetTable];
        auto result = initCondition(table);
        vector<long long> sums(rowNum, 0);
        if (result.second) {
            for (auto it = table.begin(); it != table.end(); ++it) {
                if (this->evalCondition(*it)) {
                    for (unsigned i = 0; i < rowNum; i++) {
                        sums[i] += it->get(operands[i]);
                    }
                }

            }
            output += "ANSWER = ( ";
            for (long long sum : sums) {
                output += to_string(sum) + " ";
            }
            output += ")\n";
        }
        return std::make_unique<DisplayResult>(output);
    } catch (const TableNameNotFound &e) {
        return make_unique<ErrorMsgResult>(qname, this->targetTable, "No such table."s);
    } catch (const IllFormedQueryCondition &e) {
        return make_unique<ErrorMsgResult>(qname, this->targetTable, e.what());
    } catch (const invalid_argument &e) {
        // Cannot convert operand to string
        return make_unique<ErrorMsgResult>(qname, this->targetTable, "Unknown error '?'"_f % e.what());
    } catch (const exception &e) {
        return make_unique<ErrorMsgResult>(qname, this->targetTable, "Unkonwn error '?'."_f % e.what());
    }

}

std::string SumQuery::toString() {
    return "QUERY = SUM " + this->targetTable + "\"";
}
