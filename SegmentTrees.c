#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int  buildSegTree(int *arr,int *tree,int start,int end,int pos)
{
	if(start==end)
	{
		tree[pos]=arr[start];
		return tree[pos];
	}
	else
	{
		int mid=(start+end)/2;
		tree[pos]=buildSegTree(arr,tree,start,mid,2*pos+1) + buildSegTree(arr,tree,mid+1,end,2*pos+2);
		return tree[pos];
	}
}

int updateValue(int *tree,int *arr,int start,int end,int index,int valueToAdd,int pos)
{
	if(index<start || index>end)
	{
		printf("Invalid index\n");
		return;
	}
	if(start==end && start==index)
	{
		tree[pos] += valueToAdd;
		arr[index] = tree[pos];
	}
	else
	{
		int mid=(start+end)/2;
		if(index<=mid) //go to only left
			updateValue(tree,arr,start,mid,index,valueToAdd,2*pos+1);
		else          //go to right
			updateValue(tree,arr,mid+1,end,index,valueToAdd,2*pos+2);
		tree[pos] += valueToAdd;
	}
}

int findSum(int *tree,int from,int to,int start,int end,int pos)
{
	if( (start==from) && (end==to) )
		return tree[pos];
	else
	{
		int mid=(start+end)/2;
		
		if( to<=mid ) //somewhere in left
			return findSum(tree,from,to,start,mid,2*pos+1);
		else if( from>mid ) //somewhere in right
			return findSum(tree,from,to,mid+1,end,2*pos+2);
		else if( from>=start && to<=end ) //somehere in middle
		{
			return ( findSum(tree,from,mid,start,mid,2*pos+1) + findSum(tree,mid+1,to,mid+1,end,2*pos+2) );
		}	
		
	}
}
int main()
{
	int i,n,nodes,update,index,op,choice,from,to;
	int *arr=NULL;
	int *tree=NULL;
	printf("Enter the no. of elements:: ");
	scanf("%d",&n);
	
	int height = (int)ceil(log(2*n)/log(2));
	printf("height --> %d\n", height);
	nodes=pow(2, height);
	printf("number of nodes --> %d\n",nodes);
	
	
	arr=(int *)calloc(n,sizeof(int));
	tree=(int *)calloc(nodes,sizeof(int));
	
	printf("Enter the elements\n");
	for(i=0;i<n;i++)
		scanf("%d",arr+i);
		
	buildSegTree(arr,tree,0,n-1,0);
	
	for(i=0;i<nodes;i++)
		printf("%d ",tree[i]);
	printf("\n");
	
	printf("If you want to perform any operation then press 1:: ");
	scanf("%d",&op);	
	
	while(op==1)
	{
		printf("Enter 1 for update the value\n");
		printf("Enter 2 for any query\n");
		printf("Enter 3 for exit\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				printf("Enter the index:: ");
				scanf("%d",&index);
				printf("Enter the value with which you want to update it:: ");
				scanf("%d",&update);
				updateValue(tree,arr,0,n-1,index,update,0);
				break;
			case 2:
				printf("Enter range for which you want to find sum seperated by space:: ");
				scanf("%d %d",&from,&to);
				printf("%d\n",findSum(tree,from,to,0,n-1,0));
				break;				
			case 3:
				exit(0);
				
			
		}	
		printf("If you want to perform any operation then press 1:: ");
		scanf("%d",&op);
		printf("\n");
	}
	
	return 0;
}
