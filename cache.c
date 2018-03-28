#include<stdio.h>

#include <stdint.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <unistd.h>
#include<time.h>
#include<string.h>


//#define ALLOC_SIZE (long)4096 * 1024
#define MULTIPLYING_FACTOR 20
//if doing on ccis machine make multiplying factor 5 , for MAC virutal machine m//ake multiplying factor 20.

#define BILLION 1000000000L

#define PAGESIZE 4096
#define NUMPAGES 256
#define jump PAGESIZE / 4
#define index 16*1024*1024
int a[index];
long step[20];
double result[20];
int size = 32 * 1024*1024;
//int[] linesize = {32,64,128,256};
double read_pages(long);
void plotGraph();
//int *a;
double calsize(int);
int main()
{
long min = 1024;


for(int i = 0; i < sizeof(a)/sizeof(int);i++)
{
  ++a[i] ;
}

for(int l = 0; l < 15 ; l++)
{
    step[l] = (long)min;
    min = min*2;
}

for(int j= 1 ; j < 15 ; j++)
{
  printf("Hello %ld \n" ,step[j]);
}

//  struct timeval stop, start;
  double cpu_time_used = 0.0;
  struct timespec start,end;
  //uint64_t diff;
  int i;

double threshold = 0.0;
int counter = 0;

double timediff = 0;
//int h = 4;
//int mul = 1;
for(int i = 0 ; i < 12; i++)
{
  timediff = 0;
  for(int j = 0 ; j < 10 ; j++)
  {
  timediff += read_pages(step[i]);
}
result[i] = timediff;
  printf("memory is: %ld KB elapsed time is = %lf seconds \n" , step[i]/1024, result[i]);

//h = h * 2;
}

/*for(int i= 0 ; i < 4 ;i++ )
{
  calsize(i);
}*/

plotGraph();
return 0;
}
void plotGraph(){
  /*
  FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
  char * commands = {""};
  fprintf(gnuplotPipe, "plot '-' \n");
  int i;

  for (i = 0; i < 12; i++)
  {
    fprintf(gnuplotPipe, "%ld %ld\n", result[i], step[i]);
  }

fprintf(gnuplotPipe, "e");
*/


char * commandsForGnuplot[] =
   {
        "set term png",
        "set output \"size.png\"",
        "set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 pi -1 ps 1.5",
        "set pointintervalbox 3",
        "set title \"X Axis: order of access time | Y Axis: order of array size",
        "plot 'size.dat' with linespoints ls 1"};

    FILE * temp = fopen("size.dat", "w");
    /*Opens an interface that one can use to send commands as if they were typing into the
     *     gnuplot command line.  "The -persistent" keeps the plot open even after your
     *     C program terminates.
     */
    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
    int i;
    for (i=0; i < 12; i++)
    {
    fprintf(temp, "%d,%0.3f\n",i, result[i]); //Write the data to a temporary file
    }

    for (i=0; i < 6; i++)
    {
    fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]); //Send commands to gnuplot one by one.
    }
    fflush(gnuplotPipe);
    return;
}
double read_pages(long i)
{
//  printf("index is %d",indx);
  struct timespec start,end;
  double avg_time = 0;
  //int jump = PAGESIZE/sizeof(int);
  double diff = 0;
  long k;
  /*
  for (int l = 0 ; l <1 ; l++)
  {
    for(int j = 0 ; j  < i; j+=64)
    {
      a[j] += 1;
    }
  }*/

clock_gettime(CLOCK_REALTIME,&start);

int jumper = i/sizeof(int) - 1;

for(k = 0 ; k < size; k++)
{
++a[(k * 64 ) & jumper];
//printf("elapsed time is = %llu nanoseconds \n" , (long long unsigned int) diff );
}
clock_gettime(CLOCK_REALTIME,&end);
diff = (end.tv_sec - start.tv_sec) * BILLION + (end.tv_nsec - start.tv_nsec);
  //avg_time = diff/indx;
  return diff/BILLION;
}
/*double calsize(int k)
{
  struct timespec start,end;
    a[0] = a[0] + 1;
  double linediff = 0;
  clock_gettime(CLOCK_MONOTONIC,&start);
for (int k = 0 ; k < 10000;k++)
{
  for(int i = 1; i < linesize[k] ;i++)
  {
    a[i] = a[i] + 1;
  }
}
clock_gettime(CLOCK_MONOTONIC,&end);
  linediff = (end.tv_sec - start.tv_sec) * BILLION + (end.tv_nsec - start.tv_nsec);

}*/
