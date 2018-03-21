#ifndef MOD_PARSER_HPP
#define MOD_PARSER_HPP

class StateMachine{
    char* buf;
    char* s_buf;
    enum states {
        s_null, s_error, s_number, s_indeficator, s_key_word, s_assignment, s_string
    } state;

public:
    StateMachine();
    ~StateMachine();
    int getState();
    char* step(int symbol);

private:
    void getSymbol (int symbol);
    void addSymbol (int symbol);
    char* makeLexeme();

    void stateError();
    void stateNull();   
    void stateIdentificator();
    void stateKeyWord();
    void stateAssignment();
    void stateString(); 
};

#endif