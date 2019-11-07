#include<stdio.h>
typedef struct BHnode
{
	int key;
	struct BHnode *leftChild,*rightChild,*parent;
	int degree;
}node;

node *newNode();
node *insertionBHeap(node **BHeap,int data);
node * unionHeap(node *heap,node *toBeUnion);
node * mergeHeaps(node *heap,node *toBeUnion);
void printRootList(node *BHeap);
void Link(node *child,node *parent);
node * findMin(node *heap);
node * searchKey(node *heap,int key);
node *binarySearch(node *root,int key);
void decreaseKey(node *heap,int key,int val);
node *extractMin(node **Bheap);
node * reverseRootList(node *unionPoint);
void deleteKey(node **Bheap,int key);

int main()
{
	int key;
	int value;
	int data;
	int choice;
	int op;
	int choice2;
	int op2;
	node *search=NULL;
	node *BHeap=NULL;
	node *BHeap2=NULL;
	printf("Enter 1 to perform operation:: ");
	scanf("%d",&op);
	while(op==1)
	{
		printf("Enter 1 for insertion\n");
		printf("Enter 2 for print root list\n");
		printf("Enter 3 for finding min of heap\n");
		printf("Enter 4 to perform decrease key\n");
		printf("Enter 5 to search node\n");
		printf("Enter 6 to delete key\n");
		printf("Enter 7 to extract min key\n");
		printf("Enter 8 to create another heap\n");
		printf("Enter 9 to union between two heaps\n");
		printf("Enter 10 to print heap 2 root list\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				printf("Enter the key you want to insert:: ");
				scanf("%d",&data);
				BHeap=insertionBHeap(&BHeap,data);
				break;
			case 2:
				printRootList(BHeap);
				break;
			case 3:
				search=findMin(BHeap);
				printf("Minimum element of heap is %d\n",search->key);
				break;
			case 4:
				printf("Enter the key which you want to replace:: ");
				scanf("%d",&key);
				printf("Enter the value with which you want to replace:: ");
				scanf("%d",&value);
				decreaseKey(BHeap,key,value);
				printf("Decrease Operation Successfull\n");
				break;
			case 5:
				printf("Enter the key which you want to search:: ");
				scanf("%d",&data);
				search=searchKey(BHeap,data);
				if(search)
					printf("Key founded\n");
				else
					printf("Key not founded\n");
				break;
			case 6:
				printf("Enter the key you want to delete:: ");
				scanf("%d",&data);
				deleteKey(&BHeap,data);
				break;
			case 7:
				BHeap=extractMin(&BHeap);
				break;
			case 8:
				printf("Enter 1 to perform operation:: ");
				scanf("%d",&op2);
				while(op2==1)
				{
					printf("Enter 1 for insertion\n");
					printf("Enter 2 for print root list\n");
					printf("Enter 3 for finding min of heap\n");
					printf("Enter 4 to perform decrease key\n");
					printf("Enter 5 to search node\n");
					printf("Enter 6 to delete key\n");
					printf("Enter 7 to extract min key\n");
					printf("Enter the choice for heap 2\n");
					scanf("%d",&choice2);
					switch(choice2)
					{
						case 1:
							printf("Enter the key you want to insert:: ");
							scanf("%d",&data);
							BHeap2=insertionBHeap(&BHeap2,data);
							break;
						case 2:
							printRootList(BHeap2);
							break;
						case 3:
							search=findMin(BHeap2);
							printf("Minimum element of heap is %d\n",search->key);
							break;
						case 4:
							printf("Enter the key which you want to replace:: ");
							scanf("%d",&key);
							printf("Enter the value with which you want to replace:: ");
							scanf("%d",&value);
							decreaseKey(BHeap2,key,value);
							printf("Decrease Operation Successfull\n");
							break;
						case 5:
							printf("Enter the key which you want to search:: ");
							scanf("%d",&data);
							search=searchKey(BHeap2,data);
							if(search)
								printf("Key founded\n");
							else
								printf("Key not founded\n");
							break;
						case 6:
							printf("Enter the key you want to delete:: ");
							scanf("%d",&data);
							deleteKey(&BHeap,data);
							break;
						case 7:
							BHeap=extractMin(&BHeap2);
							break;
					}
					printf("Enter 1 if you want to perform more operation:: ");
					scanf("%d",&op2);
				}
				printf("Heap 2 is created\n");
				break;
				case 9:
					BHeap=unionHeap(BHeap,BHeap2);
					break;
				case 10:
					printRootList(BHeap2);
					break;
					
		}
		printf("Enter 1 if you want to perform more operation:: ");
		scanf("%d",&op);
	}
}
node *newNode()
{
	node *temp=(node *)malloc(sizeof(node));
	return temp;
}
node *insertionBHeap(node **BHeap,int data)
{
	node *heap = *BHeap;
	node *temp=(node*)malloc(sizeof(node));
	temp->degree=0;
	temp->key=data;
	temp->leftChild=temp->parent=temp->rightChild=NULL;
	if(*BHeap == NULL)
		return temp;
	else
		heap=unionHeap(heap,temp);
}
node *unionHeap(node *heap,node *toBeUnion)
{
	heap=mergeHeaps(heap,toBeUnion);
	node *prev=NULL;
	node *head=heap;
	node *next=heap->rightChild;
	while(next!=NULL)
	{
		node *sib=next->rightChild;
		if(head->degree!=next->degree)  //no same degre node carry on
		{
			prev=head;
			head=next;
		}
		else if(sib!=NULL && (next->degree == sib->degree))  //check if three consecutive nodes have same degree
		{
			head=next;
		}
		else //means two nodes have same degree
		{
			if(head->key<=next->key)
			{
				//remove next from root list
				head->rightChild = next->rightChild;
				Link(next,head);
			}
			else
			{
				if(prev!=NULL)
				{
					prev->rightChild=next;
					Link(head,next);
				}
				else
				{
					
					Link(head,next);
					heap=next;
				}
				head=next;
			}	
		}
		next=sib;
	}
	return heap;
}
node * mergeHeaps(node *heap,node *toBeUnion)
{
	node *start=NULL;
	node *last=NULL;
	while(heap!=NULL || toBeUnion!=NULL)
	{
		if(heap==NULL)
		{
			if(start==NULL)
				start=toBeUnion;
			if(last!=NULL)
				last->rightChild=toBeUnion;
			break;
		}
		if(toBeUnion==NULL)
		{
			if(start==NULL)
				start=heap;
			if(last!=NULL)
				last->rightChild=heap;
			break;
		}
		if(heap->degree<toBeUnion->degree)
        {
            if(start==NULL)
            {
                start=heap;
                last=heap;
            }
            else
            {
                last->rightChild=heap;
                last=heap;
            }
            heap=heap->rightChild;
        }
        else
        {
            if(start==NULL)
            {
                start=toBeUnion;
                last=toBeUnion;
            }
            else
            {
                last->rightChild=toBeUnion;
            	last=toBeUnion;
            }
            toBeUnion=toBeUnion->rightChild;
       	}
	}
	return start;
}
void Link(node *child,node *parent)
{
	child->parent=parent;
	child->rightChild=parent->leftChild;
	parent->leftChild=child;
	parent->degree=parent->degree + 1;
}
void printRootList(node *BHeap)
{
	while(BHeap!=NULL)
	{
		printf("%d ",BHeap->key);
		BHeap=BHeap->rightChild;
	}
	printf("\n");
	
}
node * findMin(node *heap)
{
	node *mini=NULL;
	int min=heap->key;
	mini=heap;
	while(heap!=NULL)
	{
		if(heap->key<min)
		{	
			min=heap->key;
			mini=heap;
		}
		heap=heap->rightChild;
	}
	return mini;
}
node *searchKey(node *heap,int key)
{
		node *find=binarySearch(heap,key);
		if(find)
			return find;
		else
			return ;
}
node *binarySearch(node *root,int key)
{
	node *find=NULL;
	if(root->key == key)
	{
		find=root;
	}
	if(root->leftChild && find==NULL)
		find=binarySearch(root->leftChild,key);
	if(root->rightChild && find==NULL)
		find=binarySearch(root->rightChild,key);
	return find;
}
void decreaseKey(node *heap,int key,int val)
{
	node *pos=searchKey(heap,key);
	node *child=pos->leftChild;
	node *parent=pos->parent;
	if(val>pos->key)
	{
		printf("You are inserting a wrong value\n");
		return;
	}
	pos->key=val;
	while(parent!=NULL && pos->key<parent->key)
	{
		pos->key=parent->key;
		parent->key=val;
		pos=pos->parent;
		parent=parent->parent;
	}
}
node *extractMin(node **Bheap)
{
	node *heap=*Bheap;
	node *find=findMin(heap);
	node *prev=NULL;
	node *next=NULL;
	node *temp=heap;
	while(temp!=find)
	{
		next=temp->rightChild;
		prev=temp;
		temp=temp->rightChild;
	}
	next=temp->rightChild;
	prev->rightChild=next;
	if(find->leftChild!=NULL)
	{
		node *newRoot=find->leftChild;
		node *unionPoint=newRoot;
		while(newRoot!=NULL)
		{
			newRoot->parent=NULL;
			newRoot=newRoot->rightChild;
		}
		free(find);
		unionPoint=reverseRootList(unionPoint);  //reversing of new list is required
		heap=unionHeap(heap,unionPoint);
	}
	else
	{
		free(find);
	}
	return heap;
}
node * reverseRootList(node *unionPoint)
{
	node *prev=NULL;
	node *cur=unionPoint;
	node *next=NULL;
	while(cur!=NULL)
	{
		next=cur->rightChild;
		cur->rightChild=prev;
		prev=cur;
		cur=next;
	}
	return prev;
}
void deleteKey(node **Bheap,int key)
{
	node *heap=*Bheap;
	decreaseKey(heap,key,-1000);
	*Bheap=extractMin(Bheap);
}
