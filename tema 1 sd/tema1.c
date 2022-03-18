#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct node //Lista dublu inlantuita
{
	 int timestamp;
	double data;
	struct node *prev;
	struct node *next;
} *Node;


void free_list (Node head) //eliberare memorie lista
{
	Node tmp;
    while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }
free(head);
}
Node init_node() //initializare nod
{
	Node n=malloc(sizeof(struct node));
	n->data=0;
	n->timestamp=0;
	n->prev=NULL;
	n->next=NULL;
	
	return n;
}

double average(Node head) //not pretty but it works ¯\_(ツ)_/¯
{
	double sum=0;
	sum=head->data
	+head->prev->data+head->prev->prev->data
	+head->next->data+head->next->next->data;
	return (sum/5);
}

double deviation (Node head, double average) //standard deviation
{
	int i;
	double stnd_dev=0;
	Node temp=head;
	temp=temp->prev->prev;
	for (i = 0; i < 5; i++)
	{
		stnd_dev=stnd_dev+pow(temp->data-average,2);
		temp=temp->next;
	}
	return stnd_dev=sqrt(stnd_dev/5);
}

Node copy_list(Node head,int nr_date) //copiere lista
{
	Node cursor=head;
	Node new;
	Node backup_new;
	new=init_node();
	backup_new=new;
	int i;
	for (i = 0; i < nr_date; i++)
	{
		new->data=cursor->data;
		new->timestamp=cursor->timestamp;
		if (i<nr_date-1)
		{
			new->next=init_node();
			new->next->prev=new;
		}
		cursor=cursor->next;
		new=new->next;
	}
	new=NULL;
	cursor=NULL;
	free_list(cursor);
	free_list(new);
	return backup_new;
}

void e1 (Node head, int* nr_date) //ex 1
{
	int nr_backup;
	int i;
	double avg;
	double dev;
	Node tmp;
	Node copy;
	copy=copy_list(head, *(nr_date));
	Node copy_backup=copy;
	head=head->next->next;
	copy=copy->next->next;
	nr_backup=*nr_date;
	for (i = 0; i < nr_backup-4; i++)
	{
		avg=average(copy);
		dev=deviation(copy, avg);
		if (copy->data <= (avg - dev) || copy->data >= (avg + dev))
		{	tmp=head;
			head->prev->next=head->next;
			head->next->prev=head->prev;
			free(tmp);
			*nr_date=*nr_date-1;
		}
		head=head->next;
		copy=copy->next;
	}
	free_list(copy_backup);
}

double middle(Node head) //returneaza elementul mijolciu, sortat
{
	int i, j;
	double v[5];
	double aux;
	v[0]=head->prev->prev->data;
	v[1]=head->prev->data;
	v[2]=head->data;
	v[3]=head->next->data;
	v[4]=head->next->next->data;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j <4-i; j++)
		{
			if (v[j]>v[j+1])
			{
				aux=v[j];
				v[j]=v[j+1];
				v[j+1]=aux;
			}
		}
	}
	return v[2];
}
void e2 (Node head, int *nr_date) // exercitiul 2
{
	Node head_backup=head;
	Node copy;
	copy=copy_list(head, *nr_date);
	Node copy_backup=copy;
	copy=copy->next->next;
	*nr_date=*nr_date-4; //se scade dimensiune listei
	int i;
	for (i = 0; i < *nr_date; i++)
	{
		head->data=middle(copy);
		head->timestamp=copy->timestamp;
		head=head->next;
		copy=copy->next;
	}
	head->next=init_node();
	head->next->prev=head;
	free_list(copy_backup);
	head=head_backup;
}
void e3 (Node head,int *nr_date) //exercitiul 3
{
	Node copy;
	copy=copy_list(head, *nr_date);
	Node copy_backup=copy;
	copy=copy->next->next;
	*nr_date=*nr_date-4;
	int i;
	for (i = 0; i < *nr_date; i++)
	{
		head->data=average(copy);
		head->timestamp=copy->timestamp;
		head=head->next;
		copy=copy->next;
	}
	free_list(copy_backup);
}
 
void u (Node head, int *nr_date)
{	
	
	Node head_backup=head;
	double interval;
	head=head->next;
	while (head!=NULL)
	{
		interval=head->timestamp - head->prev->timestamp;
		if (interval <= 1000 && interval >=100)
		{
			head->data=(head->prev->data+head->data)/2;
			head->timestamp=(head->prev->timestamp+head->timestamp)/2;
		}
		head=head->next;
	}
	head=head_backup;
}

