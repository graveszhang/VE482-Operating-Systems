//
// Created by liuyuelin on 10/21/20.
//

#include "AddQuery.h"
#include "../../db/Database.h"

constexpr const char *AddQuery::qname;

QueryResult::Ptr AddQuery::execute() {
    using namespace std;
    if (this->operands.size() < 2)
        return make_unique<ErrorMsgResult>(
                qname, this->targetTable.c_str(),
                "Invalid number of operands (? operands)."_f % operands.size()
        );
    Database &db = Database::getInstance();
    Table::SizeType counter = 0;
    try {
        auto &table = db[this->targetTable];
        auto result = initCondition(table);
        if (result.second) {
            for (auto it = table.begin(); it != table.end(); ++it) {
                long long sum = it->get(operands[0]);
                if (this->evalCondition(*it)) {
                    for (unsigned i = 1; i < operands.size() - 1; i++) {
                        sum += it->get(operands[i]);
                    }
                    (*it)[operands[operands.size() - 1]] = sum;
                    ++counter;
                }
            }
        }
        return make_unique<RecordCountResult>(counter);
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

std::string AddQuery::toString() {
    return "QUERY = ADD " + this->targetTable + "\"";
}
