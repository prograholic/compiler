set (CompilerCoreTokenizerRulesSources
	SymbolClasses.h

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

	PredefinedNameTokenizerRule.cpp
	PredefinedNameTokenizerRule.h

	IntegerConstantTokenizerRule.cpp
	IntegerConstantTokenizerRule.h
)


add_library(compiler_core_tokenizer_rules STATIC ${CompilerCoreTokenizerRulesSources})
