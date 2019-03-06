#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "uwecSocket.h"


int main(){
 int portno = 7333;
// char* host = "localhost";
 int s = callServer("localhost", portno);
 printf("Reading int 1\n");
 int start = readInt(s);

 printf("Reading int 2\n");
 int end = readInt(s);
 printf("start = %d end = %d\n",start, end);


 int primes = 0;
 int i = 0;
	for(i = start ;i <= end; i++){
	 int num = 2;
	 int j = 0;
	 	while( i % num != 0){
		 j++;
		 num++;
		}
		if(i == num && j != 0){ 
		 primes++;
		}
	}
 printf("writing primes %d \n", primes);
 writeInt(primes,s);
 close(s);
 return 0;
}

