set (CompilerCoreSources
	TokenLocation.cpp
	TokenLocation.h

	ErrorCodes.h

	Error.cpp
	Error.h

	Token.cpp
	Token.h

	ParserRuleBase.cpp
	ParserRuleBase.h

	ParserRules.cpp
	ParserRules.h

	Parser.cpp
	Parser.h
)


add_library(compiler_core STATIC ${CompilerCoreSources})
