#include <stdio.h>
typedef struct{
	char nome[40];
	float poten;
	float tempo;
}Celetro;

int quant=0; 

void addEletro(Celetro e[]){
	printf("Nome: ");
	fflush(stdin);//limpar buffer teclado
	gets(e[quant].nome);
	printf("Potencia: ");
	scanf("%f", &e[quant].poten);
	printf("Tempo Medio: ");
	scanf("%f", &e[quant].tempo);	
	quant++;
}

void listaEletro(Celetro e[]){
	int i;
	for(i=0;i<quant;i++){
		printf("\n** Eletrodomestico %d **\n", i+1);
		printf("Nome: %s\n", e[i].nome);
		printf("Potencia: %.2f\n", e[i].poten);
		printf("Tempo: %.2f\n", e[i].tempo);
	}
}

void buscaNome(Celetro e[], char busca[40]){
	int  i;
	char nomeAux[40];
	for(i=0;i<quant;i++){
		strcpy(nomeAux, e[i].nome);
		strupr(nomeAux);
		if(strcmp(busca,nomeAux)==0){
			printf("\n** Eletrodomestico %d **\n", i+1);
			printf("Nome: %s\n", e[i].nome);
			printf("Potencia: %.2f\n", e[i].poten);
			printf("Tempo: %.2f\n", e[i].tempo);
			printf("-------------------------------\n");
		}//fim if	
	}//fim for
}

void calcula(Celetro e[], float valor, char busca[40]){
	int i;
	float consumo;
	char nomeAux[40];
	for(i=0;i<quant;i++){
		strcpy(nomeAux, e[i].nome);
		strupr(nomeAux);
		if(strcmp(busca,nomeAux)==0){
			consumo = (e[i].poten / 1000) * e[i].tempo;
			consumo = consumo * valor;
			printf("Consumo diario:  R$ %.2f\n", consumo);
			consumo = consumo * 30;
			printf("Consumo mensal:  R$ %.2f", consumo);
		}
	}
}
//------------------------------------------------
void salvaArquivo(Celetro e[]){
	FILE *arq;
	int i=0;
	arq=fopen("dadosEletro.txt","wb");
	fwrite(&e[i],sizeof(Celetro),quant,arq);
	printf("Dados salvos com sucesso! \n");
	fclose(arq);
}
//-----------------------------
void carregaArquivo(Celetro e[]){
	FILE *arq;
	arq=fopen("dadosEletro.txt","rb");
	if(arq==NULL){
	  printf("Arquivo nao encontrado! \n");
	  return;
	  }// fim if
	 while(fread(&e[quant],sizeof(Celetro),1,arq) >0 )
	      quant++;  
	 printf("Dados carregados com sucesso !\n");
	fclose(arq);
}
int menu(){
	int op;
	printf("*** Sistema de Cadastro de Eletrodomestico ***\n");
	printf("1- Cadastrar Eletrodomestico. \n");
	printf("2- Listar Eletrodomestico. \n");
	printf("3- Buscar eletrodomestico por nome. \n");
	printf("0- Sair\n");
	scanf("%d", &op);
	return op;
}

int main(){
	Celetro eletros[100];
	char nome[40];
	int opcao;
	float valor;
	carregaArquivo(eletros);
	do{
		opcao = menu();
		switch(opcao){
			case 1: printf("\n** Cadastrar Eletrodomestico** \n");
				addEletro(eletros);
				printf("Item cadastrado!");
				break;
			case 2: printf("\n** Listar Eletrodomestico** \n");
				listaEletro(eletros);
				break;
			case 3: printf("** Buscar eletrodomestico por nome **\n");
				printf("Digite o nome: ");
				fflush(stdin);
				gets(nome);
				strupr(nome);	
				buscaNome(eletros, nome);
				break;	
			case 4:printf("** Consumo diario e mensal ***\n");
				printf("Digite o nome: ");
				fflush(stdin);
				gets(nome);
				strupr(nome);	
				printf("Digite o valor do KW: ");
				scanf("%f", &valor);
				calcula(eletros, valor, nome);
				break;
			case 0: printf("Saindo...\n");
				salvaArquivo(eletros);
				break;
			default: printf("Opcao invalida!!\n");	
		}
		getch();//pausa
		system("cls"); // limpa tela
	} while(opcao!=0);
	return 0;
}
