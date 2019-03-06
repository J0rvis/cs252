#include <stdio.h>
 int main (){

 int nums[5];

 nums[0] = 0;
 nums[1] = 1;
 nums[2] = 2;
 nums[3] = 3;
 nums[4] = 4;

int i = 0;
 for(i =0; i < 5  ;i++){
     printf("Number Array %d = %d \n ", i, nums[i]);
 }
 printf("SIZE OF = %d\n", sizeof(nums));
 }

