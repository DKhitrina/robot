enum evaluate { yes, no };
enum lexemes { number, cchar, variable, mark, function, key_word,
    separator, assignment, error};

class Semantic{
	int lexemeEqual (struct lex* l, lexemes l_type);
	int lexemeEqual (struct lex* l, int character);
	int lexemeEqual (struct lex* l, const char* str);
	struct lex* next();
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
}
