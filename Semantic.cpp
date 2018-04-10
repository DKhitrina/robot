#include "Semantic.hpp"
#include "Utils.hpp"
/*
	как запускать рекурсивный спуск, то есть что писать в check
	правильно ли написан next
	что делать когда дошли до конца рекурсии
*/

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
	/* I didnt decided yet... */
	current =  current->next;
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
evaluate Semantic::check (struct lex* l)
{
	/* ???? */
}

//-----------------------------------------------------------------------------

void Semantic::S()
{
	if (!lexemeEqual(current, mark))
		throw SyntErr("expected mark at the beginning of the cycle",
			 current->data, current->string_num);
	next();
	L();
	next();
	if (!lexemeEqual(current, ';'))
		throw SyntErr("expected ';' at the end of the expression",
			current->data, current->string_num);
	next();
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
	if (!lexemeEqual(current, mark))
		throw SyntErr("expected mark at the end of the loop",
			current->data, current->string_num);
	next();
	if (current != NULL)
		throw SyntError("unexpected command after the main loop",
			current->data, current->string_num);
}
void Semantic::L()
{
	if (lexemeEqual(current, key_word) || lexemeEqual(current, variable)
		|| lexemeEqual(current, ';'))
	{
		next();
		K();
	}
	else
		throw SyntError("unexpected lexeme instead of expression",
			current->data, current->string_num);	
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
		next();
		if (!lexemeEqual(current, ';'))
			throw SyntErr("expected ';' at the end of the expression",
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
		if (!lexemeEqual(current, cchar))
			throw SyntErr("string expected", current->data,
				current->string_num);
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
	C();
	next();
	if (!lexemeEqual(current, ')'))
		throw SyntErr("expected ')' at the end of condition",
			current->data, current->string_num);	
	next();
	if (!lexemeEqual(current, "then")
		throw SyntErr("'then' expected after condition", current->data,
			current->string_num);	
	next();
	K();
	next();
	O();
}
void Semantic::O()
{
	if (lexemeEqual(current, "else")
	{
		next();
		K();
	}
}
void Semantic::C()
{
	Z();
	next();
	A();
}
void Semantic::A()
{
	if (lexemeEqual(current, '&') || lexemeEqual(current,'|'))
	{
		next();
		Z();
	}	
}
void Semantic::Z()
{
	Q();
	next();
	B();
}
void Semantic::B()
{
	if (lexemeEqual(current, '>') || lexemeEqual(current,'<') || lexemeEqual(current,'='))
	{
		next();
		Q();
	}	
}
void Semantic::Q()
{
	X();
	next();
	D();
}
void Semantic::D()
{
	if (lexemeEqual(current, '+') || lexemeEqual(current,'-'))
	{
		next();
		X();
	}
}
void Semantic::X()
{
	Y();
	next();
	G();
}
void Semantic::G()
{
	if (lexemeEqual(current, '*') || lexemeEqual(current,'%') || lexemeEqual(current,'/'))
	{
		next();
		Y();
	}	
}
void Semantic::Y()
{
	if(lexemeEqual(current, variable))
	{
		/*дошли до конца рекурсивного спуска*/
	}
	else
	if(lexemeEqual(current, function))
	{
		next();
		F();
	}
	else
	if(lexemeEqual(current, number))
	{
		/*дошли до конца рекурсивного спуска*/
	}
	else
	if(lexemeEqual(current, '('))
	{
		next();
		Q();
		next();
		if (!lexemeEqual(current, ')'))
			throw SyntErr("')' expected", current->data, current->string_num);
	}
	else
		throw SyntErr ("unexpected lexeme", current->data, current->string_num);
}
void Semantic::M()
{
	if (lexemeEqual(current, "buy"))
	{
		/*дошли до конца рекурсивного спуска*/
	}
	else
	if (lexemeEqual(current, "sell"))
	{
		/*дошли до конца рекурсивного спуска*/
	}
	else
		throw SyntErr ("unexpected lexeme after 'buy'/'sell'", current->data, current->string_num);
}
void Semantic::I()
{
	if (lexemeEqual(current, "print"))
	{
		/*дошли до конца рекурсивного спуска*/
	}
	else
		throw SyntErr ("unexpected lexeme after 'print'", current->data, current->string_num);	
}
void Semantic::P()
{
	if (lexemeEqual(current, "prod"))
	{
		/*дошли до конца рекурсивного спуска*/
	}
	else
	if (lexemeEqual(current, "build"))
	{
		/*дошли до конца рекурсивного спуска*/
	}
	else
		throw SyntErr ("unexpected lexeme after 'prod'/'build'", current->data, current->string_num);
}
void Semantic::F()
{
	if (!lexemeEqual(current, function))
		throw SyntErr("expected function", current->data, current->string_num);
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
			throw SyntErr("expected ')' after the argument", current->data, current->string_num);
	}
}