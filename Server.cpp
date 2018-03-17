#include <sys/types.h>
#include <sys/socket.h>
#include <Server.hpp>
#include <Containers.hpp>
#include <Utils.hpp>

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

List divide_str(const char* str)
{	
	List list = new List();
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
		m[i] = 0;
		list.add(m);
	}
	return list;
}

-------------------------------------------------------------------------------

Market::Market(int raw, int raw_price, int product, int product_price);
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

void Socket::connect (const char* serv_ip, int port)
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

void Server::sendMsg (const char* str) const
{
	int wr = write(sockfd, str, strlen(str)+1);
}
void Server::rcvMsg()
{
	char buf[128];
	char rcv_str[81];
	int i, j;	

	List list = new List();

	for(;;){
		int rd = read(sockfd, buf, sizeof(buf)-1);
		if (rd == -1){
			printf("Socket Error: Unable to Read Message\n");
			exit(1);
		}	
		buf[rd] = 0;

		/* divide string */
		j = 0;

		while(j<=rd){
			i = 0;
			while(buf[j]!='\n'){
				rcv_str[i] = buf[j];
				i++;
				j++;
			}
			rcv_str[i] = 0;
			j++;
			String str = new String(rcv_str);
			list.add (str);
		}

		if (rd < sizeof(buf)-1)
			break;

	}

	list.printList();

	Object o = list.getFirst();
	while (o){
		analyseString(o.toString());
		o = list.getNext();
	}
	
	delete list;
}

void Server::analyseString(const char* str)
{
	List l = divide_str (str);
	if(l.getFirst() == '&'){
		char* command = l.getNext().toString();
		if (cmp_str(command, "MARKET")){
			Market m = new Market(str_to_int(l.getNext().toString()),
				str_to_int(l.getNext().toString()),
				str_to_int(l.getNext().toString()),
				str_to_int(l.getNext().toString()));

			if (market)
				delete market;
			market = m;
		}
		if (cmp_str(command, "INFO")){
			Player p = new Player(l.getNext().toString(),
				str_to_int(l.getNext().toString()),
				str_to_int(l.getNext().toString()),
				str_to_int(l.getNext().toString()),
				str_to_int(l.getNext()).toString());
			players_list.add(p);
		}
		if (cmp_str(command, "PLAYERS")){
			num_players = str_to_int(l.getNext().toString());
		}	
		if (cmp_str(command, "BOUGHT") || cmp_str(command, "SOLD"){
			Auction a = new Auction(l.getNext().toString(),
				l.getNext().toString(),
				str_to_int(l.getNext().toString()),
				str_to_int(l.getNext().toString()));
			auction_list.add(a);			
		}			
		if (cmp_str(command, "ENDTURN")){
			getMarket();
			getPlayersInfo();	
		}
	}
	delete (l);
}


Server::Server(const char* name, const char* serv_ip, int port)
{
	connect(serv_ip, port);
	players_list = new UniqueList();
	auction_list = new AuctionList();
	player = new Player(name, 2, 2, 10000, 2, 0);
	market = new Market(0, 0, 0, 0);
}
Server::~Server()
{
	shutdown(sockfd, 2);
	close(sockfd);
	delete players_list;
	delete auction_list;
	delete player;
	delete market;
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

void Server::getMarket () const	{sendMsg("market\n");}
void Server::getPlayersInfo () const {sendMsg("info\n");}

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


void Server::nextTurn() const
{
	sendMsg("turn\n");
	/*renew information*/
	auction_list.cleanList;
}
