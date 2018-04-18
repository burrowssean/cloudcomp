#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <signal.h>
#include <limits.h>
#include <sys/types.h>
#include <stdbool.h>
#include <unistd.h>

FILE *inputFile;
FILE *outputFile;

int found = 0;
int *j, *k;
        
int main (void) {

   k = malloc(486000 * sizeof(int));
   j = malloc(486000 * sizeof(int));

   if ((inputFile = fopen("indata.dat","r")) == NULL) 
      printf("**** Input data file input.dat did not open \n");
   if ((outputFile = fopen("outdata3b.dat","w")) == NULL)
      printf("**** Output data file output.dat did not open \n");

   int i = 0, m = 0;
   char comma;
   while (i < 486000) {
      fscanf(inputFile,"%i %c %i",&k[i],&comma,&j[i]);
      fprintf(outputFile,"%i %c %i \n",k[i],comma,j[i]);
      i++;
      fseek(inputFile,1,SEEK_CUR);
   }


   fclose(inputFile);
   fclose(outputFile);

   system("ps aux");
   printf("process id %d \n",getpid());
}
