#include "Definitions.h"

int main()
{
	setlocale(LC_ALL, "Portuguese");
	
	int error;
	char nome[100], prontuario[9];
	char teste[255];
	
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
			case TRUE:
				adminMenu(nome, prontuario);
				break;
			case FALSE:
				runTest(nome, prontuario);
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
		return TRUE;
				
	return FALSE;
}

void adminMenu(char nome[], char prontuario[])
{
	char escolha;
	
	while (escolha != 'F')
	{
		system("cls");
		
		printf("\n====================================================");
		printf("\n        TESTE DOS SISTEMAS REPRESENTACIONAIS        ");
		printf("\n====================================================");
		printf("\n         1 - Cadastrar Questionário                 ");
		printf("\n         2 - Visualizar Questionário                ");
		printf("\n         3 - Realizar teste                         ");
		printf("\n         4 - Sobre o teste                          ");
		printf("\n         F - Fim                                    ");
		printf("\n====================================================");
		printf("\nEscolha => ");
		
		escolha = toupper(getche());
		
		switch (escolha)
		{
			case '1':
				generateTestData();
				break;
			case '2':
				showQuestions();
				break;
			case '3':
				runTest(nome, prontuario);
				break;
			case '4':
				about();
				break;
			case 'F':
				exit(0);
				break;
			default:
				throwError("Opção inválida");
				break;
		}
	}
}

void runTest(char nome[], char prontuario[])
{
	generateTestData();
	
	int escolha, i, cinestesico, auditivo, digital, visual;	
	
	cinestesico = auditivo = digital = visual = 0;
	
	FILE * reader;
		
	Questao q;
	Questao questions[quantidadeQuestoes];
	
	reader = fopen("TESTE_SISTEMA_REPRESENTACIONAL.DAT", "r");	

	if (ferror(reader))
	{
		printf ("\nErro ao ler registro de perguntas e gerar .txt");
		
		return;
	} 
	
	while (!feof(reader))
	{	
		fread(&q, sizeof(q), 1, reader);
		
		if (!feof(reader))
		{
			
		
			printHeader();
			
			printf("\n\n%i. %s\n", q.NroFrase, q.Frase);
			printf("\na)%s", q.Item1);
			printf("\nb)%s", q.Item2);
			printf("\nc)%s", q.Item3);
			printf("\nd)%s", q.Item4);
				
			int opcoesEscolhidas[4] = {0, 0, 0, 0};
		
			do
			{	
				printf("\n\nPeso da opção a => ");
				fflush(stdin);
				escolha = getch() - '0';
				
			} while (validarEscolha(escolha, opcoesEscolhidas) != TRUE);
			
			opcoesEscolhidas[0] = escolha;
			printf("%i", escolha);
			q.Cinestesico = escolha;
			
			
			do
			{	
				printf("\n\nPeso da opção b => ");
				fflush(stdin);
				escolha = getch() - '0';
				
			} while (validarEscolha(escolha, opcoesEscolhidas) != TRUE);
			
			q.Auditivo = escolha;
			
			printf("%i", escolha);
			opcoesEscolhidas[1] = escolha;
			
			do
			{	
				printf("\n\nPeso da opção c => ");
				fflush(stdin);
				escolha = getch() - '0';
				
			} while (validarEscolha(escolha, opcoesEscolhidas) != TRUE);
			
			
			opcoesEscolhidas[2] = escolha;
			printf("%i", escolha);
			q.Visual = escolha;
			
			do
			{	
				printf("\n\nPeso da opção d => ");
				fflush(stdin);
				escolha = getch() - '0';
				
			} while (validarEscolha(escolha, opcoesEscolhidas) != TRUE);
			
			opcoesEscolhidas[3] = escolha;
			printf("%i", escolha);
			q.Digital = escolha;
			
			
			cinestesico += q.Cinestesico;
			auditivo += q.Auditivo;
			visual += q.Visual;
			digital += q.Digital;
		}
	}
	
	fclose(reader);
	
	Resultado result = {cinestesico, auditivo, visual, digital};
	
	generateResults(result, nome, prontuario);
	
	getch();
}

