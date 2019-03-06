#ifndef _BLOCK_H_
#define _BLOCK_H_
#include <vector>
#include <iostream>
//make struct easily accesable 
class Block {

public:
typedef struct timeStamp{
 int hour;
 int min;
 int sec;
 long usec;
} timeStamp;

//global
private:
int blockSize; 
int valid;
int notDirty;
unsigned int addressTag;
timeStamp time;

public:
 Block(int b);
 ~Block();
 int isValid();
 int tag();
 int isDirty();
 void setTag(unsigned int t);
 void setTime(int h, int m, int s, long usec1);

};
#endif
