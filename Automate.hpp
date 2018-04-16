#ifndef MOD_AUTOMATE_HPP
#define MOD_AUTOMATE_HPP

enum lexemes { number, string, variable, mark, function, key_word,
	separator, assignment, error };
struct lex{
	const char* data;
	int string_num;
	lexemes type;
	struct lex* next;
};

class StateMachine{
	char* buf;
	char* s_buf;
	int string_count;
	int error_string;
	int new_string_flag;
	enum states {s_null, s_error, s_separate, s_number, s_indeficator,
		s_key_word,s_assignment, s_string
	} state, lexeme_type;

	void addCharacter (int symbol);
	void addSymbol (int symbol);
	struct lex* makeLexeme();

public:
	StateMachine();
	~StateMachine();
	int errorStringNumber();
	lexemes getLexemeType(char* str);
	struct lex* step(int symbol);

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
