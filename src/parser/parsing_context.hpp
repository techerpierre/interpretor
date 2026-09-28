#ifndef __PARSER_CONTEXT__H__
#define __PARSER_CONTEXT__H__

#include <vector>
#include "../lexer/token.hpp"

namespace parser {

using namespace token;

class ParsingContext {
private:
    size_t m_Cursor;
    const std::vector<Token>& m_Tokens;
public:
    ParsingContext(const std::vector<Token>& tokens);

    bool IsEnd(size_t offset = 0) const;
    bool Eat(const std::vector<TokenKind>& expected);
    const Token& EatOrFail(const std::vector<TokenKind>& expected, const char* errorMessage);
    bool CheckType(const std::vector<TokenKind>& expected);
    const Token& Peek(size_t offset = 0) const;
    const Token& Advance(size_t offset = 1);
    const Token& Previous(size_t offset = 1);
};

}

#endif // __PARSER_CONTEXT__H__