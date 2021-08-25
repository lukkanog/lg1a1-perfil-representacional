#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define quantidadeQuestoes 5
#define MASTER_USER "MASTER"

typedef struct
{
	int NroFrase;
	int Cinestesico;
	int Auditivo;
	int Visual;
	int Digital;
	char Frase[100];
	char Item1[100];
	char Item2[100];
	char Item3[100];
	char Item4[100];
}
Questao;

typedef struct
{
	int Cinestesico;
	int Auditivo;
	int Visual;
	int Digital;
}
Resultado;


int auth();
int validarEscolha(int escolha, int escolhasUtilizadas[]);
void adminMenu(char nome[], char prontuario[]);
void generateTestData();
void showQuestions();
void printHeader();
void about();
void generateResults(Resultado r, char nome[], char prontuario[]);
void runTest(char nome[], char prontuario[]);
void throwError(char *message);
