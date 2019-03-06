#include <iostream>
#include <cmath>
#include "Cache.h"
#include "Block.h"
#include <vector>
#include "Set.h"
#include <stdlib.h>
#include <stdio.h>

using namespace std;
//Cache::typedef unsigned int bitSet;

Cache::Cache(int memSize, int cacheSize, int blockSize, int setAssoc){
//setAssoc is # cache lines/blocks per set
 memory = memSize; //memory address in bits
 cache = cacheSize; // bytes in cache
 block = blockSize; // bytes in block
 set = setAssoc;//ie blocks per set 
 int i = 0;
 int setCount = cache/ (block * setAssoc);
 
 
	for(i = 0; i < setCount; i++){
	 setList.push_back(new Set(block, setAssoc)); //enter empty set
	}
}


Cache::~Cache() {
int i;
int setCount = cache/ (block * set);
	for(i = 0; i < setCount; i++) {
	 delete setList[i];
	}
}



int Cache::read(bitSet memAddress){
 cout << "I read in " << memAddress << "\n";
// int blockCount = cahce/block;
 int setCount = cache/(block * set);
 int setBits = (int) log2(setCount);
 int blockBits = (int) log2(block);
 int tagBits = memory - setBits - blockBits;

 cout <<"setCount " << setCount << " setbits " << setBits << " blockBits " << blockBits << "tagBits" << tagBits<<"\n";

 int i = 0;
 int j = 0;
 unsigned int sNum = 0;//index in set array
 unsigned int bNum = 0; // index in block array 
 
 cout<<"SET BITS \n";
	for(i = memory - (setBits + blockBits); i < memory - blockBits; i++){
		if(memAddress & (1<<(memory -1 -i))){// if 1
		 setBit(&sNum, i+blockBits);
		 cout << "set at " << i << " : 1 \n";
		} 
		cout << i << "\n";
	}  
cout << "BLOCK BITS \n";
	for( i = memory- blockBits; i < memory ; i++){
		if(memAddress * (1 << (memory -1 -i))){
		 setBit(&bNum, i);
		 cout << "block at " << i << " : 1 \n";
		}
		 cout << i << "\n";
	}
/*
 bitSet setNum  = makeBitSet(2);
 bitSet tagNum = makeBitSet(3);
 bitSet setNum = ((memAddress << tagBits) & ((unsigned int)pow(2, memory) - 1)) >> (tagBits + blockBits);
 bitSet tagNum = (memAddress >> (blockBits + setCount)); 
 */
 cout << "set number = " << sNum <<" \n";
 displayBitSet(sNum, memory);
 cout << "tag number = " << bNum << "\n";
 displayBitSet(bNum, memory);
 int read = setList[sNum]->readSet(bNum);
return 0;
}



int Cache::write(bitSet memAddress){
 cout << "I wrote in " << memAddress << "\n";
return 0;
}

int Cache::dumpCache(){
 cout << "I dumped the Cache\n";
 cout << "Wrote back " << written << " dirty bytes to Cache\n";
return written;
}



void Cache::display(){
cout << "\t\tDisplay Cache and Relative Information \n";//print
cout << "Memory Size : " << memory << "\n";//4
cout << "Cache Size : " << cache << "\n";//8
cout << "Block Size : " << block << "\n";//2
cout << "Blocks per set : " << set << "\n";//1
/*
cout << "\t Cache Calculations\n";

int blockCount = cache/block; // 4
cout << "Blocks in Cache : " << blockCount << "\n";

int setCount = cache/ (block * set); // 4
cout << "Sets in Cache : " << setCount << "\n\n";

int setBits = (int) log2(setCount);
cout << "Bits for Set : " << setBits << "\n";

int blockOffset = (int) log2(block);
cout << "Bits for Block : " << blockOffset << "\n";

int leftTag = cache - (setBits + blockOffset);
cout << "Bits for Tag : " << leftTag << "\n";

bitSet bs = makeBitSet(0);
displayBitSet(bs);
setBit(&bs, 0);
displayBitSet(bs);
clearBit(&bs,0);
displayBitSet(bs);*/
}

unsigned int Cache::makeBitSet(int num){
 bitSet bs = num;
return bs;
}

void Cache::setBit(bitSet* bs, int index){
 *bs = ((1<<(memory-1 - index))| *bs);

}

void Cache::clearBit(bitSet* bs, int index){
 *bs = (~(1<<(memory- 1 - index))& * bs);
}

void Cache::displayBitSet(bitSet bs, int size){
cout << "display bit set \n";

int i = 0;
for(i = 0; i < size ; i++){ 
	if(bs & (1<<(size -1 -i))){
	 cout << "1";
	} else {
	 cout << "0";
	}
} 
 cout << "\n\n";

}


/*
int* separateLocation(bitSet bs, int leftTag, int setBits, int blockOffset ){
 int i = 0;
 int bits[memory];

 int t,s,b; // send back index 
//make easier to work with 
	for(i = 0; i < memory; i++){
		if(bs &(1<<((memory-1)-i))){
		 bits[i] = 0;
		 cout << "0";
		} else { 
		 bits[i] = 1;
		 cout << "1";
		}
	} 

	for(i = leftTag -1; i < memory; i++){ //skip tag bc who cares 


 cout << "\n";
}
*/

