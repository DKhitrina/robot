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

struct players{
    Player data;
    struct players* next;
};

class PlayersList{
    struct players* head;
    struct players* tail;

    struct players* current;

public:
    PlayersList();
    ~PlayersList();
    void add(Player player);

    Player getCurrent();
    Player getNext();
    Player getFirst();
    
    void printList();
    void cleanList();    
};

struct auction_result{
    Auction data;
    struct auction_result* next;
};

class AuctionList{
    struct auction_result* head;
    struct auction_result* tail;

    struct auction_result* current;

public:
    AuctionList();
    ~AuctionList();
    void add(Auction new_result);

    Auction getCurrent();
    Auction getNext();
    Auction getFirst();

    int getMaxPriceBought();
    int getMinPriceBought();
    int getMaxPriceSold();
    int getMinPriceSold();

    void cleanList();    
};