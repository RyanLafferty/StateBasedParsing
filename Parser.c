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

	type = 0;
	ch = 1;
	name = NULL;
	data = NULL;
	state = 0;
	size = 0;
	error = 0;
	i = 0;
	f = NULL;

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
			/*get type*/
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
			/*get name*/
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
			/*get data*/
			/*add node*/
			/*free data*/
			state = 0;
			size = 0;
			for(i = 0; i < 1000; i++)
			{
				buffer[i] = 0;
			}
		}
		else
		{

		}
	}

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
