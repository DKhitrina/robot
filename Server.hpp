class MarketState {
	int _availableRawQuantity;
	int _rawPrice;
	int _productDemandQuantity;
	int _productPrice;

public:
	MarketState(const int AvailableRawQuantity, const int RawPrice);
	int getRawPrice();
	int getProductPrice();
	int getAvailableRawQuantity();
	int getProductDemandQuantity();
};

class Player {
	char* _name;
	int _RawQuantity;
	int _ProductQuantity;
	int _moneyQuantity;
	int _plantCount;
	int _autoPlantCount;

public:
	Player(const char* name);
	Player(const char* name, const int RawQuantity);
};

class Server{
	int sockfd;
	char buf[80];
	char rcv_str[80];
	int num_players;

	Player _player;
		
	void SendMsg(const char* buf) const;
	void RcvStr();
	void StringAnalyser(const char* str);
public:	
	Server(const char* serv_ip, int port);
	~Server();

	void EnterName(const char* name) const;
	void CreateGame() const;
	void JoinByNum(int n) const;
	void JoinByName(const char* name) const;
	void QuitGame() const;
	int  GetPlayersCount() const;

	Player getPlayer ();

	MarketState GetMarketState ();
	
	void getPlayersList ();
	void BuyResource(int num, int price) const;
	void MakeProduct(int num) const;
	void SellProduct(int num, int price) const;

	void BuildPlant(int count);
	void BuildAutoPlant(int count);
	void UpgradePlantToAuto();

	void NextTurn() const;
};