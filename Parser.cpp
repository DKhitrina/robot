// main part of parser included lexical and grammmar parts

#include "Automate.hpp"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFSIZE 128

int main(int argc, char** argv)
{
    char* buf = new char[BUFSIZE];
    char* new_str;
    int count, i;
    lexemes  lex_type;
    int err_str = 0, str_count = 1;
    int fd = open(argv[1], O_RDONLY);
    if (fd==-1)
    {
         printf ("Error: can not open file\n");
         exit (1);
    }
    StateMachine s;
    LexemeList l;
    while ((count = read(fd, buf, BUFSIZE))!=0){
        for (i = 0; i < count; i++)
        {
            new_str = s.step(buf[i]);
            if (buf[i] == '\n')
                str_count ++;
            if (new_str != NULL)
            {
                lex_type = s.getLexemeType(new_str);
                l.addLexeme(new_str, str_count, lex_type);
            }
	    if (!err_str && s.ifError())
		err_str = str_count;
        }
        buf[0] = 0;
    }
    l.printList();

    if (s.ifError())
	printf ("Lexeme Error in %d string\n", err_str);
    return 0;
}
