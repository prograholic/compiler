#ifndef COMPILER_CORE_PARSER_H
#define COMPILER_CORE_PARSER_H

#include <istream>
#include <string>
#include <list>

#include <boost/noncopyable.hpp>

#include <boost/smart_ptr/shared_ptr.hpp>




struct Location
{
	std::string fileName;
	size_t line;
	size_t colon;

	Location()
		: fileName(),
		  line(0),
		  colon(0)
	{}
};


struct Lexeme
{
	std::string lexeme;

	Location loc;
};




enum ParserRuleState
{
	PRS_Unknown,
	PRS_Intermediate,
	PRS_Finished,
	PRS_FinishedWithUnget,
	PRS_Inapropriate
};


class ParserRuleBase : private boost::noncopyable
{
public:

	ParserRuleBase();

	virtual ~ParserRuleBase();


	ParserRuleState currentState();

	virtual void init(std::string & holder);


	virtual bool firstSymbolFits(int firstSymbol) = 0;

	virtual ParserRuleState consumeSymbol(int symbol) = 0;

protected:

	std::string * mHolder;
	ParserRuleState mCurrentState;

};


typedef boost::shared_ptr<ParserRuleBase> ParserRulePtr;



class Parser : private boost::noncopyable
{
public:
	Parser(std::istream & inputStream);

	bool getNextLexeme(Lexeme & lexeme);

	void addParserRule(ParserRulePtr parserRule);

private:

	std::istream & mInputStream;

	Location mCurrentLocation;


	typedef std::list<ParserRulePtr> ParserRuleList;

	ParserRuleList mParserRuleList;


	ParserRulePtr getParserRule(int firstSymbol) const;

	void updateCurrentLocation(int symbol);

	void skipSpaces();

};

#endif // COMPILER_CORE_PARSER_H
