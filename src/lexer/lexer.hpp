#ifndef __LEXER__H__
#define __LEXER__H__

#include <string>
#include <utility>
#include <memory>
#include <vector>
#include "token.hpp"
#include "../core/position.hpp"

namespace lexer {

using namespace token;

const std::vector<std::pair<std::string, TokenKind>> ReservedSymbols = {
    {"**", TokenKind::POW},
    {"+", TokenKind::ADD},
    {"-", TokenKind::SUB},
    {"*", TokenKind::MUL},
    {"/", TokenKind::TRUE_DIV},
    {"(", TokenKind::OPEN_PAR},
    {")", TokenKind::CLOSE_PAR},
    {"{", TokenKind::OPEN_BRACE},
    {"}", TokenKind::CLOSE_BRACE}
};

struct LexingError {
    Position pos;
    std::string message;
};

std::unique_ptr<std::vector<Token>> lex(const std::string& source);

}

#endif // __LEXER__H__