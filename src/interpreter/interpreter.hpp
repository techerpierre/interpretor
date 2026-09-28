#ifndef __INTERPRETER__H__
#define __INTERPRETER__H__

#include <variant>
#include "../ast/ast.hpp"
#include "../ast/visitor.hpp"

namespace interpreter {

using namespace ast;

typedef std::variant<size_t, double> Value;

class Interpreter : public Visitor {
private:
    Value m_lastValue;
public:
    void VisitIntLiteral(const IntLiteral& node) override;
    void VisitFloatLiteral(const FloatLiteral& node) override;
    void VisitBinaryExpresion(const BinaryExpresion& node) override;
    void VisitUnaryExpression(const UnaryExpression& node) override;
    void VisitExpressionStatement(const ExpressionStatement& node) override;
    void VisitProgram(const Program& node) override;
    Value GetLastValue(void) const;
};

int interpret(const std::string& source);

}

#endif // __INTERPRETER__H__