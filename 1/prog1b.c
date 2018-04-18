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

#define NUM_THREADS  4

pthread_mutex_t mutexsum;
pthread_mutex_t mutextries;

long long int count = 0;
int maxcount = 100;
long long int randnum = 1;
int powerof = 10;
long long int modoper = 34;
long long int numtries = 0;
long long int totnumtries = 0;

void *Domath (void *threadid) {
   maxcount = 100;
   powerof = 10;
   modoper = 34;
   modoper = ldexp(1,modoper);	
   randnum = ldexp(1,powerof);
	
   while (count < maxcount) {
      numtries ++;
      if ((rand() * randnum) % modoper == 0){ 
         pthread_mutex_lock(&mutexsum);
         count ++; 
         totnumtries = totnumtries + numtries;
         printf("%lli \t %lli \t %lli \t %lli \t %lli \n",
            randnum,modoper,(randnum/modoper),numtries,count);
         numtries = 0;
         pthread_mutex_unlock(&mutexsum);
      }
   }

   pthread_exit(NULL);
} // End Domath 


int main () {

   long i;
   void *status;

   pthread_mutex_init(&mutexsum,NULL);
   pthread_mutex_init(&mutextries,NULL);

   pthread_t threads[NUM_THREADS];
   int rc;
   long t;
   for(t=0;t<NUM_THREADS;t++) {
      printf("In main: creating thread %ld\n",t);
      rc = pthread_create(&threads[t],NULL,Domath,(void *)t);
      if (rc){
         printf("ERROR; return code from pthread_create() is %d\n",rc);
         exit(-1); 
      }
   }

   for(i=0; i<NUM_THREADS; i++) {
      pthread_join(threads[i], &status);
   }

   printf("Total number of tries %lli \n",totnumtries);
   system("ps aux");

   printf("process id %d \n",getpid());


   pthread_mutex_destroy(&mutexsum);
   pthread_mutex_destroy(&mutextries);
   pthread_exit(NULL);
}


