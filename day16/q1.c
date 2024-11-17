/**Create a thread to sort given array of 10 integers using selection sort.
Main thread should print the result after sorting is completed.
Hint: Pass array to thread function (via arg4 of pthread_create()).**/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>


#define SIZE 5
#define SWAP(a,b){ int temp=a;a=b;b=temp;}

void * selectionsort(void *param){
	int *arr=(int *)param;
	for(int i=0;i<SIZE-1;i++){
		int min=i;
		for(int j=i+1;j<SIZE;j++){
			if(arr[j]<arr[min]){
				min=j;
			}
		}
		SWAP(arr[i],arr[min]);
	}
	/**for(int i=0;i<SIZE;i++){
		printf("%d\n",arr[i]);
	}**/
	return NULL;
}


int main(){
	pthread_t t;
	int ret;
	int arr[SIZE]={3,5,4,2,9};
	ret=pthread_create(&t,NULL,selectionsort,arr);
	if(ret!=0){
	perror("fail");
	return 1;
	}
	pthread_join(t,NULL);
	printf("sorted array:\n");
	for(int i=0;i<SIZE;i++){
         printf("%d ",arr[i]);
    }
	printf("\n");

	return 0;
}
		
