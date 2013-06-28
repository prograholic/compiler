set (CompilerCoreExpressionsSources
	ExpressionsFwd.h

	ExpressionBase.cpp
	ExpressionBase.h

	ExpressionsVisitorBase.cpp
	ExpressionsVisitorBase.h

	BinaryExpression.cpp
	BinaryExpression.h

	BinaryPlusExpression.cpp
	BinaryPlusExpression.h
)


add_library(compiler_core_expressions STATIC ${CompilerCoreExpressionsSources})
