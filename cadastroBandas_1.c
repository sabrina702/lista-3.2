#include <stdio.h>
#include <string.h>
typedef struct{
	char nome[40];
	char genero[40];
	int integrantes;
	int ranking;
}tbanda;
int qtd=0; // controlar a posicao de cadastro no vetor
//--------------
void addBanda(tbanda b[]){
	printf("Nome da banda:");
	fflush(stdin);// limpa o buffer do teclado
	gets(b[qtd].nome);
	printf("Genero da banda:");
	fflush(stdin);// limpa o buffer do teclado
	gets(b[qtd].genero);
	printf("Qtde de integrantes:");
	scanf("%d",&b[qtd].integrantes);
	printf("Ranking da banda:");
	scanf("%d",&b[qtd].ranking);
	qtd++;
}
//--------------
void listaBandas(tbanda b[]){
	int i;
	for(i=0;i<qtd;i++){
		printf("** Banda %d **\n",i+1);
		printf("Nome:%s\n",b[i].nome);
		printf("Genero:%s\n",b[i].genero);
		printf("Integrantes:%d\n",b[i].integrantes);
		printf("Ranking:%d\n",b[i].ranking);
		printf("------------------------\n");
	}// fim for
}
//----------------------------------
void listaRanking(tbanda b[], int busca){
	int i;
	for (i=0;i<qtd;i++){
		if(busca==b[i].ranking){
		printf("** Banda %d **\n",i+1);
		printf("Nome:%s\n",b[i].nome);
		printf("Genero:%s\n",b[i].genero);
		printf("Integrantes:%d\n",b[i].integrantes);
		printf("Ranking:%d\n",b[i].ranking);
		printf("------------------------\n");
		}
	}
}
void listaGenero(tbanda b[],char generoBusca[40]){
	int i;
	for (i=0;i<qtd;i++){
		if(strcmp(generoBusca,b[i].genero)==0){
		printf("** Banda %d **\n",i+1);
		printf("Nome:%s\n",b[i].nome);
		printf("Genero:%s\n",b[i].genero);
		printf("Integrantes:%d\n",b[i].integrantes);
		printf("Ranking:%d\n",b[i].ranking);
		printf("------------------------\n");
		}
	}
}
//-----------------------------
void salvaArquivo(tbanda bandas[]){
	FILE *arq;
	int i=0;
	arq=fopen("dadosBandas.txt","wb");
	fwrite(&bandas[i],sizeof(tbanda),qtd,arq);
	printf("Dados salvos com sucesso\n");
	fclose(arq);
}
//-----------------------------
void carregaArquivo(tbanda bandas[]){
	FILE *arq;
	arq=fopen("dadosBandas.txt","rb");
	if(arq==NULL){
	  printf("Arquivo nao encontrado :(\n");
	  return;
	  }// fim if
	 while(fread(&bandas[qtd],sizeof(tbanda),1,arq) >0 )
	      qtd++;  
	 printf("Dados carregados com sucesso !\n");
	fclose(arq);
}
//-----------------------------

int menu(){
	int opcao;
	printf("*** Sistema de Cadastro Rock4You ***\n");
	printf("1- Cadastrar\n");
	printf("2- Listar\n");
	printf("3- Busca de Ranking \n");
	printf("4- Busca genero \n");
	printf("0 - Sair\n");
	scanf("%d",&opcao);
	return opcao;
}// fim menu
//------------------
int main(){
    tbanda bandas[100];
	int opcao,busca;
	char generoBusca[40];
	carregaArquivo(bandas);
	do{
		opcao= menu();
		switch(opcao){
			case 1: addBanda(bandas);
			 break;
			case 2: listaBandas(bandas);
			 break;
			 case 3: printf("Filtro ranking: \n");
			 scanf("%d",&busca);
			 listaRanking(bandas,busca);
			 break;
			 case 4: printf("Busca Genero: \n");
			 fflush(stdin);
			 gets(generoBusca);
			 listaGenero(bandas,generoBusca);
			case 0: printf("Saindo...\n");
					salvaArquivo(bandas);
			 break;
			default: printf("Opcao invalida\n");  
		}// fim switch
	}while(opcao!=0);
	return 0;
}// fim main
