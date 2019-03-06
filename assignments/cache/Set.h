#ifndef _SET_H_
#define _SET_H_
#include <vector>
#include "Block.h"

class Set{
private:
 int blocks_per_set,bytes_per_block;
 std::vector<Block*> blockList;

public:
 Set(int setAssoc, int byteBlock);
 ~Set();
 int readSet(unsigned int address);
 int writeSet(unsigned int address);

};
#endif


