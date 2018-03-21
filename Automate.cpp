#include <Parser.hpp>
#include <stdlib.h>

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
    if (symb == ' ' || symb == '\t' || symb == '\n')
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
}
StateMachine::~StateMachine()   { delete [] buf; delete buf; }

int StateMachine::getState()    { return state; }

char* StateMachine::step(int symb)
{
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
        buf[i - 1] = s_buf[0];
        buf[i] = 0;
    }    
        s_buf[0] = symb;
}
void StateMachine::addSymbol (int symb)  /* without ungets */
{
    int i;
    for (i = 0; buf[i] != 0; i++)
    {}
    buf[i - 1] = symb;
    buf[i] = 0;
}
char* StateMachine::makeLexeme()
{
    char* lex;
    int i;
    if (buf){
        for (i = 0; buf[i] != 0; i++)
        {}
        lex = new char[i];
        for (i = 0; buf[i] != 0; i++){
            lex[i] = buf[i];
        }
        lex[i] = 0;
        buf[0] = 0; /* clean buf */
        return lex;
    }
    return NULL;
}



void StateMachine::stateError()
{
    throw "lexeme error";
}
void StateMachine::stateNull(int symb)
{
    if (symb >= '0' || symb <= '9')
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
    }
    else if (check_separating_character(symb))
    {
        state = s_separate;
        addSymbol(symb);
    }
    else if (!check_space(symb))
        state = s_error;
} 
void StateMachine::stateSeparate(int symb)
{
    if (check_space(symb))
        state = s_null;
    addSymbol(symb);
}
void StateMachine::stateNumber(int symb)
{
    if (check_space(symb))
        state = s_null;
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
        state = s_null;
    else if (check_separating_character(symb))
        state = s_separate;  
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
        state = s_null;
    else if (check_separating_character(symb))
        state = s_separate;  
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
        state = s_null;
        addSymbol(symb);
    }
    else
        state = s_error;
}
void StateMachine::stateString(int symb)
{
    if (symb == '"')
        state = s_null;
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

LexemeList::~LexemeList ()  { delete l; }
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
void LexemeList::printList()
{
    struct lex* tmp = head; 
	while (tmp)
    {
		printf("%s\n", tmp->data);
		tmp = tmp->next;
	}
}
void LexemeList::addLexeme (const char* str, int num, lexemes type)
{
    struct lex* l = new struct lex;
    l->data = str;
    l->string_num = n;
    l->type = t;
    next = NULL;
    if (tail)
    {
		tail->next = p;
		tail = tail->next;
	}
    else
		head = tail = current = p;
}
