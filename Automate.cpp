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

StateMachine::StateMachine()
{
    buf = new char[128];
    s_buf = new char;
    state = s_null;
    lexeme_type = s_null;
}
StateMachine::~StateMachine()   { delete [] buf; delete buf; }

int StateMachine::getState()    { return state; }
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
        return cchar;
    }
    return error;
}

char* StateMachine::step(int symb)
{
    printf ("state machine: %d\n", getState());
    printf ("new symbol: %d\n", symb);
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
    if (state == s_null || state == s_separate)
        return makeLexeme();
    else
        return NULL;
}



void StateMachine::getSymbol (int symb)  /* using special buf for ungets */
{
    int i;
    if (s_buf){
        for (i = 0; buf[i] != 0; i++)
        {}
        buf[i] = s_buf[0];
        buf[i+1] = 0;
    }
        s_buf[0] = symb;
printf ("BUFFER: %s\n", buf);
}
void StateMachine::addSymbol (int symb)  /* without ungets */
{
    int i;
    for (i = 0; buf[i] != 0; i++)
    {}
    buf[i] = symb;
    buf[i+1] = 0;
printf ("BUFFER: %s\n", buf);
}
char* StateMachine::makeLexeme()
{
printf ("\nMake lexeme\nbuf: %s\n",s_buf);
    char* lex;
    int i;
    if (s_buf && !check_separating_character(s_buf[0])) /*!!!*/
    {
        for (i = 0; buf[i] != 0; i++)
        {}
        buf[i] = s_buf[0];
        buf[i+1] = 0;
	s_buf[0] = 0;
    }
printf ("LEXEME: %s\n\n", buf);
    if (buf[0]!=0)
    {
        for (i = 0; buf[i] != 0; i++)
        {}
        lex = new char[i+1];
        for (i = 0; buf[i] != 0; i++){
            lex[i] = buf[i];
        }
        lex[i+1] = 0;
        for (i = 0; buf[i] != 0; i++)
        {
            buf[i] = 0;
        }
        return lex;
    }else
        return NULL;
}



void StateMachine::stateError() /* throw? */
{
    printf ("Error: lexeme expected\n");
}
void StateMachine::stateNull(int symb)
{
    if (symb >= '0' && symb <= '9')
    {
        state = s_number;
        getSymbol(symb);
    }
    else if (symb == '?' || symb == '@' || symb == '$' )
    {
        state = s_indeficator;
        getSymbol(symb);
    }
    else if ((symb >= 'A' && symb <= 'Z')
        || (symb >= 'a' && symb <= 'z'))
    {
        state = s_key_word;
        getSymbol(symb);
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
        state =  lexeme_type =  s_separate;
        addSymbol(symb);
    }
    else if (!check_space(symb))
        state = s_error;
}
void StateMachine::stateSeparate(int symb)
{
    if (!check_space(symb))
        addSymbol(symb);
    lexeme_type = s_separate;
    state = s_null;
}
void StateMachine::stateNumber(int symb)
{
    if (check_space(symb))
    {
        lexeme_type = s_number;
        state = s_null;
    }
    else if (check_separating_character(symb))
        state = s_separate;
    else
    {
        if (symb < '0' || symb > '9')
            state = s_error;
        else
            getSymbol(symb);
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
    }
    else
    {
        if (symb < '0' || (symb > '9' && symb < 'A')
            || (symb > 'Z' && symb < 'a') || symb > 'z')
            state = s_error;
        else
            getSymbol(symb);
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
getSymbol(symb);
        lexeme_type = s_key_word;
    }
    else
    {
        if (symb < 'A' || (symb > 'Z' && symb < 'a') || symb > 'z')
            state = s_error;
        else
            getSymbol(symb);
    }
}
void StateMachine::stateAssignment(int symb)
{
    if (symb == '=')
    {
        addSymbol(symb);
        lexeme_type = s_assignment;
        state = s_null;
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

//----------------Lexeme-------------------------------------------------------

LexemeList::LexemeList ()
{
    current = NULL;
    head = NULL;
    tail = NULL;
}

LexemeList::~LexemeList ()
{
    struct lex* tmp;
    while (head)
    {
        tmp = head;
        head = head->next;
		delete tmp->data;
		delete tmp;
    }
}

void LexemeList::addLexeme (const char* str, int num, lexemes type)
{
    struct lex* l = new struct lex;
    l->data = str;
    l->string_num = num;
    l->type = type;
    l->next = NULL;
    if (tail)
    {
		tail->next = l;
		tail = tail->next;
	}
    else
		head = tail = current = l;
}

const char* LexemeList::getCurrent()
{
    return (current->data);
}
const char* LexemeList::getNext()
{
    if (current->next){
        current = current->next;
        return (current->data);
    }
    return (NULL);
}
const char* LexemeList::getFirst()
{
    current = head;
    return (current->data);
}
const char* enumStr[] = { "number", "const char", "variable", "mark",
    "function", "key word", "separator", "assignment"};
void LexemeList::printList()
{
    struct lex* tmp = head;
	while (tmp)
	{
	    printf("%d: %s, %s\n", tmp->string_num, tmp->data,
                enumStr[tmp->type]);
	    tmp = tmp->next;
	}
}

