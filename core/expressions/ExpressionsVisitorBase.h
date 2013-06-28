#ifndef COMPILER_CORE_EXPRESSIONS_EXPRESSIONS_VISITOR_BASE_H
#define COMPILER_CORE_EXPRESSIONS_EXPRESSIONS_VISITOR_BASE_H

#include <boost/noncopyable.hpp>


#include "core/expressions/ExpressionsFwd.h"


enum ExpressionVisitStatus
{
  EVS_Unknown,
  EVS_StopWithError,
  EVS_StopSuccess,
  EVS_Continue
};

class ExpressionsVisitorBase : private boost::noncopyable
{
public:
  ExpressionsVisitorBase();

  virtual ~ExpressionsVisitorBase();


  ExpressionVisitStatus visitBinaryPlusExpression(BinaryPlusExpressionPtr expression);

};

#endif // COMPILER_CORE_EXPRESSIONS_EXPRESSIONS_VISITOR_BASE_H
