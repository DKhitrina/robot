// main part of parser included lexical and grammmar parts

#include <Parser.hpp>
#define BUFSIZE 128

lexemes def_lexeme(char* str)
{
    int ch = str[0];
    if (ch >= '0' && ch <= '9')
        return number;
    else if (ch = '"')
        return cchar;    
    else if (ch = '$')
        return variable;   
    else if (ch = '@')
        return mark;   
    else if (ch = '?')
        return function;                           
    else if (ch >= 'A' && ch <= 'Z' || ch >= 'a' && ch <= 'z')
        return key_word;
    else if (check_separating_character(ch))
        return separator;
    else 
        return error;        
}

int main()
{
    char* buf = new char[BUFSIZE];
    char* new_str;
    int str_count = 1;
    int fd = open();
    StateMachine s;
    LexemeList l;
    while (read(fd, buf, BUFSIZE)!=0){
        for (i = 0; i < BUFSIZE; i++)
        {
            new_str = s.step(buf[i]);

            if (buf[i] == '\n')
                str_count ++;
            if (new_str != NULL)
                l.addLexeme(new_str, str_count, def_lexeme(new_str))
        }
        buf[0] = 0;
    }
    l.printList();
    return 0;
}