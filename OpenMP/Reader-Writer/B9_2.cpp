#include<iostream>
#include<omp.h>
#include<cstdlib>
#include<unistd.h>
using namespace std;
omp_lock_t readerlock;
omp_lock_t writerlock;
omp_lock_t Z;
omp_lock_t G;
omp_lock_t H;
int buffer=-1;
int reader_count=0;
int writer_count=0;

int main()
{
int z;
int n,m;
omp_init_lock(&writerlock);
omp_init_lock(&readerlock);
omp_init_lock(&Z);
omp_init_lock(&G);
omp_init_lock(&H);
Reader_priority X;
Writer_priority Y;
cout<<"1. Reader Priority 2. Writer priority\n"; //Algorithm reference from OS by W.Stallings
cin>>z;

if(z==1) //Readers having priority
{
cout<<"Enter the number of threads for Execution: ";
cin>>n;
omp_set_num_threads(n);
cin>>m;
#pragma omp parallel shared(buffer,reader_count)
{
	int k=omp_get_thread_num();
	#pragma omp barrier //All threads after spawning wait till all threads arrive at this point
	int a=rand() % 5;
	if(a%2==1)
	{
	omp_set_lock(&G);
	cout<<"\n"<<"Incrementing the Reader count by Thread: "<<k;
   	reader_count++;
	if(reader_count==1)
		{
		cout<<"\n"<<"I m first reader.. setting writer Lock by Thread: "<<k;
		omp_set_lock(&writerlock);
	}
	omp_unset_lock(&G);
	cout<<"\n"<<"Reading..";
	cout<<"\n"<<buffer<<" Read by Thread: "<<k<<"\n";
	omp_set_lock(&G);
	cout<<"\n"<<"Decrememting the Reader count by Thread: "<<k;
   reader_count--;
	if(reader_count==0)
	{
		cout<<"\n"<<"I was last reader.. unsetting the lock by Thread: "<<k;
		omp_unset_lock(&writerlock);
	}
	omp_unset_lock(&G);
}
	else
	{ 
	omp_set_lock(&writerlock);
	cout<<"\n"<<"I am a writer thread with thread number: "<<k;
	buffer=k;
	cout<<"\n"<<"Writing Job Done with thread number: "<<k;
	omp_unset_lock(&writerlock);
	}	
}

}

if(z==2) //Writers having Priority
{
cout<<"Enter the number of threads for Execution: ";
cin>>n;
omp_set_num_threads(n);
#pragma omp parallel shared(buffer,reader_count,writer_count)
{
	int k=omp_get_thread_num();
	#pragma omp barrier
	int a=rand() % 5;
	if(a%2==0)
	{
	omp_set_lock(&H);
	cout<<"\n"<<"Incrementing the Writer count by Thread: "<<k;
   	writer_count++;
	if(writer_count==1)
	{
		cout<<"\n"<<"I m the first writer.. Locking readers by Thread: "<<k;
		omp_set_lock(&readerlock);
	}
	omp_unset_lock(&H);
	omp_set_lock(&writerlock);
	cout<<"\n"<<"Writing something by Thread: "<<k;
	buffer=k;
	omp_unset_lock(&writerlock);
  	omp_set_lock(&H);
	cout<<"\n"<<"Decrementing the Writer count by Thread: "<<k;
   	writer_count--;
	if(writer_count==0)
	{
		cout<<"\n"<<"I m the last writer.. unsetting reader lock by Thread: "<<k;
		omp_unset_lock(&readerlock);
	}
	omp_unset_lock(&H);
	}
	else
	{ 
	omp_set_lock(&Z);
	omp_set_lock(&readerlock);
	omp_set_lock(&G);
	cout<<"\n"<<"Incrementing the Reader count by Thread: "<<k;
	reader_count++;
	if(reader_count==1)
	{
		cout<<"\n"<<"I m the first reader.. setting writer lock by Thread: "<<k;
		omp_set_lock(&writerlock);
	}
	omp_unset_lock(&G);
	omp_unset_lock(&readerlock);
	omp_unset_lock(&Z);
	cout<<"\n"<<"Reading by Thread: "<<k;
	cout<<"\n"<<buffer<<" Read by Thread: "<<k<<"\n";
	omp_set_lock(&G);
	cout<<"\n"<<"Decrementing the Writer count by Thread: "<<k;
	reader_count--;
	if(reader_count==0)
	{
		cout<<"\n"<<"I m the last reader.. unsetting writer lock by Thread: "<<k;
		omp_unset_lock(&writerlock);
	}
	omp_unset_lock(&G);
	}	
}
}

omp_destroy_lock(&writerlock);
omp_destroy_lock(&readerlock);
omp_destroy_lock(&Z);
omp_destroy_lock(&G);
return 0;
}
