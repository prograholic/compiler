#include "InputStreamBase.h"

#include <cctype>



InputStreamBase::InputStreamBase()
{
}

InputStreamBase::~InputStreamBase()
{
}


void InputStreamBase::skipSpaces()
{
	int symbol;

	while ((symbol = this->peek()) != InputStreamBase::EndOfFile)
	{
		if (std::isspace(symbol))
		{
			this->next();
		}
		else
		{
			return;
		}
	}
}
