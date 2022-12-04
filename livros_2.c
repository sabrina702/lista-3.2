#include <stdio.h>
typedef struct{
	char titulo[30];
	char autor[15];
	float ano;
	int prateleira;
}Clivro;

int quant=0; 

void addLivro(Clivro l[]){
	printf("Título: ");
	fflush(stdin);//limpar buffer teclado
	gets(l[quant].titulo);
	printf("Autor: ");
	fflush(stdin);//limpar buffer teclado
	gets(l[quant].autor);
	printf("Ano de publicacao: ");
	scanf("%d", &l[quant].ano);
	printf("Prateleira: ");
	scanf("%d", &l[quant].prateleira);
	quant++;
}
//-------------------------------------
void listaLivro(Clivro l[]){
	int i;
	for(i=0;i<quant;i++){
		printf("\n** Livro %d **\n", i+1);
		printf("Título: %s\n", l[i].titulo);
		printf("Autor: %s\n", l[i].autor);
		printf("Ano de Publicacao: %d\n", l[i].ano);
		printf("Prateleira: %d\n", l[i].prateleira);
		printf("____________________________\n");
	}
}
//---------------------------------------
int pesquisaTitulo(Clivro l[], char tituloBus[40]){
	int i;
	char tituloAux[40];
	for(i=0;i<quant;i++){
		strcpy(tituloAux,l[i].titulo); 
		strupr(tituloAux);
		if(strcmp(tituloBus,tituloAux)==0){
			printf("\n** Livro %d **\n", i+1);
			printf("Título: %s\n", l[i].titulo);
			printf("Prateleira: %d\n", l[i].prateleira);
			return i;
		}
	}
	return -1;
}
//-------------------------------------------
void pesquisaAno(Clivro l[], int ano){
	int i;
	for(i=0;i<quant;i++){
		if(l[i].ano > ano){
			printf("\n** Livros mais novos **\n");
			printf("Titulo: %s\n", l[i].titulo);
		}	
	}
}
//---------------------------------------------------
void salvaArquivo(Clivro livros[]){
	FILE *arq;
	int i=0;
	arq=fopen("dadosLivros.txt","wb");
	fwrite(&livros[i],sizeof(Clivro),quant,arq);
	printf("Dados salvos com sucesso !\n");
	fclose(arq);
}
//---------------------------------------------------
void carregaArquivo(Clivro livros[]){
	FILE *arq;
	arq=fopen("dadosLivros.txt","rb");
	if(arq==NULL){
	  printf("Arquivo nao encontrado :(\n");
	  return;
	  }// fim if
	 while(fread(&livros[quant],sizeof(Clivro),1,arq) >0 )
	      quant++;  
	 printf("Dados carregados com sucesso !\n");
	fclose(arq);
}
//------------------------------------------------------
int menu(){
	int op;
	printf("*** Sistema de Cadastro de Livros ***\n");
	printf("1- Cadastrar Livro.\n");
	printf("2- Listar Livros.\n");
	printf("3- Filtrar por Título.\n");
	printf("4- Ano de publicacao.\n");
	printf("0- Sair.\n");
	scanf("%d", &op);
	return op;
}

int main(){
	Clivro livros[100];
	char titulo[30];
	int opcao, ano;
	carregaArquivo(livros);
	do{
		opcao = menu();
		switch(opcao){
			case 1: printf("\n** Cadastrar Livro** \n");
				addLivro(livros);
				printf("Item cadastrado!");
				break;
			case 2: printf("\n** Listar Livro** \n");
				listaLivro(livros);
				break;
			case 3:
				printf("Digite o título desejado: ");
				fflush(stdin);
				gets(titulo);
				strupr(titulo);
				pesquisaTitulo(livros, titulo);
				break;
			case 4:
				printf("Digite o ano: ");
				scanf("%d", &ano);
				pesquisaAno(livros, ano);
				break;
			case 0: printf("Saindo...\n");
					salvaArquivo(livros);
				break;
			default: printf("Opcao inválida!!\n");	
		}
		getch();//pausa
		system("cls"); // limpa tela
	}while(opcao!=0);
	return 0;
}
