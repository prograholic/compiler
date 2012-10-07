#ifndef COMPILER_CORE_ERROR_CODES_H
#define COMPILER_CORE_ERROR_CODES_H

enum ErrorCodes
{
	EC_NoError = 0,
	EC_UnknownError,

	EC_NoParserRule,
	EC_ParserRuleBroken,

	/// Error codes for DoubleQuotedTextParserRule
	EC_WrongMaskedSymbol,
	EC_WrongOctalSymbol,
	EC_WrongHexSymbol,

	/// Error codes for OneSymbolParserRules
	EC_WrongSemicolonSymbol,
	EC_WrongStarSymbol,
	EC_WrongAssignmentSymbol,
	EC_WrongOpenParenSymbol,
	EC_WrongCloseParenSymbol,
	EC_WrongOpenBraceSymbol,
	EC_WrongCloseBraceSymbol,
	EC_WrongOpenBracketSymbol,
	EC_WrongCloseBracketSymbol
};

#endif // COMPILER_CORE_ERROR_CODES_H
