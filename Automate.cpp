class StateMachine{
    char* buf;
    char s_buf[1];
    enum states {
        s_number, s_indeficator, s_key_word, s_assignment, s_string
    } state;
public:
    StateMachine()  { buf = new char[128]; }
    ~StateMachine() { delete [] buf; }
    char Step(const char* symbol);
};

char StateMachine::Step(const char* symbol){
    switch(state){
    case s_number:
        
    case s_indeficator:

    case s_key_word:

    case s_assignment:

    case s_string:

    }
}