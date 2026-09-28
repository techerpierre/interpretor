#include "ast_printer.hpp"
#include <iostream>
#include <cstdint>

using namespace ast;

namespace {
    std::string tabs(size_t depth) {
        return std::string(depth*4, ' ');
    }

    std::string withColor(AstColor color, const std::string& str) {
        return AstAnsiiColorsMap.find(color)->second + str + RESET_COLOR;
    }

    AstColor colorizeByDepth(
        size_t depth,
        AstColor color0 = AstColor::YELLOW,
        AstColor color1 = AstColor::PURPLE,
        AstColor color2 = AstColor::BLUE
    ) {
        switch(depth % 3) {
            case 0: return color0;
            case 1: return color1;
            case 2: return color2;
            default: return color0;
        }
    }

    std::string brace(size_t depth, int8_t closure = 0) {
        std::string braceText = closure ? "}" : "{";
        return withColor(colorizeByDepth(depth), braceText + "\n");
    }

    std::string parenthesis(size_t depth, int8_t closure = 0) {
        std::string parenthesisText = closure ? ")" : "(";
        return withColor(
            colorizeByDepth(depth, AstColor::BLUE, AstColor::YELLOW, AstColor::PURPLE),
            parenthesisText
        );
    }

    std::string statement(const std::string& name) {
        return withColor(AstColor::GREEN, name);
    }

    std::string expression(const std::string& name) {
        return withColor(AstColor::CYAN, name);
    }
}

void AstPrinter::VisitIntLiteral(const IntLiteral& node) {
    std::cout << tabs(m_Depth) << expression("IntLiteral") << parenthesis(m_Depth) << node.value << parenthesis(m_Depth, 1) << "\n";
}

void AstPrinter::VisitFloatLiteral(const FloatLiteral& node) {
    std::cout << tabs(m_Depth) << expression("FloatLiteral") << parenthesis(m_Depth) << node.value << parenthesis(m_Depth, 1) << "\n";
}

void AstPrinter::VisitBinaryExpresion(const BinaryExpresion& node) {
    std::cout << tabs(m_Depth) << expression("BinaryExpresion") << brace(m_Depth);
    m_Depth++;
    Dispatch(*node.left);
    std::cout << tabs(m_Depth) << BinaryOperatorSymbolsMap.find(node.op)->second << "\n";
    Dispatch(*node.right);
    m_Depth--;
    std::cout << tabs(m_Depth) << brace(m_Depth, 1);
}

void AstPrinter::VisitUnaryExpression(const UnaryExpression& node) {
    std::cout << tabs(m_Depth) << expression("UnaryExpression") << brace(m_Depth);
    m_Depth++;
    std::cout << tabs(m_Depth) << UnaryOperatorSymbolsMap.find(node.op)->second << "\n";
    Dispatch(*node.right);
    m_Depth--;
    std::cout << tabs(m_Depth) << brace(m_Depth, 1);
}

void AstPrinter::VisitExpressionStatement(const ExpressionStatement& node) {
    std::cout << tabs(m_Depth) << statement("ExpressionStatement") << brace(m_Depth);
    m_Depth++;
    Dispatch(*node.expression);
    m_Depth--;
    std::cout << tabs(m_Depth) << brace(m_Depth, 1);
}

void AstPrinter::VisitProgram(const Program& node) {
    std::cout << tabs(m_Depth) << statement("Program") << brace(m_Depth);
    m_Depth++;
    for (const auto& stmt : node.statements) {
        Dispatch(*stmt);
    }
    m_Depth--;
    std::cout << tabs(m_Depth) << brace(m_Depth, 1);
}

void ast::print(const Node& node) {
    AstPrinter printer;
    printer.Dispatch(node);
}
