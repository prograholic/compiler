set (CompilerCoreSources
	Location.cpp
	Location.h

	ErrorCodes.h

	Error.cpp
	Error.h

	StreamBuffer.cpp
	StreamBuffer.h

	StringRef.cpp
	StringRef.h

	InputStreamBase.cpp
	InputStreamBase.h

	BufferedInputStream.cpp
	BufferedInputStream.h

	StdInputStreamAdapter.cpp
	StdInputStreamAdapter.h

	ASTBuilder.cpp
	ASTBuilder.h
)


add_library(compiler_core STATIC ${CompilerCoreSources})


add_subdirectory(tokenizer)
add_subdirectory(expressions)
