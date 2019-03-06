#include <stdio.h>

// prototypes -- like function interfaces
// int foo(int x, int y);
//
// void bar(int* a) {
//   printf("%d\n", a[0]);
//   }
//
//   void swap(int* x, int* y) {
//     int temp = *x;
//       *x = *y;
//         *y = temp;
//         }
//           
//
//           int main() {
           int xx = 3;
           int yy = 4;

           swap(&xx, &yy);
           printf("%d\n", xx);
           printf("%d\n", yy);

       //  int z = foo(xx, yy);

         //java: int[] arr = new int[5];
            int arr[5];

            arr[0] = 3;
        //  bar(arr);




       //  arr[1] = 4;
          *(arr+1) = 4;
        //*arr+1 = 4;  // bad

      //  printf("%d\n", arr[1]);

      //  printf("%d\n", *(arr+1));
      //  printf("%p\n", arr);
      //  printf("%p\n", &(arr[0]));
/*
          int x = 5;
          int y = 8;
//   &x  // get the address of x
          int* addX = &x;
          addX = addX - 1;
          printf("%p\n", &x);
          printf("%p\n", &y);
          printf("%p\n", addX);
          printf("%d\n", sizeof(addX)/
          int valueX = *addX;  // dereference
	  printf("%d\n", valueX);
	  */
  }


    int foo(int x, int y) {
    printf("%d\n", x);
                                                           
    return x + y;
}
