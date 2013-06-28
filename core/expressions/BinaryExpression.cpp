#include "BinaryExpression.h"

BinaryExpression::BinaryExpression(ExpressionBasePtr left, ExpressionBasePtr right)
  : mLeft(left), mRight(right)
{
}


ExpressionBasePtr BinaryExpression::getLeft() const
{
  return mLeft;
}

ExpressionBasePtr BinaryExpression::getRight() const
{
  return mRight;
}
