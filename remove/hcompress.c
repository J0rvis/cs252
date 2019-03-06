#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "LinkedList.h"



int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Error: The correct format is \"compress -e filename\" or \"hcompress -d filename.huf\"\n"); fflush(stdout);
	exit(1);
	}
	
	
	LinkedList* leafNodes = createFreqTable("decind.txt");
	
	struct tNode* treeRoot = createHuffmanTree(leafNodes);	
	
	if(strcmp(argv[1], "-e") == 0){ 

		encodeFile(argv[2], leafNodes);
	
	}else{ 
		
		decodeFile(argv[2], treeRoot);
	
	}
	

	llDelete(&leafNodes);
	deleteTree(treeRoot);

	return 0;
}

LinkedList* createFreqTable(char* fileName){
	
	FILE* stream;
	stream = fopen(fileName, "r");
	
	int size = 129;
	int charArray[size];
	for(int i = 0; i < size; i++) {
		charArray[i] = 0;
	}

	char c;
	while((c = fgetc(stream)) != EOF) {
		charArray[(int)c]++;	
	}

	charArray[128]++;

	
	LinkedList* leafNodes = llCreate();	
	int i =0;
	for(i = 0; i < size; i++){
		tNode* nn = (tNode*)malloc(sizeof(tNode));
		nn->c = i;
		nn->weight = charArray[i];
		addInOrder(&leafNodes, nn);
	}

	fclose(stream);	
	
	return leafNodes;
	
}

tNode* createHuffmanTree(LinkedList* leafNodes){
	
		tNode* root;
		LinkedList* a = leafNodes;
		while (leafNodes->next != NULL) {
		
			root = (tNode*)malloc(sizeof(tNode));
			root->c = -1;

	
			leafNodes->node->parent = root;
			root->left = leafNodes->node;
			leafNodes = leafNodes->next;
		
			leafNodes->node->parent = root;
			root->right = leafNodes->node;
			leafNodes = leafNodes->next;			
	
			root->weight = (root->left)->weight + (root->right)->weight;
			
			addInOrder(&leafNodes, root);
				
		}

		leafNodes = a;
		int i = 0;
			
		addOnesAndZeroes(root);

		LinkedList* p = leafNodes;
		while(p != NULL) {
			if (p->node->c == -1) {
				removeAtIndex(&leafNodes, i);
				i--;

			}	
			i++;
			p = p->next;
		}	
		
		return root;
}


void addOnesAndZeroes(tNode* node) {
		
	
		if (node->left->c == -1) {
			node->left->weight = 0;
			addOnesAndZeroes(node->left);
		} 	
		
		if (node->right->c == -1) {
			node->right->weight = 1;
			addOnesAndZeroes(node->right);
		}
}