void st (Node head, int *nr_date, int number) //bonus
{
	double aux;
	Node head_backup;
	head_backup=head;
	int i, j, contor;
	int k=0;
	for (i = 0; i < *nr_date; i++) //sortare bubble
	{
		head=head_backup;
		for (j= 0; j < *nr_date-i-1; j++)
		{
			if (head->data > head->next->data)
			{
				aux=head->data;
				head->data=head->next->data;
				head->next->data=aux;
			}
			head=head->next;
		}
	}
	head=head_backup;
	for (i = -350; i < 350; i+=number) //exercitiul propriu-zis
	{	
		contor=0;
		if (head->next==NULL && k!=1)
		{
			head->next=init_node();
			head->next->prev=head;
			k=1;
		}
		while(head->data<=i+number && head->next!=NULL)
		{
			++contor;
			head=head->next;
		}
		if (contor!=0)
		{
			printf("[%d, %d] %d\n",i, i+number, contor);
		}
	}
	head=head->next;
}

double w(double i, double k) //functia w
{
	double omega;
	double numitor=0;
	int j;
	omega=((i/(k-1))*(i/(k-1))*0.9+0.1);
	for (j = 0; j <= k-1; j++)
	{
		numitor=numitor+((j/(k-1))*(j/(k-1))*0.9+0.1);
	}
	omega=omega/numitor;
	return omega;
}

double C (double timestamp, double timestampright, double timestampleft)
{
	double C1;
	C1=((timestamp-timestampleft)/(timestampright-timestampleft));
	return C1;	
} 

void c (Node head, int *nr_date) // 1.4
{
	double sumleft=0;
	double sumright=0;
	int lefttimestamp;
	int righttimestamp;
	int nr;
	int diferenta;
	int i;
	int j;
	nr=*nr_date;
	const int k=3;
	Node left;
	Node right;
	Node new;
	double C_1;
	int l;
	head=head->next->next->next;
	for (i = 0; i < nr-5; i++)
	{
		diferenta=head->timestamp-head->prev->timestamp;
		if (diferenta>=1000)
		{
			left=head->prev;
			right=head;
			sumleft=0;
			sumright=0;
			lefttimestamp=left->timestamp;
			righttimestamp=right->timestamp;
			for (l = 2; l >= 0; l--)
			{
				sumleft+=(left->data)*w(l, k);
				sumright+=(right->data)*w(l, k);
				left=left->prev;
				right=right->next;
			}
			for (j = lefttimestamp+200; j < righttimestamp; j+=200)
			{
				C_1=C(j, righttimestamp, lefttimestamp);
				new=init_node();
				new->data=(1-C_1)*sumleft+C_1*sumright;
				new->timestamp=j;
				new->next=head;
				new->prev=head->prev;
				new->prev->next=new;
				head->prev=new;
				*nr_date=*nr_date+1;
			}
		}
		head=head->next;
	}
}

int main(int argc, char *argv[])
{
	int nr_date;
	int timestamp;
	double data;
	int i, number;
	scanf("%d",&nr_date);
	char * ptr;
	int sta=0;
	Node head = init_node();
	Node cursor=head;
	for (i = 0; i < nr_date; i++) //citire lista
	{
		scanf("%d", &timestamp);
		scanf("%lf", &data);
		cursor->data=data;
		cursor->timestamp=timestamp;
		if (i<nr_date-1)
		{		
			cursor->next=init_node();
			cursor->next->prev=cursor;
		}
		cursor=cursor->next;
	}
	cursor=head;
	for (i = 0; i < argc; i++)
	{
		if (strcmp(argv[i],"--e1")==0)
		{
			e1(head, &nr_date);
		}
		if (strcmp(argv[i],"--e2")==0)
		{
			e2(head, &nr_date);
		}
		if (strcmp(argv[i],"--e3")==0)
		{
			e3(head, &nr_date);
		}
		if (strcmp(argv[i],"--u")==0)
		{
			u(head, &nr_date);
		}
		if (strcmp(argv[i],"--c")==0)
		{
			c(head, &nr_date);
		}
		if (strncmp(argv[i],"--st", 4)==0)
		{
			ptr=strtok(argv[i],"--st");
			number=atoi(ptr);
			st(head, &nr_date, number);
			sta=1;//pentru bonus
		}
	}
	if (sta!=1) //output specific bonusului
	{
		printf("%d\n", nr_date);
		for (i = 0; i < nr_date; i++)
		{
			printf("%d %.2lf\n",cursor->timestamp, cursor->data);
			cursor=cursor->next;
		}
	}
	free_list(head); //eliberare lista
}
