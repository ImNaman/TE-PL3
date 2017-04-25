#include <stdio.h>
#include <math.h>
#include <cuda.h>
#include<iostream>
using namespace std;

__global__ void mul(int *a, int n)
{
  __shared__ int s[4];
  int t = threadIdx.x;

  s[t] = a[2*t]*a[2*t+1];
  a[2*t]=s[t];
}

int main(void)
{
  const int n = 8;
  int a[n], d[n],ans;

  int no,x,y;
  cout <<"Enter your number" << endl;
  cin>>no;

  x=(no/10)*10;
  y=no%10;
  cout<<"x:"<<x<<" y:"<<y<<endl;
  a[0]=a[1]=a[2]=a[4]=x;
  a[3]=a[5]=a[6]=a[7]=y;

  int *d_d;
  cudaMalloc(&d_d, n * sizeof(int));
  cudaMemcpy(d_d, a, n*sizeof(int), cudaMemcpyHostToDevice);
  mul<<<1,n/2>>>(d_d, n/2);
  cudaMemcpy(d, d_d, n*sizeof(int), cudaMemcpyDeviceToHost);
  cudaFree(d_d);
  ans=d[0]+d[2]+d[4]+d[6];

  cout<<"The Square is:"<<ans;

 return 0;
}


