#ifndef __AST__H__
#define __AST__H__

#include <vector>
#include <memory>
#include "position.hpp"

namespace ast {

enum class NodeKind {
    INT_LITERAL,
    FLOAT_LITERAL,
    BINARY_EXPRESSION,
    UNARY_EXPRESSION,
    EXPRESSION_STATEMENT,
    PROGRAM,
    UNKNOWN,
};

class Node {
public:
    NodeKind kind;
    Position position;
    Node(NodeKind kind = NodeKind::UNKNOWN) : kind(kind) {}
};

class Expression : public Node {
public:
    Expression(NodeKind kind = NodeKind::UNKNOWN) : Node(kind) {}
};

class Statement : public Node {
public:
    Statement(NodeKind kind = NodeKind::UNKNOWN) : Node(kind) {}
};

class Program : public Node {
public:
    std::vector<std::unique_ptr<Statement>> statements;
    Program() : Node(NodeKind::PROGRAM) {}
};

class IntLiteral : public Expression {
public:
    size_t value;
    IntLiteral() : Expression(NodeKind::INT_LITERAL) {}
};

class FloatLiteral : public Expression {
public:
    double value;
    FloatLiteral() : Expression(NodeKind::FLOAT_LITERAL) {}
};

enum class BinaryExpOperator {
    ADD,
    SUB,
    MUL,
    TRUE_DIV,
    POW
};

class BinaryExpresion : public Expression {
public:
    std::unique_ptr<Expression> left;
    BinaryExpOperator op;
    std::unique_ptr<Expression> right;
    BinaryExpresion() : Expression(NodeKind::BINARY_EXPRESSION) {}
};

enum class UnaryExpOperator {
    ADD,
    SUB,
};

class UnaryExpression : public Expression {
public:
    std::unique_ptr<Expression> right;
    UnaryExpOperator op;
    UnaryExpression() : Expression(NodeKind::UNARY_EXPRESSION) {}
};

class ExpressionStatement : public Statement {
public:
    std::unique_ptr<Expression> expression;
    ExpressionStatement() : Statement(NodeKind::EXPRESSION_STATEMENT) {}
};

}

#endif // __AST__H__