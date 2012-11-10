#include "core/tokenizer/TokenizerRulesFacade.h"

#include <boost/smart_ptr/make_shared.hpp>
#include <boost/foreach.hpp>


#include "core/tokenizer/rules/AlphaNumTokenizerRule.h"
#include "core/tokenizer/rules/DoubleQuotedTextTokenizerRule.h"
#include "core/tokenizer/rules/OneSymbolTokenizerRule.h"
#include "core/tokenizer/rules/RelationOperatorTokenizerRule.h"
#include "core/tokenizer/rules/IncrementTokenizerRule.h"
#include "core/tokenizer/rules/AssignmentTokenizerRule.h"




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

	mTokenizerRuleList.push_back(boost::make_shared<IncrementTokenizerRule>());
}





TokenizerRuleList TokenizerRulesFacade::getTokenizerRule(int firstSymbol) const
{
	TokenizerRuleList result;
	BOOST_FOREACH(const TokenizerRulePtr & tokenizerRule, mTokenizerRuleList)
	{
		if (tokenizerRule->firstSymbolFits(firstSymbol))
		{
			result.push_back(tokenizerRule);
		}
	}

	return result;
}
