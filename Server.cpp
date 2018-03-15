#include <sys/types.h>
#include <sys/socket.h>
#include <Server.hpp>

char* int_to_str(int num)
{
	char* ar = NULL;
	int с = 0, n = num;
	while (n!=0){
		n = n/10;
		c++;
	}
	ar = malloc(c+1);
	ar[c] = 0;
	n = num;
	for(i=1; i<=c; i++){
		ar[c-i]=(n%10) + '0';
		n=n/10;
	}
	return ar;
}

int str_to_int(const char* str)
{
	char* ar = str;
	int num = 0;
	while (ar!=0){
		num = num*10 + ar[i] - '0';
		i++;
	}
	return num;
}

/* 0 - no match, 1 - match*/
int cmp_str(const char* ar1, const char* ar2)
{
	int i = 0;
	while (ar1[i]!=0){
		if (ar1[i]!=ar2[i]){
			return 0;
		}
		i++;
	}
	if (ar2[i]!=0){
		return 0;
	}
	return 1;
}

-----------------------------------------------------------------------------------------------------------

struct strlist{
	char* data;
	struct strlist* next;
};

void clean_struct (struct item *str)	/* clean list after output */
{
	while (str){
		char *m;
		struct item *tmp = str;
		m = str->data;
		str = str->next;
		free (tmp);
		free (m);
	}
}

char* double_array (char* m, int* ar_form)	/* copy array + double it */
{
	int i;
	char *da;
	da = malloc ((*ar_form)*2);
	*ar_form = (*ar_form)*2;
	for (i = 0; i<=*ar_form; i++){
		da[i] = m[i];
	}
	free (m);
	m = da;
	return m;
}

struct strlist* divide_str(const char* str)
{
	struct strlist* head = NULL;
	struct strlist* end = NULL;
	int i = 0, j = 0;
	int ar_size = 8;
	while (str[j]!='\n'){
		char* m = malloc(ar_size);
		i = 0;
		ar_size = 8;
		while (str[j]!='\n' && str[j]!='\t' && str[j]!=' '){
			if (i>ar_size)
				m = double_array(m, &ar_size);
			m[i]=str[j];
			i++;
			j++;
		}
		struct strlist *p;
		p = malloc (sizeof(struct strlist));
		p->data = new_str;
		p->next = NULL;
		if (end){
			end ->next = p;
			end = end->next;
		}else{
			head = end = p;
		}
	}
	return head;
}

-------------------------------------------------------------------------------

Market(int raw, int raw_price, int product, int product_price);
{
	rawQuantity = raw;
	rawPrice = raw_price;
	productQuantity = product;
	productPrice = product_price;
}
int Market::getRawPrice() const {return rawPrice;}
int Market::getProductPrice() const {return productPrice;}
int Market::getRawQuantity() const {return rawQuantity;}
int Market::getProductQuantity() const {return productQuantity;}

-------------------------------------------------------------------------------

Auction(const char* state, const char* name, int amount, int price);
{
	auctionState = state;
	winnerName = name;
	winningAmount = amount;
	winningPrice = price;	
}
char* Auction::getAuctionState() const {return auctionState;}
char* Auction::getWinnerName() const {return winnerName;}
int Auction::getWinningAmount() const {return winningAmount;}
int Auction::getWinningPrice() const {return winningPrice;}

-------------------------------------------------------------------------------

Player(const char* str)
{
	name = str;
	rawQuantity = 2;
	productQuantity = 2;
	moneyQuantity = 10000;
	plantCount = 2;
	autoPlantCount = 0;
}
Player(const char* str, int raw, int product, int money, int plant,
	int aplant)
{
	name = str;
	rawQuantity = raw;
	productQuantity = product;
	moneyQuantity = money;
	plantCount = plant;
	autoPlantCount = aplant;
}
const char* getPlayerName() const {return name;}
int Player::getRawQuantity() const {return rawQuantity;}
int Player::getProductQuantity() const {return productQuantity;}
int Player::getMoneyQuantity() const {return moneyQuantity;}
int Player::getPlantCount() const {return plantCount;}
int Player::getAutoPlantCount() const {return autoPlantCount;}

