/*
	Desenvolvido por Anderson Oliveira Santos
	como atividade da disciplina de 
	Criptografia e Segurança de Dados
*/

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
void cabecalho(char nome[50]);

void gerar_alfabeto(char alfabeto[5][5]);
void alterar_alfabeto(char alfabeto[5][5]);
void gerar_base(char base[3][5][5]);
void selecionar_base(char base[3][5][5], char alfabeto[5][5], int opcao);
void exibir_alfabeto(char alfabeto[5][5]);

char *remove_espaco(char palavra[]);
char *separa_pares(char palavra[]);
char *separa_grupos(char palavra[]);
char *codifica(char palavra[], char alfabeto[][5]);
Posicao busca_posicao(char caracter, char alfabeto[][5]);
int nova_posicao(int posicao);

char *decodifica(char palavra[], char alfabeto[][5]);
int reverte_posicao(int posicao);

int main(void){
	int opcao, j, i;
	char palavra[MAX];
	char msg_cifrada[MAX], msg_decifrada[MAX];
	char alfabeto[5][5];
	
	
	//FILE *arq = le_arquivo("teste.txt", "r");
	gerar_alfabeto(alfabeto); 
	
	
	setlocale(LC_ALL, "Portuguese");//habilita a acentuação para o português

	do{
		
		opcao = menu();
		switch(opcao){
			case 1:
				cabecalho("ALTERAR CIFRA");
				alterar_alfabeto(alfabeto);
				break;
				
			case 2:
				cabecalho("CIFRAR MENSAGEM");
				limpa_buffer();
				
				printf("Insira a mensagem:\n");
				gets(palavra);
				strcpy(palavra,strupr(palavra));
				palavra[strlen(palavra)] = '\0';
				limpa_buffer();
				
				strcpy(msg_cifrada, separa_pares(remove_espaco(palavra)));
				strcpy(msg_cifrada, codifica(msg_cifrada, alfabeto));
				strcpy(msg_cifrada, separa_grupos(msg_cifrada));
				
				
				printf("Mensagem cifrada com sucesso!\n");
				break;
				
			case 3:
				cabecalho("MENSAGEM CIFRADA");
				if(strlen(msg_cifrada)>0){
					printf("Mensagem cifrada: %s\n", msg_cifrada);
				}else{
					printf("Nenhuma mensagem encontrada =(\n");
				}
				break;
				
			case 4:
				cabecalho("DECIFRAR MENSAGEM");
				msg_decifrada[0] = '\0';
				if(strlen(msg_cifrada) > 0){
					printf("Mensagem decifrada: %s\n", decodifica(msg_cifrada, alfabeto));
				}else{
					printf("Nenhuma mensagem encontrada =(\n)");
				}
				break;
				
			case 5:
				cabecalho("EXIBIR ALFABETO");
				exibir_alfabeto(alfabeto);
				break;
				
			default:
				cabecalho("SAINDO");
				printf("Adeus\n");
				break;			
		}
		if(opcao!=6){
			printf("----------------------------------------\n");
			printf("\nPressione qualquer tecla para continuar...\n");
			getchar();
		}
		limpa_tela();
	}while(opcao!=6);
	
	
	
	return 0;	
}

// exibe menu, le e retorna a opção desejada
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
	
	limpa_buffer();
	limpa_tela();
	
	return opcao;
}

// limpar tela em windows e linux
void limpa_tela(){
	#ifdef WIN32
		system("CLS");
	#else
		system("clear");
	#endif
}

// limpar buffer em windows e linux
void limpa_buffer(){
	#ifdef WIN32
		fflush(stdin);
	#else
		__fpurge(stdin);
	#endif
}

// Para exibir cabeçalho em cada escolha
void cabecalho(char nome[50]){
	printf("----------------------------------------\n");
	printf("\t %s\n", nome);
	printf("----------------------------------------\n");
}

// Gera um alfabeto inicial
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

// Alterar a cifra 
void alterar_alfabeto(char alfabeto[5][5]){
	char base[3][5][5];
	int x,y,z,opcao = INITIAL;
	gerar_base(base);
	
	do{
		if(opcao!= INITIAL){
			limpa_tela();
			cabecalho("ALTERAR CIFRA");
		}
		for(x=0;x<3;x++){
			printf("Pressione %d para:\n",x+1);
			for(y=0;y<5;y++){
				printf("\t");
				for(z=0;z<5;z++)
					printf("%c ", base[x][y][z]);
				printf("\n");
			}
			printf("\n");
		}
		printf("----------------------------------------\n");
		printf("Selecione uma opção:\n");
		scanf("%d", &opcao);
	}while(opcao<1 || opcao>3);
	
	selecionar_base(base, alfabeto, opcao-1);
	
	
}

