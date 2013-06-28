#include "BinaryPlusExpression.h"

BinaryPlusExpression::BinaryPlusExpression(ExpressionBasePtr left, ExpressionBasePtr right)
  : BinaryExpression(left, right)
{
}


ExpressionVisitStatus BinaryPlusExpression::visit(ExpressionsVisitorBase & visitor)
{
  return visitor.visitBinaryPlusExpression(shared_from(this));
}
