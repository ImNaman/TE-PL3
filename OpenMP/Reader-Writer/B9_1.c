#include<stdio.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>

int main()
{
 int i=0,NumberofReaderThread=0,NumberofWriterThread;



omp_lock_t writelock;
omp_init_lock(&writelock);

int readCount=0;

 printf("\nEnter number of Readers thread(MAX 10)");
 scanf("%d",&NumberofReaderThread); 
 printf("\nEnter number of Writers thread(MAX 10)");
 scanf("%d",&NumberofWriterThread); 

int tid=0;
#pragma omp parallel
#pragma omp for

 for(i=0;i<NumberofReaderThread;i++)
 {
   // time_t rawtime;
  //struct tm * timeinfo;

//  time ( &rawtime );
  //timeinfo = localtime ( &rawtime );
  //printf ( "Current local time and date: %s", asctime (timeinfo) );
    //sleep(2); 
    
    printf("\nReader %d is trying to enter into the Database for reading the data",i);


    omp_set_lock(&writelock);
    readCount++;
    if(readCount==1)
    {

      printf("\nReader %d is reading the database",i); 
    }

    omp_unset_lock(&writelock);
    readCount--;
    if(readCount==0)
    {
      printf("\nReader %d is leaving the database",i);  
    }
 }

#pragma omp parallel shared(tid)// Specifies that one or more variables should be shared among all threads.
#pragma omp for nowait     //If there are multiple independent loops within a parallel region
 for(i=0;i<NumberofWriterThread;i++)
 { 


    printf("\nWriter %d is trying to enter into database for modifying the data",i);

    omp_set_lock(&writelock);

    printf("\nWriter %d is writting into the database",i); 
    printf("\nWriter %d is leaving the database",i); 

    omp_unset_lock(&writelock);
 }
 
   omp_destroy_lock(&writelock); 
 return 0;
}

//--->gcc -fopenmp d.c
//--->./a.out
