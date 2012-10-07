set (CompilerCoreSources
	Location.cpp
	Location.h

	ErrorCodes.h

	Error.cpp
	Error.h

	Token.cpp
	Token.h

	ParserRuleBase.cpp
	ParserRuleBase.h

	ParserRules.cpp
	ParserRules.h

	InputStreamBase.cpp
	InputStreamBase.h

	BufferedInputStream.cpp
	BufferedInputStream.h

	StdInputStreamAdapter.cpp
	StdInputStreamAdapter.h

	Parser.cpp
	Parser.h

	ASTBuilder.cpp
	ASTBuilder.h
)


add_library(compiler_core STATIC ${CompilerCoreSources})
