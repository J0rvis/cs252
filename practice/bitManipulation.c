#include <stdio.h>
#include <math.h>

typedef unsigned short bitSet;

bitSet makeBitSet();
void displayBitSet(bitSet bit);
bitSet division(bitSet bit);
bitSet multiplication(bitSet bit);
bitSet addition(bitSet bit);

int main(){
 bitSet bit1 = makeBitSet();
 displayBitSet(bit1);
 bitSet div = division(bit1);
 displayBitSet(div); //12?
 /*bitSet mult = multiplication(bit1);
 displayBitSet(mult);
 bitSet add = addition(bit1);
 displayBitSet(add);*/

}

bitSet makeBitSet(){ // create a new bitset
 bitSet bs = 24; //make even for division
 return bs;
}

void displayBitSet(bitSet bs) {
int i;
        for (i = 0; i < 16; i++) {
        printf("%d", ((bs & (int)pow(2, (15 - i))) >> (15 - i)));

       }
 printf("\n\n");
}

bitSet division(bitSet b){
 bitSet s = b >> 1;
 return s;

}

