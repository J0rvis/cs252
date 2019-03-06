#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"


typedef unsigned char bitSet;
tnode* found; //pointer to the found char in node tree memory
tnode* treeRoot;//creates huffman tree as reference 


/*prototypes*/
tnode* ptnodeSet(double w, int count, char direction, tnode* l, tnode* r, tnode*p);
tnode tnodeSet(double w, int character, char direction, tnode* l, tnode* r, tnode* p);
void testLinkedList();

LinkedList* generateFreqTable(char* file); //reads in text file and makes freq
void createHuffmanTree(LinkedList** tree);
void encodeFile(char* file, tnode* tree); //string file name to write to
void decodeFile(char* file, tnode* tree); // string file name to write to


bitSet* getPath(char c, tnode* root);
tnode** setToZero();
void displayTnodeFreq(tnode** nodes);
void updateFreq(char scan, tnode** zeros);
LinkedList* tnodeToLinkedList(tnode** node);
void displayTreeRecursively(tnode* n);//root
void setPath(tnode* root);
void findNodeAddress(tnode* n, int c);
tnode* cloneTree(tnode* root, tnode* parent);
char* copyFileName(char* file, char* extend);
int maxHeight(tnode* node);
void freeTree(tnode* root);
void freeLinkedList(LinkedList* top);

/*BIT FUNCTIONS */
bitSet makeBitSet();
void displayBitSet(bitSet bs);
void setBit(bitSet* bs, int index);
void clearBit(bitSet* bs, int index);
void reverseBitSet(bitSet* bs, int start, int end);


int main(int argc, char *argv[]){ 
/* LinkedList* freqTable = generateFreqTable("extinct.txt");//compile like ./compress -g testWord.txt
 createHuffmanTree(&freqTable); //ft is now a root of the tree 
 treeRoot = cloneTree(freqTable->value, NULL);

encodeFile("dino.txt", freqTable->value);//Dinosaurs Sadly Extinct Before Invention Of Bazooka
decodeFile("dino.huf", freqTable->value);
*/

	//Check the make sure the input parameters are correct
	if (argc != 3) {
	 printf("Error: The correct format is \"hcompress -e filename\" or  \"hcompress -d filename.huf\"\n"); 
	 fflush(stdout);
	 exit(1);
	}
 // Create the frequency table by reading the generic file
 LinkedList* freqTable = generateFreqTable("extinct.txt");
 // Create the huffman tree from the frequency table
 createHuffmanTree(&freqTable);
 treeRoot = cloneTree(freqTable->value, NULL);	
	// encode
	 if (strcmp(argv[1], "-e") == 0) {
	 // Pass the leafNodes since it will process bottom up
	 encodeFile(argv[2], freqTable->value);
	
	} else { // decode
	 // Pass the tree root since it will process top down
	 decodeFile(argv[2], freqTable->value);
	}

 freeTree(treeRoot);
 free(found);
 freeLinkedList(freqTable);
 return 0;
}
 
void freeTree(tnode* root){
 if(root != NULL){
	freeTree(root->right);
	freeTree(root->left);
 	free(root);
 }
}

void freeLinkedList(LinkedList* top){
 LinkedList* temp = top;
 while(temp->next != NULL){
  llRemoveTop(&temp);
  temp = temp->next;
 }

}

/*
//Check the make sure the input parameters are correct
	if (argc != 3) {
	 printf("Error: The correct format is \"hcompress -e filename\" or  \"hcompress -d filename.huf\"\n"); fflush(stdout);
	 exit(1);
	}
 // Create the frequency table by reading the generic file
 tnode* leafNodes = generateFreqTable("decind.txt");
 // Create the huffman tree from the frequency table
 tnode* treeRoot = createHuffmanTree(leafNodes);

	 // encode
	if (strcmp(argv[1], "-e") == 0) {
	 // Pass the leafNodes since it will process bottom up
	 encodeFile(argv[2], leafNodes);

	} else { // decode
	 // Pass the tree root since it will process top down
	 decodeFile(argv[2], treeRoot);
	}
 return 0;*/


