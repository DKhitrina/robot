// main part of parser included lexical and grammmar parts

#include "Automate.hpp"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFSIZE 128

const char* enumStr[] = { "number", "string", "variable", "mark", "function",
	"key word", "separator", "assignment" };

struct lex{
	const char* data;
	int string_num;
	lexemes type;
	struct lex* next;
};

void add_lexeme (struct lex** head, const char* str, int num, lexemes type)
{
	struct lex* tmp = (*head);
	struct lex* l = new struct lex;
	l->data = str;
	l->string_num = num;
	l->type = type;
	l->next = NULL;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = l;
	}
	else
		(*head) = l;
}

void print_list (struct lex* head)
{
	struct lex* tmp = head;
	while (tmp)
	{
		printf ("%d: %s, %s\n", tmp->string_num, tmp->data,
			enumStr[tmp->type]);
		tmp = tmp->next;
	}
}

void delete_list(struct lex* head)
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

int main(int argc, char** argv)
{
	char* buf = new char[BUFSIZE];
	char* new_str;
	int count, i;
	lexemes  lex_type;
	StateMachine s;
	struct lex* head = NULL;
	int err_str = 0, str_count = 1;
	int fd = open(argv[1], O_RDONLY);
	if (fd==-1){
		printf ("Error: can not open file\n");
		exit (1);
	}
	while ((count = read(fd, buf, BUFSIZE))!=0){
		for (i = 0; i < count; i++){
			new_str = s.step(buf[i]);
			if (new_str != NULL){
				lex_type = s.getLexemeType(new_str);
				add_lexeme(&head, new_str, str_count, lex_type);
			}
			if (buf[i] == '\n')
				str_count ++;
			if (s.ifError() && !err_str)
				err_str = str_count;
		}
		buf[0] = 0;
	}

	print_list(head);

	if (s.ifError())
		printf ("%d: lexeme error\n", err_str);
	delete [] buf;
	delete_list (head);
	return 0;
}
