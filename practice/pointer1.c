#include <stdio.h>
//pointer= variable that holds address of another variable
int main(){
   int val = 30;

 //declare a pointer
   int *pointer; //value is address of another variable
   pointer = &val; //assign address of val to pointer
   
   printf("address of val = %d \n", &val);
   printf("value of pointer variable = %d \n",&pointer);
   printf("value of pointer = %d \n", *pointer);
}
