//
// Created by liuyuelin on 10/21/20.
//

#include "CountQuery.h"
#include "../../db/Database.h"
#include <iostream>

constexpr const char *CountQuery::qname;

QueryResult::Ptr CountQuery::execute() {
    using namespace std;
    string output;
    if (!this->operands.empty())
        return make_unique<ErrorMsgResult>(
                qname, this->targetTable.c_str(),
                "Invalid number of operands (? operands)."_f % operands.size()
        );
    Database &db = Database::getInstance();
    try {
        auto &table = db[this->targetTable];
        auto result = initCondition(table);
        unsigned long long count = 0;
        if (result.second) {
            for (auto it : table) {
                if (this->evalCondition(it)) {
                    count += 1;
                }

            }
            output =  "ANSWER = " + to_string(count)  + "\n";
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

std::string CountQuery::toString() {
    return "QUERY = COUNT " + this->targetTable + "\"";
}