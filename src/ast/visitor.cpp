#include "visitor.hpp" 
#include <iostream>

using namespace ast;

void Visitor::Dispatch(const Node& node) {
    switch (node.kind) {
    case NodeKind::INT_LITERAL: {
        const auto& intLit = static_cast<const IntLiteral&>(node);
        VisitIntLiteral(intLit);
        break;
    }
    case NodeKind::FLOAT_LITERAL: {
        const auto& floatLit = static_cast<const FloatLiteral&>(node);
        VisitFloatLiteral(floatLit);
        break;
    }
    case NodeKind::BINARY_EXPRESSION: {
        const auto& binaryExpr = static_cast<const BinaryExpresion&>(node);
        VisitBinaryExpresion(binaryExpr);
        break;
    }
    case NodeKind::UNARY_EXPRESSION: {
        const auto& unaryExpr = static_cast<const UnaryExpression&>(node);
        VisitUnaryExpression(unaryExpr);
        break;
    }
    case NodeKind::EXPRESSION_STATEMENT: {
        const auto& expressionStmt = static_cast<const ExpressionStatement&>(node);
        VisitExpressionStatement(expressionStmt);
        break;
    }
    case NodeKind::PROGRAM: {
        const auto& prog = static_cast<const Program&>(node);
        VisitProgram(prog);
        break;
    }
    case NodeKind::BLOCK_STATEMENT:
        const auto& blockStmt = static_cast<const BlockStatement&>(node);
        VisitBlockStatement(blockStmt);
        break;
    }
}