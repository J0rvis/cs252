 #include <stdio.h>
 #include <string.h>
 #include <math.h>
 #include <stdlib.h>
 #include <omp.h> // compile with -fopenmp
 #include <iostream>

 int main(int argc, char* argv[]){// take in array of ints 
 // int i,j,k;
  //i = isPrime(2);//is prime
  //j = isPrime(99);//not prime
  //k = isPrime(199);//is prime

//printf("Non-primes should be 0 \n %d \t %d \t %d \t\n", i,j, k);
 int c;
 int start = atoi(argv[1]);
 int end = atoi(argv[2]);
 printf("args: %s , %s \n ", argv[1], argv[2]);
 c = countPrimes(start,end);
 printf("Prime Counter = %d\n",c);

 //int i = omp_get_thread_num();
 int n = omp_get_num_threads();
 printf("number of threads %d\n", i, n);

 }

int isPrime(int prime){
 int primeR = 0;
 int i=2;
         while(prime%i != 0 && i != prime){
          i++;
         }
 // while prime is not evenly devisible and not last number check next number
         if(i == prime){
    //    printf("%d is a PRIME\n",prime);
          primeR = prime;
         } else {
   // printf("the first divisor is %d and %d is not a prime\n", i, prime)    ;

        }

 return primeR;
 }


int countPrimes(int start, int end){


//#pragma omp parallel

  int count = 0;
  int i = start; //start at 10
 int current = 0;// buffer
         while(i != end){
          current = isPrime(i);
                 if(current != 0){
                  //printf("count: %d\n",count);
                  count++;
                 }
          i++; // see if next is prime
         }

  return count;
 
 }

int countPrimesBlocking(int start, int end){
 
 int count = 0;
 int i = start; //start at 10
 int current = 0;// buffer
	while(i != end){
         current = isPrime(i);
         	if(current != 0){
              //   printf("count: %d\n",count);
                 count++;
                }
         i++;//  see if next is prime
        }
 return count;
}

int countPrimesStriping(int start, int end){
 int count = 0;
 int i = start; //start at 10
 int current = 0;// buffer
	while(i != end){
         current = isPrime(i);
         	if(current != 0){
               //  printf("count: %d\n",count);
                 count++;
                }
         i++;//  see if next is prime
        }
 return count;
}





/*bool isPrime(int prime){
 int primeR = 0;
 int i=2;
 bool primeB = true; 
         while(prime%i != 0 && i != prime && primeB == true){
          i++;
         }
        if(i == prime){
         printf("%d is a PRIME\n",prime);
         primeR = prime;
        } else {
         printf("the first divisor is %d and %d is not a prime\n", i, prime);
	 primeB = false;
        }

 return primeB;
 }*/
