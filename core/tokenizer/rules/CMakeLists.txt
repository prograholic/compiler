set (CompilerCoreTokenizerRulesSources
	AlphaNumTokenizerRule.cpp
	AlphaNumTokenizerRule.h

	DoubleQuotedTextTokenizerRule.cpp
	DoubleQuotedTextTokenizerRule.h

	RelationOperatorTokenizerRule.cpp
	RelationOperatorTokenizerRule.h

	IncrementTokenizerRule.cpp
	IncrementTokenizerRule.h

	AssignmentTokenizerRule.cpp
	AssignmentTokenizerRule.h

	OneSymbolTokenizerRule.h
)


add_library(compiler_core_tokenizer_rules STATIC ${CompilerCoreTokenizerRulesSources})