void generateResults(Resultado r, char nome[], char prontuario[])
{
	system("cls");
	
	printf("\n\tCALCULANDO RESULTADOS...");
	sleep(1);
	system("cls");
	
	
	r.Cinestesico *= 2;
	r.Auditivo *= 2;
	r.Visual *= 2;
	r.Digital *= 2;
		
	
	char* keys[4] = {"Cinestésico", "Auditivo", "Visual", "Digital"};
	int values[4] = {r.Cinestesico, r.Auditivo, r.Visual, r.Digital};
	char* auxKey;
	int auxValue, i, j;
	
	for ( j = 0; j < 4; j++) 
    {
       for ( i = 0;  i < 3 - j; i++) 
       {
           if ( values[i] < values[i+1])
           {
	            auxValue = values[i];
				values[i]   = values[i+1];
				values[i+1] = auxValue;
				
				auxKey = keys[i];
				keys[i]   = keys[i+1];
				keys[i+1] = auxKey;
		   }
	   }
	}
	
	FILE  *  fileHandler;

	char fileName[255] = "";

	strcat(fileName, "RESULTADO");
	strcat(fileName, "_");
	strcat(fileName, nome);
    strcat(fileName, "_");
    strcat(fileName, prontuario);
    strcat(fileName, ".txt");


    for (i = 0; i < strlen(fileName); i++)
	{	
		if (fileName[i] == ' ')
		{
			fileName[i] = '_';
		} 
		
		fileName[i] = toupper(fileName[i]);
	}
	
	
	fileHandler = fopen ( fileName,  "w"  );
	
	fprintf(fileHandler, "==============================   PERFIL REPRESENTAICONAL DE %s   =============================", nome);
	fprintf(fileHandler, "\n\t%i%% Visual\t%i%% Auditivo\t%i%% Cinestésico\t%i%% Digital", r.Visual, r.Auditivo, r.Cinestesico, r.Digital);
	fprintf(fileHandler, "\n=====================================================================================================");
	fprintf(fileHandler, "\nAlgumas pessoas captam melhor as mensagens do mundo exterior através da audição, são as pessoas chamadas auditivas.\nOutras pessoas sentem necessidade de perguntar muito, necessitam de muitas informações e fatos. Estas são asdigitais.\nAs cinestésicas aprendem melhor por meio das sensações táteis, como o tato, a temperatura, a umidade, assensações internas e as emoções.\nJá as pessoas visuais aprendem melhor quando se valendo da visão.");
	fprintf(fileHandler, "\n=====================================================================================================");
	fprintf(fileHandler, "\nSeu perfil é %s", keys[0]);
	fprintf(fileHandler, "\n=====================================================================================================");
	
	fclose(fileHandler);
	
	system("cls");
	
	printf("\nEXIBINDO RESULTADOS...");
	system(fileName);
	
}

void generateTestData()
{
	system("cls");
	
	int i;
	
	printf("\nPopulando dados de questões. Por favor, aguarde.");
	sleep(1);

	system("cls");
	
	Questao questoes[quantidadeQuestoes] = 
	{
		{
			1,
			0,
			0,
			0,
			0,
			"Eu tomo decisões importantes baseado em: ",
			"intuição",
			"o que me soa melhor",
			"o que me parece melhor",
			"um estudo preciso e minucioso do assunto"
		},
		{
		
			2,
			0,
			0,
			0,
			0,
			"Durante uma discussão eu sou mais influenciado por: ",
			"se eu posso ou não ver o argumento da outra pessoa",
			"o tom da voz da outra pessoa",
			"a lógica do argumento da outra pessoa",
			"se eu entro em contato ou não com os sentimentos reais do outro"
		},
		{
		
			3,
			0,
			0,
			0,
			0,
			"Eu comunico mais facilmente o que se passa comigo: ",
			"do modo como me visto e aparento",
			"pelos sentimentos que compartilho",
			"pelas palavras que escolho",
			"pelo tom da minha voz"
		},
		{
		
			4,
			0,
			0,
			0,
			0,
			"É muito fácil para mim: ",
			"achar o volume e a sintonia ideais num sistema de som",
			"selecionar o ponto mais relevante relativo a um assunto interessante",
			"escolher os móveis mais confortáveis",
			"escolher as combinações de cores mais ricas e atraentes"
		},
		{
		
			5,
			0,
			0,
			0,
			0,
			"Eu me percebo assim: ",
			"se estou muito em sintonia com os sons dos ambientes",
			"se sou muito capaz de raciocinar com fatos e dados novos",
			"eu sou muito sensível à maneira como a roupa veste o meu corpo",
			"eu respondo fortemente às cores e à aparência de uma sala"
		}

	};

  FILE * fileHandler = fopen ("TESTE_SISTEMA_REPRESENTACIONAL.DAT", "w" );	
  
  
  if (fileHandler == NULL)
  {
  	printf ("\nErro ao abrir arquivo TESTE_SISTEMA_REPRESENTACIONAL.DAT!");
  	getch();
  	exit(0);
  }
  
  for ( i = 0; i < quantidadeQuestoes; i++ )
  {
	fwrite (&questoes[i], sizeof(questoes[i]), 1, fileHandler);
	
	if (ferror(fileHandler))
	{
		printf ("\nErro ao gravar no arquivo TESTE_SISTEMA_REPRESENTACIONAL.DAT!");
		getch();
		exit(0);
	}
  }
  
  fclose(fileHandler);
  
  printf ("\nTESTE_SISTEMA_REPRESENTACIONAL.DAT gerado com sucesso!");
  sleep(1);
}

