#include "core/tokenizer/TokenizerRulesFacade.h"

#include <boost/smart_ptr/make_shared.hpp>
#include <boost/foreach.hpp>


#include "core/tokenizer/rules/AlphaNumTokenizerRule.h"
#include "core/tokenizer/rules/DoubleQuotedTextTokenizerRule.h"
#include "core/tokenizer/rules/OneSymbolTokenizerRule.h"
#include "core/tokenizer/rules/RelationOperatorTokenizerRule.h"
#include "core/tokenizer/rules/PreIncrementTokenizerRule.h"




TokenizerRulesFacade::TokenizerRulesFacade()
{
	mTokenizerRuleList.push_back(boost::make_shared<AlphaNumTokenizerRule>());
	mTokenizerRuleList.push_back(boost::make_shared<DoubleQuotedTextTokenizerRule>());

	mTokenizerRuleList.push_back(boost::make_shared<SemicolonTokenizerRule>());

	mTokenizerRuleList.push_back(boost::make_shared<StarTokenizerRule>());

	mTokenizerRuleList.push_back(boost::make_shared<AssignmentTokenizerRule>());


	mTokenizerRuleList.push_back(boost::make_shared<OpenParenTokenizerRule>());
	mTokenizerRuleList.push_back(boost::make_shared<CloseParenTokenizerRule>());

	mTokenizerRuleList.push_back(boost::make_shared<OpenBraceTokenizerRule>());
	mTokenizerRuleList.push_back(boost::make_shared<CloseBraceTokenizerRule>());

	mTokenizerRuleList.push_back(boost::make_shared<OpenBracketTokenizerRule>());
	mTokenizerRuleList.push_back(boost::make_shared<CloseBracketTokenizerRule>());

	mTokenizerRuleList.push_back(boost::make_shared<RelationOperatorTokenizerRule>());

	mTokenizerRuleList.push_back(boost::make_shared<PreIncrementTokenizerRule>());
}





TokenizerRulePtr TokenizerRulesFacade::getTokenizerRule(int firstSymbol) const
{
	BOOST_FOREACH(const TokenizerRulePtr & tokenizerRule, mTokenizerRuleList)
	{
		if (tokenizerRule->firstSymbolFits(firstSymbol))
		{
			return tokenizerRule;
		}
	}

	return TokenizerRulePtr();
}
