#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<locale.h>

#define INITIAL -15975 
#define MAX 100

typedef struct _Posicao{
	int linha;
	int coluna;
} Posicao;

// declação de funções
int menu();
void limpa_tela();
void limpa_buffer();
FILE *le_arquivo(char *caminho, char *permissao);
void gerar_alfabeto(char alfabeto[5][5]);
char *remove_espaco(char palavra[]);
char *separa_pares(char palavra[]);
char *codifica(char palavra[], char alfabeto[][5]);
Posicao busca_posicao(char caracter, char alfabeto[][5]);
int nova_posicao(int posicao);

int main(){
	int opcao, j, i;
	char palavra[] = { "E ESTA CIFRA E INQUEBRAVEL" };
	char aux[MAX];
	char alfabeto[5][5];
	gerar_alfabeto(alfabeto);
	//FILE *arq = le_arquivo("teste.txt", "r");
	
	
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			printf("alfabeto[%d][%d] = %c\n", i, j, alfabeto[i][j]);
		}
	}
	/*
	strcpy(aux, remove_espaco(palavra));
	strcpy(aux, separa_pares(aux));
	
	printf("mensagem = %s\n", codifica(aux, alfabeto));
	
	/*
	setlocale(LC_ALL, "Portuguese");//habilita a acentuação para o português

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

void limpa_buffer(){
	#ifdef WIN32
		fflush(stdin);
	#else
		__fpurge(stdin);
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

void gerar_alfabeto(char alfabeto[5][5]){
	
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

char *codifica(char palavra[], char alfabeto[5][5]){
	int i=0, passa=0, indice=0, tamanho=strlen(palavra);
	Posicao primeiro_caracter, segundo_caracter;
	char copia[MAX];
	
	printf("palavra = %s\n", palavra);
	
	for(i=0; i<tamanho; i++){
		if(palavra[i] == ' ' && passa){
			copia[indice] = palavra[i];
			passa++;
		}else if(palavra[i] == ' ' && !passa){
			passa = 0;
		}else{
			primeiro_caracter = busca_posicao(palavra[i], alfabeto);
			i++;
			segundo_caracter = busca_posicao(palavra[i], alfabeto);
			
			printf("indice = %d\n", i);
			printf("copia = %s\n", copia);
			getchar();
			/*
			Se os dois caracteres estão na mesma linha na tabela, são substituídos pelos caracteres 
			imediatamente à direita de cada um deles. Numa linha da tabela é considerado que à direita 
			do último caracter está o primeiro. Exemplo: ES é codificado para OK.
			*/
			if(primeiro_caracter.linha==segundo_caracter.linha){
					
				copia[indice] = alfabeto[primeiro_caracter.linha][nova_posicao(primeiro_caracter.coluna)];
				indice++;
				copia[indice] = alfabeto[segundo_caracter.linha][nova_posicao(segundo_caracter.coluna)];
				indice++;
				
			/* 
			Se ambos os caracteres estiverem na mesma coluna, são substituídos pelos caracteres imediatamente
			a baixo de cada um deles. Numa coluna da tabela é considerado que a baixo do último caracter 
			está o primeiro. Exemplo: RA é codificado para AL
			*/
			}else if(primeiro_caracter.coluna == segundo_caracter.coluna){
				
				copia[indice] = alfabeto[nova_posicao(primeiro_caracter.linha)][primeiro_caracter.coluna];
				indice++;
				copia[indice] = alfabeto[nova_posicao(segundo_caracter.linha)][segundo_caracter.coluna];
				indice++;
				
			/* 
			Se os dois caracteres estão em linhas e colunas difenrentes na tabela, cada caracter é substituído 
			pelo caracter na mesma linha e que está na mesma coluna em que está o outro caracter. 
			Exemplo: CI é codificado por BN.
			*/
			}else{
				copia[indice] = alfabeto[primeiro_caracter.linha][segundo_caracter.coluna];
				indice++;
				copia[indice] = alfabeto[segundo_caracter.linha][primeiro_caracter.coluna];
				indice++;
			}
		}
	}
	
}

Posicao busca_posicao(char caracter, char alfabeto[5][5]){
	int i, j;
	Posicao pos;
	pos.linha = -1;
	pos.coluna = -1;
	
	printf("caracter = %c\n=======================================\n", caracter);
	for(i=0;i<5;i++)
		for(j=0;j<5;j++)
			printf("alfabeto[%d][%d] = %c\n",i,j,alfabeto[i][j]);
			
	for(i=0;i<5;i++)
		for(j=0;j<5;j++)
			if(alfabeto[i][j] == caracter){
				printf("encontrou");
				pos.coluna=j;
				pos.linha=i;
				break;
			}
	
	return pos;
}

int nova_posicao(int posicao){
	printf("entrou com posicao = %d\n", posicao);
	if(posicao==4)
		return 0;
	return posicao+1;			
}


