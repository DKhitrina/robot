#ifndef MOD_SYNTAX_HPP
#define MOD_SYNTAX_HPP

#include "Automate.hpp"

class Syntax{
	struct lex* current;
	bool lexemeEqual (struct lex* lx, lexemes l_type);
	bool lexemeEqual (struct lex* lx, int character);
	bool lexemeEqual (struct lex* lx, const char* str);
	void next();
public:
	Syntax();
	~Syntax();
	void check (struct lex* l);
private:
	void S();
	void L();
	void K();
	void H();
	void O();
	void J();
	void R();
	void C();
	void A();
	void Z();
	void B();
	void Q();
	void D();
	void X();
	void G();
	void Y();
	void N();
	void F();
	void E();
};

class SyntErr{
	char* comment;
	char* lexeme;
	int string_num;
public:
	SyntErr(const char* com, const char* lex, int num);
	~SyntErr();
	const char* getComment() const;
	const char* getLexeme() const;
	const int getStringNum() const;
private:
	static char* strDuplicate(const char* str);
};

#endif
