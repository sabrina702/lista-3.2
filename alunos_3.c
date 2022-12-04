#include <stdio.h>
#include <string.h>
typedef struct{
	char nome[40];
	int matricula;
	float n1;
	float n2;
	float n3;
}Caluno;

int quant=0; 

void addAluno(Caluno a[]){
	printf("Nome do aluno: ");
	fflush(stdin);//limpar buffer teclado
	gets(a[quant].nome);
	printf("Matricula: ");
	scanf("%d", &a[quant].matricula);
	printf("Insira as notas da prova 1, 2 e 3: ");
	scanf("%f%f%f", &a[quant].n1, &a[quant].n2, &a[quant].n3);
	quant++;
}

void listaAluno(Caluno a[]){
	int i;
	for(i=0;i<quant;i++){
		printf("\n** Aluno %d **\n", i+1);
		printf("Nome: %s\n", a[i].nome);
		printf("Matricula: %d\n", a[i].matricula);
		printf("Nota 1: %.2f\n", a[i].n1);
		printf("Nota 2: %.2f\n", a[i].n2);
		printf("Nota 3: %.2f\n", a[i].n3);	
		printf("____________________________\n");
	}
}

void BuscMatricula(Caluno a[], int busca){
	int  i;
	for(i=0;i<quant;i++){
		if(busca==a[i].matricula){
			printf("\n** Aluno **\n");
			printf("Nome: %s\n", a[i].nome);
			printf("Nota 1: %.2f\n", a[i].n1);
			printf("Nota 2: %.2f\n", a[i].n2);
			printf("Nota 3: %.2f\n", a[i].n3);
			printf("____________________________\n");	
		}	
	}
}

void BuscNome(Caluno a[], char busca[40]){
	int  i;
	char nomeAux[40];
	for(i=0;i<quant;i++){
		strcpy(nomeAux, a[i].nome);
		strupr(nomeAux);
		if(strcmp(busca,nomeAux)==0){
			printf("\n** Aluno **\n");
			printf("Nome: %s\n", a[i].nome);
			printf("Nota 1: %.2f\n", a[i].n1);
			printf("Nota 2: %.2f\n", a[i].n2);
			printf("Nota 3: %.2f\n", a[i].n3);
			printf("____________________________\n");	
		}//fim if	
	}//fim for
}

void mediaGeral(Caluno a[], int matricula){
	int i;
	float media=0;
	for(i=0;i<quant;i++){
		if(a[i].matricula == matricula){
				media =  (a[i].n1 +  a[i].n2 +  a[i].n3) / 3;
				if(media >= 6)
					printf("** %s Aprovado com sucesso! Sua media: %.2f\n**",  a[i].nome, media);
				else
				printf("** %s Reprovado! Sua media: %.2f\n **",  a[i].nome, media);
		}
	}
}

void maiorMedia(Caluno a[]){
	int i, pos;
	float media=0, mMedia=0;
	for(i=0;i<quant;i++){
		media =  (a[i].n1 +  a[i].n2 +  a[i].n3) / 3;
		if(media > mMedia){
			mMedia = media;
			pos = i; 
		}
	}
	printf("** Maior media: %.2f. \nEla perrtece a %s **", mMedia , a[pos].nome);
}

void salvaArquivo(Caluno a[]){
	FILE *arq;
	int i=0;
	arq=fopen("dadosAlunos.txt","wb");
	fwrite(&a[i],sizeof(Caluno),quant,arq);
	printf("Dados salvos com sucesso! \n");
	fclose(arq);
}
//-----------------------------
void carregaArquivo(Caluno a[]){
	FILE *arq;
	arq=fopen("dadosAlunos.txt","rb");
	if(arq==NULL){
	  printf("Arquivo nao encontrado! \n");
	  return;
	  }// fim if
	 while(fread(&a[quant],sizeof(Caluno),1,arq) >0 )
	      quant++;  
	 printf("Dados carregados com sucesso! \n");
	fclose(arq);
}
int menu(){
	int op;
	printf("*** Sistema de Cadastro de Alunos ***\n");
	printf("1- Cadastrar Aluno. \n");
	printf("2- Listar Alunos. \n");
	printf("3- Filtrar aluno por nome ou matricula. \n");
	printf("4- Reprovados ou Aprovados\n");
	printf("5- Maior media geral. \n");
	printf("0- Sair\n");
	scanf("%d", &op);
	return op;
}

int main(){
	Caluno alunos[100];
	char nome[40];
	int opcao, op, matricula;
	carregaArquivo(alunos);
	do{
		opcao = menu();
		switch(opcao){
			case 1: printf("\n** Cadastrar Aluno** \n");
				addAluno(alunos);
				printf("Item cadastrado!");
				break;
			case 2: printf("\n** Listar Alunos** \n");
				listaAluno(alunos);
				break;
			case 3: printf("** Filtrar aluno por nome ou matricula **\n");
				printf("Deseja buscar por matricula ou nome? (1/2) ");
				scanf("%d", &op);
				if(op == 1){
					printf("Digite a matricula: ");
					scanf("%d", &matricula);
					BuscMatricula(alunos, matricula);
				} else if(op == 2){
					printf("Digite o nome: ");
					fflush(stdin);
					gets(nome);
					strupr(nome);	
					BuscNome(alunos, nome);
				}
				else
					printf("Opção invalida!");
				break;	
			case 4: printf("** Reprovados ou Aprovados **\n");
				printf("Insira a matricula: ");
				scanf("%d", &op);
				mediaGeral(alunos, op);
				break;
			case 5: printf("*** Maior media ***\n");
				maiorMedia(alunos);
				break;
			case 0: printf("Saindo...\n");
				salvaArquivo(alunos);
				break;
			default: printf("Opção invalida!\n");	
		}
		getch();//pausa
		system("cls"); // limpa tela
	}while(opcao!=0);
	return 0;
}
