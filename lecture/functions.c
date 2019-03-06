#include <stdio.h> 

//prototpes 
int foo(int x, int y);

void bar(int* a){
printf("%d\n", a[0]);
}

int main () {
 int xx = 3;
 int yy =4;
 int z = foo(xx, yy);
 //arr is a pointer
 int arr[5};
arr[0] = 3;
bar(arr);
}
