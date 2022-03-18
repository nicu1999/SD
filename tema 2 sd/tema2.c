//Rosca Nicolae 312CC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
	int id;
	int idparent;
	int nraddr;
	int nr_children;
	char **addr;
	struct node *parent;
	struct node **child;
} *Node;

typedef struct arbor
{
	struct node *server;
	struct arbor *next;
} *Arbor;

typedef struct treestrct
{
	struct node *root;
} *Treestrct;


Node init_node()
{
	Node current;
	current=(Node)malloc(sizeof(struct node));
	current->nraddr=0;
	current->nr_children=0;
	current->parent=NULL;
	return current;
}

void recursive_print(Node current, FILE *output)
{
	int i;
	fprintf(output, "%d", current->id);
	if (current->nr_children!=0)
	{
		for (i = 0; i < current->nr_children; i++)
		{
			fprintf(output," %d", current->child[i]->id);
		}
		fprintf(output, "\n");
		for (i = 0; i < current->nr_children; i++)
		{
			recursive_print(current->child[i], output);
		}
	}
	if (current->nr_children==0)
		fprintf(output, "\n");
}

void free_node(Node current)
{
	int i;
	if (current->nr_children!=0)
	{
		for (i = 0; i < current->nr_children; i++)
		{
			free(current->child[i]);
		}
		free(current->child);
	}
	if (current->nraddr!=0)
	{
		for (i = 0; i < current->nraddr; i++)
		{
			free(current->addr[i]);
		}
		free(current->addr);
	}
	free(current);
}

void recursive_free(Node current)
{
	int i;
	if (current->nr_children!=0)
	{
		for (i = 0; i < current->nr_children; i++)
		{
			recursive_free(current->child[i]);
		}
	}
	else
	{
		free_node(current);
	}
}

void free_tree(Arbor tree)
{
	recursive_free(tree->server);
}

void construction(Arbor tree, int *nr)
{
	Arbor tree_backup;
	Arbor tree_i;
	Arbor tree_j;
	Node current;
	int id;
	int idparent;
	int nraddr;
	int i;
	int j;
	int k;
	char buffer[10];
	FILE *input=fopen("tree.in","r");
	fscanf(input, "%d", nr);
	//tree=(Arbor)malloc(sizeof(struct arbor));
	tree_backup=tree;
	for (i = 0; i < *nr; i++)
	{
		current=init_node();
		fscanf(input, "%d", &id);
		current->id=id;
		fscanf(input, "%d ", &idparent);
		current->idparent=idparent;
		fscanf(input, "%d", &nraddr);
		current->nraddr=nraddr;
		current->addr=malloc(sizeof(char*)*nraddr);
		for (j = 0; j < nraddr; j++)
		{
			current->addr[j] = (char*)malloc((sizeof(buffer) + 1) * sizeof(char));
			fscanf(input, "%s", buffer);
			strcpy(current->addr[j], buffer);
		}
		tree->server=current;
		tree->next=(Arbor)malloc(sizeof(struct arbor));
		tree=tree->next;
	}
	fclose(input);
	FILE *output=fopen("tree.out","w");
	tree=tree_backup;
	tree_i=tree;
	tree_j=tree;
	for (i = 0; i < *nr; i++)
	{
		for (j = 0; j < *nr; j++)
		{
			if (tree_i->server->id==tree_j->server->idparent)
			{	
				tree_i->server->nr_children=tree_i->server->nr_children+1;
			}
			tree_j=tree_j->next;
		}
		tree_i->server->child=(struct node**)malloc(sizeof(struct node*)*(tree_i->server->nr_children));
		tree_j=tree;
		tree_i=tree_i->next;
	}
	tree_i=tree;
	tree_j=tree;
	for (i = 0; i < *nr; i++)
	{
		k=0;
		for (j = 0; j < *nr; j++)
		{
			if (tree_i->server->id==tree_j->server->idparent)
			{	
				tree_i->server->child[k]=malloc(sizeof(struct node*));
				tree_i->server->child[k]=tree_j->server;
				k++;
			}
			tree_j=tree_j->next;
		}
		tree_j=tree;
		tree_i=tree_i->next;
	}
	tree_i=tree;
	recursive_print(tree->server, output);
	fclose(output);
	tree=tree_backup;
}	

void recursive_print_addres(Node current, FILE *output)
{
	int i;

	for (i = 0; i < current->nr_children; i++)
	{
		recursive_print_addres(current->child[i], output);
	}
	if (current->nr_children==0)
	{
		for (i = 0; i < current->nraddr; i++)
		{
			fprintf(output," %s",current->addr[i] );
		}
	}	
}

void address_print(Node current, FILE *output)
{
	int i;
	fprintf(output, "%d", current->id);
	recursive_print_addres(current, output);
	fprintf(output,"\n");
	if (current->nr_children!=0)
	{
		for (i = 0; i < current->nr_children; i++)
		{
			address_print(current->child[i], output);
		}
	}
}

void add_addrs(Node current, Node child)
{
	int i;
	current->addr=realloc(current->addr,(current->nraddr+child->nraddr)*sizeof(char*));
	for (i = 0; i < child->nr_children; i++)
	{
		current->addr[current->nr_children+i+1]=strdup(child->addr[i]);
	}
}

void hierarchy(Node current)
{
	char buffer[10];
	int i;
	int j;
	int nr_addr_total;
		for (i = 0; i < current->nr_children; i++)
		{
			//printf("%d\n", current->nr_children);
			//printf("%s\n", "1");
			add_addrs(current, current->child[i]);
		}
		for (i = 0; i < current->nr_children; i++)
		{	//printf("%s\n", "2");
			hierarchy(current->child[i]);
		}

}

void initialization(Arbor tree)
{
	FILE *output=fopen("hierarchy.out","w");
	hierarchy(tree->server);
	address_print(tree->server, output);
	fclose(output);
	
}

int main()
{	
	Arbor tree=(Arbor)malloc(sizeof(struct arbor));
	int nr;
	construction(tree, &nr);
	initialization(tree);
	FILE *dummy2=fopen("queries.out","w");
	fclose(dummy2);
	free_tree(tree);
	return 0;
}