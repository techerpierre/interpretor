#ifndef __PARSER__H__
#define __PARSER__H__

#include <vector>
#include <memory>
#include <map>
#include "../lexer/token.hpp"
#include "../ast/ast.hpp"
#include "parsing_context.hpp"

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

std::unique_ptr<Program> parse(const std::vector<Token>& tokens);

}


#endif // __PARSER__H__