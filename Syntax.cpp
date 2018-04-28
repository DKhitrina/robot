#include "Syntax.hpp"
#include <string.h>
#include <stdio.h>

bool cmp_str (const char* ar1, const char* ar2)
{
	int i = 0;
	while (ar1[i]!=0)
	{
		if (ar1[i]!=ar2[i])
			return false;
		i++;
	}
	if (ar2[i]!=0)
		return false;
	return true;
}

bool Syntax::lexemeEqual (struct lex* lx, lexemes l_type)
{
	if (lx->type == l_type)
		return true;
	else
		return false;
}
bool Syntax::lexemeEqual (struct lex* lx, int character)
{
	if (lx->data[0] == character)
		return true;
	else
		return false;
}
bool Syntax::lexemeEqual (struct lex* lx, const char* str)
{
	if (cmp_str(lx->data, str))
		return true;
	else
		return false;
}

void Syntax::next ()
{
	current =  current->next;
}

bool firstK(const char* str)
{
	if ( cmp_str(str, "endturn") || cmp_str(str, "if")
		|| cmp_str(str, "buy") || cmp_str(str, "sell")
		|| cmp_str(str, "print") || cmp_str(str, "prod")
		|| cmp_str(str, "build"))
		return true;
	else
		return false;
}
//-----------------------------------------------------------------------------

Syntax::Syntax()
{
	current = new struct lex;
}
Syntax::~Syntax()
{
	delete current;
}
void Syntax::check (struct lex* l)
{
	current = l;
	S();
}

//-----------------------------------------------------------------------------

void Syntax::S()
{
	if (!lexemeEqual(current, "@begin"))
		throw SyntErr("expected '@begin' at the beginning of cycle",
			 current->data, current->string_num);
	next();
	L();
	if (!lexemeEqual(current, "goto"))
		throw SyntErr("expected 'goto' at the end of the loop",
			current->data, current->string_num);
	next();
	if (!lexemeEqual(current, "@begin"))
		throw SyntErr("expected '@begin' at the end of the loop",
			current->data, current->string_num);
	next();
	if (current != NULL)
		throw SyntErr("unexpected command after the main loop",
			current->data, current->string_num);
}
void Syntax::L()
{
	if (firstK(current->data) || lexemeEqual(current, variable))
	{
		K();
		if (!lexemeEqual(current, ';'))
			throw SyntErr("expected ';' at the end of operator",
				current->data, current->string_num);
		next();
		L();
	}
}
void Syntax::K()
{
	if (lexemeEqual(current, "endturn")
		|| lexemeEqual(current, "info")
		|| lexemeEqual(current, "market"))
	{
		next();
		/* end of recursive descent */
	}
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
void Syntax::H()
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
void Syntax::O()
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
void Syntax::J()
{
	C();
	R();
}
void Syntax::R()
{
	if (lexemeEqual(current,'|'))
	{
		next();
		J();
	}
}
void Syntax::C()
{
	Z();
	A();
}
void Syntax::A()
{
	if (lexemeEqual(current, '&'))
	{
		next();
		C();
	}
}
void Syntax::Z()
{
	if (lexemeEqual(current, variable) || lexemeEqual(current, function)
		|| lexemeEqual(current, number) || lexemeEqual(current, '-')
		|| lexemeEqual(current, '('))
	{
		Q();
		B();
	}
	else
	if (lexemeEqual(current, '!'))
	{
		next();
		if (!lexemeEqual(current, '('))
			throw SyntErr("expected '(' for condision after '!'",
				current->data, current->string_num);
		next();
		J();
		if (!lexemeEqual(current, ')'))
			throw SyntErr("expected ')' at end of '!' condition",
				current->data, current->string_num);
		next();
	}
	else
		throw SyntErr ("condision expected",
			current->data, current->string_num);
}
void Syntax::B()
{
	if (lexemeEqual(current, '>') || lexemeEqual(current,'<')
		|| lexemeEqual(current,'='))
	{
		next();
		Q();
	}
}
void Syntax::Q()
{
	X();
	D();
}
void Syntax::D()
{
	if (lexemeEqual(current, '+') || lexemeEqual(current,'-'))
	{
		next();
		Q();
	}
}
void Syntax::X()
{
	Y();
	G();

}
void Syntax::G()
{
	if (lexemeEqual(current, '*') || lexemeEqual(current,'%')
		|| lexemeEqual(current,'/'))
	{
		next();
		X();
	}
}
void Syntax::Y()
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
	if (lexemeEqual(current, number) || lexemeEqual(current, '-'))
	{
		if (lexemeEqual(current, '-'))
		{
			next();
			if (!lexemeEqual(current, number))
				throw SyntErr ("expected negative number",
					current->data, current->string_num);
		}
		next();
		/* end of recursive descent */
	}
	else
	if (lexemeEqual(current, '('))
	{
		next();
		Q();
		if (!lexemeEqual(current, ')'))
			throw SyntErr("')' expected after expression",
				current->data, current->string_num);
		next();
	}
	else
		throw SyntErr ("unexpected lexeme", current->data,
			current->string_num);
}
void Syntax::N()
{
	if (lexemeEqual(current, '['))
	{
		next();
		Q();
		if (!lexemeEqual(current, ']'))
			throw SyntErr("']' expected after element number",
				current->data, current->string_num);
		next();
	}
		/* end of recursive descent */
}
void Syntax::F()
{
	if (!lexemeEqual(current, function))
		throw SyntErr("expected function", current->data,
			current->string_num);
	next();
	E();
}
void Syntax::E()
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

const char* SyntErr::getComment() const { return comment; }
const char* SyntErr::getLexeme() const { return lexeme; }
const int SyntErr::getStringNum() const { return string_num; }

char* SyntErr::strDuplicate(const char* str)
{
	char* cp = new char [strlen(str)+1];
	strcpy (cp, str);
	return cp;
}
