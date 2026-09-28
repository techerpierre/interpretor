#include "parsing_context.hpp"
#include <algorithm>
#include "../core/error.hpp"

using namespace parser;

ParsingContext::ParsingContext(const std::vector<Token>& tokens)
    : m_Cursor(0),
    m_Tokens(tokens) {}

bool ParsingContext::IsEnd(size_t offset) const {
    return m_Tokens.size() <= 0 ||
        m_Cursor + offset > m_Tokens.size();
}

bool ParsingContext::Eat(const std::vector<TokenKind>& expected) {
    if (CheckType(expected)) {
        auto t = Advance();
        return true;
    }
    return false;
}

const Token& ParsingContext::EatOrFail(const std::vector<TokenKind>& expected, const char* errorMessage) {
    if (CheckType(expected)) {
        return Advance();
    }
    throw error::ParsingError(errorMessage, Peek().pos);
}

bool ParsingContext::CheckType(const std::vector<TokenKind>& expected) {
    return std::find(expected.begin(), expected.end(), Peek().kind) != expected.end();
}

const Token& ParsingContext::Peek(size_t offset) const {
    return m_Tokens[m_Cursor + offset];
}

const Token& ParsingContext::Advance(size_t offset) {
    if (!IsEnd(offset)) m_Cursor += offset;
    return m_Tokens[m_Cursor - 1];
}

const Token& ParsingContext::Previous(size_t offset) {
    return m_Tokens[m_Cursor - offset];
}
