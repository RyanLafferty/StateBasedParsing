/*
Ryan Lafferty
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct node
{
	char * name;
	char * data;
	char type;
	struct node * next;
}node;

void parseFile(char * fileName);
node * createNode(char * name, char * data, char type);
char getType(char buffer[1000], int size);
char * getName(char buffer[1000], int size);
char * getData(char buffer[1000], int size);
void displayNode(node * n);
int destroyNode(node * n);
int destroyDataStructure(node * nav);

int main(int argc, char *argv[])
{
	char * fileName;

	fileName = NULL;

	if(argc < 2)
	{
		printf("Error: Please enter a file name.\n");
		return 1;
	}
	if(argv[1] == NULL)
	{
		printf("Error: No file name given.\n");
		return 1;
	}

	fileName = argv[1];

	printf("File = %s\n", fileName);
	parseFile(fileName);


	return 0;
}

void parseFile(char * fileName)
{
	char type;
	char ch;
	char buffer[1000];
	char * name;
	char * data;
	int state;
	int error;
	int size;
	int i;
	FILE * f;
	node * head;
	node * nav;

	type = 0;
	ch = 1;
	name = NULL;
	data = NULL;
	state = 0;
	size = 0;
	error = 0;
	i = 0;
	f = NULL;
	head = NULL;
	nav = NULL;

	if(fileName == NULL)
	{
		printf("Error: No filename given.\n");
		return;
	}

	f = fopen(fileName, "r");
	if(f == NULL)
	{
		printf("Error: Could not open file.\n");
		return;
	}

	for(i = 0; i < 1000; i++)
	{
		buffer[i] = 0;
	}

	while(ch != EOF)
	{
		/*printf("%c", ch);*/
		ch = fgetc(f);

		if(isalpha(ch)||isnumber(ch))
		{
			/*printf("%c", ch);*/
			buffer[size] = ch;
			size++;
			if(state == 0)
			{
				state = 1;
			}
		}
		else if(ch == ' ' && state == 1)
		{
			/*printf("type = %s\n", buffer);*/
			type = getType(buffer, size);
			if(type == 0)
			{
				printf("Error: Invalid type.\n");
				return;
			}

			state = 2;
			size = 0;
			for(i = 0; i < 1000; i++)
			{
				buffer[i] = 0;
			}
		}
		else if(ch == '=')
		{
			/*printf("name = %s\n", buffer);*/
			if(type == 0)
			{
				printf("Error: Invalid type.\n");
				return;
			}
			name = getName(buffer, size);
			if(name == NULL)
			{
				printf("Error: Invalid Name.\n");
				return;
			}
			/*printf("name = %s\n", name);*/

			state = 3;
			size = 0;
			for(i = 0; i < 1000; i++)
			{
				buffer[i] = 0;
			}
		}
		else if(ch == ';')
		{
			/*printf("data = %s\n", buffer);*/
			if(name == NULL)
			{
				printf("Error: Invalid name.\n");
				return;
			}
			if(type == 0)
			{
				printf("Error: Invalid type.\n");
				return;
			}

			data = getData(buffer, size);
			if(data == NULL)
			{
				printf("Error: Invalid data.\n");
				free(name);
				return;
			}
			/*printf("data = %s\n", data);*/

			if(head == NULL)
			{
				head = createNode(name, data, type);
				if(head == NULL)
				{
					printf("Error: Could not create head.\n");
					return;
				}
				nav = head;
			}
			else
			{
				nav->next = createNode(name, data, type);
				if(nav->next == NULL)
				{
					printf("Error: Could not create node.\n");
					return;
				}
				nav = nav->next;
			}

			state = 0;
			size = 0;
			for(i = 0; i < 1000; i++)
			{
				buffer[i] = 0;
			}

			free(name);
			free(data);
			type = 0;
			name = NULL;
			data = NULL;
		}
		else
		{

		}
	}

	if(head == NULL)
	{
		return;
	}

	printf("Displaying data structure contents\n");
	printf("==================================\n");

	nav = head;
	while(nav->next != NULL)
	{
		displayNode(nav);
		nav = nav->next;
	}
	displayNode(nav);

	printf("Destroying DataStructure.\n");
	error = destroyDataStructure(head);
	printf("Destruction Errors = %d.\n", error);

	printf("\n");
}

