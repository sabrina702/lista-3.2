#include <stdio.h>
typedef struct{
	char npessoa[30];
	char emprestado;
	char data[15];	
}Cdata;

typedef struct{
	char titulo[30];
	char console[15];
	int ano;
	int ranking;
	Cdata Cdata;
}Cjogo;

int quant=0; 

void addJogo(Cjogo j[]){
	printf("Titulo: ");
	fflush(stdin);//limpar buffer teclado
	gets(j[quant].titulo);
	printf("Console: ");
	fflush(stdin);//limpar buffer teclado
	gets(j[quant].console);
	printf("Ano: ");
	scanf("%d", &j[quant].ano);
	printf("Ranking: ");
	scanf("%d", &j[quant].ranking);
	quant++;
}

int buscaNome(Cjogo j[], char nomeBusca[40]){
	int i;
	char nomeAux[40];
	for(i=0;i<quant;i++){
		strcpy(nomeAux,j[i].titulo); 
		strupr(nomeAux);
		if(strcmp(nomeBusca,nomeAux)==0){
			printf("\n** Jogo **\n");
			printf("Nome: %s\n", j[i].titulo);
			printf("Console: %s\n", j[i].console);
			printf("Valor: %d\n", j[i].ano);
			printf("Ranking: %d\n", j[i].ranking);
			return i;
		}
	}
	return -1;
}

void buscaConsole(Cjogo j[], char consoleBusca[40]){
	int i;
	char consoleAux[40];
	for(i=0;i<quant;i++){
		strcpy(consoleAux,j[i].console); 
		strupr(consoleAux);
		if(strcmp(consoleBusca,consoleAux)==0){
			printf("\n** Jogo **\n");
			printf("Nome: %s\n", j[i].titulo);
			printf("Console: %s\n", j[i].console);
			printf("Valor: %d\n", j[i].ano);
			printf("Ranking: %d\n", j[i].ranking);			
		}
	}
}

void emprestar(Cjogo j[], char nomeBusca[40]){
	int i;
	char nomeAux[40];
	for(i=0;i<quant;i++){
		strcpy(nomeAux,j[i].titulo); 
		strupr(nomeAux);
		if(strcmp(nomeBusca,nomeAux)==0){
			printf("Digite seu nome: ");
			fflush(stdin);
			gets(j[i].Cdata.npessoa);
			printf("Data de emprestimo: ");
			fflush(stdin);
			gets(j[i].Cdata.data);
			j[i].Cdata.emprestado = 'S';
			printf("Emprestimo realizado com sucesso!");
		}
	}
}

void devolver(Cjogo j[], char nomeBusca[40]){
	int i;
	char nomeAux[40];
	for(i=0;i<quant;i++){
		strcpy(nomeAux,j[i].titulo); 
		strupr(nomeAux);
		if(strcmp(nomeBusca,nomeAux)==0){
			j[i].Cdata.emprestado = 'N';
			printf("Livro devolvido com sucesso!");
		}
	}
}

void listarEmprestimos(Cjogo j[]){
	int i;
	for(i=0;i<quant;i++){
		if(strcmp(j[i].Cdata.emprestado, 'S')==0)
			printf("--> O jogo %s , esta emprestado para %s\n", j[i].titulo, j[i].Cdata.npessoa );
 	}
}
void salvaArquivo(Cjogo j[]){
	FILE *arq;
	int i=0;
	arq=fopen("dadosJogo.txt","wb");
	fwrite(&j[i],sizeof(Cjogo),quant,arq);
	printf("Dados salvos com sucesso! \n");
	fclose(arq);
}

void carregaArquivo(Cjogo j[]){
	FILE *arq;
	arq=fopen("dadosJogo.txt","rb");
	if(arq==NULL){
	  printf("Arquivo nao encontrado !! \n");
	  return;
	  }// fim if
	 while(fread(&j[quant],sizeof(Cjogo),1,arq) >0 )
	      quant++;  
	 printf("Dados carregados com sucesso !\n");
	fclose(arq);
}
int menu(){
	int op;
	printf("*** Sistema de Cadastro de Jogos ***\n");
	printf("1- Cadastrar Jogo. \n");
	printf("2- Buscar jogo. \n");
	printf("3- Buscar console. \n");
	printf("4- Emprestimo. \n");
	printf("5- Devolucao. \n");
	printf("6- Listar emprestimos. \n");
	printf("0- Sair. \n");
	scanf("%d", &op);
	return op;
}

int main(){
	Cjogo jogos[100];
	char nome[30];
	int opcao;
	carregaArquivo(jogos);
	do{
		opcao = menu();
		switch(opcao){
			case 1: printf("\n** Cadastrar Jogo** \n");
				addJogo(jogos);
				printf("Item cadastrado!");
				break;
			case 2: printf("\n** Buscar jogo ** \n");
				printf("Insira o nome do jogo:");
			 	fflush(stdin);
				gets(nome);
				strupr(nome);
				buscaNome(jogos, nome);
				break;
			case 3: printf("** Buscar console **\n");
				printf("Digite  o console:");
			 	fflush(stdin);
				gets(nome);
				strupr(nome);
				buscaConsole(jogos, nome);
				break;	
			case 4: printf("** Emprestar **\n");
				printf("Insira o nome  do jogo:");
			 	fflush(stdin);
				gets(nome);
				strupr(nome);
				emprestar(jogos, nome);
				break;
			case 5: printf("** Devolver **\n");
				printf("Insira o nome do jogo:");
			 	fflush(stdin);
				gets(nome);
				strupr(nome);
				devolver(jogos, nome);
				break;
			case 6: printf("** Listar Emprestimos **\n");
				listarEmprestimos(jogos);
				break;
			case 0: printf("Saindo...\n");
				salvaArquivo(jogos);
				break;
			default: printf("Opcao invalida!!\n");	
		}
		getch();//pausa
		system("cls"); // limpa tela
	}while(opcao!=0);
	return 0;
}