/* HAVE THIS ONE ADD IN ORDER AT THE END */
LinkedList* generateFreqTable(char* file){
//part A collect data 
 FILE* fileOpen; 
 fileOpen = fopen(file, "r");
	if(fileOpen == NULL){
	 printf("\t\t EMPTY OR NOT EXISTING FILE \n");
	 return NULL;
	}

 tnode** nodeZeros = setToZero(); //each element is address to heap 
 char buffer;

	while(fscanf(fileOpen, "%c", &buffer) != EOF){
	 //check to see if each char is in tnode
	printf("char : %c \n", buffer); 	 
	updateFreq(buffer, nodeZeros);
	} 
 fclose(fileOpen);
 LinkedList* ll = tnodeToLinkedList(nodeZeros);
 return ll;
}



void createHuffmanTree(LinkedList** ll){
  
	while((*ll)->next != NULL){//stops at root... tree created by tnodes not LL
	 
	 double tempW = ((*ll)->value->weight) + ((*ll)->next->value->weight);
	 
	 tnode* pnewNode = ptnodeSet(tempW, 33, -1, (*ll)->value, (*ll)->next->value, NULL); //33 = !	

	 (*ll)->value->parent = pnewNode; //whenever a parent is made it will be 
	
	 (*ll)->next->value->parent = pnewNode;	

	 llRemoveTop(ll);//ll
	 llRemoveTop(ll);//ll->next
		
	 lladdInOrder(ll, pnewNode);
	


	} 

}

void encodeFile(char* file, tnode* n){

printf("ENCODE \n ");
 char* filename = copyFileName(file, ".huf");
  FILE* fileOpen;
 fileOpen = fopen(file, "r");
	if(fileOpen == NULL){
	 printf("\t\t EMPTY OR NOT EXISTING FILE \n");
	 return;
	}

 
 bitSet bit = makeBitSet();
 tnode* root = treeRoot;
 setPath(root);
 char buffer;
 int i = 0;
 int level = 0;
 FILE* fileWrite;
 printf("filename %s \n",filename);
 fileWrite = fopen(filename, "w"); 
 printf("scan : \n");
 
	while(fscanf(fileOpen, "%c", &buffer) != EOF){	
	 int num = buffer; 	 
	 findNodeAddress(root, num);
	 
	 tnode* foundRoot = found;
	 	while(foundRoot->weight != root->weight){//
	 	 foundRoot = foundRoot->parent;
		}
		
	 setPath(foundRoot);
	
		while(found->parent != NULL){//while not root
			printf("\nLEVEL %d \n", level);
			if(found->direction == '0'){
		//	 printf("\nLEVEL %d \t : 0 \n", level);
			 clearBit(&bit,7 - level);
		//	 displayBitSet(bit);
			 level++;
	//		 printf("0");
			} else if (found->direction == '1'){
		//	 printf("\nLEVEL %d \t : 1 \n", level);
			 setBit(&bit,7 - level);
		//	 displayBitSet(bit);
			 level++;
	//		printf("1");
			} 

			if (level == 8){
			 //printf("\n\n\n");
			 level = 0;
			 printf("\n WRITE OUT \n"); 
		//	 displayBitSet(bit);
			 fputc(bit, fileWrite);
			 printf("issues \n");
			 bit = makeBitSet();	
			}

		 printf("\n\n LEVEL %dn", level);
		 found = found->parent;
		 //level++;
		} 

	// reverseBitSet(&bit0, start, end);
//	 printf(".");
	 printf("\n BITSET + LEVEL %d  \n\n", level);
	// displayBitSet(bit0);
	 i++;
	} // dooone 

 	if(level > 0 && level < 7){//aka has a bit left over for a marker 
	 setBit(&bit,7 - level);
//	 printf("\n WRITE OUT \n"); 
	 fputc(bit, fileWrite);
//	 displayBitSet(bit);


	}

 fclose(fileOpen);
 fclose(fileWrite);
 //printf("\n\n");
// free(filename);
}

