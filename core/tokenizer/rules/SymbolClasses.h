#ifndef COMPILER_CORE_TOKENIZER_RULES_SYMBOL_CLASSES_H
#define COMPILER_CORE_TOKENIZER_RULES_SYMBOL_CLASSES_H

#include <cctype>


inline bool fitsAsIdentifier(const int symbol, bool firstSymbol = false)
{
	if (firstSymbol)
	{
		return std::isalpha(symbol) || (symbol == '_');
	}
	else
	{
		return std::isalnum(symbol) || (symbol == '_');
	}
}



inline bool isOctal(const int symbol)
{
	switch (symbol)
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
		return true;
	}

	return false;
}


#endif // COMPILER_CORE_TOKENIZER_RULES_SYMBOL_CLASSES_H
