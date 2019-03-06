#include <stdio.h>
#include <string.h>

int foo1(int * x){
 int c = 5;
 int i = 0;
	for(i = 0; i < c; i++){
	 x[i] = i;

	}

 return c;

}


void foo2(int* x, int* y){
 int c = 10;
 int i = 0;
	for(i = *y; i < c; i++){
	 x[i] = i;
	}

 *y = c;
}



void foo3(int * x, int * y, int z){
 int c = 15;
	while(*y < c){
	 *(x+*y) = *y;
	 (*y)++;
	}
 z = c;

}


int main(){
 int size = 20;
 int a[size];

 int b = foo1(a);
 printf("%d %d %d\n", a[2],a[8], a[12]);
 printf("%d %d\n", b ,size);

 foo2(a,&b);
 printf("%d %d %d\n", a[2],a[8], a[12]);
 printf("%d %d\n", b ,size);


 foo3(a,&b, size);
 printf("%d %d %d\n", a[2],a[8], a[12]);
 printf("%d %d\n", b ,size);



}
