class StateMachine{
    char* buf;
    char s_buf[1];
    enum states {
        s_null, s_number, s_indeficator, s_key_word, s_assignment, s_string
    } state;
public:
    StateMachine()  { buf = new char[128]; }
    ~StateMachine() { delete [] buf; }
    char* Step(int symbol, int string_num);
};

int check_separating_character (int ch) /* 1 - match, 0 - don't match */
{ 
    if (symb == ' ' || symb == '\t' || symb == '\n' || symb == '+'
        || symb == '-' || symb == '*' || symb == '/' || symb == '%'
        || symb == '<' || symb == '>' || symb == '=' || symb == ':')
        return 1;
    else    
        return 0;
}
void add_symb_in_buf (int symb)
{
    int i;
    for (i = 0; buf[i]==0; i++) {}
    buf[i-1] = symb;
    buf[i] = 0;
}

char* make_lexeme()
{

    /* ??? */

}

char* StateMachine::Step(int symb, int string_num){
    switch(state){
    case s_null:
        if (symb>='0' || symb<='9'){
            state = s_number;
            add_symb_in_buf (symb);
        }
        else
        if (symb == '?' || symb == '@' || symb == '$'){
            state = s_indeficator;
            add_symb_in_buf (symb);
        }
        else
        if (symb>='A' && symb<='Z' || symb>='a' && symb<='z'){
            state = s_key_word;
            add_symb_in_buf (symb);
        }    
        else
        if (symb == ':'){
            state = s_assignment;
            add_symb_in_buf (symb);
        }    
        else
        if (symb == '"')
            state = s_string;
        else                                                
        if (symb != ' ' && symb != '\t' && symb != '\n')
            throw FileException(string_num, "lexem analysys is failed");
        break;    
    case s_number:
        if (check_separating_character(symb)){
            state = s_null;
            return make_lexeme();
        }else{
            if (symb<'0' || symb>'9')
                throw FileException(string_num, "lexeme analysys is failed");
            else
                add_symb_in_buf(symb);
        }        
        break;
    case s_indeficator:
        if (check_separating_character(symb)){
            state = s_null;
            return make_lexeme();
        }else{
            if (symb<'0' || (symb>'9' && symb<'A') || (symb>'Z' && symb<'a') || symb>'z')
                throw FileException(string_num, "lexeme analysys is failed");
            else
                buf = add_symb_in_buf(symb);
        }                 
        break;
    case s_key_word:
        if (check_separating_character(symb)){
            state = s_null;
            return make_lexeme();
        }else{
            if (symb<'A' || (symb>'Z' && symb<'a') || symb>'z')
                throw FileException(string_num, "lexeme analysys is failed");
            else
                buf = add_symb_in_buf(symb);
        }                 
        break;
    case s_assignment:
        if (symb == '='){
            state = s_null;
            buf = add_symb_in_buf(symb);
            return make_lexeme();
        }else    
            throw FileException(string_num, "lexem analysys is failed");
        break;    
    case s_string:
        if (symb == '"'){
            state = s_null;
            return make_lexeme();
        }
        break;
    }
}