-------------------------------------------------------------------------------

void Server::sendMsg (const char* str) const
{
	int wr = write(sockfd, str, strlen(str)+1);
}
void Server::rcvMsg()
{
	int i = 0, j = 0;
	int rd = read(sockfd, buf, sizeof(buf)-1);
	if (re==-1)
		throw										/* error read from socket */
	buf[rd] = '\0';
	/* divide string */
	while(buf!='\n'){
		rcv_str[i]=buf[i];
		i++;
	}
	rcv_str[i]='\n';
	i++;
	/* bufer "shift" */
	while(i<=rd){
		buf[j]=buf[i];
		i++;
		j++;
	}
	return rcv_str;
}
void Server::analyseString(const char* str)
{
/*make double array*/
	if(ar[0] == '&'){
		if (cmp_str(ar[1], "MARKET")){
			Market m(str_to_num(ar[2]), str_to_num(ar[3]),
				str_to_num(ar[4]), str_to_num(ar[5]));
			market = m;
		}
		if (cmp_str(ar[1], "INFO")){
			Player p(a[2],str_to_num(ar[3]),str_to_num(ar[4]),
				str_to_num(ar[5]),str_to_num(ar[6]));
			getPlayerList(p);
		}
	}
}


Server::Server(const char* serv_ip, int port)
{
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd==-1){
		throw										/* smth */
	}
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	if (!inet_aton(serv_ip, &(addr.sin_addr))){
		throw										/* invalid IP */
	}
	if (connect(sockfd, addr, sizeof(addr)!=0){
		throw										/* failed connection */
	}
}
Server::~Server()
{
	shutdown(sockfd, 2);
	close(sockfd);
}


void Server::enterName(const char* name) const
{
	sendMsg(name); sendMsg("\n");
}
void Server::createGame() const {sendMsg(".create\n");}
void Server::joinGame(int n) const
{
	sendMsg(".join "); sendMsg(int_to_str(n)); sendMsg("\n");
}
void Server::joinGame(const char* name) const
{
	sendMsg(".join "); sendMsg(name); sendMsg("\n");
}
void Server::quitGame() const 	{sendMsg("quit\n");}
int  Server::getPlayersCount() const 	{return num_players;}


struct players {
	Player data;
	struct players* next;
};
void Server::getPlayersList(Player p1)
{
	char* name1 = p1.getPlayerName();
	char* name2;
	struct players* temp = list_of_players;
	struct palyers* list;
	while(temp){
		name2 = (temp->data).getPlayerName;
		if (cmp_str(name1, name2)){
			temp->data = p1;
			return;
		}
		temp = temp->next;
	}
	list = malloc(sizeof(struct players));
	list->data = p1;
	list->next = NULL;
	temp = list_of_players;
	if (temp){
		while (temp->next)
			temp = temp->next;
		temp->next = list;
	}
}
void Server::buyResource(int num, int price) const
{
	sendMsg("buy "); sendMsg(int_to_str(num)); sendMsg(int_to_str(price)); sendMsg("\n");
}
void Server::makeProduct(int num) const
{
	sendMsg("prod "); sendMsg(int_to_str(num)); sendMsg("\n");
}
void Server::sellProduct(int num, int price) const
{
	sendMsg("sell "); sendMsg(int_to_str(num)); sendMsg(int_to_str(price)); sendMsg("\n");
}


void Server::buildPlant() const {sendMsg("plant\n");}
void Server::buildAutoPlant() const {sendMsg("aplant\n");}
void Server::upgradePlantToAuto() const {sendMsg("upgrade\n");}


void Server::nextTurn() const {sendMsg("turn\n");}
