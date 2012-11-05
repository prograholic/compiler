set (CompilerCoreTokenizerSources
	Token.cpp
	Token.h

	TokenizerRuleBase.cpp
	TokenizerRuleBase.h

	Tokenizer.cpp
	Tokenizer.h

	TokenizerRulesFacade.cpp
	TokenizerRulesFacade.h
)


add_library(compiler_core_tokenizer STATIC ${CompilerCoreTokenizerSources})


add_subdirectory(rules)
