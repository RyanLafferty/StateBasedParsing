/*
Ryan Lafferty
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void parseFile(char * fileName);

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
	int state;
	int error;
	int size;
	int i;
	FILE * f;
	
	type = 0;
	ch = 1;
	state = -1;
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
			state++;
		}
		else if(ch == '=')
		{
			/*printf("State 1 active.\n");*/
			state = 3;
		}
		else
		{
			
		}
		
		switch (state) 
		{
			case 0:
			{
				break;	
			}
			case 1:
			{
				break;	
			}
			case 2:
			{
				break;	
			}
			case 3:
			{
				break;	
			}
			default:
			{
				break;		
			}
		}
	}
	
	printf("\n");
}