#include <stdio.h>
#include <stdlib.h>

int* makeArray(int* pCount);

int main(){
/*ask for pointers*/
 int* arr; 
 int count;
 int i;
 /*point to heap*/
 arr = makeArray(&count);
 //arr  = (int*) malloc(5 * sizeof(int)); //open spots on heap

 //makeArray(&arr, &count);// both need addresses 
 printf("\n MAIN METHOD RETURNS \n"); 
 printf("count : %d\n", count);

 for(i = 0; i < count; i++){
  printf(" arr[%d]= %d \n", i, arr[i]); //may need to fix

 }

 free(arr);
 return 0;
}


int* makeArray(int* pCount){
 int i;

 int* arr = (int*) malloc(5 * sizeof(int));// array on heap

 printf("\n HELPER METHOD RETURN \n");
 *pCount = 5;
 for(i = 0; i< *pCount ; i++){
   arr[i] = i;
 }

 for(i = 0; i< *pCount; i++){
  printf(" arr[%d]= %d \n", i, arr[i]);

 }

/* printf("\n HELPER METHOD RETURNS \n");
 for (i =0; i < 5; i++){
  printf(" arr[%d] = %d \n",i , (*arr)[i]);
 }*/
 return arr;
}
