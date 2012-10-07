set (CompilerCoreSources
	Parser.cpp
	Parser.h

	ParserRuleBase.cpp
	ParserRuleBase.h

	Token.cpp
	Token.h

	TokenLocation.cpp
	TokenLocation.h

	ParserRules.cpp
	ParserRules.h
)


add_library(compiler_core STATIC ${CompilerCoreSources})
