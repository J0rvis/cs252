#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "lab4.h"
int binToDec(char* bin);
char* decToBin(int dec);
int baseToDec(int base, char* value);
char* decToBase(int base, int dec);
int converter(char c);
char convertInt(int i);
/*
*int baseToDesc(int base, char* value);
*char* decToBase(int base, int desc);
* */

/*int main(){

 int dec = binToDec("11101");//1100101010101
 printf("\n ANSWER\n binary 11101 = decimal %d\n", dec);

 char* bin = decToBin(29);
 printf("\n ANSWER\n decimal 29 = binary %s\n", bin);

 int decimal = baseToDec(16, "1D");//should be 29
 printf("\n ANSWER\n base 16 (HEX:1D) = decimal %d\n", decimal);

 char* bin2 = decToBase(16,29);// should be 11A or 1 1 10
 printf("\n ANSWER\n base 16 (DEC:29) = hexadecimal %s\n",bin2);
 free(bin2);
 free(bin);
}*/

int binToDec(char* bin){
 printf("\n\tBIN TO DEC\n");
 int addUp = 0;
 int i = 0;
 double exp = 0;
	for(i = strlen(bin) -1; i >= 0; i--){
	 char c = bin[i];
	 int current = c - '0';
		if(current != 0){
		 double convert = pow(2.0,exp);
		 addUp += convert;
		}
	 exp++;
	 
	}
}

char* decToBin(int dec){
 printf("\n\tDEC TO BIN\n");
 char temp [100];
 int dec2 = dec;
 int i =0;
	while(dec2 > 0){
	 temp[i] = dec2%2; //records if it is 1 or 0
 	 dec2 = dec2/2;
	 i++;
	}
	
 char* bin = (char*) malloc( (i+1) * sizeof(char)); //correct size... saved to different array to save space + space for \0 
 int j =0;
 int k = 0;
	for(j = i-1; j >= 0; j--){
	 bin[k] = temp[j] + '0';
	 k++; //iterate through empty array
	}
 bin[i] = '\0';
 return bin;

}

int baseToDec(int base, char* bin){
 printf("\n\tBASE TO DEC\n");
 int addUp = 0;
 int i = 0;
 int power = 1;
	for(i = strlen(bin) -1; i >= 0; i--){
	 addUp += converter(bin[i]) * power;
	 power = power * base;
	}

return addUp;

}

char* decToBase(int base, int dec){
 printf("\n\tDEC TO BASE\n");
 int temp [100];
 int dec2 = dec;
 int i =0;
	while(dec2 > 0){
	 temp[i] = dec2%base; //records if it is 1 or 0 or A ...
	 dec2 = dec2/base;
	 i++;
	}

char* bin = (char*) malloc( (i+1) * sizeof(char)); //correct size... saved to different array to save space + space for \0
 int j =0;
 int k = 0;
	for(j = i-1; j >= 0; j--){
	 bin[k] = convertInt(temp[j]);
	 k++; //iterate through empty array
	}
 bin[i] = '\0';
 printf("\n");
 return bin;

}

int converter(char c){
	if(c <= '9'){
	 return c - '0';
	} else { 
	return c - 'A' + 10;
	}
}

char convertInt(int i){
	if(i <= 9){
	 return i + '0';
	} else {
	 return 'A' + i - 10;
	}  
}


