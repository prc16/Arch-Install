//#include <math.h>
#include <stdio.h>

int checkPrimeNumber(int n);

void main() {
   int n, flag;
   printf("Enter a positive integer: ");
   scanf("%d", &n);

   // check prime number
   if (n % 2 == 0) {
         flag = 0;
         goto END;
    }

   flag = checkPrimeNumber(n);

   END:
   if (flag == 1)
      printf("%d is a prime number.\n", n);
   else
      printf("%d is not a prime number.\n", n);

}

// function to check prime number
int checkPrimeNumber(int n) {
   int i, flag = 1, squareRoot;

   // computing the square root
   //squareRoot = sqrt(n);
   for (i = 3; i < n; i+=2) {
      // condition for non-prime number
      if (n % i == 0) {
         flag = 0;
         break;
      }
   }
   return flag;
}
