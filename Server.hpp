#include <Containers.hpp>

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

class Server{
	int sockfd;
	char buf[80];
	char rcv_str[80];
	int num_players;

	Player player;
	Market market;
	PlayersList players_list;
	AuctionList auction_list;

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

	void getMarket() const;
	void getPlayersInfo() const;

	void buyResource(int num, int price) const;
	void makeProduct(int num) const;
	void sellProduct(int num, int price) const;

	void buildPlant() const;
	void buildAutoPlant() const;
	void upgradePlantToAuto() const;

	void nextTurn() const;
};
