#include "Automate.hpp"
#include <stdlib.h>
#include <stdio.h>

int check_separating_character (int symb) /* 1 - match, 0 - don't match */
{
	if ( symb == '+' || symb == '-' || symb == '*' || symb == '/'
		|| symb == '%' || symb == '<' || symb == '>' || symb == '='
		|| symb == '&' || symb == '|' || symb == '!' || symb == '('
		|| symb == ')' || symb == '[' || symb == ']' || symb == ';'
		|| symb == ',')
		return 1;
	else
		return 0;
}

int check_space (int symb)
{
	if (symb == '\n' || symb == ' ' || symb == '\t')
		return 1;
	else
		return 0;
}

struct lex* make_struct (const char* str, int num, lexemes type)
{
	struct lex* l = new struct lex;
	l->data = str;
	l->string_num = num;
	l->type = type;
	l->next = NULL;
	return l;
}

//-----------------------------------------------------------------------------

void StateMachine::addCharacter (int symb)
{
	s_buf[0] = symb;
}
void StateMachine::addSymbol (int symb)
{
	int i;
	for (i = 0; buf[i] != 0; i++)
	{}
	buf[i] = symb;
	buf[i+1] = 0;
}
struct lex* StateMachine::makeLexeme()
{
	char* lex;
	int i;
	if (buf[0] == ':' && buf[1] == 0)
		return NULL;
	if (s_buf[0]!=0 && lexeme_type == s_separate)
	{
		lex = new char[2];
		lex[0] = s_buf[0];
		lex[1] = 0;
		s_buf[0] = 0;
		return make_struct(lex, string_count, getLexemeType(lex));
	}
	else if (buf[0]!=0)
	{
		for (i = 0; buf[i] != 0; i++)
		{}
		lex = new char[i+1];
		for (i = 0; buf[i] != 0; i++){
			lex[i] = buf[i];
		}
		lex[i+1] = 0;
		for (i = 0; buf[i] != 0; i++){
			buf[i] = 0;
		}
		return make_struct(lex, string_count, getLexemeType(lex));
	}
	else
		return NULL;
}



StateMachine::StateMachine()
{
	buf = new char[128];
	s_buf = new char;
	string_count = 1;
	error_string = 0;
	new_string_flag = 0;
	state = s_null;
	lexeme_type = s_null;
}

StateMachine::~StateMachine()
{
	delete [] buf;
	delete s_buf;
}

int StateMachine::ErrorStringNumber()
{
	if (state == s_error)
		return error_string;
	else
		return 0;
}

lexemes StateMachine::getLexemeType(char* str)
{
	switch (lexeme_type)
	{
	case s_null:
		break;
	case s_error:
		return error;
	case s_separate:
		return separator;
	case s_number:
		return number;
	case s_indeficator:
		if (str[0] == '$')
			return variable;
		if (str[0] == '@')
			return mark;
		if (str[0] == '?')
			return function;
	case s_key_word:
		return key_word;
	case s_assignment:
		return assignment;
	case s_string:
		return string;
	}
	return error;
}

struct lex* StateMachine::step(int symb)
{
	int flag_delayed_output = 0;
	if (state == s_separate && s_buf[0] != 0)
		flag_delayed_output = 1;
	if (new_string_flag)
	{
		string_count++;
		new_string_flag = 0;
	}
	switch (state)
	{
	case s_null:
		stateNull(symb);
		break;
	case s_error:
		stateError();
		break;
	case s_number:
		stateNumber(symb);
		break;
	case s_separate:
		stateSeparate(symb);
		break;
	case s_indeficator:
		stateIdentificator(symb);
		break;
	case s_key_word:
		stateKeyWord(symb);
		break;
	case s_assignment:
		stateAssignment(symb);
		break;
	case s_string:
		stateString(symb);
		break;
	}

