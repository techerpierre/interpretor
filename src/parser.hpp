#ifndef __PARSER__H__
#define __PARSER__H__

#include <vector>
#include <memory>
#include <map>
#include "token.hpp"
#include "ast.hpp"

namespace parser {

using namespace ast;
using namespace token;

const std::map<TokenKind, BinaryExpOperator> BinaryExprOperatorsMap = {
    {TokenKind::ADD, BinaryExpOperator::ADD},
    {TokenKind::SUB, BinaryExpOperator::SUB},
    {TokenKind::MUL, BinaryExpOperator::MUL},
    {TokenKind::TRUE_DIV, BinaryExpOperator::TRUE_DIV},
    {TokenKind::POW, BinaryExpOperator::POW}
};

const std::map<TokenKind, UnaryExpOperator> UnaryExprOperatorsMap = {
    {TokenKind::ADD, UnaryExpOperator::ADD},
    {TokenKind::SUB, UnaryExpOperator::SUB},
};

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

std::unique_ptr<Program> parse(const std::vector<Token>& tokens);

}


#endif // __PARSER__H__