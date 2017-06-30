#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<locale.h>

#define INITIAL -15975 

// declação de funções
int menu();
void limpa_tela();
FILE *le_arquivo(char *caminho, char *permissao);
char *gerar_alfabeto();
char *remove_espaco(char palavra[]);

int main(){
	
	int c  = menu();
	FILE *arq = le_arquivo("teste.txt", "r");

	setlocale(LC_ALL, "Portuguese");//habilita a acentuação para o português


	char *alfabeto = gerar_alfabeto();

	if(arq != NULL){
		while((c = fgetc(arq)) != EOF)
	        printf("Caractere lido: %c\n", c);
	}
	
	fflush(stdin);
	char palavra[100];
	gets(palavra);
	
	strcpy(palavra, remove_espaco(palavra));
	printf("palavra sem espaço = %s\n", palavra);
	
	return 0;	
}



// exibe menu e le a opção desejada
int menu(){
	setlocale(LC_ALL, "Portuguese"); //habilita a acentuação para o português
	int opcao = INITIAL;
	do{
		
		printf("===========================================================\n");
		printf("\t1 - Escolher uma tabela de cifra nova;\n");
		printf("\t2 - Introduzir uma mensagem para cifrar;\n"); // (de um arquivo ou do stdin)
		printf("\t3 - Ver a mensagem cifrada;\n");
		printf("\t4 - Decifrar a mensagem;\n");
		printf("\t5 - Ver o alfabeto;\n");
		printf("\t6 - Terminar.\n");
		printf("===========================================================\n");
		
		if(opcao != INITIAL)
			printf("Insira uma opção válida:\n");
		else
			printf("Escolha uma opção:\n");
			
		scanf("%d", &opcao);
		
		if(opcao < 1 || opcao > 6){
			limpa_tela();
		}
		
	}while(opcao < 1 || opcao > 6);
	
	limpa_tela();
	return opcao;
}

void limpa_tela(){
	#ifdef WIN32
		system("CLS");
	#else
		system("clear");
	#endif
}

/* 
	Abre e retorna arquivo
	Recebe caminho do arquivo e permissão como parâmetro
	Em caso de erro exibe mensagem e retorna valor nulo 
*/
FILE *le_arquivo(char *caminho, char *permissao){
	FILE *arq;
	
	if((arq = fopen(caminho, permissao)) == NULL){
		printf("Erro ao abrir arquivo \"%s\"\n", caminho);
		return NULL;
	}
	
	return arq;
}

char *gerar_alfabeto(){
	char alfabeto[5][5];
	
	alfabeto[0][0] = 'Y';
	alfabeto[0][1] = 'Q';
	alfabeto[0][2] = 'D';
	alfabeto[0][3] = 'L';
	alfabeto[0][4] = 'G';
	
	alfabeto[1][0] = 'M';
	alfabeto[1][1] = 'J';
	alfabeto[1][2] = 'X';
	alfabeto[1][3] = 'F';
	alfabeto[1][4] = 'U';
	
	alfabeto[2][0] = 'V';
	alfabeto[2][1] = 'W';
	alfabeto[2][2] = 'C';
	alfabeto[2][3] = 'P';
	alfabeto[2][4] = 'B';
	
	alfabeto[3][0] = 'O';
	alfabeto[3][1] = 'S';
	alfabeto[3][2] = 'K';
	alfabeto[3][3] = 'R';
	alfabeto[3][4] = 'E';
	
	alfabeto[4][0] = 'T';
	alfabeto[4][1] = 'H';
	alfabeto[4][2] = 'N';
	alfabeto[4][3] = 'A';
	alfabeto[4][4] = 'I';
	
	int i=0,j=0;
	
	for(i=0;i<5;i++)
		for(j=0;j<5;j++)
			printf("alfabeto[%d][%d] = %c\n",i,j,alfabeto[i][j]);
			
	return alfabeto;
}

/* 
	Remove caracteres vazios da palavra
*/
char *remove_espaco(char palavra[]){
	int x, y;
	for(x = 0; palavra[x] != '\0'; x++)
        while(palavra[x] == ' ')
            for(y = x; palavra[y] != '\0'; y++)
                palavra[y] = palavra[y + 1];
                
    return palavra;
}

