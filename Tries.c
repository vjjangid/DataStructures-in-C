#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

struct trie{
	struct trie *(arr[26]);
};

struct trie *newNode()
{
	struct trie *temp=(struct trie*)calloc(1,sizeof(struct trie));
	return temp;
}

struct trie * build(struct trie *myTrie,char *str)
{
	if(str[0]!='\0')
	{
		int index = tolower(str[0]);
		index = index -97;
		if(myTrie==NULL)
			myTrie=newNode();
		(myTrie->arr)[index]=build((myTrie->arr)[index],str+1);
	}
	return (myTrie == NULL? newNode() : myTrie);
}

int findPrefix(struct trie *myTrie,char *prefix)
{

	int index=tolower(prefix[0]);
	index=index-97;
	if( (myTrie->arr)[index] )
	{
		if(prefix[1]=='\0')
			return 1;
		return (1 && findPrefix((myTrie->arr)[index],prefix+1));
	}
	else 
		return 0;			
	
	return 1;
}
int main()
{
	struct trie *myTrie=NULL;
	int op,choice;
	char str[20];
	char *temp;
	
	printf("Enter 1 if you want to perform any operation:: ");
	scanf("%d",&op);
	
	while(op==1)
	{
		printf("Enter 1 to build trie\n");
		printf("Enter 2 to find prefix\n");
		printf("Enter 3 to exit\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				printf("Enter the string :: ");
				scanf("%s",str);
				temp=str;
				while(temp[0]!='\0')
				{
					printf("%c ",temp[0]);
					myTrie=build(myTrie,temp);
					temp++;
				}
				break;			
			case 2:
				printf("Enter the prefix which you want find:: ");
				scanf("%s",str);
				if( findPrefix(myTrie,str) )
					printf("prefix found\n");
				else
					printf("prefix not present\n");
				break;
			case 3:
				exit(0);
		}
		printf("\nEnter 1 if you want to perform any operation:: ");
		scanf("%d",&op);	
	}
	return 0;
}
