#include <iostream>
#include <string>
#include "interpreter.hpp"

int main(void) {
    //const std::string code = "2 * 2 + 3 * (2 + 3)"; // = 19
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