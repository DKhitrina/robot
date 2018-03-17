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
		printf("%s\n", tmp->data.toString);
		tmp = tmp->next;
	}
}
void List::cleanList()
{
    struct item* tmp;    
    while (head){ 
        tmp = head;
        head = head->next;
		delete (tmp->data);
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

int AuctionList::getMinPriceBought()
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
int AuctionList::getMaxPriceSold()
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