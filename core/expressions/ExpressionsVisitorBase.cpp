#include "ExpressionsVisitorBase.h"

ExpressionsVisitorBase::ExpressionsVisitorBase()
{
}

ExpressionsVisitorBase::~ExpressionsVisitorBase()
{
}

ExpressionVisitStatus ExpressionsVisitorBase::visitBinaryPlusExpression(BinaryPlusExpressionPtr expression)
{
  return EVS_Continue;
}
