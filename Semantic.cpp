#include "Semantic.hpp"
#include <string.h>
#include <stdio.h>

int cmp_str (const char* ar1, const char* ar2)
{
	int i = 0;
	while (ar1[i]!=0)
	{
		if (ar1[i]!=ar2[i])
			return 0;
		i++;
	}
	if (ar2[i]!=0)
		return 0;
	return 1;
}

int Semantic::lexemeEqual (struct lex* l, lexemes l_type)
{
	if (l->type == l_type)
		return 1;
	else
		return 0;
}
int Semantic::lexemeEqual (struct lex* l, int character)
{
	if (l->data[0] == character)
		return 1;
	else
		return 0;
}
int Semantic::lexemeEqual (struct lex* l, const char* str)
{
	if (cmp_str(l->data, str))
		return 1;
	else
		return 0;
}

void Semantic::next ()
{
	current =  current->next;
}

int Semantic::firstK(const char* str)
{
	if (cmp_str(str, "if") || cmp_str(str, "buy") || cmp_str(str, "sell")
		|| cmp_str(str, "print") || cmp_str(str, "prod")
		|| cmp_str(str, "build"))
		return 1;
	else
		return 0;
}
//-----------------------------------------------------------------------------

Semantic::Semantic()
{
	current = new struct lex;
}
Semantic::~Semantic()
{
	delete current;
}
void Semantic::check (struct lex* l)
{
	current = l;
	S();
}

//-----------------------------------------------------------------------------

void Semantic::S()
{
	if (!lexemeEqual(current, "@begin"))
		throw SyntErr("expected '@begin' at the beginning of cycle",
			 current->data, current->string_num);
	next();
	L();
	if (!lexemeEqual(current, "endturn"))
		throw SyntErr("expected 'endturn' before the end of the loop",
			current->data, current->string_num);
	next();
	if (!lexemeEqual(current, ';'))
		throw SyntErr("expected ';' at the end of the expression",
			current->data, current->string_num);
	next();
	if (!lexemeEqual(current, "goto"))
		throw SyntErr("expected 'goto' at the end of the loop",
			current->data, current->string_num);
	next();
	if (!lexemeEqual(current, "@end"))
		throw SyntErr("expected '@end' at the end of the loop",
			current->data, current->string_num);
	next();
	if (current != NULL)
		throw SyntErr("unexpected command after the main loop",
			current->data, current->string_num);
}
void Semantic::L()
{
	if (firstK(current->data) || lexemeEqual(current, variable))
	{
		K();
		if (!lexemeEqual(current, ';'))
			throw SyntErr("expected ';' at the end of expression",
				current->data, current->string_num);
		next();
		L();
	}
}
void Semantic::K()
{
	if (lexemeEqual(current, "if"))
	{
		next();
		H();
	}
	else
	if (lexemeEqual(current, "buy") || lexemeEqual(current, "sell"))
	{
		next();
		Q();
		if (!lexemeEqual(current, ','))
			throw SyntErr("expected ',' between arguments",
				current->data, current->string_num);
		next();
		Q();
	}
	else
	if (lexemeEqual(current, variable))
	{
		next();
		if (!lexemeEqual(current, assignment))
			throw SyntErr("assignment expected", current->data,
				current->string_num);
		next();
		Q();
	}
	else
	if (lexemeEqual(current, "print"))
	{
		next();
		if (!lexemeEqual(current, string))
			throw SyntErr("string expected", current->data,
				current->string_num);
		next();
	}
	else
	if (lexemeEqual(current, "prod") || lexemeEqual(current, "build"))
	{
		next();
		Q();
	}
}
void Semantic::H()
{
	if (!lexemeEqual(current, '('))
		throw SyntErr("expected '(' at the beginning of condition",
			current->data, current->string_num);
	next();
	J();
	if (!lexemeEqual(current, ')'))
		throw SyntErr("expected ')' at the end of condition",
			current->data, current->string_num);
	next();
	if (!lexemeEqual(current, "then"))
		throw SyntErr("'then' expected after condition", current->data,
			current->string_num);
	next();
	K();
	O();
}
void Semantic::O()
{
	if (lexemeEqual(current, "else"))
	{
		next();
		K();
	}
	else
	if (lexemeEqual(current, ';') && lexemeEqual(current->next, "else"))
		throw SyntErr("unexpected ';' before 'else' ", current->data,
			current->string_num);
}
void Semantic::J()
{
	C();
	R();
}
void Semantic::R()
{
	if (lexemeEqual(current,'|'))
	{
		next();
		J();
	}
}
void Semantic::C()
{
	Z();
	A();
}
void Semantic::A()
{
	if (lexemeEqual(current, '&'))
	{
		next();
		C();
	}
}
void Semantic::Z()
{
	Q();
	B();
}
void Semantic::B()
{
	if (lexemeEqual(current, '>') || lexemeEqual(current,'<')
		|| lexemeEqual(current,'='))
	{
		next();
		Q();
	}
}
void Semantic::Q()
{
	X();
	D();
}
void Semantic::D()
{
	if (lexemeEqual(current, '+') || lexemeEqual(current,'-'))
	{
		next();
		Q();
	}
}
void Semantic::X()
{
	Y();
	G();
}
void Semantic::G()
{
	if (lexemeEqual(current, '*') || lexemeEqual(current,'%')
		|| lexemeEqual(current,'/'))
	{
		next();
		X();
	}
}
void Semantic::Y()
{
	if (lexemeEqual(current, variable))
	{
		next();
		N();
	}
	else
	if (lexemeEqual(current, function))
	{
		F();
	}
	else
	if (lexemeEqual(current, number))
	{
		next();
		/* end of recursive descent */
	}
	else
	if (lexemeEqual(current, '('))
	{
		next();
		Q();
		if (!lexemeEqual(current, ')'))
			throw SyntErr("')' expected", current->data,
				current->string_num);
		next();
	}
	else
		throw SyntErr ("unexpected lexeme", current->data,
			current->string_num);
}
void Semantic::N()
{
	if (lexemeEqual(current, '['))
	{
		next();
		Q();
		if (!lexemeEqual(current, ']'))
			throw SyntErr("']' expected after number of array element",
				current->data, current->string_num);
		next();
	}
		/* end of recursive descent */
}

void Semantic::F()
{
	if (!lexemeEqual(current, function))
		throw SyntErr("expected function", current->data,
			current->string_num);
	next();
	E();
}
void Semantic::E()
{
	if (lexemeEqual(current, '('))
	{
		next();
		F();
		if (!lexemeEqual(current, ')'))
			throw SyntErr("expected ')' after the argument",
				current->data, current->string_num);
		next();
	}
		/* end of recursive descent */
}


//-----------------------------------------------------------------------------

SyntErr::SyntErr(const char* com, const char* lex, int num)
{
	comment = strDuplicate(com);
	lexeme = strDuplicate(lex);
	string_num = num;
}

SyntErr::~SyntErr()
{
	delete [] comment;
	delete [] lexeme;
}

char* SyntErr::getComment() { return comment; }
char* SyntErr::getLexeme() { return lexeme; }
int SyntErr::getStringNum() { return string_num; }

char* SyntErr::strDuplicate(const char* str)
{
	char* cp = new char [strlen(str)+1];
	strcpy (cp, str);
	return cp;
}
