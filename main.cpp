#include <iostream>

#include "node.h"
#include "Reader.h"

int main() {
    // main REPL loop
    std::string input;

    std::cout << "> ";
    while(std::getline(std::cin, input)) {
        try {
            auto output = clojure::Read(input);
            std::cout << output << std::endl;
        } catch (const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
        }
        std::cout << "> ";
    }

    return 0;
}
