#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
//#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "uwecSocket.h"
#include <omp.h> // -fopenmp


int main(){
 int index1 = 1000;
 int index2 = 1000000;
 int portno = 7333;
 int nodes = 4;

 printf("Starting\n");
 int ss = setupServerSocket(portno);

 int s[nodes];
 int nConnect = 0;
	while(nConnect < nodes){
	 printf("Waiting for Conection ... \n");
	 s[nConnect] = serverSocketAccept(ss);
	 printf("Connected %d of %d\n", nConnect + 1, nodes);
	 nConnect++;
	}

	if(nodes == nConnect){
	 printf("All Nodes Connected\n");
	 omp_set_num_threads(nodes);
	 int count = 0;
	 printf("Threading in parallel\n");
	 #pragma omp parallel reduction (+:count)
	{
	
	 int currentThread = omp_get_thread_num();
	 int start = (int) (((double) (index2 -index1) / (double) nodes) * currentThread) + index1;
 	 int end  = (int) (((double) (index2 -index1) / (double) nodes) * (currentThread + 1)) + index1;
 
	 printf("Writing out %d to %d from server \n", start, end);

	 writeInt(start, s[currentThread]);
	 writeInt(end, s[currentThread]);
	
	 printf("Finished Writing\n");
	 int primes = readInt(s[currentThread]);
	 printf("Primes from %d to %d : %d\n", start, end, primes);
	 count += primes;
	}

	printf("Total Number of Primes: %d\n", count);
	}
return 0;
}
