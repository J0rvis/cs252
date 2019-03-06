 #include <stdio.h>
 #include <string.h>
 #include <math.h>
 #include <stdlib.h>
 #include <omp.h> // compile with -fopenmp
 


int isPrime(int prime){
 int primeR = 0;//accounting for 2
 int i = 2;
         while(prime%i != 0 && i < prime + 1 || i == 1){ //halfs work
	//  printf("%d\n", i);
		if(i == 2){
		 i++;
		} else if( i >= 3)  {// only check odd numbers
         	 i += 2;//only goes through odds
        	}
	}
 // while prime is not evenly divisible and not last number check next number
           if(i == prime){
	 // int tNum = omp_get_thread_num();
         // printf(" %d: %d\n",tNum, prime);
          primeR = prime;
         } else {
   // printf("the first divisor is %d and %d is not a prime\n", i, prime)    ;
	  //int tNum2 = omp_get_thread_num();
          //printf(" %d: %d\n",tNum2, prime);

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
 omp_set_num_threads(4); 
 int count = 0;
 int i = start; //start at 10

 #pragma omp parallel for reduction(+:count)
	//int current = 0;
	for(i = start; i < end + 1; i++){
	int current = 0;
         current = isPrime(i);
         	if(current != 0){
		 //#pragma omp ordered
		 int tNum = omp_get_thread_num();
		 printf(" %d : %d\n" ,tNum,current);
                 count++;
                } else {
		 int tNum = omp_get_thread_num();
		 printf(" %d : %d\n",tNum, i);
		}
        }
 
 return count;
}

int countPrimesStriping(int start, int end){
 int count = 0;
 int i = start; //start at 10
 //int current = 0;// buffer
	//while(i != end){
	#pragma omp parallel reduction (+:count) 
	{	
		int current = 0;
		//#pragma omp nowait
		#pragma omp for schedule(static, 1) // reduction(+:count)
		for(i = start; i < end+ 1; i++){
        	 current = isPrime(i);
         		if(current != 0){
                	 int tNum = omp_get_thread_num();
			 printf(" %d: %d\n",tNum, current);
			 count++;
                	} else {
			 int tNum = omp_get_thread_num();
			 printf(" %d: %d\n",tNum, i);

			}
         //i++;//  see if next is prime
        	}
	}
 return count;
}


int timeBlocking(int start, int end){
 omp_set_num_threads(4);
 int count = 0;
 int i = start; //start at 10

 /*time for 0: 0.668064 with 4199 found*/
//if prime then total for all and total for each thread
 double total = 0;
 double t0 = 0;
 double t1 = 0;
 double t2 = 0;
 double t3 = 0;
 
//if prime is found then ++
 int primet0 = 0;
 int primet1 = 0;
 int primet2 = 0;
 int primet3 = 0;

  #pragma omp parallel reduction(+:primet0) reduction(+:primet1) reduction(+:primet2) reduction(+:primet3) reduction(+:t0) reduction(+:t1) reduction(+:t2) reduction(+:t3)  reduction(+:count) reduction(+:total)
 {
         double tmOMP1 = omp_get_wtime();//past
 	#pragma omp for
        for(i = start; i < end + 1; i++){
         int current = 0;
         current = isPrime(i);
	 int tNum = omp_get_thread_num();
                if(current != 0){ // prime found 
                 //#pragma omp ordered
                 //int tNum = omp_get_thread_num();
                	if(tNum == 0){
			 primet0 ++;//got a prime
			} else if (tNum == 1){
			 primet1 ++;
			} else if (tNum == 2){
			 primet2 ++;
			} else if (tNum == 3){
			 primet3 ++;
			}
                 count++;// prime count all
                } else {
                // int tNum = omp_get_thread_num();
                 
                }
	 double tmOMP2 = omp_get_wtime();//current
	 double calculated = tmOMP2 - tmOMP1; // thread time 
	 total += calculated; //add thread time to norm
		if(tNum == 0){
		 t0 += calculated;//save thread time regardless of if prime was found 
		} else if (tNum == 1){
		 t1 += calculated;
		} else if (tNum == 2){
		 t2 += calculated;
		} else if (tNum == 3){
		 t3 += calculated;
		}	
        }
 }

 printf("Blocking\n");
 printf(" time for 0: %f with %d found\n", t0, primet0);
 printf(" time for 1: %f with %d found\n", t1, primet1);
 printf(" time for 2: %f with %d found\n", t2, primet2);
 printf(" time for 3: %f with %d found\n", t3, primet3);
 printf(" overall time %f with %d found\n\n", total, count); 
 return count;
}

int timeStriping(int start, int end){
 omp_set_num_threads(4);
 int count = 0;
 int i = start; //start at 10
 /*time for 0: 0.668064 with 4199 found*/
//if prime then total for all and total for each thread
 double total = 0;
 double t0 = 0;
 double t1 = 0;
 double t2 = 0;
 double t3 = 0;
//if prime is found then ++
 int primet0 = 0;
 int primet1 = 0;
 int primet2 = 0;
 int primet3 = 0;
  #pragma omp parallel reduction(+:primet0) reduction(+:primet1) reduction(+:primet2) reduction(+:primet3) reduction(+:t0) reduction(+:t1) reduction(+:t2) reduction(+:t3)  reduction(+:count) reduction(+:total)
 {
         double tmOMP1 = omp_get_wtime();
 #pragma omp for schedule(static,1)
        for(i = start; i < end + 1; i++){
         int current = 0;
         current = isPrime(i);
         int tNum = omp_get_thread_num();
                if(current != 0){ 
                        if(tNum == 0){
                         primet0 ++;
                        } else if (tNum == 1){
                         primet1 ++;
                        } else if (tNum == 2){
                         primet2 ++;
                        } else if (tNum == 3){
                         primet3 ++;
                        }
                 count++;
                } else {
                 int tNum = omp_get_thread_num();
                }
         double tmOMP2 = omp_get_wtime();
         double calculated = tmOMP2 - tmOMP1; 
         total += calculated; 
                if(tNum == 0){
                 t0 += calculated;//save thread time regardless of if prime was found
                } else if (tNum == 1){
                 t1 += calculated;
                } else if (tNum == 2){
                 t2 += calculated;
                } else if (tNum == 3){
                 t3 += calculated;
                }
        }
}

 printf("Striping\n");
 printf(" time for 0: %f with %d found\n", t0, primet0);
 printf(" time for 1: %f with %d found\n", t1, primet1);
 printf(" time for 2: %f with %d found\n", t2, primet2);
 printf(" time for 3: %f with %d found\n", t3, primet3);
 printf(" overall time %f with %d found\n\n", total, count);
 return count;
}





int main(int argc, char* argv[]){// take in array of ints
 // int i,j,k;
 //i = isPrime(2);//is prime
 //j = isPrime(99);//not prime
 //k = isPrime(199);//is prime

 //printf("Non-primes should be 0 \n %d \t %d \t %d \t\n", i,j, k);
 int b,s;
 int start = atoi(argv[1]);
 int end = atoi(argv[2]);
 
printf("Blocking Not Timed\n");
 //printf("args: %s , %s \n ", argv[1], argv[2]);
 b = countPrimesBlocking(start,end);
 printf("Prime Counter = %d\n\n",b);

 printf("Striping Not Timed\n");
 s = countPrimesStriping(start,end);
 printf("Prime Counter = %d\n\n",s);
 
 printf("\n\tTimed Portion\n");

 int tBlock = 0;
 tBlock = timeBlocking(start, end);

 int tStripe = 0;
 tStripe = timeStriping(start,end);
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

