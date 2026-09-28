#include "lexer.hpp"
#include <cctype>
#include "error.hpp"

using namespace lexer;

LexingContext::LexingContext(const std::string& source)
    : m_Line(1),
    m_Cursor(0),
    m_Start(0),
    m_LastLine(0),
    m_Source(source),
    m_Tokens(std::make_unique<std::vector<Token>>()) {}


bool LexingContext::IsEnd(void) const {
    return m_Cursor >= m_Source.size();
}

char LexingContext::Peek(size_t offset) const {
    if (IsEnd()) return '\0';
    return m_Source[m_Cursor + offset];
}

bool LexingContext::Match(std::string expected) {
    if (IsEnd()) return false;

    for (size_t i = 0; i < expected.size(); i++) {
        if (m_Source[m_Cursor + i] != expected[i]) {
            return false;
        }
    }

    m_Cursor += expected.size();
    return true;
}

char LexingContext::Advance(void) {
    return m_Source[m_Cursor++];
}

void LexingContext::SkipEmpty(void) {
    if (Peek() == '\n') {
        m_LastLine = m_Start;
        m_Line++;
    }
    m_Cursor++;
}

void LexingContext::StartTurn(void) {
    m_Start = m_Cursor;
}

Position LexingContext::Position(void) const {
    return { m_Start, m_Cursor, m_Line };
}

void LexingContext::PushToken(TokenKind kind, const std::string& text) {
    m_Tokens->push_back({ kind, text, Position() });
}

std::unique_ptr<std::vector<Token>> LexingContext::MoveTokens(void) {
    return std::move(m_Tokens);
}

namespace {
    void scanToken(LexingContext& ctx);
    template<typename T>
    bool scanRules(LexingContext& ctx, const std::vector<std::pair<std::string, T>>& rules);
    void scanNumber(LexingContext& ctx);

    void scanToken(LexingContext& ctx) {
        if (isspace(ctx.Peek())) {
            ctx.SkipEmpty();
            return;
        }

        if (scanRules(ctx, ReservedSymbols)) return;

        if (std::isdigit(ctx.Peek())) {
            scanNumber(ctx);
            return;
        }

        throw error::ParsingError(std::string("Unexpected token: ") + ctx.Peek(), ctx.Position());
    }

    template<typename T>
    bool scanRules(LexingContext& ctx, const std::vector<std::pair<std::string, T>>& rules) {
        for (const auto& [token, kind] : rules) {
            if (ctx.Match(token)) {
                ctx.PushToken(kind, token);
                return true;
            }
        }
        return false;
    }

    void scanNumber(LexingContext& ctx) {
        std::string text;
        TokenKind kind = TokenKind::INT;

        while (!ctx.IsEnd() && std::isdigit(ctx.Peek())) {
            text.push_back(ctx.Advance());
        }

        if (ctx.Peek() == '.' && isdigit(ctx.Peek(1))) {
            kind = TokenKind::FLOAT;
            text.push_back(ctx.Advance());

            while (!ctx.IsEnd() && std::isdigit(ctx.Peek())) {
                text.push_back(ctx.Advance());
            }
        }

        ctx.PushToken(kind, text);
    }
}

std::unique_ptr<std::vector<Token>> lexer::lex(const std::string& source) {
    LexingContext ctx(source);

    while (!ctx.IsEnd()) {
        ctx.StartTurn();
        scanToken(ctx);
    }

    ctx.PushToken(TokenKind::END_OF_FILE);
    return ctx.MoveTokens();
}