void showQuestions()
{
	setlocale(LC_ALL, "Portuguese.UTF-8");

	FILE * reader;
	FILE * writer;
	
	system("cls");
	
	Questao q;
	Questao questions[quantidadeQuestoes];
	
	reader = fopen("TESTE_SISTEMA_REPRESENTACIONAL.DAT", "r");
	writer = fopen("QUESTIONARIO_1.txt", "w");
	
	fprintf(writer, "\nNúmero\tFrase\t\t\tC\tItem 1\t\t\tA\tItem 2\t\t\tV\tItem 3\t\t\tD\tItem 4");
	fprintf(writer, "\n=========================================================================================================");
	
	printf("QUESTÕES EM nTESTE_SISTEMA_REPRESENTACIONAL.DAT");
	
	
	if (ferror(reader) || ferror(writer))
	{
		printf ("\nErro ao ler registro de perguntas e gerar .txt");
		
		return;
	} 
	
	while (!feof(reader))
	{	
		fread(&q, sizeof(q), 1, reader);
		
		fprintf(writer,"\n\n%i\t%s\t%i\t%s\t%i\t%s\t%i\t%s\t%i\t%s", q.NroFrase, q.Frase, q.Cinestesico, q.Item1, q.Auditivo, q.Item2, q.Visual, q.Item3, q.Digital, q.Item4);
		printf("\n\n%i. %s", q.NroFrase, q.Frase);
	   
	}
	
	fclose(reader);
	fclose(writer);
	
	system("cls");
	printf("Exibindo questionário");
	system("QUESTIONARIO_1.TXT");
	
	
}

void about()
{
	setlocale(LC_ALL, "Portuguese");
	FILE * fileHandler;
	
	fileHandler = fopen ( "REFERENCIAL_TEORICO.txt",  "w"  );
	
	fprintf(fileHandler, "REFERENCIAL TEÓRICO   ");
	fprintf(fileHandler, "\n=====================================================================================================");
	fprintf(fileHandler, "\n\nSegundo Albert Merabian, em seu livro “Silent Messages”, o poder de influência das palavras não passa de 7%%, enquanto a forma como as palavras são ditas e a fisiologia representam 38%% e 55%% deste poder, respectivamente.\n\nPara Merabian 55%% do impacto da comunicação é não-verbal. Corresponde à postura, gestos e contato visual dapessoa enquanto se comunica.\n\nO tom da voz representa 38%% do impacto da comunicação.\n\nPor fim, as palavras propriamente ditas detêm 7%% do impacto da comunicação.\n\nAssim sendo, conclui Merabian, não é o que dizemos, mas como dizemos que faz a diferença na comunicação.\n\nAs portas da percepção são os nossos sentidos, nossos olhos, nariz, ouvidos, boca e pele, nossos únicos pontos de contato com o mundo exterior. Da mesma forma que utilizamos os sentidos para filtrarmos as experiências, utilizamos os sentidos para estruturar nosso pensamento e nossa comunicação.\n\nDe acordo com a Programação Neurolinguística existem os seguintes sistemas representacionais.\n\n- Auditivo\n- Digital\n- Cinestésico\n- Visual\nAlgumas pessoas captam melhor as mensagens do mundo exterior através da audição, são as pessoas chamadas auditivas.\nOutras pessoas sentem necessidade de perguntar muito, necessitam de muitas informações e fatos. Estas são asdigitais.\nAs cinestésicas aprendem melhor por meio das sensações táteis, como o tato, a temperatura, a umidade, as sensações internas e as emoções.\nJá as pessoas visuais aprendem melhor quando se valendo da visão.\n\nCada pessoa tem um sistema representacional predominante e adequar a comunicação ao sistema representacional dominante dela é fundamental para diálogos eficientes.");
	
	fclose(fileHandler);
	
	system("cls");
	
	printf("\nEXIBINDO REFERENCIAL TEÓRICO...");
	system("REFERENCIAL_TEORICO.txt");
}

void printHeader()
{
	system("cls");
	printf("Nas frases a seguir, pontue com:\n4 a que melhor descreve você;\n3 a próxima melhor descrição;\n2 a próxima melhor; e\n1 aquela que menos descreve você.");
}

int validarEscolha (int escolha, int escolhasUtilizadas[])
{
	int i;
	for (i = 0; i < quantidadeQuestoes - 1; i++)
	{
		
		if (escolha == escolhasUtilizadas[i] || escolha < 1 || escolha > 4)
		{
			printf("Opção inválida.");
			return FALSE;
		}
	}
	
	return TRUE;
}

void throwError(char *message)
{
	system("cls");
	system ("color  47");
	printf("\n\n\tERRO: %s", message);
	sleep(1);
	system("color 07");
}
