#include <stdio.h>
#include <stdlib.h> // malloc
#include "linkedList.h"
//linkedList
//turn into queue
LinkedList* llCreate() {
  
  return NULL;
}

int llIsEmpty(LinkedList* ll) {
  return (ll == NULL);
}

/*TESTED AND WORKS */

void llRemoveTop(LinkedList** ll){
 LinkedList* temp = *ll;//head 
 LinkedList* nxt = temp->next;
 free(temp);
 *ll = nxt; // set the pointer to the next
}

void llFreeAll(LinkedList** ll){
 LinkedList* current = *ll;
 LinkedList* nxt;
 	while(current != NULL){
	 nxt = current->next; //don't burn the bridge you're on
	 free(current);// now you can burn it
	 current = nxt;
	}
 *ll = NULL;
}

void llDisplay(LinkedList* ll){
 LinkedList* p = ll;
 int i = 0;
	while(p != NULL){ 
	 printf("%s \t", p->histNode);
	 i++;
	 p = p->next;
	}
	printf("\n");
}


char* llGetAtIndex(LinkedList* ll, int histCount){
 LinkedList* p = ll;
 int i = 0;
	while(p != NULL && i < histCount - 4){
	 i++;
	 p = p->next;
	}
 return p->histNode; 
}





void llAdd(LinkedList** ll, char** newValue) {
 
 LinkedList* newNode = (LinkedList*)malloc(1 * sizeof(LinkedList));
 newNode->histNode = *newValue;
 newNode->next = NULL;

 LinkedList* p = *ll;
 
	if (p == NULL) { 
	 *ll = newNode;
	 //printf(" THIS LIST IS EMPTY \n");
	} else {

		while (p->next != NULL) {
		 p = p->next;
		}
    
	 p->next = newNode;
	}

} 
/*
int main(){
LinkedList* history = llCreate();
 char* t1 = "Hello";
 char* t2 = "World";
 char* t3 = "Test";
 llAdd(&history,&t1);
 llAdd(&history,&t2);
 llAdd(&history,&t3);
 llDisplay(history);
 llRemoveTop(&history);
 llFreeAll(&history);

return 0;
}
*/
