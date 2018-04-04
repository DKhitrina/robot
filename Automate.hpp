#ifndef MOD_PARSER_HPP
#define MOD_PARSER_HPP

enum lexemes { number, string, variable, mark, function, key_word,
	separator, assignment, error };

class StateMachine{
	char* buf;
	char* s_buf;
	enum states {
	s_null, s_error, s_separate, s_number, s_indeficator, s_key_word,
		s_assignment, s_string
	} state, lexeme_type;

	void addCharacter (int symbol);
	void addSymbol (int symbol);
	char* makeLexeme();

public:
	StateMachine();
	~StateMachine();
	int ifError();
	lexemes getLexemeType(char* str);
	char* step(int symbol);

private:
	void stateError();
	void stateNull(int symbol);
	void stateSeparate(int symbol);
	void stateNumber(int symbol);
	void stateIdentificator(int symbol);
	void stateKeyWord(int symbol);
	void stateAssignment(int symbol);
	void stateString(int symbol);
};

#endif