void encodeFile(char* file, LinkedList* leafNodes){


	FILE* stream;
	if ((stream = fopen(file, "r")) == NULL) { 

		printf("The file you specified does not exist.\n");

	} else { 
	
		strcat(file, ".huf");
		
		FILE* writeStream;
		writeStream = fopen(file, "w");
	
	
		
		tNode* currNode;
		LinkedList* p;
		int charCode[100];
		int bitArray[8];	
		
	
		unsigned char buffer = 0;
		int bitCount = 0;
		int charCodeSize;
		int packingIndex;
		char c;
		int bytesWritten = 0;
	
		while((c = fgetc(stream)) != EOF) {
			
			charCodeSize = 0;
			p = leafNodes;
			
			
			while (p->node->c != (int)c) {
				p = p->next;
			}
	
			currNode = p->node->parent;
	
	
			if ((currNode->right->c) == (p->node->c)) {
				charCode[charCodeSize] = 1;
			} else {
				charCode[charCodeSize] = 0;
			}
	
			charCodeSize++;
	
		
			while (currNode->parent != NULL) {
				
				charCode[charCodeSize] = (int)currNode->weight;
				currNode = currNode->parent;
				charCodeSize++;			
	
			}
	
	
			
			int flippedCharCode[charCodeSize];
			int i =0;
			int j =0;
			for (i = 0; i < charCodeSize; i++) {
				flippedCharCode[i] = charCode[charCodeSize - i - 1];
			}
	
			
			for(j = 0; j < charCodeSize; j++) {
				
				bitArray[bitCount] = flippedCharCode[j];
				
				bitCount++;
			
				if (bitCount == 8) {
					packingIndex = 0;
					while(packingIndex < 8) {
						
						buffer = buffer << 1;
						if (bitArray[packingIndex] == 1) {
							buffer = buffer | 1;
						}			
						packingIndex++;	
	
					}
			
					putc(buffer, writeStream);
					bytesWritten++;
					bitCount = 0;
					buffer = 0;
				}
	
			}
	
			
		}
	
	
			int bitsPacked = 0;
			charCodeSize = 0;
			p = leafNodes;
			
			
			while (p->node->c != 128) {
				p = p->next;
			}
	
			currNode = p->node->parent;
	
			if ((currNode->right->c) == (p->node->c)) {
				charCode[charCodeSize] = 1;
			} else {
				charCode[charCodeSize] = 0;
			}
	
			charCodeSize++;
	
		
			while (currNode->parent != NULL) {
				
				charCode[charCodeSize] = (int)currNode->weight;
				currNode = currNode->parent;
				charCodeSize++;			
	
			}
	
	
	
			int flippedCharCode[charCodeSize];
			int k = 0;
			for ( k  = 0; k < charCodeSize; k++) {
				flippedCharCode[k] = charCode[charCodeSize - k - 1];
			}
	
			int l = 0;
			for(l = 0; l < charCodeSize; l++) {
			
				bitArray[bitCount] = flippedCharCode[l];
				bitsPacked++;
				
				bitCount++;
			
				if (bitCount == 8) {
					bitsPacked = 0;
					packingIndex = 0;
				
					while(packingIndex < 8) {
						buffer = buffer << 1;
						if (bitArray[packingIndex] == 1) {
							buffer = buffer | 1;
						}			
						packingIndex++;	
	
					}
				
					putc(buffer, writeStream);
					bytesWritten++;
					bitCount = 0;
					buffer = 0;
				}
	
			}
			if (bitsPacked > 0) {
				int m = 0;
			
				for (m = 0; m < bitsPacked; m++) {
					buffer = buffer << 1;
					if (bitArray[m] == 1) {
						buffer = buffer | 1;
					}
				}
				
				buffer = buffer << (8 - bitsPacked);
				putc(buffer, writeStream);
				fclose(writeStream);
				fclose(stream);
			}
	}
}
	
void masterDebugger(LinkedList* ll) {

	LinkedList* p  = ll;
	tNode* currNode;
	
	while (p != NULL) { 
		printf(" %d with weight = %f::  ", p->node->c, p->node->weight);

		currNode = p->node->parent;
		
		if ((currNode->right->c) == (p->node->c)) {
			printf("%d", 1);
		} else {
			printf("%d" , 0);
		}

		while (currNode->parent != NULL) { 
			printf(" weight %f ", currNode->weight);
			currNode = currNode->parent;
		}

		printf("\n");
	
		p = p->next;
	}
}

void decodeFile(char* file, tNode* root){

	FILE* stream;
	if ((stream = fopen(file, "rb")) == NULL) { 
		printf("The file you specified does not exist.\n");

	} else {
		
		fseek(stream, 0, SEEK_END);
		long charsInFile = ftell(stream);
		rewind(stream);
	
		
		strcat(file, ".dec");
		FILE* writeStream;
		writeStream = fopen(file, "w");	
	
		
		char c;
		char* bin;
		int count = 0;
		tNode* node = root;	
		int isFileDone = 1;
	
		unsigned char characters[charsInFile];
		fread(characters, sizeof(char), charsInFile, stream);
	
		int index = 0;
		while(index < charsInFile && isFileDone == 1) {
			
			c = characters[index];
	
			bin = decToBin(c);
				
			count = 0;
			while(count <= 7 && isFileDone == 1){
				if(bin[count] == '1'){
					node = node->right;
				}else if (bin[count] == '0'){
					node = node->left;	
				}
				if(node->c == 128){
					isFileDone = 0;
				}
				
				if(isFileDone == 1 && node->right == NULL && node->left == NULL){
					putc(node->c, writeStream);	
					node = root;
					
				}
				count++;
			
			}
			index++;
			free(bin);
		}
		
		fclose(stream);	
		fclose(writeStream);
	}
}

char* decToBin(int dec){
	
	if(dec < 0)
		dec += 256;
	
	char* bin = (char*)malloc(8*sizeof(char));
	int i =0;
	for(i = 0; i < 8; i++){
		if(dec - (pow(2, 8 - 1 - i)) >= 0){
			*(bin + i) = '1';
			dec = dec - (pow(2, 8 - 1 - i));
		}else
			*(bin+i) = '0';
	}
	return bin;
}

void deleteTree(tNode* node){
	
	if(node != NULL){
	
	deleteTree(node->left);
	deleteTree(node->right);
	free(node);
	}
}
