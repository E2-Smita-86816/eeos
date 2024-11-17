/**reate a thread to sort given array of "n" integers using bubble sort
. Main thread should print the result after sorting is completed.**/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>


#define SIZE 5
#define SWAP(a,b){ int temp=a;a=b;b=temp;}

void * bubblesort(void *param){
	int *arr=(int *)param;
	for(int i=0;i<SIZE;i++){
		for(int j=0;j<SIZE;j++){
			if(arr[i]<arr[j]){
				SWAP(arr[i],arr[j]);
			}
		}
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
	ret=pthread_create(&t,NULL,bubblesort,arr);
	if(ret!=0){
	perror("fail");
	}
	pthread_join(t,NULL);
	printf("sorted array:\n");
	for(int i=0;i<SIZE;i++){
         printf("%d ",arr[i]);
    }
	printf("\n");

	return 0;
}
		
