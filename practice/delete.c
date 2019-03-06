#include <stdio.h>
#include <math.h>

typedef unsigned short bitSet;
typedef unsigned int intBitSet;

bitSet makeBitSet(); //Create a new bitset
void displayBitSet(bitSet); //Displays the 16 bits of the bitsef to the screen
void setBit(bitSet*, int); //Sets bit 'index' of the bitset to 1
void clearBit(bitSet*, int); //Sets bit 'index' of the bitset to 0
int bitValue(bitSet, int); //Returns the value of the bit at 'index'

int main() {
	
	bitSet set = makeBitSet();
	displayBitSet(set);

	setBit(&set, 4);
	printf("setting the bit at index 4 to 1...\n");
	displayBitSet(set);			

	clearBit(&set, 4);
	printf("setting the bit at index 4 to 0...\n");
	displayBitSet(set);	

	printf("getting the value of the bit at index 4...\n");
	printf("%d\n", bitValue(set, 4));

}

bitSet makeBitSet() {
	bitSet set = 25;
	printf("the bitset holds the number %d\n", set);
	return set;
}
  
void displayBitSet(bitSet bs) {
	int i;
	for (i = 0; i < 16; i++) {
		printf("%d", ((bs & (int)pow(2, (15 - i))) >> (15 - i)));
	}

	printf("\n\n");
}

void setBit(bitSet* bs, int index) {
	*bs = *bs | (int)pow(2, index);
}

void clearBit(bitSet* bs, int index) {
	*bs = *bs & (255 - (int)pow(2, index));
}
 
int bitValue(bitSet bs, int index) {
	return ((bs & (int)pow(2, index)) >> index);
} 
