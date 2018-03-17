#include <Containers.hpp>

List::List(){
    head = NULL;
    tail = NULL;
    currentItem = NULL;
}
   
List::~List(){
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

char* getCurrent()
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
		printf("%s ", tmp->data);
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