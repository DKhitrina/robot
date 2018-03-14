class Market {
	int rawQuantity;
	int rawPrice;
	int productQuantity;
	int productPrice;

public:
	Market(int raw, int raw_price, int product, int product_price);
	int getRawPrice();
	int getProductPrice();
	int getRawQuantity();
	int getProductQuantity();
};

class Player {
	const char* name;
	int rawQuantity;
	int productQuantity;
	int moneyQuantity;
	int plantCount;
	int autoPlantCount;

public:
	Player(const char* str);
	Player(const char* str, int raw, int product, int money, int plant,
		int aplant);
	int getRawQuantity();
	int getProductQuantity();
	int getMoneyQuantity();
	int getPlantCount();
	int getAutoPlantCount();
};

class Server{
	int sockfd;
	char buf[80];
	char rcv_str[80];
	int num_players;

	Player player;
	Market market;
		
	void sendMsg(const char* buf) const;
	void rcvMsg();
	void analyseString(const char* str);

public:	
	Server(const char* serv_ip, int port);
	~Server();

	void enterName(const char* name) const;
	void createGame() const;
	void joinByNum(int n) const;
	void joinByName(const char* name) const;
	void quitGame() const;
	int  getPlayersCount() const;

	Player getPlayer ();
	Market getMarket ();
	
	void getPlayersList ();
	void buyResource(int num, int price) const;
	void makeProduct(int num) const;
	void sellProduct(int num, int price) const;

	void buildPlant() const;
	void buildAutoPlant() const;
	void upgradePlantToAuto() const;

	void nextTurn() const;
};