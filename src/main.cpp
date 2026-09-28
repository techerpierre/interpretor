#include <iostream>
#include <string>
#include "interpreter/interpreter.hpp"

int main(void) {
    std::string code;
    std::cout << "> "; 

    while (std::getline(std::cin, code)) {
        if (code.empty()) {
            std::cout << "> "; 
            continue;
        }
        interpreter::interpret(code);
        std::cout << "> "; 
    }

    return 0;
}