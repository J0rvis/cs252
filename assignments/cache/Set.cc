#include <iostream>
#include <cmath>
#include "Cache.h"
#include "Block.h"
#include <vector>
#include "Set.h"

using namespace std;
//set the skeleton 
/*SET
 * translate block offset 
 * place info in block
 *
 *
 * */

Set::Set(int setAssoc, int byteBlock){// blocks per set, bytes per block
//setAssoc is # cache lines/blocks per set
 blocks_per_set = setAssoc;
 bytes_per_block = byteBlock;
 int i =0;
	for(i = 0; i < blocks_per_set; i++){
	 blockList.push_back(new Block(bytes_per_block));
	}
}


Set::~Set(){
 int i = 0;
	for(i = 0; i < blocks_per_set; i++){
	// blockList.erase(blockList.begin() + i -1);
	delete blockList[i];
	}

}

int Set::readSet(unsigned int address){
 cout << "Read [in Set] \n" << address << "\n";
 int result;
 struct timeval tv;
 struct tm* tm;
 struct timezone tz;
 int temp = -1;
	int i = 0;
	for(i = 0; i < blocks_per_set; i++){
		if((blockList[i]->tag == address && blockList[i]->isValid == 0){ //exists and is filled 
		 temp = i;
		}
	}

//hit
	if(temp != -1){
	 result = 0;
	 gettimeofday(&tv,&tz);
	 tm = localtime(&tv.tv_sec);
	 int h = tm->tm_hour;
	 int m = tm->tm_min;
	 int s = tm->tm_sec;
	 long usec = tv.tv_usec;
	 blockList[temp]->setTime(h,m,s,usec);
//miss
	} else {//left off here
	/*
	 result = 1;
		while((blockList[i]->tag == address && blockList[i]->isValid == 0)){ 	 
		i++;
		}

	*/

	}

return 0;
}


int Set::writeSet(unsigned int address){
 cout << "Write [in Set] " << address << "\n";
 return 0;
}


/*
void displayBitSet(unsigned int bs) {
int i;
        for (i = 0; i < 16; i++) {
         //printf("%d", ((bs & (int)pow(2, (15 - i))) >> (15 - i)));
         printf("%d",((1 << (15 - i)) & bs) ? 1 :0);
        }

  printf("\n\n");
}


*/




