#include <iostream>
#include <cmath>
#include "Cache.h"
#include "Block.h"
#include <vector>
#include "Set.h"
#include <sys/time.h>

using namespace std;
 
Block::Block (int b){ // create empty block
 blockSize = b;
 valid = 0; // invalid if 1
 notDirty = 0; //is dirty if = 1 


 time.hour = 0;
 time.min = 0;
 time.sec = 0;
 time.usec =0;


}

Block::~Block(){
}

int Block::isValid(){
 cout << "isValid = " << valid << "\n";
 return 0;
}


int Block::tag(){
 cout << "tag = " << addressTag << "\n";

 return tag;
}

int Block::isDirty(){
 cout << "isDirty = " << notDirty << "\n";

 return 0;
}

void setTag(unsigned int t){
 tag = t;
}


void setTime(int h, int m, int s, long usec1){
 time.hour = h;
 time.min = m;
 time.sec = s;
 time.usec = uesc;
}
