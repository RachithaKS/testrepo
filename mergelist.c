#include <stdio.h>
#include <stdlib.h>
#include<math.h>
struct node
{
	int key;
	struct node *next;
};

typedef struct node node_t;

struct list
{
	node_t *head;
};
typedef struct list list_t;

#define ALLOC(x) (x*)malloc(sizeof(x))

void disp_list(list_t mylist)
{	
	node_t* temp = mylist.head;
	while(temp)
	{
		printf("\n%d ", temp->key);
		temp = temp->next;
	}
	printf("\n");
}

void insert(list_t mylist, int key)
{
}
void make_list(list_t *ptr_mylist, int a[], int n)
{
	node_t *temp; node_t* tail = 0;
	int i;	
	for(i = 0; i < n; i++)
	{
		temp = ALLOC(node_t);
		temp->key = a[i];
		if(tail == 0)
		{
			ptr_mylist->head = tail = temp;
		}
		else
		{
			tail = tail->next = temp;
		}
	
		temp->next = 0;
	}
}
void init_list(list_t *ptr_mylist)
{
	ptr_mylist->head = 0;
}
void clean_list(list_t ptr_mylist)
{
	node_t* pres = ptr_mylist.head;
	node_t* temp;
	while(pres)
	{
		temp = pres;
		pres = pres->next;
		free(temp);
	}
}
node_t* merge_list(list_t* ptr_lista, list_t* ptr_listb)
{
	// assume that none of the lists is empty
	node_t* presa = ptr_lista->head; node_t* prev = 0;
	node_t* presb = ptr_listb->head; 
	ptr_listb->head = 0;
	if(presb->key <  presa->key)
	{
		ptr_lista->head = presb;
		prev = presb;
		presb = presb->next;
	}
	else
	{
		prev = presa;
		presa = presa->next;
	}
	while(presa && presb)
	{
		if(presa->key < presb->key)
		{
			prev->next = presa;
			prev = presa;
			presa = presa->next;
			
		}
		else
		{
			prev->next = presb;
			prev = presb;
			presb = presb->next;
		}
	}
	if(presa)
	{
		prev->next = presa;
	}
	else
	{
		prev->next = presb;
	}
	return ptr_lista->head;

}

void mergesort(list_t* mylist,int n)
{
	double size=log10(n)/log10(2);
	list_t* arr[((int)size)+1];
	int i;
	for(i=0;i<=(int)size;i++)
	{
		arr[i]=ALLOC(list_t);
		arr[i]->head=0;
	}			
	node_t* temp=mylist->head;
	list_t templist;
	while(temp!=0)
	{
		templist.head=temp;
		temp=temp->next;
		(templist.head)->next=0;
		int j=0;
		while(arr[j]->head)
		{
			j=j+1;
		}
		if(j==0)
			arr[0]->head=templist.head;
		else
		{
			arr[0]->head=merge_list(arr[0],
					&templist);
			for(i=1;i<j;i++)
			{
				arr[i]->head=merge_list(arr[i],
					arr[i-1]);
				arr[i-1]->head=0;
			}
			arr[j]->head=arr[j-1]->head;
			arr[j-1]->head=0;
		}
	}
	int j=0;
	while(j<(int)size )
	{
		if(arr[j]->head!=0)
			arr[(int)size]->head=merge_list(arr[j],arr[(int)size]);
		j=j+1;
	}
	mylist->head=arr[(int)size]->head;
}
void reverse_dijkstra(list_t* my_list)
{
	node_t* prev;
	node_t* pres;
	prev=my_list->head;
	pres=prev->next;
	node_t* head1=prev;
	prev->next=0;
	while(pres)
	{
		prev=pres;
		pres=pres->next;
		prev->next=head1;
		head1=prev;
		
	}
	my_list->head=head1;
}

int main()
{

 	int n = 11;
	int a[] = {44,34,1,2,3,4,90,6,7,456,1,67};
	list_t lista;
	init_list(&lista); 
	make_list(&lista, a, n); 
	mergesort(&lista,n);
	printf("after mergesort\n");
	disp_list(lista);
	reverse_dijkstra(&lista);
	printf("after reversing the list\n");
	disp_list(lista);
}
