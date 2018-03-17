class Object{
public:
    abstract char* toString();
}

class String(Object) {
    char* value
public:
    String(const char* newValue);
    ~String();
    char* toString() const;
}

class Player(Object) {
	const char* name;
	int rawQuantity;
	int productQuantity;
	int moneyQuantity;
	int plantCount;
	int autoPlantCount;
public:
	Player(const char* name);
	Player(const char* name, int raw, int product, int money, int plant,
		int aplant);
    char* toString() const;
	const char* getPlayerName () const;
	int getRawQuantity() const;
	int getProductQuantity() const;
	int getMoneyQuantity() const;
	int getPlantCount() const;
	int getAutoPlantCount() const;
};

class Auction(Object) {
	const char* auctionState;
	const char* winnerName;
	int winningAmount;
	int winningPrice;
public:
	Auction(const char* state, const char* name, int amount, int price);
	char* toString() const;
    char* getAuctionState() const;
	char* getWinnerName() const;
	int getWinningAmount() const;
	int getWinningPrice() const;
}

struct item{
    Object data;
    struct item* next;
};

class List{
    struct item* head;
    struct item* tail;
    struct item* currentItem;

public:
    List();
    ~List();
    void add(Object obj);

    Object getCurrent() const;
    Object getNext();
    Object getFirst();
    
    void printList() const;
    void cleanList();    
};

class UniqueList(List) {
public:
    void add(Object obj);
}

class AuctionList(List){
public:
    int getMinPriceBought() const;
    int getMaxPriceSold() const;   
};