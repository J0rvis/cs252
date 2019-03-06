#ifndef XYZ_LINKEDLIST_H
#define XYZ_LINKEDLIST_H

typedef struct tNode {
	int c;
	double weight;
	struct tNode* right;
	struct tNode* left;
	struct tNode* parent;
} tNode;

typedef struct ll{
	tNode* node;
	struct ll* next;
}LinkedList;

LinkedList* llCreate();
void llDisplay(LinkedList*);
void llAdd(LinkedList**, tNode*);
int llSize(LinkedList*);
void llAddAtIndex(LinkedList**, tNode*, int);
void removeAtIndex(LinkedList**, int);
void llDelete(LinkedList**);
void addInOrder(LinkedList**, tNode*);
void rootDisplay(tNode*);
#endif
