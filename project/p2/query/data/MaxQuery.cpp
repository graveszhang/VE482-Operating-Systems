//
// Created by liuyuelin on 10/21/20.
//

#include "MaxQuery.h"
#include "../../db/Database.h"
#include <iostream>
#include <climits>

constexpr const char *MaxQuery::qname;

QueryResult::Ptr MaxQuery::execute() {
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
        vector<long long> max(rowNum, LONG_LONG_MIN);
        if (result.second) {
            for (auto it = table.begin(); it != table.end(); ++it) {
                if (this->evalCondition(*it)) {
                    for (unsigned i = 0; i < rowNum; i++) {
                        auto value = it->get(operands[i]);
                        max[i] = value > max[i] ? value : max[i];
                    }
                }
            }
            if (max[0] != LONG_LONG_MIN) {
                output += "ANSWER = ( ";
                for (long long i : max) {
                    output +=  to_string(i) + " ";
                }
                output += ")\n" ;
            }
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

std::string MaxQuery::toString() {
    return "QUERY = MAX " + this->targetTable + "\"";
}
