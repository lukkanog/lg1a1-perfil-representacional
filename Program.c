#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>
#include <strings.h>
#include <ctype.h>

const char* MASTER_USER = "MASTER";

FILE  *  fileHandler;


int main()
{
	int error;
	char nome[100], prontuario[9];
	
	do
	{
		fflush(stdin);
		
		printf("\nDIGITE O SEU NOME: ");
		fgets(nome, 100, stdin);
		nome[strcspn( nome, "\n" )] = '\0';

		
		fflush(stdin);
		printf("\nDIGITE O SEU PRONTUARIO: ");
		fgets(prontuario, 9, stdin);
		prontuario[strcspn( prontuario, "\n" )] = '\0';

		
		switch (auth(nome, prontuario))
		{
			case 1:
				printf("\nUSUARIO MASTER (ADMIN)");
				generateFile("RESULTADO", nome, prontuario);
				break;
			case 0:
				printf("\nUSUARIO COMUM");
				generateFile("RESULTADO", nome, prontuario);
				break;
			default:
				printf("\nERRO. TENTE NOVAMENTE!");
				error = 1;
				break;
		}
	} while (error);
	
}

int auth(char nome[], char prontuario[])
{	
	if (strcasecmp(nome, MASTER_USER) == 0)
		return 1;
				
	return 0;
}

void generateFile(char file[], char nome[], char prontuario[])
{	    
	char fileName[255] = "";

	strcat(fileName, file);
	strcat(fileName, "_");
	strcat(fileName, nome);
    strcat(fileName, "_");
    strcat(fileName, prontuario);
    strcat(fileName, ".txt");


    int i;
    for (i = 0; i < strlen(fileName); i++)
	{	
		if (fileName[i] == ' ')
		{
			fileName[i] = '_';
		} 
		
		fileName[i] = toupper(fileName[i]);
	}
	

	printf("\nNOME DO ARQUIVO: %s", fileName);
	
	fileHandler = fopen ( fileName,  "w"  );
	
//	fprintf (fileHandler, "====================================\n");
//	fprintf (fileHandler, "             %s              \n", nome);
//	fprintf (fileHandler, "====================================\n");


	fclose(fileHandler);
	
	system(fileName);
			
}

