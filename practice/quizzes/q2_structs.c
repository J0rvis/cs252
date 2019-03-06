#include <stdio.h>
#include <string.h>

struct pt {
 int x;
 int * y;
};

void foo1(int * p){
 int i =0;
	for(i = 0; i < 10; i++){
	 p[i] = i;
	}

}



void foo2(struct pt p){
 p.x =3;
 p.y[2] = 7;

}


void foo3(struct pt* p){
 p->x = 3;
 p->y[2] = 8;

}


int main(){
 int a[10];

 foo1(a);
 printf("%d \n", a[2]);


 struct pt b;

 b.x =5;
 b.y =a;
foo2(b);
 printf("%d\n", b.x);
 printf("%d\n",a[2]);

 foo3(&b);
 printf("%d\n", b.x);
 printf("%d\n",a[2]);

}
