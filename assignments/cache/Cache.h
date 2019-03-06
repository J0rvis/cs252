#ifndef _CACHE_H
#define _CACHE_H

#include "Set.h" 
//typedef unsigned short bitSet;
#include <vector>

class Cache {

public:
typedef unsigned int bitSet;

private:
 int memory; 
 int cache;
 int block; 
 int set;
 int written;
 std::vector<Set*> setList;	

public:
 Cache(int memSize, int cacheSize, int blockSize, int setAssoc);
 ~Cache();
 int read(bitSet memAddress);
 int write(bitSet memAddress);
 int dumpCache();
 unsigned int makeBitSet(int num);
 void setBit(bitSet* bs, int index); // 1
 void clearBit(bitSet* bs, int index); // 0
 void displayBitSet(bitSet bs, int size);
//int bitValue(bitSet bs, int index); 

void display();
};
#endif
