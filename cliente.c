#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "produto.h"

int c = 0;
Clientes *identificador = 0;

extern Produto *escolhido;
extern int n;

void ver_cliente() {//mostra clientes.
	    
	system("cls");
	int i;
	
	for(i = 0; i < c; i++) {
	    printf("\n|********* CLIENTES *********|\n");
	    printf("|----------------------------|\n");
	    printf("|--------- CLIENTE #%d -------|\n", i+1);
	    printf(" Nome: %s\n", identificador[i].nome_cliente);
	    printf("|----------------------------|\n");
	    
		printf(" Nome do produto: %s\n", identificador[i].nome_produto);
	    printf("|----------------------------|\n");
	    
		printf(" quantidade: %d\n", identificador[i].qtd);
	    printf("|****************************|\n\n");
	    printf("\n");
	}
	    
	if(c == 0){
	    printf("\n Nao ha clientes cadastrados.\n\n");
	}
}

Clientes ler_(int i, int quantidade, char nome){ //scaneia clientes.
		
	Clientes identificador;
	int opcao = 0;
	system("cls");
	setbuf(stdin, NULL);
	    
	printf("\n|**********CLIENTES**********|\n");
	printf("|----------------------------|\n");
	printf(" Digite o nome do cliente: \n");
	scanf(" %[^\n]", identificador.nome_cliente);
	printf("|----------------------------|\n");
	
	strcpy(identificador.nome_produto, escolhido[i].nome);
	identificador.qtd = quantidade;
	
	printf("|----------------------------|\n");
	printf("|****************************|\n\n");
	system("cls");
	
	printf("\n Cadastrado com sucesso!\n\n");
	return identificador;	
}

Clientes* remove_clientes(char *nome_cliente){ //remove clientes dinamicamente.
	
	for(int i = 0; i < c; i++) { 
		if(strcmp(identificador[i].nome_cliente, nome_cliente) == 0){
			
			identificador[i] = identificador[c-1];
			identificador = (Clientes*) realloc(identificador, (c-1) * sizeof(Clientes));
			
			if(identificador == 0 && c > 1){
				printf(" ERRO: Nao foi possivel alocar memoria");
				return 0;
			}
			
			c--;
			break;
		}
	}
	return identificador;
}

void insere_clientes(Clientes novo){ //insere clientes dinamicamente.
	
	identificador = (Clientes *) realloc(identificador, (c + 1) * (sizeof(Clientes)));
	
	if(identificador == 0){
		printf("ERRO: Nao foi possivel alocar memoria");
	   	return;
	}
	
	identificador[c] = novo;
	c++;
}

void menu_historico(){
	int opcao = 0;
	
	printf("\n Escolha sua acao: \n");
	printf("\n (1) Para REMOVER um cliente.\n");
	printf("\n (2) Para ver clientes cadastrados.\n");
	printf("\n (3) Para SAIR dessa secao.\n");
	printf("\n Opcao: ");
	scanf("%d", &opcao);
	
	if(opcao == 1){
		char nome[50];
		printf(" Digite o nome do cliente: \n");
		scanf(" %[^\n]", nome);
		
		remove_clientes(nome);
		printf("\n Cliente Removido\n\n");
		
	}else if(opcao == 2){
		ver_cliente();
		
	}else if(opcao == 3){
		
		system("cls");
		chama_menu();
	
	}else if ((opcao < 1) || (opcao > 3)){
		printf(" Opcao Invalida, Tente novamente !");
		menu_historico();
	}	 
}

void clientes_para_arquivo(){ //joga clientes no arquivo
		        
	FILE *f = fopen("clientes.txt", "w");
	    if (f == 0){ 
			printf("Erro ao abrir arquivo."); 
		}
	        
	    for(int i = 0; i < c; i++)
	        fprintf(f, "%s\n%s\n%d\n", identificador[i].nome_cliente, identificador[i].nome_produto, identificador[i].qtd);
	          	fclose(f);
}

void imprime_clientes_arquivo(){ //scaneia clientes do arquivo
	FILE *f = fopen("clientes.txt", "r");
		if (f == 0){
		   	printf("Erro ao abrir arquivo.");
		}
	        
		Clientes a;
	       	
		while(fscanf(f, "%[^\n]\n%[^\n]\n%d\n", a.nome_cliente, a.nome_produto, &a.qtd ) == 3){
		   	c++;
			identificador = (Clientes*) realloc(identificador, (c)*sizeof (Clientes));
			identificador[c-1] = a;
	       	printf("\n");
	    }
}
