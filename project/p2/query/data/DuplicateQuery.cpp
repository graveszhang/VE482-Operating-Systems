//
// Created by liuyuelin on 10/21/20.
//

#include "DuplicateQuery.h"
#include "../../db/Database.h"

constexpr const char *DuplicateQuery::qname;

QueryResult::Ptr DuplicateQuery::execute() {
    using namespace std;
    if (!this->operands.empty())
        return make_unique<ErrorMsgResult>(
                qname, this->targetTable.c_str(),
                "Invalid number of operands (? operands)."_f % operands.size()
        );
    Database &db = Database::getInstance();
    Table::SizeType counter = 0;
    vector<Table::Iterator> its;

    try {
        auto &table = db[this->targetTable];
        auto result = initCondition(table);
        vector<Table::ValueType> data;
        if (result.second) {
            if (!result.first.empty()) {
                auto end = table.end();
                auto it = table.getValueByIndex(result.first);
                if (it != end) {
                    if (table.Duplicate(it)) {
                        table.Duplicate_helper();
                        ++counter;
                    }
                }
            } else {
                auto end = table.end();
                for (auto it = table.begin(); it != end; ++it) {
                    if (this->evalCondition(*it)) {
                        if (table.Duplicate(it))
                            ++counter;
                    }
                }
                table.Duplicate_helper();
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

std::string DuplicateQuery::toString() {
    return "QUERY = DUPLICATE " + this->targetTable + "\"";
}
