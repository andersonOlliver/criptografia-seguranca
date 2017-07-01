#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<locale.h>

#define INITIAL -15975 
#define MAX 100

// decla��o de fun��es
int menu();
void limpa_tela();
void limpa_buffer();
FILE *le_arquivo(char *caminho, char *permissao);
char *gerar_alfabeto();
char *remove_espaco(char palavra[]);
char *separa_pares(char palavra[]);
char *codifica(char palavra[])

int main(){
	int opcao;
	char palavra[] = { "E ESTA CIFRA E INQUEBRAVEL" };
	char aux[MAX];
	char *alfabeto = gerar_alfabeto();
	//FILE *arq = le_arquivo("teste.txt", "r");
	
	strcpy(aux, remove_espaco(palavra));
	strcpy(aux, separa_pares(aux));
	
	printf("mensagem = %s\n",aux);
	
	/*
	setlocale(LC_ALL, "Portuguese");//habilita a acentua��o para o portugu�s

	opcao = menu();
	switch(opcao){
		case 1:
			
			break;
		case 2:
			
			break;
		case 3:
			
			break;
		case 4:
			
			break;
		case 5:
			
			break;
		default:
			printf("\n");
			break;			
	}
	*/
	

	
	return 0;	
}



// exibe menu e le a op��o desejada
int menu(){
	setlocale(LC_ALL, "Portuguese"); //habilita a acentua��o para o portugu�s
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
			printf("Insira uma op��o v�lida:\n");
		else
			printf("Escolha uma op��o:\n");
			
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

void limpa_buffer(){
	#ifdef WIN32
		fflush(stdin);
	#else
		__fpurge(stdin);
	#endif
}

/* 
	Abre e retorna arquivo
	Recebe caminho do arquivo e permiss�o como par�metro
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

char *separa_pares(char palavra[]){
	int i=0, indice=0, cont=1, tamanho=strlen(palavra);
	char temp, copia[MAX];
	
	printf("tamanho antes = %d\n", tamanho);
	
	for(i=0; i<tamanho; i++){
		temp = palavra[i];
		
		copia[indice] = temp;
		indice++;
		
		if(palavra[i+1] == temp || (i+1)==tamanho){
			copia[indice] = 'X';
			indice++;
		}
		
		if(indice>=1 && copia[indice-2] != ' ' && (i+1)<tamanho){
			copia[indice] = ' ';
			indice++;
		}
	}
		
	printf("tamanho depois = %d\n", strlen(copia));
	printf("indice = %d\n", indice);
	return copia;
}

char *codifica(char palavra[]){
	
}


