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
			end->next = p;
			end = end->next;
		}else{
			begin = end = p;
		}
	}
	return head;
}

-----------------------------------------------------------------------------------------------------------------

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

Server::~Server(){
	shutdown(sockfd, 2);
	close(sockfd);
}

void Server::SendMsg (const char* str) const
{
	int wr = write(sockfd, str, strlen(str)+1);
}

void Server::RcvMsg()
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

void Server::ListPlayers(struct strlist* list)
{
	/* full the struct */
	struct player* p;
	p = malloc(sizeof(struct players))
	list = list->next;
	player->name = list->data;
	list = list->next;
	player->raw = str_to_int(list->data);
	list = list->next;
	player->prod = str_to_int(list->data);
	list = list->next;
	player->money = str_to_int(list->data);
	list = list->next;
	player->plants = str_to_int(list->data);
	list = list->next;
	player->auto_plants = str_to_int(list->data);
	player->next = NULL;


	return player;
}

void Server::StringAnalyser(const char* str)
{
	struct strlist* list = divide_str(str);
	if(str[0] == '&'){
		list = list->next;	
		if cmp_str(list->data, "MARKET"){
			list = list->next;
			bank->raw = str_to_int(list->data);
			list = list->next;
			bank->min_price = str_to_int(list->data);
			list = list->next;
			bank->prod = str_to_int(list->data);
			list = list->next;
			bank->max_price = str_to_int(list->data);
		}
		if cmp_str(list->data, "INFO"){
			ListPlayers(list);
		}

	}
}

void Server::EnterName(const char* name) const
{
	SendMsg(name); SendMsg("\n");
}

int  Server::GetNumPl() const 	{return num_players;}

void Server::CreateGame() const {SendMsg(".create\n");}

void Server::JoinByNum(int n) const
{
	SendMsg(".join "); SendMsg(IntToStr(n)); SendMsg("\n");
}

void Server::JoinByName(const char* name) const
{
	SendMsg(".join "); SendMsg(name);
}

void Server::Buy(int num, int price) const
{
	SendMsg("buy "); SendMsg(IntToStr(num)); SendMsg(IntToStr(price)); SendMsg("\n");
}

void Server::Sell(int num, int price) const
{
	SendMsg("sell "); SendMsg(IntToStr(num)); SendMsg(IntToStr(price)); SendMsg("\n");
}

void Server::Prod(int num) const
{
	SendMsg("prod "); SendMsg(IntToStr(num)); SendMsg("\n");
}

void Server::EndTurn() const 	{SendMsg("turn\n");}

void Server::QuitGame() const 	{SendMsg("quit\n");}