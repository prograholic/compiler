set (CompilerCoreSources
	Parser.cpp
	Parser.h

	ParserRules.cpp
	ParserRules.h
)


add_library(compiler_core STATIC ${CompilerCoreSources})
