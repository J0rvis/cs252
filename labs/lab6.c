#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h> // compile with -pthread flag


typedef struct range{
 int index1; //ie 10
 int index2; // ie 100
} range;


int total;
pthread_mutex_t mutex_count;



int* arrayCopy(int* srcArry,int srcLength, int srcPos, int startPos, int desLength);
int isPrime(int prime);
int countPrimes(int start, int end);
void* threadPrimes(void *x_void_ptr);
int** divide(int starter, int end, int threads, range* rangeC);


int isPrime(int prime){
 int primeR = 0;
 int i=2;
	while(prime%i != 0 && i != prime+ 1){
	 i++;
	} 
	if(i == prime){
	 primeR = prime;
	} 

 return primeR;
}


int countPrimes(int start, int end){
 int count = 0; 
 int i = start;// start at 10
 int current = 0;// buffer 

	//while(i != end+1){
	 for(i = start; i < end +1; i++){
	 current = isPrime(i);
		if(current != 0){
		 //printf("count: %d\n",count);
	 	 count++;
		}
	// i++; // see if next is prime
	}
 return count;
}

int runThreads(start,end,tNum){
 int i =0;
 pthread_t thr[tNum];
 //int r;
 range* rangeC = (range*) malloc(tNum * sizeof(range)); //ie 4 threads have 4 ranges 


int ** arr = divide(start, end, tNum, rangeC);
 int x;
// thread_data_t thr_data[tNum];
	for(i = 0; i < tNum; i++){
	 pthread_create(&thr[i], NULL, threadPrimes, &rangeC[i]);
	}
	//wait for all to complete 
	for(i = 0; i< tNum; i++){
	 pthread_join(thr[i], NULL);
	}
 printf("total = %d\n", total);
 free(rangeC);
 return 0;
}

void* threadPrimes(void *rangeP){
printf("\t\t\tTHREAD PRIMES \n\n\n");
range* rangeT = rangeP;

int start = rangeT->index1;
int end = rangeT->index2;

 int count = 0;
 int i = start;// start at 10
 int current = 0;// buffer
 //one thread per call 

 int n = 0;
//printf("thread primes\n\n gStart = %d \t gEnd = %d\n",start, end);
	//while(i != gEnd+1){
	for(i = start; i < end+1 ; i++){
	 current = isPrime(i);
		if(current != 0){
		 //printf("count = %d prime is : %d\n", count, i);
		 count++;
		} 
	}
 printf("countPrimes of %d to %d = %d\n", start, end, count);
 pthread_mutex_lock(&mutex_count);
 total += count;
 pthread_mutex_unlock(&mutex_count);

}


int** divide(int starter, int end, int threads, range* rangeC){
 double dthreads = threads;
 double length = (end - starter)+1;
 double slots = length/ dthreads; 

 int roundSlots = ceil(slots);
// printf("Original length = %f  exact slots = %f  rounded up = %d\n", length, slots, roundSlots);
 
 int array[(int)length];//temp
 int n = 0;
 int k =0; 
 //range rangeT[tNum];
 //make array of original range
	for(k = starter; k < end; k++) {
	 array[n] =  k;
	 printf("k = %d\n", k);
	 n++;		
	}

 int** output = (int**) malloc((threads)* sizeof(int*));//[threads] [int*]

 int i = 0; //threads
 int p = 1;

 rangeC[0].index1 = starter;
 rangeC[0].index2 = starter + roundSlots -1 ;
 //printf("thread : %d new range [ %d , %d ]\n", p, rangeC[0].index1, rangeC[0].index2);
	for(i = 0; i < threads; i++) {
	 int start = i * roundSlots;//start
		if(i == threads -1){
		 if(start + 5 > end){
		//  printf("start > end\n ");
		  int calc = (start+5) - end;
		 // printf("old end  - first end = %d\n", calc);
		  roundSlots = roundSlots - calc;
		 // printf("ROUND SLOTS = %d",roundSlots);
		 }
		}	


	if(p < threads){	
	 rangeC[p].index1 = rangeC[p-1].index1 + roundSlots;
	 rangeC[p].index2 = rangeC[p-1].index2 + roundSlots; //end  is -1 bc 0 start
	//	if(p != threads-1){
//		 printf("thread : %d new range [ %d , %d ]\n", p, rangeC[p].index1, rangeC[p].index2);	 
//	 	}
	 p++;
	}
	 int* temp = (int*) malloc(roundSlots * sizeof(int));
	 temp = arrayCopy(array, length, start, 0, roundSlots);//original Array, oAlength, 
	 output[i] = temp;
	}
	rangeC[p-1].index2 = rangeC[p-2].index2 + roundSlots;
//	printf("thread : %d new range[ %d , %d ]\n", p-1 , rangeC[p-1].index1, rangeC[p-1].index2);  
	//rangeC = rangeT;
	//free(array);
 return output; //FREE THIS THING*/
}

int* arrayCopy(int* srcArry,int srcLength, int srcPos, int startPos, int desLength){
 int* arry = (int*) malloc(desLength * sizeof(int));
 int i = 0;
 int j = 0;
	for(i = srcPos; i < srcLength; i++){
	 arry[j] = srcArry[i]; 
	 j++;
	} 
 return arry;

}

	
int min(int a, int b){
 int result;
	if(a < b){
	 result = a;
	} else if (b < a){
	 result = b;
	} else { //ie =
	 result = a;
	}
return result;
}

int main(int arc, char* argv[]){
// int c;
// c = countPrimes(10, 10000);
// printf("Counter = %d\n",c);


/* int* arry = (int*) malloc(9 * sizeof(int)); 
 int j = 0;
 int k = 1;
	for(k = 1; k < 10; k++){
	 printf("k = %d\n", k);
	 arry[j] = k;
	 j++;
	}


//{1,2,3,4,5,6,7,8,9};//{3456789}
int* arry2;// = (int*) malloc(6* sizeof(int)); 
 arry2 = arrayCopy(arry, 9, 2, 0, 6);

 int i = 0;

	for(i = 0; i < 7; i++){
	 printf("arry2[%d] = %d\n", i, arry2[i]);

	}

*/

int start = atoi(argv[1]);
int end = atoi(argv[2]);
int threads = atoi(argv[3]);

int c = countPrimes(start,end);
printf("\t\tCOUNT PRIMES = %d\n\n", c);

int r = runThreads(start,end,threads); // threadnum
	

}
