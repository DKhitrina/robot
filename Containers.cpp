#include <Containers.hpp>
#include <Utils.hpp>

String::String(const char* newstr) {
    int len = strlen(newstr)+1;
    value = malloc(len);
    for(int i=0; i<len; i++) {
        value[i] = newstr[i]
    } 
    value[i] = 0;
}
String::~String() 
    {free (value);
}
char* String::toString const {return value;}

-------------------------------------------------------------------------------

Player::Player(const char* str)
{
	name = str;
	rawQuantity = 2;
	productQuantity = 2;
	moneyQuantity = 10000;
	plantCount = 2;
	autoPlantCount = 0;
}
Player::Player(const char* str, int raw, int product, int money, int plant,
	int aplant)
{
	name = str;
	rawQuantity = raw;
	productQuantity = product;
	moneyQuantity = money;
	plantCount = plant;
	autoPlantCount = aplant;
}
Player::toString() const {return name;}
const char* Player::getPlayerName() const {return name;}
int Player::getRawQuantity() const {return rawQuantity;}
int Player::getProductQuantity() const {return productQuantity;}
int Player::getMoneyQuantity() const {return moneyQuantity;}
int Player::getPlantCount() const {return plantCount;}
int Player::getAutoPlantCount() const {return autoPlantCount;}

-------------------------------------------------------------------------------

Auction::Auction(const char* state, const char* name, int amount, int price);
{
	auctionState = state;
	winnerName = name;
	winningAmount = amount;
	winningPrice = price;	
}
char* Auction::toString() const {return name;}
char* Auction::getAuctionState() const {return auctionState;}
char* Auction::getWinnerName() const {return winnerName;}
int Auction::getWinningAmount() const {return winningAmount;}
int Auction::getWinningPrice() const {return winningPrice;}

-------------------------------------------------------------------------------

List::List()
{
    head = NULL;
    tail = NULL;
    currentItem = NULL;
}
   
List::~List()
{
    cleanList();
}

void List::add(Object obj)
{
	struct item *p;
	p = malloc (sizeof(struct item));
    p->data = obj;
	p->next = NULL;
	if (tail){
		tail->next = p;
		tail = tail->next;
	}else{
		head = tail = currentItem = p;
	}
}

Object List::getCurrent() const
{
    return (currentItem->data);    
}
Object List::getNext()
{
    if (currentItem->next){
        currentItem = currentItem->next;
        return (currentItem->data);
    }
    return (NULL);
}
Object List::getFirst()
{
    currentItem = head;
    return (currentItem->data);
}
   
void List::printList() const
{
    struct item* tmp = head; 
	while (tmp){
		printf("%s\n", (tmp->data).toString);
		tmp = tmp->next;
	}
}
void List::cleanList()
{
    struct item* tmp;    
    while (head){ 
        tmp = head;
        head = head->next;
		delete tmp->data;
		free (tmp);
	}
} 

void UniqueList::add(Object obj)
{
    struct players* temp = head;
    int new_flag = 1;
    /*wheather the name is already in list*/
    while (temp){
        if (cmp_str(temp->data.toString(), obj.toString())){
            delete (temp->data);
            temp->data = obj;
            new_flag = 0;
            break;
        }
        temp = temp->next;
    } 
    /*if new name*/
    if (new_flag == 1){
        List::add(obj)
    }
}

int AuctionList::getMinPriceBought() const
{
    Auction au;
    int min = 10000;
    int price;

    au = (Auction)getFirst()

    while (au){
        price = au.getWinningPrice();
        if(cmp_str(au.getAuctionState(),"BOUGHT") && price < min)
            min = price;
        au = (Auction)getNext();
    }
    return min;
}
int AuctionList::getMaxPriceSold() const
{
    Auction au;
    au = (Auction)getFirst();
    int max = 0;
    int price;
    while (au){
        price = au.getWinningPrice();
        if(cmp_str(au.getAuctionState(),"SOLD") && price > max)
            max = price;
        au = (Auction)getNext();    
    }
    return max;
}