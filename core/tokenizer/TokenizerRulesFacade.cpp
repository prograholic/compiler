#include "core/tokenizer/TokenizerRulesFacade.h"

#include <algorithm>

#include <boost/smart_ptr/make_shared.hpp>
#include <boost/foreach.hpp>


#include "core/tokenizer/rules/AlphaNumTokenizerRule.h"
#include "core/tokenizer/rules/DoubleQuotedTextTokenizerRule.h"
#include "core/tokenizer/rules/OneSymbolTokenizerRule.h"
#include "core/tokenizer/rules/RelationOperatorTokenizerRule.h"
#include "core/tokenizer/rules/IncrementTokenizerRule.h"
#include "core/tokenizer/rules/AssignmentTokenizerRule.h"
#include "core/tokenizer/rules/PredefinedNameTokenizerRule.h"
#include "core/tokenizer/rules/IntegerConstantTokenizerRule.h"




namespace
{
	struct TokenizerRuleComparator
	{
		bool operator()(TokenizerRulePtr left, TokenizerRulePtr right)
		{
			return left->priority() > right->priority();
		}
	};
}



TokenizerRulesFacade::TokenizerRulesFacade()
{
	constructRules();
	sortWithPriority();
}





TokenizerRuleList TokenizerRulesFacade::getTokenizerRules(int firstSymbol) const
{
	/// @todo create previously prepared lists for given symbol
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




void TokenizerRulesFacade::constructPredefinedSymbolTokenizers()
{
	mTokenizerRuleList.push_back(boost::make_shared<PredefinedNameTokenizerRule>(TK_Return, "return"));

	mTokenizerRuleList.push_back(boost::make_shared<PredefinedNameTokenizerRule>(TK_If, "if"));
	mTokenizerRuleList.push_back(boost::make_shared<PredefinedNameTokenizerRule>(TK_Else, "else"));

	mTokenizerRuleList.push_back(boost::make_shared<PredefinedNameTokenizerRule>(TK_While, "while"));
	mTokenizerRuleList.push_back(boost::make_shared<PredefinedNameTokenizerRule>(TK_Do, "do"));
	mTokenizerRuleList.push_back(boost::make_shared<PredefinedNameTokenizerRule>(TK_For, "for"));

	mTokenizerRuleList.push_back(boost::make_shared<PredefinedNameTokenizerRule>(TK_Continue, "continue"));
	mTokenizerRuleList.push_back(boost::make_shared<PredefinedNameTokenizerRule>(TK_Break, "break"));

	mTokenizerRuleList.push_back(boost::make_shared<PredefinedNameTokenizerRule>(TK_Switch, "switch"));
	mTokenizerRuleList.push_back(boost::make_shared<PredefinedNameTokenizerRule>(TK_Case, "case"));
	mTokenizerRuleList.push_back(boost::make_shared<PredefinedNameTokenizerRule>(TK_Default, "default"));

	mTokenizerRuleList.push_back(boost::make_shared<PredefinedNameTokenizerRule>(TK_Goto, "goto"));




	mTokenizerRuleList.push_back(boost::make_shared<PredefinedNameTokenizerRule>(TK_Const, "const"));
	mTokenizerRuleList.push_back(boost::make_shared<PredefinedNameTokenizerRule>(TK_Volatile, "volatile"));
	mTokenizerRuleList.push_back(boost::make_shared<PredefinedNameTokenizerRule>(TK_Register, "register"));
	mTokenizerRuleList.push_back(boost::make_shared<PredefinedNameTokenizerRule>(TK_Restricted, "restricted"));
	mTokenizerRuleList.push_back(boost::make_shared<PredefinedNameTokenizerRule>(TK_Static, "static"));
	mTokenizerRuleList.push_back(boost::make_shared<PredefinedNameTokenizerRule>(TK_Inline, "inline"));


	mTokenizerRuleList.push_back(boost::make_shared<PredefinedNameTokenizerRule>(TK_Signed, "signed"));
	mTokenizerRuleList.push_back(boost::make_shared<PredefinedNameTokenizerRule>(TK_Unsigned, "unsigned"));
	mTokenizerRuleList.push_back(boost::make_shared<PredefinedNameTokenizerRule>(TK_Void, "void"));
	mTokenizerRuleList.push_back(boost::make_shared<PredefinedNameTokenizerRule>(TK_Char, "char"));
	mTokenizerRuleList.push_back(boost::make_shared<PredefinedNameTokenizerRule>(TK_Short, "short"));
	mTokenizerRuleList.push_back(boost::make_shared<PredefinedNameTokenizerRule>(TK_Int, "int"));
	mTokenizerRuleList.push_back(boost::make_shared<PredefinedNameTokenizerRule>(TK_Long, "long"));
	mTokenizerRuleList.push_back(boost::make_shared<PredefinedNameTokenizerRule>(TK_Float, "float"));
	mTokenizerRuleList.push_back(boost::make_shared<PredefinedNameTokenizerRule>(TK_Double, "double"));

	mTokenizerRuleList.push_back(boost::make_shared<PredefinedNameTokenizerRule>(TK_Struct, "struct"));
	mTokenizerRuleList.push_back(boost::make_shared<PredefinedNameTokenizerRule>(TK_Enum, "enum"));
	mTokenizerRuleList.push_back(boost::make_shared<PredefinedNameTokenizerRule>(TK_Union, "union"));
	mTokenizerRuleList.push_back(boost::make_shared<PredefinedNameTokenizerRule>(TK_Typedef, "typedef"));
	mTokenizerRuleList.push_back(boost::make_shared<PredefinedNameTokenizerRule>(TK_Extern, "extern"));
	mTokenizerRuleList.push_back(boost::make_shared<PredefinedNameTokenizerRule>(TK_Auto, "auto"));

	mTokenizerRuleList.push_back(boost::make_shared<PredefinedNameTokenizerRule>(TK_Sizeof, "sizeof"));
}



void TokenizerRulesFacade::constructRules()
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

	mTokenizerRuleList.push_back(boost::make_shared<IntegerConstantTokenizerRule>());


	constructPredefinedSymbolTokenizers();
}




void TokenizerRulesFacade::sortWithPriority()
{
	std::sort(mTokenizerRuleList.begin(), mTokenizerRuleList.end(), TokenizerRuleComparator());
}
