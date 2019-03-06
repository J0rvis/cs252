#include <stdio.h>
#include <stdlib.h>
#include <omp.h>  /*compile with -fopenmp*/

void vecAdd(int* a, int* b, int* c, int n) {
  
  int i;
#pragma omp parallel for schedule(static, 5)
  for (i=0; i<n; i++) {
    c[i] = a[i] + b[i];
    printf(" schedule i = %d\n" , i);
  }

}

int dotProd(int* a, int* b, int n) {
  
  int result = 0;
  
  int i;
#pragma omp parallel for schedule(static, 5) reduction(+: result)
  for (i=0; i<n; i++) {

 /*   #pragma omp critical    I suggest not using cricital - it is slow*/
    result = result + (a[i] * b[i]);
    printf("parallel schedule static i = %d\n", i );
  }
  
  return result;
}

int main() {

  omp_set_num_threads(4);

  int n = 20;
  int a[n];
  int b[n];
  int c[n];
  
  int i;
  for (i=0; i<n; i++) {
    a[i] = i;
    b[i] = i;
  }
  
  /*
 *   vecAdd(a, b, c, n);
 *
 *     for (i=0; i<n; i++) {
 *         printf("%d\n", c[i]);
 *           }
 *             */

  int result = dotProd(a, b, n);
  printf("%d\n", result);


  /*
 * #pragma omp parallel
 *   {
 *           int i = omp_get_thread_num();
 *                   int n = omp_get_num_threads();
 *                          printf("hello %d of %d\n", i, n);
 *                            }
 *                              */


  /*
 * #pragma omp parallel 
 *   {
 *     int i;
 *
 *     #pragma omp for nowait
 *       for (i=0; i<20; i++) {
 *           int tn = omp_get_thread_num();
 *               printf("%d: %d\n", tn, i);
 *                 }
 *
 *                   }
 *                     */

  /*
 *   int i;
 *   #pragma omp parallel for schedule(static, 1)
  for (i=0; i<20; i++) {
    int tn = omp_get_thread_num();
    printf("%d: %d\n", tn, i);
  }

  */

  printf("done\n");
}