void decodeFile(char* file, tnode* tree){
 char* filename = copyFileName(file, ".huf.dec");
 FILE* fileOpen;
 
 fileOpen = fopen(file, "r");
	if(fileOpen == NULL){
	 printf("\t\t EMPTY OR NOT EXISTING FILE \n");
	 return;
	}

char saved; //buffer char  
bitSet buffer = makeBitSet(); // 
//int level = 0;
FILE* fileWrite;
fileWrite = fopen(filename, "w");
int count = 0;
fseek(fileOpen,0, SEEK_SET);
int end = (int) ftell(fileOpen);
//printf("BEGINNING INT  %d\n",end);
printf("\t\tDECODE \n\n");
	while(fscanf(fileOpen, "%c", &buffer) != EOF){// while end != 0;
	 displayBitSet(buffer);
	 //printf("count : %d\n", count);
	 count++;// I now know how many bytes 
	}
tnode* root = tree;
int written = 0;
int i = 0;
//printf("opposite way \t end %d \n", end);
end = (int) ftell(fileOpen);
count --;
int ind = 0; 
int startBit = 0;
int j =0;
char firstByte[9]  = {'0','0','0','0','0','0','0','0','\0' };
fseek(fileOpen, count, SEEK_SET);
fscanf(fileOpen,"%c", &buffer); //scan in first byte 
reverseBitSet(&buffer, 0, 8);
	while(end != 0){
		if(startBit == 0 || startBit == 1){
			for(j = 0; j < 8; j++){
				if(buffer & (1<<(7-j))&& startBit == 0){//start everything
		// 	 printf("found start marker j = %d\n", j);
				 clearBit(&buffer, 7-j);
			//	 printf("DISPLAY BITSET AFTER CLEAR J =  %d: \n", j);
			//	 displayBitSet(buffer);
				 ind = j+1; //index to start at
				 startBit = 1;
				 firstByte[j] = '0'; 
		//		 printf("0\n");
				}else if(buffer & (1<<(7-j))) {
				 firstByte[j] = '1';
			//	 printf("1\n");
				} else {
			//	 printf("0\n");
				 firstByte[j] = '0';
	
         	       		}

			}
//		printf("Display at Byte : %d \n%s\n\n", count, firstByte);
		 count--;
		 startBit = 22;
		}
		//count is two and is second byte use firstByte char[]
		if(ind != -1){
		 fseek(fileOpen, count, SEEK_SET);
		 end = (int) ftell(fileOpen); 
		 fscanf(fileOpen, "%c", &buffer);
		 reverseBitSet(&buffer, 0,8);
//		 printf("Display at Byte : %d\n", count);
		 displayBitSet(buffer);
			for(i = ind;i < 8 ;i++ ){
				if(firstByte[i] == '1'){
				 root = root->right;
				// printf("1");
				}else if(firstByte[i] == '0'){
				 root = root ->left;
				// printf("0");
				}
				if(root->right == NULL && root ->left == NULL){// parent of none
//				printf("\nCHAR FOUND : %c\n", root->c);
				 saved = root->c;
				 root = tree; 
				 putc(saved, fileWrite);
				 written++;
				}
			}

			for(i = 0; i < 8; i++){
                                 if(buffer & (1<<(7-i))) {
                                  root= root->right;
                                //  printf("1");
                                 } else {
                                 // printf("0");
                                  root = root->left;
                                 }
				if(root->right == NULL && root->left == NULL){
//				 printf("CHAR FOUND : %c\n", root->c);
				 saved = root->c;
				 root = tree;
				 putc(saved, fileWrite);
				 written++;
				}

			}
		 ind = -1;
		 //printf("COUNT SHOULD BE 1 : %d\n", count);
		 count --;
		} else { //else is not byte 1 or byte 2
	 	 startBit = -33;
	  	 fseek(fileOpen, count, SEEK_SET);
	 	 end = (int) ftell(fileOpen); //last byte 
	 	 fscanf(fileOpen, "%c", &buffer);
	 	 reverseBitSet(&buffer,0,8 );
//		printf("Display at Byte : %d\n", count);	 
		displayBitSet(buffer);
		 	for(i = 0; i < 8; i++){
				if(buffer & (1<<(7-i))) {
				 root = root->right;
				// printf("1");
				}else {
				 root = root ->left;
				// printf("0");
				}
				if(root->right ==NULL && root->left == NULL){
//				printf("CHAR FOUND : %c\n", root->c);
				saved = root->c;
				root = tree;
				putc(saved,fileWrite);
				written++; 
				}
			 
		 	}
		
	 	 count--;
		}
	}
	fseek(fileWrite,0, SEEK_SET);
	end = (int) ftell(fileWrite);
//	printf("IS THIS THE BEGINNING THEN : %d \n", end);	
/*
fileOpen = fopen(file, "r");
if(fileOpen == NULL){
printf("\t\t EMPTY OR NOT EXISTING FILE \n");
return NULL;
}*/
fclose(fileOpen);
fclose(fileWrite);
//tnode** nodeZeros = setToZero(); //each element is address to heap
FILE* f;
f = fopen(filename, "r+");
int current = 0;
int size = written;
char buf;
char temp;
/*safe first to buf then */
printf("SIZE OF FILE IN BYTES = %d \n\n\n", written);

	while(fscanf(f, "%c", &buf) != EOF && current != size/2){//sav
	 //putf('1', fileWrite);
	 end = (int) ftell(f);
	 fseek(f, written-1, SEEK_SET);//find location at end
	 fscanf(f, "%c", &temp);//scan in thing to swap
	 fseek(f, written -1, SEEK_SET); //step back one
	 putc(buf, f);
	 fseek(f, current, SEEK_SET);
	 putc(temp,f);//place end to beginning 
	
	current++;
	written--;
	}


fclose(f);
//free(filename);
//	while(fscanf(f,"%c", &buf)!= EOF){
//	 putc();


//	}
//reverse everything to be readable 

}




