//
// Created by liuyuelin on 10/20/20.
//

#include "SelectQuery.h"
#include "../../db/Database.h"
#include <iostream>

constexpr const char *SelectQuery::qname;

QueryResult::Ptr SelectQuery::execute() {
    using namespace std;
    string output;
    if (this->operands.empty())
        return make_unique<ErrorMsgResult>(
                qname, this->targetTable.c_str(),
                "Invalid number of operands (? operands)."_f % operands.size()
        );
    Database &db = Database::getInstance();
    try {
        auto &table = db[this->targetTable];
        auto result = initCondition(table);
        vector<string> rows;
        if (result.second) {
            for (auto it = table.begin(); it != table.end(); ++it) {
                if (this->evalCondition(*it)) {
                    std::string row;
                    for (unsigned i = 0; i < operands.size(); i++) {
                        if (operands[i] == "KEY") {
                            row += (*it).key();
                        } else {
                            row += std::to_string((*it)[table.getFieldIndex(operands[i])]);
                        }
                        row += " ";
                    }
                    if (rows.empty()) {
                        rows.emplace_back(row);
                    } else {
                        for (unsigned i = 0; i < rows.size(); i++) {
                            if (row < rows[i]) {
                                rows.insert(rows.begin() + i, row);
                                break;
                            } else if (i == rows.size() - 1) {
                                rows.emplace_back(row);
                                break;
                            }
                        }
                    }
                }

            }
            for (auto &row : rows) {
                output += "( " + row + ")" + "\n";
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

std::string SelectQuery::toString() {
    return "QUERY = SELECT " + this->targetTable + "\"";
}
