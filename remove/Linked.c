#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"


LinkedList* llCreate(){
	return NULL;
}


void llDisplay(LinkedList* ll){
	LinkedList* p  = ll;

	printf("[");
	while (p != NULL) { 
		printf(" %d ", p->node->c);
		p = p->next;
	}
	printf("]\n");
}


void llAdd (LinkedList** ll, tNode* str) {
	
	
	LinkedList* nn = (LinkedList*)malloc(sizeof(LinkedList));
	nn->node = str;
	nn->next = NULL;
	
	LinkedList* p = *ll;

	if(p == NULL) {
		*ll = nn;
	} else{
		while(p->next != NULL){
			p = p->next;
		}
	p->next = nn;
	}
}

int llSize(LinkedList *ll){
	LinkedList* p = ll;
	int size = 0;
	
	if(p == NULL){
		return size;
	}
	
	while(p != NULL){
		p = p->next;
		size++;
	}
	return size;
}


void llAddAtIndex(LinkedList** ll, tNode* node, int index){
	int size = llSize(*ll);
	if(ll != NULL && index <= size){ 
		LinkedList* nn = (LinkedList*)malloc(sizeof(LinkedList));
		nn->node = node;
		nn->next = NULL;
		LinkedList* p = *ll;		
			
		if(index == 0){
			*ll = nn;
			nn->next = p;
		}else{
			int i = 0;
			while(p != NULL && i < index - 1 ){
				p = p->next;
				i++;
			}
			if(p != NULL){
				LinkedList* a = p->next;	
				p->next = nn;
				nn->next = a;
			}else{
				llAdd(ll, node);
			}
		}

	}
}


void removeAtIndex(LinkedList** ll, int index){
	int size = llSize(*ll);
	if(*ll != NULL && index < size){
		LinkedList* p = *ll;
		if(index == 0){
			*ll = p->next;
			free(p);	
		}else{
			int i = 0;
			while(p != NULL && i <  index - 1){
				p = p->next;
				i++;
			}
			
			LinkedList* c = p->next;
			LinkedList* a = c->next;
			p->next = a;
			free(c);
		}
	}
}


void llDelete(LinkedList** ll){
	LinkedList* p = *ll;
	
	while(p != NULL){
		LinkedList* c = p->next;
		free(p->node);
		free(p);
		p = c;
	}
	*ll = p;
}

void addInOrder(LinkedList** ll, tNode* nn){
	
	if(*ll == NULL){ 

		llAdd(ll, nn);

	}else{ 
		
		LinkedList* p = *ll;
		int count = 0;

		while ((p != NULL) && (nn->weight > (p->node)->weight)) {
			count++;
			p = p->next;
		}
		
		llAddAtIndex(ll, nn, count);
	}
}