// para copiar a opção escolhida pelo usuário para a matriz alfabeto
void selecionar_base(char base[3][5][5], char alfabeto[5][5], int opcao){
	int i,j;
	for(i=0;i<5;i++)
		for(j=0;j<5;j++)
			alfabeto[i][j] = base[opcao][i][j];
}

// apenas para não gerar a base de cifras
void gerar_base(char base[3][5][5]){
	base[0][0][0] = 'Y';
	base[0][0][1] = 'Q';
	base[0][0][2] = 'D';
	base[0][0][3] = 'L';
	base[0][0][4] = 'G';
	
	base[0][1][0] = 'M';
	base[0][1][1] = 'J';
	base[0][1][2] = 'X';
	base[0][1][3] = 'F';
	base[0][1][4] = 'U';
	
	base[0][2][0] = 'V';
	base[0][2][1] = 'W';
	base[0][2][2] = 'C';
	base[0][2][3] = 'P';
	base[0][2][4] = 'B';
	
	base[0][3][0] = 'O';
	base[0][3][1] = 'S';
	base[0][3][2] = 'K';
	base[0][3][3] = 'R';
	base[0][3][4] = 'E';
	
	base[0][4][0] = 'T';
	base[0][4][1] = 'H';
	base[0][4][2] = 'N';
	base[0][4][3] = 'A';
	base[0][4][4] = 'I';

	base[1][4][0] = 'Y';
	base[1][4][1] = 'Q';
	base[1][4][2] = 'D';
	base[1][4][3] = 'L';
	base[1][4][4] = 'G';
	
	base[1][3][0] = 'M';
	base[1][3][1] = 'J';
	base[1][3][2] = 'X';
	base[1][3][3] = 'F';
	base[1][3][4] = 'U';
	
	base[1][2][0] = 'V';
	base[1][2][1] = 'W';
	base[1][2][2] = 'C';
	base[1][2][3] = 'P';
	base[1][2][4] = 'B';
	
	base[1][1][0] = 'O';
	base[1][1][1] = 'S';
	base[1][1][2] = 'K';
	base[1][1][3] = 'R';
	base[1][1][4] = 'E';
	
	base[1][0][0] = 'T';
	base[1][0][1] = 'H';
	base[1][0][2] = 'N';
	base[1][0][3] = 'A';
	base[1][0][4] = 'I';

	base[2][4][0] = 'Y';
	base[2][4][1] = 'Q';
	base[2][4][2] = 'D';
	base[2][4][3] = 'L';
	base[2][4][4] = 'G';
	
	base[2][2][0] = 'M';
	base[2][2][1] = 'J';
	base[2][2][2] = 'X';
	base[2][2][3] = 'F';
	base[2][2][4] = 'U';
	
	base[2][1][0] = 'V';
	base[2][1][1] = 'W';
	base[2][1][2] = 'C';
	base[2][1][3] = 'P';
	base[2][1][4] = 'B';
	
	base[2][3][0] = 'O';
	base[2][3][1] = 'S';
	base[2][3][2] = 'K';
	base[2][3][3] = 'R';
	base[2][3][4] = 'E';
	
	base[2][0][0] = 'T';
	base[2][0][1] = 'H';
	base[2][0][2] = 'N';
	base[2][0][3] = 'A';
	base[2][0][4] = 'I';
}

// para exibir o alfabeto
void exibir_alfabeto(char alfabeto[5][5]){
	int i,j;
	printf("Alfabeto:\n");
	for(i=0;i<5;i++){
		printf("\t");
		for(j=0;j<5;j++)
			printf("%c ", alfabeto[i][j]);
			
		printf("\n");
	}
}

// Remove caracteres vazios da palavra
char *remove_espaco(char palavra[]){
	int x, y;
	for(x = 0; palavra[x] != '\0'; x++)
        while(palavra[x] == ' ')
            for(y = x; palavra[y] != '\0'; y++)
                palavra[y] = palavra[y + 1];
                
    return palavra;
}

