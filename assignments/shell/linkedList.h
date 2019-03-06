#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_


typedef struct node {
  char* histNode;
  struct node* next;
} LinkedList;

LinkedList* llCreate();

int llIsEmpty(LinkedList* ll);

void llFreeAll(LinkedList** ll);

void llRemoveTop(LinkedList** ll);

void llDisplay(LinkedList* ll);

char* llGetAtIndex(LinkedList* ll, int histCount);

void llAdd(LinkedList** ll, char** newValue);


#endif
