class Market {
	int rawQuantity;
	int rawPrice;
	int productQuantity;
	int productPrice;

public:
	Market(int raw, int raw_price, int product, int product_price);
	int getRawPrice() const;
	int getProductPrice() const;
	int getRawQuantity() const;
	int getProductQuantity() const;
};

class Auction {
	const char* auctionState;
	const char* winnerName;
	int winningAmount;
	int winningPrice;
public:
	Auction(const char* state, const char* name, int amount, int price);
	char* getAuctionState() const;
	char* getWinnerName() const;
	int getWinningAmount() const;
	int getWinningPrice() const;
}

class Player {
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
	const char* getPlayerName () const;
	int getRawQuantity() const;
	int getProductQuantity() const;
	int getMoneyQuantity() const;
	int getPlantCount() const;
	int getAutoPlantCount() const;
};

class Server{
	int sockfd;
	char buf[80];
	char rcv_str[80];
	int num_players;

	Player player;
	Market market;
	struct players* list_of_players;

	void sendMsg(const char* buf) const;
	void rcvMsg();
	void analyseString(const char* str);

public:
	Server(const char* serv_ip, int port);
	~Server();

	void enterName(const char* name) const;
	void createGame() const;
	void joinGame(int n) const;
	void joinGame(const char* name) const;
	void quitGame() const;
	int  getPlayersCount() const;

	void getPlayersList ();
	void buyResource(int num, int price) const;
	void makeProduct(int num) const;
	void sellProduct(int num, int price) const;

	void buildPlant() const;
	void buildAutoPlant() const;
	void upgradePlantToAuto() const;

	void nextTurn() const;
};