int maxHeight(tnode* node){
	if (node==NULL){ 
	 return 0;
	}  else {
         int l = maxHeight(node->left);
         int r = maxHeight(node->right);
 
        	if (l > r) {
         	 return(l+1);
       		} else{
	 	 return(r+1);
   		}
	}
} 



char* copyFileName(char* file, char* extend){
	if(strcmp(extend, ".huf") == 0){
	 char* temp = (char*) malloc((strlen(file)+1) * sizeof(char)); //same size file
	 int i = 0;
	 printf("FILENAME LENGTH : %d \t HUFNAME LENGTH : %d \n", (int)strlen(file),(int) strlen(temp));
		for(i = 0; i < strlen(file)-3 ;i++){
		 printf("file: %c\n", file[i]);
		 temp[i] = file[i];
		}
	 printf("BEFORE ADDING AT END %s \n ", temp);
	 temp[strlen(file) - 3] = 'h';
	 temp[strlen(file) - 2] = 'u';
	 temp[strlen(file) - 1] = 'f';
	 temp[strlen(file)] = '\0' ;
	 printf("AFTER ADDING AT END %d \n ",(int) strlen(temp));
	 return temp;
	} else if (strcmp(extend, ".huf.dec") == 0){
	 char* temp = (char*) malloc((strlen(file) + 4 +1) * sizeof(char));
	 int i = 0;
		for(i = 0; i < strlen(file)-3 ;i++){
		 temp[i] = file[i];
		}
		 printf("BEFORE %s \n ", temp);

		temp[strlen(file) - 3] = 'h';
		temp[strlen(file) - 2] = 'u';
		temp[strlen(file) - 1] = 'f';		
		temp[strlen(file)] = '.';
		 printf("MID %s \n ", temp);

		temp[strlen(file) + 1] = 'd';
		temp[strlen(file) + 2] = 'e';
		temp[strlen(file) + 3] = 'c';
		temp[strlen(file) + 4] = '\0';
		printf("AFTER %s \n ", temp);

	 return temp;
	}
 return NULL;
}

void reverseBitSet(bitSet* bs, int start, int end){// takes in the index of last character introduced
 //printf("\nreverse \n");
 int i = 0;
 int j = end - 1;
bitSet temp = *bs;

temp = *bs;// reset
	for(i = start; i < end; i++){//if zero
			if(*bs & (1<<(7-i))){//
			 setBit(&temp, 7 - j); 
			}else{
			 clearBit(&temp,7 - j);
			}
	 j--;
	}
 //displayBitSet(temp);
 *bs = temp;
}


void findNodeAddress(tnode* root, int c){//root
        if(root!= NULL){
	 findNodeAddress(root->left,c);  
         findNodeAddress(root->right,c);
	
		if(root->c == c){
	 	 found = root;
 
		}
	}
}


tnode* cloneTree(tnode* root, tnode* parent){
	if(root == NULL){
         return NULL;
	}
    /* create a copy of root node */
    tnode* newNode = ptnodeSet(root->weight, root->c, root->direction,  NULL, NULL, parent);
    /* Recursively create clone of left and right sub tree */
    newNode->left = cloneTree(root->left, root);
    newNode->right = cloneTree(root->right, root);
    /* Return root of cloned tree */
    return newNode;
}



void setPath(tnode* root){
	if(root->left != NULL){
	 root->left->direction = '0';
	 setPath(root->left);
	}

	if(root->right != NULL){
	 root->right->direction = '1';
	 setPath(root->right);

	}


}

void updateFreq(char scan, tnode** zeros){
 int i = 0;
 int temp = scan;
	for(i = 0; i < 128; i++){
		if((*zeros)[i].c == temp){// finds matching char regardles of weight
		 (*zeros)[i].weight++;
		
		 return; //stop loop to save time
		}
	}
}

