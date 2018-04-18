#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <signal.h>
#include <limits.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdbool.h>
#include <unistd.h>

register long long int count asm("r12");
int maxcount = 3;
register long long int randnum asm("r13");
int powerof = 1;
register long long int modoper asm("r14");
register long long int numtries asm("r15");
long long int totnumtries = 0;
	
int main () {
   maxcount = 100;
   modoper = 34;
   modoper = ldexp(1,modoper);
   powerof = 10;
   count = 0;

   while (count < maxcount) {
        	
      randnum = rand() * ldexp(1,powerof); 
      numtries ++;

      if (randnum % modoper == 0){ 
         printf("%lli \t %lli \t %lli \t %lli \n",
            randnum,modoper,(randnum/modoper),numtries);
         count ++; 
         totnumtries = totnumtries + numtries;
         numtries = 0;
      }
   }

   printf("Total number of tries %lli \n",totnumtries);
   system("ps aux");
   printf("process id %d \n",getpid());
}
