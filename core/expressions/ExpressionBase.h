#ifndef COMPILER_CORE_EXPRESSIONS_EXPRESSION_BASE_H
#define COMPILER_CORE_EXPRESSIONS_EXPRESSION_BASE_H

#include <boost/smart_ptr/enable_shared_from_this.hpp>

#include "core/expressions/ExpressionsVisitorBase.h"
#include "core/tokenizer/Token.h"



class ExpressionBase : public boost::enable_shared_from_this<ExpressionBase>
{
public:

  virtual ~ExpressionBase();

  virtual ExpressionVisitStatus visit(ExpressionsVisitorBase & visitor) = 0;


  /**
   * Use this method instead of shared_from_this()
   * usage is very simple: shared_from(this); which very similar to previous function
   *
   * @sa http://stackoverflow.com/questions/657155/how-to-enable-shared-from-this-of-both-parend-and-derived
   * for details
   */
  template <typename ThisT>
  boost::shared_ptr<ThisT> shared_from(ThisT * thisPointer)
  {
    /**
     * If you got assert here, than you passed incorrect pointer as function argument (must be `this`)
     */
    BOOST_ASSERT(this == static_cast<ExpressionBase*>(thisPointer));

    return boost::static_pointer_cast<ThisT>(ExpressionBase::shared_from_this());
  }


private:

  /// @todo think how to pass corresponding tokens to Expression
  TokenList mTokens;

};




#endif /* COMPILER_CORE_EXPRESSIONS_EXPRESSION_BASE_H */