void displayTnodeFreq(tnode** node ){
 int i = 0;
 printf("\t\t DISPLAY NODES FREQ TABLE \n\n");
	for(i = 0; i < 128; i++){
	 printf("int c = %d :\tweight = %f :\tchar = %c \n", node[i]->c , node[i]->weight, node[i]->c);

	}
 

}

LinkedList* tnodeToLinkedList(tnode** node ){
 LinkedList* ll = llCreate();
 int i = 0;
	for(i = 0; i < 128; i++){
	 lladdInOrder(&ll, node[i]);//should be ptr	
	}
 return ll;

}

tnode* ptnodeSet(double w, int count, char d, tnode* l, tnode* r, tnode* p){
 tnode* node = (tnode*)malloc(1* sizeof(tnode)); 
 node->weight = w;
 node->c = count;
 node->direction = d;
 node->left = l;
 node->right = r;
 node->parent = p;
 return node;
}

tnode tnodeSet(double w, int character, char d, tnode* l, tnode* r, tnode* p){
 tnode node;
 node.weight = w;
 node.c = character;
 node.direction = d;
 node.left = l;
 node.right= r;
 node.parent = p;
 return node;
}

tnode** setToZero(){//* = tnode point ** = pointer arry
 tnode* node  = (tnode*) malloc(128*sizeof(tnode));//save actual numbers to heap
 tnode** pNodes = (tnode**) malloc(128*sizeof(tnode));
 
 int i = 0;
	for(i = 0; i < 128; i++){
	 node[i] = tnodeSet(0, i, -1, NULL, NULL, NULL);// saves actual val
	 pNodes[i] = &(node[i]);	 
	}

 return pNodes;
}

void displayTreeRecursively(tnode* root){//root{
	double w = -1;
	if(root != NULL && root->parent != NULL){
	 w = root->parent->weight;
	}
 	if(root!= NULL){
	printf("c = %c \t w = %f \t d: %c\t parent w= %f\n\n",root->c, root->weight,root->direction, w); 

	 displayTreeRecursively(root->left);
	 displayTreeRecursively(root->right);
	}


}


bitSet makeBitSet(){
 bitSet bs = 0;
 return bs;

}


void setBit(bitSet* bs, int index){
 
 *bs = ((1<<(index ))| *bs);
 
}


void clearBit(bitSet* bs, int index){
 *bs = (~(1 << index)& *bs);
}


void displayBitSet(bitSet bs){
 int i;
	for (i = 0; i < 8; i++) {
	 printf("%d",((1 << (7- i)) & bs) ? 1 :0);
	}

 printf("\n\n");

}












/*

void testLinkedList() {
 printf("\t MAIN \n");
 LinkedList* ll = llCreate();

	if (llIsEmpty(ll)) {
	 printf("Empty\n");
	} else {
	 printf("Not Empty\n");
	}


 llDisplay(ll);

 tnode* node0;
 tnode* node1;
 tnode* node2;
 tnode* node3;
 tnode* node4;
 node0 = tnCreate();
 node1 = tnCreate();
 node2 = tnCreate();
 node3 = tnCreate();
 node4 = tnCreate();

 node0 = ptnodeSet(0.0, 0, NULL, NULL, NULL);//root
 node1 = ptnodeSet(1.0, 1, NULL, NULL, NULL);//root
 node2 = ptnodeSet(2.0, 2, NULL, NULL, NULL);//root
 node3 = ptnodeSet(3.0, 3, NULL, NULL, NULL);//root
 node4 = ptnodeSet(4.0, 4, NULL, NULL, NULL);//root
	
 
 
 printf("\nAdd 0: \n");
 lladdInOrder(&ll, node0);
 llDisplay(ll);	

 printf("\nADD 2: \n");
 lladdInOrder(&ll, node2);
 llDisplay(ll);

 printf("\nAdd 3 \n");
 lladdInOrder(&ll, node3);
 llDisplay(ll);


 printf("\n\torder should be : 0 2 4 \n");
 llDisplay(ll);

 printf("\nAdd 1\n");
 lladdInOrder(&ll, node1);
 llDisplay(ll);

 printf("\nAdd 4\n");
 lladdInOrder(&ll, node4);

 printf("\n\torder should be : 0 1 2 3 4 \n");
 llDisplay(ll);
free(node0);
free(node1);
free(node2);
free(node3);
free(node4);

}
*/
