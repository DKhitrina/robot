struct item{
    char* data;
    struct item* next;
};

class List{
    struct item* head;
    struct item* tail;

    struct item* currentItem;
public:
    List();
    ~List();
    void add(char* str);

    char* getCurrent();
    char* getNext();
    char* getFirst();
    
    void printList();
    void cleanList();    
};