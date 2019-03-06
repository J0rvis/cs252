#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



typedef unsigned short bitSet;

bitSet makeBitSet();// create new bitset
void displayBitSet(bitSet bs); // displays the 16 bits of the bitset to the screen
void setBit(bitSet* bs, int index); // sets bit index of bitset to 1
void clearBit(bitSet* bs, int index); // sets bit index of the bitset to 0
int bitValue(bitSet bs, int index); // returns the val of the bit at index

/*
 *bitwise operators
 *&= AND assignment
 *|= inclusive OR
 *^= excluslive OR
 *<<= left shift assignment 
 *>>= right shift assignment
 *
 *bitwise logic
 *
 * 
 *
 *
 *
 * */


int main(){
 bitSet myset = makeBitSet();
 displayBitSet(myset);

 setBit(&myset, 6);
 displayBitSet(myset);
 clearBit(&myset, 6);
 displayBitSet(myset);

 int value = bitValue(myset, 6); //0
 printf("\n INDEX 6 VALUE : %u\n", (value ? 1 : 0));

 int val2 = bitValue(myset, 4);
 printf("\n INDEX 4 VALUE : %u\n", (val2 ? 1 :0));

 myset = 1 << 3;
 printf("1 << 01000000 = ");
 displayBitSet(myset);
}

bitSet makeBitSet(){ // create a new bitset 
 bitSet bs = 8;// 0000000000010100 
 return bs;

}

//void displayBitSet(bitSet bit){
// int i =0;  
//}
/**
 *ex 2: 
 *bs & 2 pow (15-i) checks to see if the current indexs are both 1's = 010
 *>> (15-i) moves the "010" allll the way to the end so 0 by 14 then 10 = 16 digits
 *0's exist because of & opperator >> just moves everythin
 */

void displayBitSet(bitSet bs) {
 int i;
	for (i = 0; i < 8; i++) {
	//printf("%d", ((bs & (int)pow(2, (15 - i))) >> (15 - i)));
	printf("%d",((1 << (7 - i)) & bs) ? 1 :0);
	}

 printf("\n\n");
}

/**
 *| gives 1 if any of b | a = 1
 *de referenced 4 is 100 if (4,2) then = 0010000000000100 = 
 * basically places a 4 at index
 * */
void setBit(bitSet* bs, int index){ //sets bit index of the bitset to 1
 *bs = ((1 << index) | *bs);


}

void clearBit(bitSet* bs, int index){
 *bs = (~(1 << index)& *bs);
}

int bitValue(bitSet bs, int index){
 bitSet val = (int)((1 << index)& bs);
 //printf("\n Value: %u\n",val ? 1 : 0);
 return val;
}




