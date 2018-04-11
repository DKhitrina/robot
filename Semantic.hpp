#ifndef MOD_SEMANTIC_HPP
#define MOD_SEMANTIC_HPP

#include "Automate.hpp"

enum evaluate { correct, incorrect };

class Semantic{
	int lexemeEqual (struct lex* l, lexemes l_type);
	int lexemeEqual (struct lex* l, int character);
	int lexemeEqual (struct lex* l, const char* str);
	void next();
	void epselentRule();
	struct lex* previous;
	struct lex* current;
public:
	Semantic();
	~Semantic();
	evaluate check (struct lex* l);
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
	void M();
	void I();
	void P();
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
	char* getComment();
	char* getLexeme();
	int getStringNum();
private:
	static char* strDuplicate(const char* str);
};

#endif