node * createNode(char * name, char * data, char type)
{
	node * n;

	n = NULL;

	if(name == NULL)
	{
		printf("Error: No name given.\n");
		return NULL;
	}
	if(data == NULL)
	{
		printf("Error: No data given.\n");
		return NULL;
	}

	n = malloc(sizeof(node)*1);
	if(n == NULL)
	{
		printf("Error: Out of memory.\n");
		return NULL;
	}
	n->name = malloc(sizeof(char)*(strlen(name)+1));
	if(n->name == NULL)
	{
		printf("Error: Out of memory.\n");
		free(n);
		return NULL;
	}
	n->data = malloc(sizeof(char)*(strlen(data)+1));
	if(n->data == NULL)
	{
		printf("Error: Out of memory.\n");
		free(n->name);
		free(n);
		return NULL;
	}

	n->next = NULL;
	n->type = type;
	strncpy(n->name, name, (strlen(name)+1));
	strncpy(n->data, data, (strlen(data)+1));

	return n;
}

char getType(char buffer[1000], int size)
{
	int i;

	i = 0;

	if(buffer == NULL)
	{
		printf("Error: No buffer given.\n");
		return 0;
	}
	if(size < 3)
	{
		printf("Error: Invalid type.\n");
		return 0;
	}

	/*printf("%s\n", buffer);*/

	if(size == 3
	   && buffer[0] == 'i'
	   && buffer[1] == 'n'
	   && buffer[2] == 't')
	{
		/*printf("Type = int\n");*/
		return 1;
	}
	if(size == 4
	   && buffer[0] == 'c'
	   && buffer[1] == 'h'
	   && buffer[2] == 'a'
	   && buffer[3] == 'r')
	{
		/*printf("Type = char\n");*/
		return 2;
	}

	printf("Error: Invalid type given.\n");
	return 0;
}

char * getName(char buffer[1000], int size)
{
	char * name;
	int i;

	name = NULL;
	i = 0;

	if(size < 1 || buffer[0] == 0)
	{
		printf("Error: No name given.\n");
		return NULL;
	}

	name = malloc(sizeof(char)*(size + 1));
	if(name == NULL)
	{
		printf("Error: Out of memory.\n");
		return NULL;
	}

	for(i = 0; i < size; i++)
	{
		name[i] = buffer[i];
	}
	name[size] = '\0';

	return name;
}

char * getData(char buffer[1000], int size)
{
	char * data;
	int i;

	data = NULL;
	i = 0;

	if(size < 1 || buffer[0] == 0)
	{
		printf("Error: No data given.\n");
		return NULL;
	}

	data = malloc(sizeof(char)*(size + 1));
	if(data == NULL)
	{
		printf("Error: Out of memory.\n");
		return NULL;
	}

	for(i = 0; i < size; i++)
	{
		data[i] = buffer[i];
	}
	data[size] = '\0';

	return data;
}

void displayNode(node * n)
{
	if(n == NULL)
	{
		printf("Error: No node given.\n");
		return;
	}
	if(n->name == NULL || n->type == 0 || n->data == NULL)
	{
		printf("Error: Bad node given.\n");
		return;
	}

	printf("type = %d, name = %s, data = %s\n", n->type, n->name, n->data);
}

int destroyNode(node * n)
{
	if(n == NULL)
	{
		printf("Error: Cannot destroy an empty node.\n");
		return 0;
	}
	if(n->name != NULL)
	{
		free(n->name);
	}
	if(n->data != NULL)
	{
		free(n->data);
	}

	free(n);
	return 1;
}
int destroyDataStructure(node * nav)
{
	node * temp;
	int suc;
	int error;

	temp = NULL;
	suc = 0;
	error = 0;

	if(nav == NULL)
	{
		printf("Error: Cannot destroy an empty data structure.\n");
		return 0;
	}

	while(nav->next != NULL)
	{
		temp = nav;
		nav = nav->next;
		suc = destroyNode(temp);
		if(suc == 0)
		{
			error++;
		}
	}
	suc = destroyNode(nav);
	if(suc == 0)
	{
		error++;
	}

	return error;
}
