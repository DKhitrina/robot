#ifndef MOD_PARSER_HPP
#define MOD_PARSER_HPP

enum lexemes { number, cchar, variable, mark, function, key_word,
    separator, assignment, error};

class StateMachine{
    char* buf;
    char* s_buf;
    enum states {
        s_null, s_error, s_separate, s_number, s_indeficator, s_key_word,
        s_assignment, s_string
    } state, lexeme_type;

    void addCharacter (int symbol);
    void addSymbol (int symbol);
    char* makeLexeme();

public:
    StateMachine();
    ~StateMachine();
    int ifError();
    lexemes getLexemeType(char* str);
    char* step(int symbol);

private:
    void stateError();
    void stateNull(int symbol);
    void stateSeparate(int symbol);
    void stateNumber(int symbol);
    void stateIdentificator(int symbol);
    void stateKeyWord(int symbol);
    void stateAssignment(int symbol);
    void stateString(int symbol);
};

struct lex{
    const char* data;
    int string_num;
    lexemes type;
    struct lex* next;
};

class LexemeList{
    struct lex* current;
    struct lex* head;
    struct lex* tail;
public:
    LexemeList();
    ~LexemeList();

    void addLexeme(const char* str, int num, lexemes type);

    const char* getCurrent();
    const char* getNext();
    const char* getFirst();

    void printList();
};

#endif
