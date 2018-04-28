// main part of parser included lexical and grammmar parts

#include "Automate.hpp"
#include "Syntax.hpp"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFSIZE 128

const char* enumStr[] = { "number", "string", "variable", "mark", "function",
	"key word", "separator", "assignment" };

void add_struct_item (struct lex** head, struct lex* l)
{
	struct lex* tmp = (*head);
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
	int c;
	StateMachine s;
	struct lex* head = NULL;
	struct lex* new_struct_item;
	FILE* f;
	if (argc < 2)
	{
		fprintf (stderr, "Too few arguments\n");
		exit (1);
	}
	f = fopen(argv[1], "r");
	if (!f)
	{
		perror (argv[1]);
		exit (1);
	}
	while ((c = fgetc(f))!=EOF)
	{
		new_struct_item = s.step(c);
		if (new_struct_item != NULL)
			add_struct_item(&head, new_struct_item);
	}
//	print_list(head);
	if (s.errorStringNumber()!=0)
		fprintf (stderr, "%d: lexeme error\n", s.errorStringNumber());
	else
	{
		try{
			Syntax s;
			s.check(head);
			printf ("Correct syntax\n");
		}
		catch (const SyntErr &er){
			fprintf (stderr, "%d: %s, '%s' found\n",
				er.getStringNum(), er.getComment(),
				er.getLexeme());
			return 1;
		}
	}

	delete_list (head);
	return 0;
}
