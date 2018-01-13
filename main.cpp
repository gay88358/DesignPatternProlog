#include <string>
#include <iostream>

using std::string;
#include "./include/scanner.h"
#include "./include/parser.h"

void printBanner(string &query) {
    query.clear();
    std::cout << "?- ";
}

void printWraps() {
    std::cout << "|    ";
}

void prologing(string query) {
    try {
        Scanner scanner(query);
        Parser parser(scanner);
        parser.buildExpression();
        std::cout << parser.getResult() << std::endl << std::endl;
    } catch (std::string& msg) {
        std::cout << "\033[1;31m" << msg << "\033[0m" << std::endl
                  << std::endl;
    } catch (...) {
        std::cout << "\033[1;31munexpected exception\033[0m" << std::endl
                  << std::endl;
    }
}

void input(string &query, string &buffer) {
    while (std::getline(std::cin, buffer)) {
        query += buffer;
        if (query.empty()) break;
        if (buffer.back() == '.') {
            break;
        }
        printWraps();
    }
}

int main() {
    string query;
    string buffer;
    while (true) {
        printBanner(query);
        input(query, buffer);
        if (query.empty()) continue;
        if (query == "halt.") 
            break;
        prologing(query);
    }
    return 0;
}