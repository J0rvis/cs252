#include <stdio.h>
#include <stdlib.h>
#include <omp.h>  // compile with -fopenmp

void printOutOrdered(){
 int i = 0;
 int nums[] = {1,2,3,4,5,6,7,8,9,10};
 int count = 0;
 #pragma omp parallel for ordered  
	for(i = 0; i < 10; i++){
	  int totalThreads = omp_get_num_threads();
	  int tNumber = omp_get_thread_num();
	  #pragma omp ordered
	  printf("Thread %d of %d where nums[%d] = %d count = %d\n",tNumber, totalThreads,i, nums[i], count);
	  // printf("Nums[%d] = %d\ count = n",i,  nums[i], count);
	  count++;
	}


}

void printOutOrderedThreads(){
 int i = 0;
 int nums[] = {1,2,3,4,5,6,7,8,9,10};

	#pragma omp parallel 
	{
		#pragma omp barrier
		#pragma omp for nowait
		for(i = 0; i < 10; i++){
		 int totalThreads = omp_get_num_threads();
		 int tNumber = omp_get_thread_num();
		 printf("Thread %d of %d where nums[%d] = %d\n",tNumber, totalThreads,i,  nums[i]);
		}
	}

}

void printOutNormal(){
 int i = 0;
 int nums[] = {1,2,3,4,5,6,7,8,9,10};
	for(i = 0; i < 10; i++){
         printf("Nums[%d] = %d\n",i,  nums[i]);
        }

}


int main(){
// printf("BLOCK: \n");
//printOutOrdered();

 printf("STRIPING: \n");
 printOutOrderedThreads();
// printOutNormal();
 return 0;
}
