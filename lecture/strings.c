#include <stdio.h> //stack
#include <stdlib.h> //malloc
#include <string.h> //string ops

int main (){
 char ch1 = 'h';
 char str1[6];
 str1[0] = 'h';
 str1[1] = 'e';
 str1[2] = 'l';
 str1[3] = 'l';
 str1[4] = 'o';
 str1[5] = '\0';

printf("%s\n", str1);

//OR

char* str2 = "hello";
nt len = strlen(str1); //get length of string not include \0
//on heap
char* str3 = (char*) malloc(6 * sizeof(char));
str3  = "hello";
printf("%s\n\n",str3); 


int cmp0 = (str1 == str2);
int cmp1 = strcmp(str1, str2);

printf("%d %d\n",cmp0 ,cmp1);

}
