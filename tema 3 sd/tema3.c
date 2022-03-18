// Rosca Nicolae 312CC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
	char *name;
	int id;
	struct node *prev;
	struct node *next;
} * Node;

typedef struct a_node
{
	int dest;
	struct a_node *next;
} * A_node;

typedef struct l_adiacenta
{
	A_node head;
} * L_adiac;

typedef struct graph
{
	int k;
	L_adiac array;
} * Graph;

A_node init_a_node(int dest)
{
	A_node new = malloc(sizeof(struct a_node));
	new->dest = dest;
	new->next = NULL;
	return new;
}

Graph creat_graph(int k)
{
	Graph g = malloc(sizeof(struct graph));
	g->k = k;
	g->array = malloc(k * sizeof(struct l_adiacenta));
	int i;
	for (i = 0; i < k; i++)
	{
		g->array[i].head = NULL;
	}
	return g;
}

void add_edge(Graph g, int src, int dest)
{
	A_node n = init_a_node(dest);
	n->next = g->array[dest].head;
	g->array[dest].head = n;
	n->next = g->array[dest].head;
	g->array[dest].head = n;
}

void printGraph(Graph g)
{
	int v;
	for (v = 0; v < g->k; ++v)
	{

		A_node pCrawl = g->array[v].head;
		printf("\n Adjacency list of vertex %d\n head ", v);
		while (pCrawl)
		{
			printf("-> %d", pCrawl->dest);
			pCrawl = pCrawl->next;
		}
		printf("\n");
	}
}

Node init_node() // initializare nod
{
	Node n = malloc(sizeof(struct node));
	n->prev = NULL;
	n->next = NULL;
	n->name = NULL;
	int id = 0;
	return n;
}

void free_list(Node head) // eliberare memorie lista
{
	Node cursor;
	Node prev;
	cursor = head;
	while (cursor != NULL)
	{
		prev = cursor;
		cursor = cursor->next;
		free(prev->name);
		free(prev);
	}
}

int search_if_duplicate(Node head, char *nume)
{
	Node cursor;
	cursor = head;
	int k = 0;
	while (cursor->next != NULL)
	{
		if (strcmp(cursor->name, nume) == 0)
		{
			printf("%s\n", cursor->name);
			return 0;
		}
		cursor = cursor->next;
		k++;
	}
	return 1;
}

void cititerc1(Node head, int *k)
{
	FILE *input = fopen("test1.in", "r");
	int i;
	int j;
	*k = 0;
	int nr_filem;
	int nr_actori;
	int nr_actuali = 0;
	Node cursor;
	cursor = head;
	char buffer[69];
	fgets(buffer, 69, input);
	nr_filem = atoi(buffer);
	for (i = 0; i < nr_filem; i++)
	{
		fgets(buffer, 69, input);
		fgets(buffer, 69, input);
		nr_actori = atoi(buffer);
		for (j = 0; j < nr_actori; j++)
		{
			fgets(buffer, 69, input);
			if (i == 0)
			{
				cursor->name = malloc(sizeof(char) * (strlen(buffer) + 1));
				strcpy(cursor->name, buffer);
				cursor->next = init_node();
				cursor->next->prev = cursor;
				cursor->id = *k;
				cursor = cursor->next;
				*k = *k + 1;
			}
			else
			{
				if (search_if_duplicate(head, buffer) == 1)
				{
					cursor->name = malloc(sizeof(char) * (strlen(buffer) + 1));
					strcpy(cursor->name, buffer);
					cursor->next = init_node();
					cursor->next->prev = cursor;
					cursor = cursor->next;
					*k = *k + 1;
					cursor->id = *k;
				}
			}
		}
	}
	fclose(input);
}

void crearegraf(Graph g, Node head, int k)
{
	int i;
	int j;
	int nr_filem;
	int nr_actori;
	FILE *input = fopen("test1.in", "r");
	char buffer[69];
	fgets(buffer, 69, input);
	nr_filem = atoi(buffer);
	printf("%d\n", nr_filem);
	fclose(input);
}

void c1()
{
	int k;
	Node head = init_node();
	Node cursor;
	cursor = head;
	cititerc1(head, &k);
	printf("%d\n", k);
	Graph g = creat_graph(k);
	crearegraf(g, head, k);
	free_list(head);
}

int main(int argc, char *argv[])
{
	c1();
	int V = 5;
	Graph g = creat_graph(V);
	add_edge(g, 0, 1);
	add_edge(g, 0, 4);
	add_edge(g, 1, 2);
	add_edge(g, 1, 3);
	add_edge(g, 1, 4);
	add_edge(g, 2, 3);
	add_edge(g, 3, 4);

	// print the adjacency list representation of the above graph
	printGraph(g);
}