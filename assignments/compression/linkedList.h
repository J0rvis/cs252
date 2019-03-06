#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_


typedef struct treeNode{
 double weight;
 int c;
 char direction; //left or right
 struct treeNode* left;
 struct treeNode* right;
 struct treeNode* parent;
} tnode;


typedef struct node {
  tnode* value;
  struct node* next;
} LinkedList;



LinkedList* llCreate();

int llIsEmpty(LinkedList* ll);

tnode* tnCreate();

void llRemoveTop(LinkedList** ll);

void llRemoveIndex(LinkedList** ll, int index);

void llFreqDisplay(LinkedList* ll);

void llDisplay(LinkedList* ll);

void llAdd(LinkedList** ll, tnode* newValue);

void lladdInOrder(LinkedList** ll, tnode* newVal);




#endif
