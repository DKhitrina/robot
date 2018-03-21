#include <Parser.hpp>

int check_separating_character (int ch) /* 1 - match, 0 - don't match */
{ 
    if (symb == ' ' || symb == '\t' || symb == '\n' || symb == '+'
        || symb == '-' || symb == '*' || symb == '/' || symb == '%'
        || symb == '<' || symb == '>' || symb == '=' || symb == ':')
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

char* StateMachine::Step(int symb)
{
    switch (state)
    {
    case s_null:
        stateNull(symb);
        break;
    case s_number:
        stateNumber(symb);
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
    if (state == s_null)
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
    else if (symb >= 'A' && symb <= 'Z'
        || symb >= 'a' && symb <= 'z')
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
        state = s_string;
    else if (!check_separating_character(symb))
        state = s_error;
} 
void StateMachine::stateNumber()
{
    if (check_separating_character(symb))
        state = s_null;
    else
    {
        if (symb < '0' || symb > '9')
            state = s_error;
        else
            getSymbol(symb);
    }
}
void StateMachine::stateIdentificator()
{
    if (check_separating_character(symb))
        state = s_null;
    else
    {
        if (symb < '0' || (symb > '9' && symb < 'A')
            || (symb > 'Z' && symb < 'a') || symb > 'z')
            state = s_error;
        else
            getSymbol(symb);
    }
}
void StateMachine::stateKeyWord()
{
    if (check_separating_character(symb))
        state = s_null;
    else
    {
        if (symb < 'A' || (symb > 'Z' && symb < 'a') || symb > 'z')
            state = s_error;
        else
            getSymbol(symb);
    }
}
void StateMachine::stateAssignment()
{
    if (symb == '=')
    {
        state = s_null;
        addSymbol(symb);
    }
    else
        state = s_error;
}
void StateMachine::stateString()
{
    if (symb == '"')
        state = s_null;
    else
        addSymbol(symb);
}