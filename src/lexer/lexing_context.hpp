#ifndef __LEXING_CONTEXT__H__
#define __LEXING_CONTEXT__H__

#include <string>
#include <memory>
#include <vector>
#include "token.hpp"

using namespace token;

namespace lexer {

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

}

#endif // __LEXING_CONTEXT__H__