#include <stdio.h>
#include <stdlib.h> // malloc
#include "linkedList.h"
//linkedList
//turn into priority queue
LinkedList* llCreate() {
  
  return NULL;
}

int llIsEmpty(LinkedList* ll) {
  return (ll == NULL);
}

tnode* tnCreate(){
 return NULL;
}

/*TESTED AND WORKS */

void llRemoveTop(LinkedList** ll){
 LinkedList* temp = *ll;//head 
 *ll = temp->next; // set the pointer to the next
 free(temp); //free original
}

/*TESTED AND WORKS */
void llRemoveIndex(LinkedList** ll, int index){

 LinkedList* p = *ll;
 int counter = 0; 
	if (p == NULL) {
	 printf(" THIS LIST IS EMPTY \n");
	} else if (index == 0){
	llRemoveTop(ll);
	} else {
		while (p->next != NULL && counter + 1 < index) {
		 p = p->next;
		 counter++;
		}
	//delete p-> next bc counter is staggered
	 LinkedList* temp = p->next->next;
	 free(p->next->value);//frees pointer ->next pointer
	 free(p->next);
	 p->next = temp;
	}

}


void llFreqDisplay(LinkedList* ll){
 LinkedList* p = ll;
 int i = 0;
	while(p != NULL){ 
	 printf("int c  = %d :\tweight = %f :\tchar = %c \n", p->value->c , p->value->weight, p->value->c);
	 i++;
	 p = p->next;
	}
}



void llDisplay(LinkedList* ll) {
  
  LinkedList* p = ll;

  printf(" { ");
 
  while (p != NULL) {
    printf(" [w:%.2f, c: %d] ", p->value->weight, p->value->c);// current.tnode-> tnode.weight //prints weight
    p = p->next;// next ll
  }

  printf(" }\n");
}


void llAdd(LinkedList** ll, tnode* newValue) {
 
 LinkedList* newNode = (LinkedList*)malloc(1 * sizeof(LinkedList));
 newNode->value = newValue;
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

void lladdInOrder(LinkedList** ll, tnode* newVal){
 LinkedList* newNode = (LinkedList*) malloc(1* sizeof(LinkedList));
 newNode->value = newVal; //set contents of ll
 newNode->next = NULL; //set nothing here to hold it 

 LinkedList* p = *ll; //beginning of list


	if(p == NULL ){ //empty
		*ll = newNode;


	} else if (p->value->weight > newVal->weight){// makes new head 
	 newNode->next = *ll; //new node points at head 
	 *ll = newNode;
	 

	} else if(p != NULL) {
		while(p->next != NULL){ //(newNode->value).weight > (p->next->value).weight
			if ((p->next->value->weight)> (newVal->weight) ){//if next is bigger OR if next is same  
			 LinkedList* temp = p->next;

			 p->next = newNode; //
		
			 newNode-> next = temp;
			 return; 
			} else { // if newNode > next weight then keep moving down the line
		 	 p = p->next; //
			} 
		} 
	

	 llAdd(ll, newVal);
         
	}

}

