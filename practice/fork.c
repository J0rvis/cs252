#include<stdio.h>
#include <sys/types.h>
#include<unistd.h>

void forkexample(){
 int x = 1;


  	if (fork()==0){
         printf("Hello from Child! %d\n", ++x);
	}else{    
         printf("Hello from Parent! %d\n", --x); 
	}
}

int main(){ 
    forkexample();
    return 0; 
}
/*
#include  <stdio.h>
#include  <sys/types.h>
int main()
{
    fork();
    fork();
    fork();
    printf("hello\n");
    return 0;
}
*/
