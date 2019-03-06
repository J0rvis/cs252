#include <stdio.h>
#include<stdlib.h>
#include <math.h>
#include <string.h>
//#include "lab4.h": make it work later
//unions 
typedef union intU {
 unsigned int bits;
 int theInt;
}intU;

void displayInt(int theI);
int makeInt(char* i);
int binToDec(char* i);


int main(){
 printf("\t DISPLAY INT \n");
 displayInt(5);
 printf("\n");
 displayInt(-9);
 
 int pos = makeInt("+101"); 
 int neg = makeInt("-1001");//-9 
 printf("POS +101 : %d \n", pos);
 printf("NEG -1001 : %d \n", neg);
 return 0;
}



void displayInt(int theI){
 unsigned int temp = theI;
 int i =0;
	for (i = 0; i < 32; i++) {
		if(i %8 == 0){
		 printf(" ");
		}
	 printf("%d",((1 << (31 - i)) & temp) ? 1 :0);
		
	}
 printf("\n");

}



int makeInt(char* i){
 intU makeU;
	if(i[0] == '+'){
	 printf("IS POSITIVE \n");
	 makeU.theInt  = binToDec(i);
	 printf("UNSIGNED POS INT: %d \n", makeU.theInt);
	 return makeU.theInt;
	} else {
	 printf("IS NEGATIVE \n");
	 //use bitwise ops to revers then add 1 in binary "long addition"
	 //i = i ^ 1;
	 makeU.bits = binToDec(i); // 101
	 displayInt(makeU.bits); 
	 makeU.bits = ~makeU.bits+1;
	 displayInt(makeU.bits);
	 return makeU.bits;
	}

}

int binToDec(char* bin){
 printf("\n\tBIN TO DEC\n");
 int addUp = 0;
 int i = 0;
 double exp = 0;
	for(i = strlen(bin) -1; i >= 1; i--){
	 char c = bin[i];
	 int current = c - '0';
		if(current != 0){
		 double convert = pow(2.0,exp);
		 addUp += convert;
		}
	 exp++;
	}
 return addUp;
}


void displayBitSet(unsigned int bs) {
 int i;
        for (i = 0; i < 16; i++) {
         //printf("%d", ((bs & (int)pow(2, (15 - i))) >> (15 - i)));
         printf("%d",((1 << (15 - i)) & bs) ? 1 :0);
        }

  printf("\n\n");
 }