	if (symb == '\n')
		new_string_flag = 1;
	if (flag_delayed_output)
	{
		lexeme_type = s_separate;
		return makeLexeme();
	}
	else
	if (state == s_null || state == s_separate || state == s_assignment)
		return makeLexeme();
	else
		return NULL;
}


void StateMachine::stateError()
{
	state = lexeme_type = s_error;
	if (error_string == 0)
		error_string = string_count;
}
void StateMachine::stateNull(int symb)
{
	if (symb >= '0' && symb <= '9')
	{
		state = s_number;
		addSymbol(symb);
	}
	else if (symb == '?' || symb == '@' || symb == '$' )
	{
		state = s_indeficator;
		addSymbol(symb);
	}
	else if ((symb >= 'A' && symb <= 'Z')
		|| (symb >= 'a' && symb <= 'z'))
	{
		state = s_key_word;
		addSymbol(symb);
	}
	else if (symb == ':')
	{
		state = s_assignment;
		addSymbol(symb);
	}
	else if (symb == '"')
	{
		state = s_string;
		addSymbol(symb);
	}
	else if (check_separating_character(symb))
	{
		state = lexeme_type =  s_separate;
		addCharacter(symb);
	}
	else if (!check_space(symb))
		state = s_error;
}
void StateMachine::stateSeparate(int symb)
{
	if (check_space(symb))
		state = s_null;
	else if (check_separating_character(symb))
	{
		addCharacter(symb);
		lexeme_type = s_separate;
	}
	else
		stateNull(symb);
}
void StateMachine::stateNumber(int symb)
{
	if (check_space(symb))
	{
		lexeme_type = s_number;
		state = s_null;
	}
	else if (check_separating_character(symb))
	{
		state = s_separate;
		lexeme_type = s_number;
		addCharacter(symb);
	}
	else if (symb == ':')
	{
		state = s_assignment;
		lexeme_type = s_number;
		addCharacter(symb);
	}
	else
	{
		if (symb < '0' || symb > '9')
			state = s_error;
		else
			addSymbol(symb);
	}
}
void StateMachine::stateIdentificator(int symb)
{
	if (check_space(symb))
	{
		state = s_null;
		lexeme_type = s_indeficator;
	}
	else if (check_separating_character(symb))
	{
		state = s_separate;
		lexeme_type = s_indeficator;
		addCharacter(symb);
	}
	else if (symb == ':')
	{
		state = s_assignment;
		lexeme_type = s_indeficator;
		addCharacter(symb);
	}
	else
	{
		if (symb < '0' || (symb > '9' && symb < 'A')
			|| (symb > 'Z' && symb < 'a') || symb > 'z')
			state = s_error;
		else
			addSymbol(symb);
	}
}
void StateMachine::stateKeyWord(int symb)
{
	if (check_space(symb))
	{
		state = s_null;
		lexeme_type = s_key_word;
	}
	else if (check_separating_character(symb))
	{
		state = s_separate;
		lexeme_type = s_key_word;
		addCharacter(symb);
	}
	else if (symb == ':')
	{
		state = s_assignment;
		lexeme_type = s_key_word;
		addCharacter(symb);
	}
	else
	{
		if (symb < 'A' || (symb > 'Z' && symb < 'a') || symb > 'z')
			state = s_error;
		else
			addSymbol(symb);
	}
}
void StateMachine::stateAssignment(int symb)
{
	if (symb == '=')
	{
		addSymbol (s_buf[0]);
		s_buf[0] = 0;
		addSymbol(symb);
		lexeme_type = s_assignment;
		state = s_null;
	}
	else if (check_separating_character(symb) || check_space (symb))
	{
		state = lexeme_type = s_separate;
		stateSeparate(symb);
	}
	else
		state = s_error;
}
void StateMachine::stateString(int symb)
{
	if (symb == '"')
	{
		addSymbol(symb);
		lexeme_type = s_string;
		state = s_null;
	}
	else if (symb == '\n')
		state = s_error;
	else
		addSymbol(symb);
}
