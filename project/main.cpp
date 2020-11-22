//
// Created by liu on 18-10-21.
//

#include "query/QueryParser.h"
#include "query/QueryBuilders.h"
#include "utils/threadPool.h"

#include <getopt.h>
#include <fstream>
#include <iostream>
#include <string>
#include <stack>


struct {
    std::string listen;
    long threads = 0;
} parsedArgs;

void parseArgs(int argc, char *argv[]) {
    const option longOpts[] = {
            {"listen",  required_argument, nullptr, 'l'},
            {"threads", required_argument, nullptr, 't'},
            {nullptr,   no_argument,       nullptr, 0}
    };
    const char *shortOpts = "l:t:";
    int opt, longIndex;
    while ((opt = getopt_long(argc, argv, shortOpts, longOpts, &longIndex)) != -1) {
        if (opt == 'l') {
            parsedArgs.listen = optarg;
        } else if (opt == 't') {
            parsedArgs.threads = std::strtol(optarg, nullptr, 10);
        } else {
            std::cerr << "lemondb: warning: unknown argument " << longOpts[longIndex].name << std::endl;
        }
    }
}

std::string extractQueryString(std::istream &is) {
    std::string buf;
    do {
        int ch = is.get();
        if (ch == ';') return buf;
        if (ch == EOF) throw std::ios_base::failure("End of input");
        buf.push_back((char) ch);
    } while (true);
}

int main(int argc, char *argv[]) {
    // Assume only C++ style I/O is used in lemondb
    // Do not use printf/fprintf in <cstdio> with this line
    std::ios_base::sync_with_stdio(false);

    // check where dir is
    /*
    char *buffer;
    if((buffer = getcwd(NULL, 0)) == NULL)
    {
        perror("getcwd error");
    }
    else
    {
        printf("%s\n", buffer);
        free(buffer);
    }
    */
    parseArgs(argc, argv);

    std::fstream fin;
    if (!parsedArgs.listen.empty()) {
        fin.open(parsedArgs.listen);
        if (!fin.is_open()) {
            std::cerr << "lemondb: error: " << parsedArgs.listen << ": no such file or directory" << std::endl;
            exit(-1);
        }
    }
    std::istream is(fin.rdbuf());

#ifdef NDEBUG
    // In production mode, listen argument must be defined
    if (parsedArgs.listen.empty()) {
        std::cerr << "lemondb: error: --listen argument not found, not allowed in production mode" << std::endl;
        exit(-1);
    }
#else
    // In debug mode, use stdin as input if no listen file is found
    if (parsedArgs.listen.empty()) {
        std::cerr << "lemondb: warning: --listen argument not found, use stdin instead in debug mode" << std::endl;
        is.rdbuf(std::cin.rdbuf());
    }
#endif

    if (parsedArgs.threads < 0) {
        std::cerr << "lemondb: error: threads num can not be negative value " << parsedArgs.threads << std::endl;
        exit(-1);
    } else if (parsedArgs.threads == 0) {
        parsedArgs.threads = std::thread::hardware_concurrency();
        std::cerr << "lemondb: info: auto detect thread num" << ": " << parsedArgs.threads << std::endl;
    } else {
        std::cerr << "lemondb: info: running in " << parsedArgs.threads << " threads" << std::endl;
    }

    QueryParser p;

    p.registerQueryBuilder(std::make_unique<QueryBuilder(Debug)>());
    p.registerQueryBuilder(std::make_unique<QueryBuilder(ManageTable)>());
    p.registerQueryBuilder(std::make_unique<QueryBuilder(Complex)>());

    class threadPool threads(parsedArgs.threads - 1);

    unsigned listening = 0;
    std::stack<std::string> files;
    std::stack<unsigned> rowNum;
    unsigned counter = 0; // counter for multiple listen
    while (is) {
        try {
            counter++;
            std::string queryStr = extractQueryString(is);
            Query::Ptr query = p.parseQuery(queryStr);
            if (query->toString().find("LISTEN") != std::string::npos) {
                std::string filename = query->execute()->info();
                fin.close();
                fin.open(filename);
                if (!fin.is_open()) {
                    std::cerr << "Cannot open file " << filename << std::endl;
                }
                is.rdbuf(fin.rdbuf());
                listening++;
                files.push(filename);
                rowNum.push(counter);
                counter = 0;
            }
            if (query->toString() == "QUERY = Quit") {
                threads.stop();
                query->execute();
            } else {
                threads.getTask(std::move(query));
            }
        } catch (const std::ios_base::failure &e) {
            if (listening > 0) {
                listening--;
                if (rowNum.size() == 1) {
                    if (!parsedArgs.listen.empty()) {
                        unsigned count = rowNum.top();
                        rowNum.pop();
                        files.pop();
                        fin.close();
                        fin.open(parsedArgs.listen);
                        if (!fin.is_open()) {
                            std::cerr << "lemondb: error: " << parsedArgs.listen << ": no such file or directory"
                                      << std::endl;
                            exit(-1);
                        }
                        is.rdbuf(fin.rdbuf());
                        while (count > 0) {
                            extractQueryString(is);
                            count--;
                        }
                    } else {
                        is.rdbuf(std::cin.rdbuf());
                    }
                } else {
                    files.pop();
                    unsigned count = rowNum.top();
                    std::string name = files.top();
                    rowNum.pop();
                    fin.close();
                    fin.open(name);
                    if (!fin.is_open()) {
                        std::cerr << "lemondb: error: " << parsedArgs.listen << ": no such file or directory"
                                  << std::endl;
                        exit(-1);
                    }
                    is.rdbuf(fin.rdbuf());
                    while (count > 0) {
                        extractQueryString(is);
                        count--;
                    }
                }
                continue;
            }
            threads.stop();
            break;
        } catch (const std::exception &e) {
            std::cout.flush();
            std::cerr << e.what() << std::endl;
        }
    }
    return 0;
}