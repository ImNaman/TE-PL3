#include <iostream>
#include <omp.h>
using namespace std;
class paper
{
public:
 int v,a[10][10],vis[10];
 paper()
 { v=0;
  for(int i=0;i<10;i++)
  { vis[i]=-1;
   //minbox[i]=0;
   for(int j=0;j<10;j++)
   {
    a[i][j]=99;
   }
  }
 }
 void create()
 {
  cout<<"enter number of houses : "<<endl;
  cin>>v;
  for(int i=0;i<v;i++)
    {
    for(int j=i+1;j<v;j++)
     { cout<<"enter distance from house "<<i<<" to "<<j<<" : ";
      cin>>a[i][j];
      if(a[i][j]==0) a[i][j]=99;
      a[j][i]=a[i][j];

     }
    }
 }

 void setvis(int d)
 {
  vis[d]=d;
  cout<<d<<" ";
 }
 int chkvis(int d)
  {
   if(vis[d]==d)return 1;
   else return 0;
  }

 void prims()
 {
  int min=99,total=0,k,l;
  for(int i=0;i<v;i++)
  {
   for(int j=0;j<v;j++)
   {
    if(a[i][j]<min)
    {
     min=a[i][j];
     k=i;
     l=j;
    }
   }
  }
  total=min;
  setvis(k);
  cout<<"--";
  setvis(l);
  cout<<" val:"<<a[k][l]<<endl;
  for(int m=0;m<v-2;m++)
  {
   min=99;
   int minbox[10],tid;
   for(int oo=0;oo<10;oo++)
    minbox[oo]=0;
   omp_set_num_threads(v);
   #pragma omp parallel private(minbox, tid)
   //for(int i=0;i<v;i++)
  {
	  tid=omp_get_thread_num();
    if(chkvis(tid)==1)
    {
     for(int j=0;j<v;j++)
     {
      if(chkvis(j)==0)
      {
       if(a[tid][j]<min)
       {
        min=a[tid][j];
        k=tid;
        l=j;
       }
      }
     }
    minbox[tid]=min;
    }
   }
  for(int ww=0;ww<v;ww++)
  {
   if(minbox[ww]<min && minbox[ww] != 0)
    min=minbox[ww];
  }
  setvis(k);
  cout<<"--";
  setvis(l);
  cout<<" val:"<<a[k][l]<<endl;
  total=total+min;
  }
  cout<<"total: "<<total;
 }

 void display()
 {
 for(int i=0;i<v;i++)
 {
  for(int j=0;j<v;j++)
  {
   cout<<a[i][j]<<" ";
  }
 cout<<endl;
 }

 }
};
int main() {
 paper p;
 p.create();
 p.display();
 p.prims();

 return 0;
}