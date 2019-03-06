include <stdio.h>

int main(){
 unsigned short x = 50;
 printf("%d/n", (x >>1)); 

/*brings in 0's
 *start 010 (2)
 *shift<< 001 division by half
 *shift<< 000
 *
 *OR 
 *
 *unsigned (-4)
 * start 100
 * shift 0>> 010 XX = +2 noooo 
 * shift 1>> 110 is -2 or division by half
 * **/

}
