//
// Created by liuyuelin on 11/9/20.
//

#include <fstream>
#include "Listen.h"
#include "iostream"
#include "../db/Database.h"
#include "QueryResult.h"
#include <thread>
#include "QueryBuilders.h"
#include "QueryParser.h"
constexpr const char *ListenQuery::qname;

//void read (std::istream is) {
//    QueryParser p;
//
//    p.registerQueryBuilder(std::make_unique<QueryBuilder(Debug)>());
//    p.registerQueryBuilder(std::make_unique<QueryBuilder(ManageTable)>());
//    p.registerQueryBuilder(std::make_unique<QueryBuilder(Complex)>());
//    while (is) {
//        try {
//// A very standard REPL
//// REPL: Read-Evaluate-Print-Loop
////            if (parsedArgs.threads > 0){
////                parsedArgs.threads--;
////                std::thread t;
////            }
//            std::string queryStr = extractQueryString(is);
//            Query::Ptr query = p.parseQuery(queryStr);
//            if (query->toString() == "QUERY = Quit") {
//                threads.stop();
//                query->execute();
//            } else {
//                threads.getTask(std::move(query));
//            }
//        } catch (const std::ios_base::failure &e) {
//            threads.stop();
//            break;
//        } catch (const std::exception &e) {
//            std::cout.flush();
//            std::cerr << e.what() << std::endl;
//        }
//    }
//}

QueryResult::Ptr ListenQuery::execute() {
    using namespace std;
    try {
//        fstream fin;
//            fin.open(this->dir);
//            if (!fin.is_open()) {
//                return make_unique<ErrorMsgResult>(qname, "Cannot open file '?'"_f % this->dir);
//            }
//            istream is(fin.rdbuf());
//            fin.close();
        return make_unique<ListenMsgResult>(qname, this->dir);
    }
    catch (const TableNameNotFound &e) {
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

std::string ListenQuery::toString() {
    return "QUERY = LISTEN " + this->targetTable + "\"";
}
