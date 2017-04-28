//Assignment No-B3

 #include "iostream"  
 using namespace std;  
 __global__ void sort(int *arr_d, int pivot, int len, int *arrl_d, int *arrh_d)  
 {  
   int id = threadIdx.x;  
   bool flag;  
   int element = arr_d[id+1];  
   if( element <= pivot )  
     flag = true;  
   else  
     flag = false;  
   __syncthreads();  
   if(flag)  
     arrl_d[id] = element;  
   else  
     arrh_d[id] = element;  
 }  
 void quicksort(int *arr, int len)  
 {  
   if(len == 1 || len == 0)  
     return;  
   int pivot = arr[0];  
   size_t size = len*sizeof(int);  
   int *arr_d, *arrl_d, *arrh_d, *arrl, *arrh;  
   arrl = new int[len];  
   arrh = new int[len];  
   for(int i=0; i<len; i++)  
   {  
     arrl[i] = -9999;  
     arrh[i] = -9999;  
   }  
   cudaMalloc((void **)&arr_d, size);  
   cudaMalloc((void **)&arrl_d, size);  
   cudaMalloc((void **)&arrh_d, size);  
   cudaMemcpy(arr_d, arr, size, cudaMemcpyHostToDevice);  
   cudaMemcpy(arrl_d, arrl, size, cudaMemcpyHostToDevice);  
   cudaMemcpy(arrh_d, arrh, size, cudaMemcpyHostToDevice);  
   sort<<<1, len-1>>>(arr_d, pivot, len, arrl_d, arrh_d);  
   cudaMemcpy(arrl, arrl_d, size, cudaMemcpyDeviceToHost);  
   cudaMemcpy(arrh, arrh_d, size, cudaMemcpyDeviceToHost);  
   int *temp1 = new int[len];  
   int *temp2 = new int[len];  
   for(int i=0; i<len; i++)  
   {  
     temp1[i]=temp2[i]=-9999;  
   }  
   int j=0, k=0;  
   for(int i=0; i<len; i++)  
   {  
     if(arrl[i]!=-9999)  
     {  
       temp1[j++] = arrl[i];  
     }  
     if(arrh[i]!=-9999)  
     {  
       temp2[k++] = arrh[i];  
     }  
   }  
   quicksort(temp1, j);  
   int p=0;  
   for(int i=0; i<j; i++)  
     arr[p++] = temp1[i];  
   arr[p++] = pivot;  
   quicksort(temp2, k);  
   for(int i=0; i<k; i++)  
     arr[p++] = temp2[i];  
   delete(arrl); delete(arrh); delete(temp1); delete(temp2);  
   cudaFree(arr_d); cudaFree(arrl_d); cudaFree(arrh_d);  
 }  
 int main()  
 {  
   int n;  
   cout<<"\nEnter no. of elements you want to sort: ";  
   cin>>n;  
   int arr[n];  
   cout<<"\n\nEnter no.s to be sorted: \n";  
   for (int i = 0 ; i < n ; i++)  
     cin>>arr[i];  
   quicksort(arr, n);  
   cout<<"\nSorted array is: \n";  
   for(int i=0;i<n;i++)  
       cout<<arr[i]<<"\t";  
   return 0;  
 }  

