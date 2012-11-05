#ifndef COMPILER_CORE_AST_BUILDER_H
#define COMPILER_CORE_AST_BUILDER_H

#include "core/tokenizer/Tokenizer.h"

class ASTBuilder : private boost::noncopyable
{
public:
	ASTBuilder(Tokenizer & tokenizer);



private:

	Tokenizer & mTokenizer;
};

#endif // COMPILER_CORE_AST_BUILDER_H
