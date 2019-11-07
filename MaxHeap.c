#include<stdio.h>
#include<conio.h>

void buildHeap(int *arr,int heapSize);
void maxHeapify(int *arr,int i,int heapSize);


int main()
{
	int arr[100]={};
	int heapSize;
	int op;
	int choice;
	printf("Do you want to perform any operation then press 1:: ");
	scanf("%d",&op);
	while( op == 1 )
	{
		printf("Press 1 for build heap\n");
		printf("Press 2 for insertion in heap\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				printf("Enter no of elements in heap:: ");
				scanf("%d",&heapSize);
				if(heapSize)
					buildHeap(arr,heapSize);
				else
					printf("You have no elements in heap\n");
				break;
			
		}
		printf("Do you want to perform more operation then press 1:: ");
		scanf("%d",&op);
	}
}

void buildHeap(int *arr,int heapSize)
{
	int i;
	printf("Enter the elements you want to insert\n");
	for(i=1;i<=heapSize;i++)
	{
		scanf("%d",&arr[i]);
	}
	
	for(i=heapSize/2;i>=1;i--)
		maxHeapify(arr,i,heapSize);
		
	for(i=1;i<=heapSize;i++)
	{
		printf("%d ",arr[i]);
	}
}

void maxHeapify(int *arr,int i,int heapSize)
{
	int temp;
	int leftChild = i<<1; //one left shift for i=2 leftChild = 4
	int rightChild = (i<<1) + 1; //one left shift + 1 rightChild = 5
	printf("leftChild is %d righChild is %d\n",leftChild,rightChild);
	int largest;
	if(leftChild<=heapSize && arr[i]<arr[leftChild])
		largest=leftChild;
	else 
		largest=i;
	if(rightChild<=heapSize && arr[largest]<arr[rightChild])
		largest=rightChild;
	if(largest!=i)
	{
		temp=arr[i];
		arr[i]=arr[largest];
		arr[largest]=temp;
		maxHeapify(arr,largest,heapSize);
	}
	
}