// separa em pares e adiciona X
char *separa_pares(char palavra[]){
	int i=0, indice=0, cont=1, tamanho=strlen(palavra);
	char temp, copia[MAX];
	
	
	// adiciona X entre caracteres repetidos
	for(i=0; palavra[i] != '\0'; i++){
		if(palavra[i] == palavra[i+1]){
			copia[indice] = palavra[i];
			indice++;
			copia[indice] = 'X';
		}else{
			copia[indice] = palavra[i];
		}
		indice++;
	}
	// se quantidade ímpar de caracteres adiciona 'X' no final
	if(strlen(copia)%2 != 0){
		copia[indice] = 'X';
		indice++;
	}
	copia[indice] = '\0';
	
	indice = 0;
	for(i=0; copia[i] != '\0'; i++){
		if(i%2 != 0){
			palavra[indice] = copia[i];
			indice++;
			palavra[indice] = ' ';
		}else{
			palavra[indice] = copia[i];
		}
		indice++;
	}
	palavra[indice] = '\0';
	
	return palavra;
}

// separa em grupos de 4 caracteres
char *separa_grupos(char palavra[]){
		int i, y, indice=0;
		char copia[MAX];
	for(i = 0; palavra[i] != '\0'; i++){
		if((i+1)%4==0){
			copia[indice] = palavra[i];
			indice++;
			copia[indice] = ' ';
		}else{
			copia[indice] = palavra[i];
		}
		indice++;
	}
	copia[indice] = '\0';
    
    return copia;
}

// codificação é feita aqui
char *codifica(char palavra[], char alfabeto[5][5]){
	int i=0, passa=0, indice=0, tamanho=strlen(palavra);
	Posicao primeiro_caracter, segundo_caracter;
	char copia[MAX];
	
	for(i=0; palavra[i] != '\0'; i++){
		if(palavra[i] != ' '){
			primeiro_caracter = busca_posicao(palavra[i], alfabeto);
			i++;
			segundo_caracter = busca_posicao(palavra[i], alfabeto);
			
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
			copia[indice] = '\0';
		}
	}
	
	return copia;
	
}

// decodificação é feita aqui
char *decodifica(char palavra[], char alfabeto[][5]){
	int i=0, passa=0, indice=0, tamanho=strlen(palavra);
	Posicao primeiro_caracter, segundo_caracter;
	char copia[MAX];
	
	for(i=0; palavra[i] != '\0'; i++){
		if(palavra[i] != ' '){
			primeiro_caracter = busca_posicao(palavra[i], alfabeto);
			i++;
			segundo_caracter = busca_posicao(palavra[i], alfabeto);
			
			/*
			Se os dois caracteres estão na mesma linha na tabela, são substituídos pelos caracteres 
			imediatamente à direita de cada um deles. Numa linha da tabela é considerado que à direita 
			do último caracter está o primeiro. Exemplo: ES é codificado para OK.
			*/
			if(primeiro_caracter.linha==segundo_caracter.linha){
					
				copia[indice] = alfabeto[primeiro_caracter.linha][reverte_posicao(primeiro_caracter.coluna)];
				indice++;
				copia[indice] = alfabeto[segundo_caracter.linha][reverte_posicao(segundo_caracter.coluna)];
				indice++;
				
			/* 
			Se ambos os caracteres estiverem na mesma coluna, são substituídos pelos caracteres imediatamente
			a baixo de cada um deles. Numa coluna da tabela é considerado que a baixo do último caracter 
			está o primeiro. Exemplo: RA é codificado para AL
			*/
			}else if(primeiro_caracter.coluna == segundo_caracter.coluna){
				
				copia[indice] = alfabeto[reverte_posicao(primeiro_caracter.linha)][primeiro_caracter.coluna];
				indice++;
				copia[indice] = alfabeto[reverte_posicao(segundo_caracter.linha)][segundo_caracter.coluna];
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
			copia[indice] = '\0';
		}
	}
	
	return copia;
}

// retorna a posição do caracter na cifra
Posicao busca_posicao(char caracter, char alfabeto[5][5]){
	int i, j;
	Posicao pos;
	pos.linha = -1;
	pos.coluna = -1;
			
	for(i=0;i<5;i++)
		for(j=0;j<5;j++)
			if(alfabeto[i][j] == caracter){
				pos.coluna=j;
				pos.linha=i;
				break;
			}
	
	return pos;
}

// retorna nova posição para codificar
int nova_posicao(int posicao){
	if(posicao==4)
		return 0;
	return posicao+1;			
}

// retorna nova posição para decodificar
int reverte_posicao(int posicao){
	if(posicao==0)
		return 4;
	return posicao-1;			
}


