#include <Containers.hpp>
#include <Utils.hpp>

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

void List::add(char* str)
{
	struct item *p;
	p = malloc (sizeof(struct item));
    p->data = str;
	p->next = NULL;
	if (tail){
		tail->next = p;
		tail = tail->next;
	}else{
		head = tail = currentItem = p;
	}
}

char* List::getCurrent()
{
    return (currentItem->data);    
}

char* List::getNext()
{
    if (currentItem->next){
        currentItem = currentItem->next;
        return (currentItem->data);
    }
    return (NULL);
}
char* List::getFirst()
{
    currentItem = head;
    return (currentItem->data);
}
   
void List::printList()
{
    struct item* tmp = head; 
	while (tmp){
		printf("%s\n", tmp->data);
		tmp = tmp->next;
	}
}
void List::cleanList()
{
    struct item* tmp;    
    while (head){ 
        tmp = head;
        head = head->next;
		free (tmp->data);
		free (tmp);
	}
} 

-------------------------------------------------------------------------------

PlayersList::PlayersList()
{
    head = NULL;
    tail = NULL;
    current = NULL;
}
PlayersList::~PlayersList()
{
    cleanList();
}
void PlayersList::add(Player player)
{
    struct players* temp = head;
    int new_flag = 1;
    /*wheather the name is already in list*/
    while (temp){
        if (cmp_str(getCurrent.getPlayerName, player.getPlayerName)){
            temp->data = player;
            new_flag = 0;
            break;
        }
        temp = temp->next;
    }
    /*if new name*/
    if (new_flag == 1){
    	struct players *p;
    	p = malloc (sizeof(struct players));
        p->data = player;
    	p->next = NULL;
    	if (tail){
    		tail->next = p;
    		tail = tail->next;
    	}else{
    		head = tail = current = p;
    	}
    }
}

Player PlayersList::getCurrent()
{
    return (current);
}
Player PlayersList::getNext()
{
    current = current->next;
    return (current);
}
Player PlayersList::getFirst()
{
    current = head;
    return (current);
}
    
void PlayersList::printList()
{
    struct players* tmp = head;
    Player p; 
	while (tmp){
        p = tmp->data;
		printf("%s\n", p.getPlayerName);
		tmp = tmp->next;
	}
}
void PlayersList::cleanList()
{
    struct players* tmp;    
    while (head){ 
        tmp = head;
        head = head->next;
		free (tmp);
	}
}   

-------------------------------------------------------------------------------

AuctionList::AuctionList()
{
    head = NULL;
    tail = NULL;
    current = NULL;
}
AuctionList::~AuctionList()
{
    cleanList();
}
void AuctionList::add(Auction new_result)
{
	struct auction_result *p;
	p = malloc (sizeof(struct auction_result));
    p->data = new_result;
	p->next = NULL;
	if (tail){
		tail->next = p;
		tail = tail->next;
	}else{
		head = tail = current = p;
	}
}

Auction AuctionList::getCurrent()
{
    return (current->data);
}
Auction AuctionList::getNext()
{
    current = current->next;
    return (current->data);
}
Auction AuctionList::getFirst()
{
    current = head;
    return (current->data);
}

int AuctionList::getMinPriceBought()
{
    struct auction_result temp = head;
    Auction au;
    int min = 10000;
    int price;
    while (head){
        au = temp.getCurrent;
        price = au.getWinningPrice;
        if(cmp_str(au.getAuctionState,"BOUGHT") && price < min)
            min = price;
    }
    return min;
}
int AuctionList::getMaxPriceSold();
{
    struct auction_result temp = head;
    Auction au;
    int max = 0;
    int price;
    while (head){
        au = temp.getCurrent;
        price = au.getWinningPrice;
        if(cmp_str(au.getAuctionState,"SOLD") && price > max)
            max = price;
    }
    return max;
}

void AuctionList::cleanList()
{
    struct auction_result* tmp;    
    while (head){ 
        tmp = head;
        head = head->next;
		free (tmp);
	}    
}