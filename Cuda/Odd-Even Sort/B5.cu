
#include<stdio.h>
#include<cuda.h>
#include<time.h>
#include<stdlib.h>

__global__ void even(int *a,int n)

{
int k=blockIdx.x*512+threadIdx.x;
k=2*k;
if(k < n-1)
{
if(a[k] > a[k+1])
{
int t=a[k];
a[k]=a[k+1];
a[k+1]=t;

}
}
}

__global__ void odd(int *a,int n)
{
int k=blockIdx.x*512+threadIdx.x;
k=2*k+1;
if(k < n-1)
{
if(a[k] > a[k+1])
{
int t=a[k];
a[k]=a[k+1];
a[k+1]=t;

}
}
}
void odd_even_sort(int *a, const int n)
{

int *ad;
cudaMalloc((void **)&ad,n*sizeof(int));
cudaMemcpy(ad,a,n*sizeof(int),cudaMemcpyHostToDevice);
for(int i=0;i < n/2;i++)
{
even<<<n/1024+1,512>>>(ad,n);
odd<<<n/1024+1,512>>>(ad,n);
}
cudaMemcpy(a,ad,n*sizeof(int),cudaMemcpyDeviceToHost);
return;
}

int main()
{
int n = 20;
int a[n];
time_t t;
srand((unsigned)time(&t));


int x,flag;
for (unsigned i = 0 ; i < n ; i++)
{
x=rand()%n;
flag=0;
for(int j=0;j < i;j++)
{
if(a[j]==x)
{
i--;
flag=1;
break;
}

}
if(flag==0)
a[i]=x;
}
printf("\n\n original array\n");
for(int i=0;i < n;i++)
printf("%d\t ",a[i]);
printf("\n\n");
odd_even_sort(a,n);
printf("\n\n after sorting\n");
for(int i=0;i < n;i++)
printf("%d\t ",a[i]);


}
