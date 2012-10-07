#ifndef COMPILER_CORE_AST_BUILDER_H
#define COMPILER_CORE_AST_BUILDER_H

#include "core/Parser.h"

class ASTBuilder : private boost::noncopyable
{
public:
	ASTBuilder(Parser & parser);



private:

	Parser & mParser;
};

#endif // COMPILER_CORE_AST_BUILDER_H
