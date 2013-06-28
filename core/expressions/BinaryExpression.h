#ifndef COMPILER_CORE_EXPRESSIONS_BINARY_EXPRESSION_H
#define COMPILER_CORE_EXPRESSIONS_BINARY_EXPRESSION_H

#include "core/expressions/ExpressionBase.h"

class BinaryExpression : public ExpressionBase
{
public:
  BinaryExpression(ExpressionBasePtr left, ExpressionBasePtr right);


  ExpressionBasePtr getLeft() const;

  ExpressionBasePtr getRight() const;

private:
  ExpressionBasePtr mLeft;
  ExpressionBasePtr mRight;

};

#endif // COMPILER_CORE_EXPRESSIONS_BINARY_EXPRESSION_H
