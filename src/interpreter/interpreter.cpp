#include "interpreter.hpp"
#include <iostream>
#include <cmath>
#include "../lexer/lexer.hpp"
#include "../parser/parser.hpp"
#include "../core/error.hpp"

using namespace interpreter;

void Interpreter::VisitIntLiteral(const IntLiteral& node) {
    m_lastValue = node.value;
}

void Interpreter::VisitFloatLiteral(const FloatLiteral& node) {
    m_lastValue = node.value;
}

void Interpreter::VisitBinaryExpresion(const BinaryExpresion& node) {
    Dispatch(*node.left);
    Value leftValue = m_lastValue;

    Dispatch(*node.right);
    Value rightValue = m_lastValue;

    if (std::holds_alternative<size_t>(leftValue)) {
        if (!std::holds_alternative<size_t>(rightValue)) {
            throw error::RuntimeError("Left & right elements are not the same type in int operation.", node.right->position);
        }

        auto left = std::get<size_t>(leftValue);
        auto right = std::get<size_t>(rightValue);

        switch (node.op) {
        case BinaryExpOperator::ADD:
            m_lastValue = left + right;
            break;
        case BinaryExpOperator::SUB:
            m_lastValue = left - right;
            break;
        case BinaryExpOperator::MUL:
            m_lastValue = left * right;
            break;
        case BinaryExpOperator::TRUE_DIV:
            m_lastValue = left / right;
            break;
        case BinaryExpOperator::POW:
            throw error::RuntimeError("Power operator cannot be used with elements of type int.", node.position);
        }
    } else if (std::holds_alternative<double>(leftValue)) {
        if (!std::holds_alternative<double>(rightValue)) {
            throw error::RuntimeError("Left & right elements are not the same type in float operation.", node.right->position);
        }

        auto left = std::get<double>(leftValue);
        auto right = std::get<double>(rightValue);

        switch (node.op) {
        case BinaryExpOperator::ADD:
            m_lastValue = left + right;
            break;
        case BinaryExpOperator::SUB:
            m_lastValue = left - right;
            break;
        case BinaryExpOperator::MUL:
            m_lastValue = left * right;
            break;
        case BinaryExpOperator::TRUE_DIV:
            m_lastValue = left / right;
            break;
        case BinaryExpOperator::POW:
            m_lastValue = pow(left, right);
            break;
        }
    }
}

void Interpreter::VisitUnaryExpression(const UnaryExpression& node) {
    Dispatch(*node.right);
    Value rightValue = m_lastValue;

    if (std::holds_alternative<size_t>(rightValue)) {
        auto right = std::get<size_t>(rightValue);

        switch (node.op) {
        case UnaryExpOperator::ADD:
            m_lastValue = right;
            break;
        case UnaryExpOperator::SUB:
            m_lastValue = -right;
            break;
        }
    } else if (std::holds_alternative<double>(rightValue)) {
        auto right = std::get<double>(rightValue);

        switch (node.op) {
        case UnaryExpOperator::ADD:
            m_lastValue = right;
            break;
        case UnaryExpOperator::SUB:
            m_lastValue = -right;
            break;
        }
    }
}

void Interpreter::VisitExpressionStatement(const ExpressionStatement& node) {
    Dispatch(*node.expression);
}

void Interpreter::VisitProgram(const Program& node) {
    for (const auto& stmt : node.statements) {
        Dispatch(*stmt);
    }
}

Value Interpreter::GetLastValue(void) const {
    return m_lastValue;
}

int interpreter::interpret(const std::string& source) {
    try {
        auto tokens = lexer::lex(source);
        auto ast = parser::parse(*tokens);
        Interpreter inter;
        inter.Dispatch(*ast);

        std::visit([](auto&& arg) {
            std::cout << arg;
        }, inter.GetLastValue());
        std::cout << std::endl;
        return 0;
    } catch(const error::Error& err) {
        std::cout << err.What() << std::endl;
        return 1;
    }
}