// main part of parser included lexical and grammmar parts

#include <Parser.hpp>
#define BUFSIZE 128

int main(int argc, char** argv)
{
    char* buf = new char[BUFSIZE];
    char* new_str;
    int count, lex_type;
    int str_count = 1;
    int fd = open(argv[1], O_RDONLY)
    if (fd==-1)
    {
        printf ("Error: can not open file");
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
                lex_type = s.getLexemeType();
                l.addLexeme(new_str, str_count, lex_type);
            }
        }
        buf[0] = 0;
    }
    l.printList();
    return 0;
}