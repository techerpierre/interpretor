#ifndef __VISITOR__H__
#define __VISITOR__H__

#include "ast.hpp"
#include <iostream>

namespace ast {

class Visitor {
public:
    virtual ~Visitor(void) = default;
    virtual void VisitIntLiteral(const IntLiteral& node) {}
    virtual void VisitFloatLiteral(const FloatLiteral& node) {}
    virtual void VisitBinaryExpresion(const BinaryExpresion& node) {
        Dispatch(*node.left);
        Dispatch(*node.right);
    }
    virtual void VisitUnaryExpression(const UnaryExpression& node) {
        Dispatch(*node.right);
    }
    virtual void VisitExpressionStatement(const ExpressionStatement& node) {
        Dispatch(*node.expression);
    }
    virtual void VisitProgram(const Program& node) {
        for (const auto& stmt : node.statements) {
            Dispatch(*stmt);
        }
    }
    virtual void VisitBlockStatement(const BlockStatement& node) {
        for (const auto& stmt : node.body) {
            Dispatch(*stmt);
        }
    }
    void Dispatch(const Node& node);
};

}

#endif // __VISITOR__H__