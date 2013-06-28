#ifndef COMPILER_CORE_EXPRESSIONS_BINARY_PLUS_EXPRESSION_H
#define COMPILER_CORE_EXPRESSIONS_BINARY_PLUS_EXPRESSION_H

#include "core/expressions/BinaryExpression.h"

class BinaryPlusExpression : public BinaryExpression
{
public:

  BinaryPlusExpression(ExpressionBasePtr left, ExpressionBasePtr right);

  virtual ExpressionVisitStatus visit(ExpressionsVisitorBase & visitor);
};

#endif // COMPILER_CORE_EXPRESSIONS_BINARY_PLUS_EXPRESSION_H
