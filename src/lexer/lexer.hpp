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

class LexingContext {
private:
    size_t m_Line;
    size_t m_Cursor;
    size_t m_Start;
    size_t m_LastLine;

    std::unique_ptr<std::vector<Token>> m_Tokens;
    std::string m_Source;
public:
    LexingContext(const std::string& source);

    bool IsEnd(void) const;
    char Peek(size_t offset = 0) const;
    bool Match(std::string expected);
    char Advance(void);
    void StartTurn(void);
    void SkipEmpty(void);
    Position Position(void) const;
    void PushToken(TokenKind kind, const std::string& text = "");
    std::unique_ptr<std::vector<Token>> MoveTokens(void);
};

std::unique_ptr<std::vector<token::Token>> lex(const std::string& source);

}

#endif // __LEXER__H__