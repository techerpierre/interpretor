#include "parser.hpp"
#include <iostream>
#include "../core/error.hpp"

using namespace parser;

namespace {
    std::unique_ptr<Statement> parseStatement(ParsingContext& ctx);
    std::unique_ptr<Expression> parseExpression(ParsingContext& ctx);
    std::unique_ptr<Expression> parseTermExpression(ParsingContext& ctx);
    std::unique_ptr<Expression> parseFactorExpression(ParsingContext& ctx);
    std::unique_ptr<Expression> parsePowerExpression(ParsingContext& ctx);
    std::unique_ptr<Expression> parseUnaryExpression(ParsingContext& ctx);
    std::unique_ptr<Expression> parseLiteralExpression(ParsingContext& ctx);

    std::unique_ptr<Statement> parseStatement(ParsingContext& ctx) {
        auto st = std::make_unique<ExpressionStatement>();
        st->expression = parseExpression(ctx);
        return st;
    }

    std::unique_ptr<Expression> parseExpression(ParsingContext& ctx) {
        return parseTermExpression(ctx);
    }

    std::unique_ptr<Expression> parseTermExpression(ParsingContext& ctx) {
        auto expr = parseFactorExpression(ctx);

        while (ctx.Eat({TokenKind::ADD, TokenKind::SUB})) {
            auto op = ctx.Previous();
            auto right = parseFactorExpression(ctx);

            auto binaryExpr = std::make_unique<BinaryExpresion>();
            binaryExpr->left = std::move(expr);
            binaryExpr->right = std::move(right);
            binaryExpr->op = BinaryExprOperatorsMap.find(op.kind)->second;
            binaryExpr->position = binaryExpr->left->position;
            expr = std::move(binaryExpr);
        }

        return expr;
    }

    std::unique_ptr<Expression> parseFactorExpression(ParsingContext& ctx) {
        auto expr = parsePowerExpression(ctx);

        while (ctx.Eat({TokenKind::MUL, TokenKind::TRUE_DIV})) {
            auto op = ctx.Previous();

            auto binaryExpr = std::make_unique<BinaryExpresion>();
            binaryExpr->left = std::move(expr);
            binaryExpr->right = parsePowerExpression(ctx);
            binaryExpr->op = BinaryExprOperatorsMap.find(op.kind)->second;
            binaryExpr->position = binaryExpr->left->position;
            expr = std::move(binaryExpr);
        }

        return expr;
    }

    std::unique_ptr<Expression> parsePowerExpression(ParsingContext& ctx) {
        auto expr = parseUnaryExpression(ctx);

        while (ctx.Eat({TokenKind::POW})) {
            auto op = ctx.Previous();

            auto binaryExpr = std::make_unique<BinaryExpresion>();
            binaryExpr->left = std::move(expr);
            binaryExpr->right = parsePowerExpression(ctx);
            binaryExpr->op = BinaryExprOperatorsMap.find(op.kind)->second;
            binaryExpr->position = binaryExpr->left->position;
            expr = std::move(binaryExpr);
        }

        return expr;
    }

    std::unique_ptr<Expression> parseUnaryExpression(ParsingContext& ctx) {
        if (ctx.Eat({TokenKind::ADD, TokenKind::SUB})) {
            auto op = ctx.Previous();

            auto unaryExpr = std::make_unique<UnaryExpression>();
            unaryExpr->right = parseUnaryExpression(ctx);
            unaryExpr->op = UnaryExprOperatorsMap.find(op.kind)->second;
            unaryExpr->position = op.pos;
            return unaryExpr;
        }

        return parseLiteralExpression(ctx);
    }

    std::unique_ptr<Expression> parseLiteralExpression(ParsingContext& ctx) {
        auto token = ctx.Peek();

        if (ctx.Eat({TokenKind::INT})) {
            auto expr = std::make_unique<IntLiteral>();
            expr->value = std::stoi(token.text);
            expr->position = token.pos;
            return expr;
        }

        if (ctx.Eat({TokenKind::FLOAT})) {
            auto expr = std::make_unique<FloatLiteral>();
            expr->value = std::stod(token.text);
            expr->position = token.pos;
            return expr;
        }

        if (ctx.Eat({TokenKind::OPEN_PAR})) {
            auto expr = parseExpression(ctx);
            auto closePar = ctx.EatOrFail({TokenKind::CLOSE_PAR}, ") is expected to close parenthesis.");
            return expr;
        }

        throw error::ParsingError(std::string("Unexpected token: ") + token.text, token.pos);
    }
}

std::unique_ptr<Program> parser::parse(const std::vector<Token>& tokens) {
    ParsingContext ctx(tokens);
    auto program = std::make_unique<Program>();

    while (!ctx.IsEnd() && !ctx.CheckType({ TokenKind::END_OF_FILE })) {
        program->statements.push_back(parseStatement(ctx));
    }

    return program;
}