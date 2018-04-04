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

//-----------------------------------------------------------------------------

void StateMachine::addCharacter (int symb)  /* using special buf for ungets */
{
	s_buf[0] = symb;
}
void StateMachine::addSymbol (int symb)  /* without ungets */
{
	int i;
	for (i = 0; buf[i] != 0; i++)
	{}
	buf[i] = symb;
	buf[i+1] = 0;
}
char* StateMachine::makeLexeme()
{
	char* lex;
	int i;
	if (s_buf[0]!=0 && lexeme_type == s_separate)
	{
		lex = new char[2];
		lex[0] = s_buf[0];
		lex[1] = 0;
		s_buf[0] = 0;
		return lex;
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
		return lex;
	}
	else
		return NULL;
}



StateMachine::StateMachine()
{
	buf = new char[128];
	s_buf = new char;
	state = s_null;
	lexeme_type = s_null;
}

StateMachine::~StateMachine()	{ delete [] buf; delete s_buf; }

int StateMachine::ifError()
{
	if (state == s_error)
		return 1;
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

char* StateMachine::step(int symb)
{
	int flag_delayed_output = 0;
	if (state == s_separate && s_buf[0] != 0)
		flag_delayed_output = 1;
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
	if (state == s_null || state == s_separate || state == s_assignment)
		return makeLexeme();
	else if (flag_delayed_output)
	{
		lexeme_type = s_separate;
		return makeLexeme();
	}
	else
		return NULL;
}



void StateMachine::stateError()
{
	state = lexeme_type = s_error;
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
		lexeme_type = s_number;
		state = s_assignment;
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
		lexeme_type = s_indeficator;
		state = s_null;
	}
	else if (check_separating_character(symb))
	{
		lexeme_type = s_indeficator;
		state = s_separate;
		addCharacter(symb);
	}
	else if (symb == ':')
	{
		lexeme_type = s_indeficator;
		state = s_assignment;
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
		lexeme_type = s_key_word;
		state = s_assignment;
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
	else
		addSymbol(symb);
}
