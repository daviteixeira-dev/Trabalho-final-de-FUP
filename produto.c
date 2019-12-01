#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "produto.h"

int n = 0;
Produto *escolhido = 0;

extern Clientes *identificador;
extern int c;

void cadastrar_produto();

Produto* remove_produto(char *nome);

void mostrar_produtos(){ //Função que mostra os Produtos cadastrados no estoque.
	
	system("cls");
	
	int i;
	
	for(i = 0; i < n; i++) {
		printf("\n|* PRODUTOS *|\n");
		printf("|----------------------------|\n");
		printf("|--------- Produto #%d -------|\n", i+1);
		printf(" Nome: %s\n", escolhido[i].nome);
		printf("|----------------------------|\n");
		printf(" Quantidade: %d\n", escolhido[i].estoque);
		printf("|----------------------------|\n");
		printf("|****|\n\n");
		printf("\n");
	}
	
	if(n == 0)
		printf("\n O estoque esta VAZIO.\n\n");
	
}

Produto ler(){
	Produto escolhido;
	
	int opcao = 0;
	
	system("cls");
	setbuf(stdin, NULL);
	
	printf("\n|**PRODUTOS**|\n");
	printf("|----------------------------|\n");
	printf(" Digite o nome: \n");
	scanf("%[^\n]", escolhido.nome);
	printf("|----------------------------|\n");
	printf(" Digite a quantidade: ");
	scanf("%d", &escolhido.estoque);
	printf("|----------------------------|\n");
	printf("|****|\n\n");
    system("pause");
	system("cls");
	printf("\n Cadastrado com sucesso!\n\n");
	
	printf("\n Deseja continuar a cadastrar produtos?\n\n");
	printf("\n (1) Sim\n (2) Nao\n");
	printf("\n Opcao: ");
	
	scanf("%d", &opcao);
	
	if(opcao == 1)
		menu_cadastros();
	else
		return escolhido;
}

Produto* remove_produto(char *nome){
	for(int i = 0; i < n; i++) { 
		if(strcmp(escolhido[i].nome, nome) == 0){
			escolhido[i] = escolhido[n-1];
			escolhido = (Produto*) realloc(escolhido, (n-1) * sizeof(Produto));
			if(escolhido == 0 && n > 1){
				printf(" ERRO: Nao foi possivel alocar memoria");
				return 0;
			}
			n--;
			break;
		}
	 }
	 return escolhido;
}

void cadastrar_produto(Produto novo){
	escolhido = (Produto *) realloc(escolhido, (n + 1) * (sizeof(Produto)));
	
	if(escolhido == 0){
		printf("ERRO: Nao foi possivel alocar memoria");
		return;
	}
	escolhido[n]=novo;
	n++;
	
	for(int i = 0; i < n-1; i++){
		  if(strcmp(escolhido[i].nome, escolhido[n-1].nome)==0){
		  	escolhido[n-1].estoque = escolhido[n-1].estoque + escolhido[i].estoque;
		  	remove_produto(escolhido[i].nome);
		}
	}
}

void menu_cadastros(){ // Função para a realização das opções de Inserir e Remover produtos.
	int opcao = 0;
	
	printf("\n Escolha sua acao: \n");
	printf("\n (1) Para INSERIR um novo produto.\n");
	printf("\n (2) Para REMOVER um produto.\n");
	printf("\n (3) Para SAIR dessa secao.\n");
	
	printf("\n Opcao: ");
	
	scanf("%d", &opcao);
	
	if(opcao == 1){
		
		Produto exemplo = ler();
		cadastrar_produto(exemplo);
		
	}else if(opcao == 2){
		
		char nome[50];
		
		printf(" Digite o nome do produto: \n");
		scanf(" %[^\n]", nome);
		
		remove_produto(nome);
		printf("\n Produto Removido\n\n");
		
	}else if(opcao == 3){
		
		chama_menu();
			
	}else if ((opcao < 1) || (opcao > 3)){
		printf(" Opcao Invalida, Tente novamente !");
		menu_cadastros();
	}		
}

void produto_para_arquivo(){ //joga produtos em texto
			
	FILE *f = fopen("produtos.txt", "w");
	   if (f == 0){ 
			printf("Erro ao abrir arquivo."); 
		}
		
		for(int i = 0; i < n; i++)
			fprintf(f, "%s\n%d\n", escolhido[i].nome, escolhido[i].estoque);
				fclose(f);
}

void imprime_produto_arquivo(){  //scaneia produtos do texto
	FILE *f = fopen("produtos.txt", "r");
	   if (f == 0){
			printf("Erro ao abrir arquivo.");
	 	}
		
		Produto a;
		
		while(fscanf(f, "%[^\n]\n%d\n", a.nome, &a.estoque ) == 2){
			n++;
			escolhido = (Produto*) realloc(escolhido, (n)*sizeof (Produto));
			escolhido[n-1] = a;

			printf("\n");
		}
}

void menu_consultas(){
	
	char nome_produto[50];
	int procurar_produto = 0;
	getchar();
	
	system("cls");
	printf("\n|******************CONSULTA********************|\n");
	printf("|----------------------------------------------|\n");
	printf("  Digite o nome do produto desejado: ");
	scanf("%[^\n]", nome_produto);
	printf("|----------------------------------------------|\n");
	
	for(int i = 0; i < n; i++){
		if(strcmp(escolhido[i].nome, nome_produto) == 0){
			procurar_produto = 1;
			printf("\n\nProduto(s) em ESTOQUE: \n\n");
			printf(" nome: %s\n\n quantidade(s): %d\n\n", escolhido[i].nome, escolhido[i].estoque);
		}
	}
	if(procurar_produto == 0) printf("Produto nao encontrado\n");
}

int chama_menu(){ // Função do Menu de Funcionalidades do Programa
	
	int escolha;
	
	printf("--------------------------Bem vindo(a) ao Sistema de Budegas---------------------------\n");
	printf("---------------------------------------------------------------------------------------\n");
	printf(" (1) Vendas (2) Estoque (3) Cadastros (4) Consultas (5) Historico de Clientes (6) Sair \n");
	printf("---------------------------------------------------------------------------------------\n");
	
	printf(" Escolha: ");
	
	scanf("%d", &escolha);
	
	switch(escolha){
		case 1:
			printf("\n------- Menu de Vendas -----------\n\n");
			menu_vendas();
			break;
		case 2:
			printf("\n------- Menu de Estoque -----------\n\n");
			mostrar_produtos();
			break;
		case 3:
			printf("\n------- Menu de Cadastro ----------\n\n");
			menu_cadastros();
			break;
		case 4:
			printf("\n------- Menu de Consultas -----------\n\n");
			menu_consultas();
			break;
		case 5:
			printf("\n\n------- Menu de Historico de Compra(s) -----------\n\n");
			menu_historico();
			break;
		case 6:
			produto_para_arquivo();
			clientes_para_arquivo();

			free(escolhido);
			free(identificador);
			
			printf("\n Saindo... Tchau <3");
			return 0;
		default:
			printf("\n Opção invalida! Informe novamente!\n");
			system("pause");
	}
	return 1;
}

void menu_vendas(){
	
	char nome_produto[50];
	int quantidade, i, opcao, procurar_produto = 0;
	
	printf("\n (1) Para realizar a venda de PRODUTOS.\n");
	printf("\n (2) Para RETORNAR ao menu principal.\n\n");
	printf("\n Opcao: ");
	scanf("%d", &opcao);
	
	system("cls");
	if(opcao == 1){
		getchar();
		printf("\n|***************VENDAS*****************|\n");
		printf("|--------------------------------------|\n");
		printf("\n Digite o nome do produto: ");
		scanf("%[^\n]", nome_produto);
		printf("|--------------------------------------|\n");
		
		for(i = 0; i < n; i++){
			if(strcmp(escolhido[i].nome, nome_produto) == 0)
			procurar_produto = 1;
		}
		
		printf("\n Digite a quantidade desejada: ");
		scanf("%d", &quantidade);
		printf("|--------------------------------------|\n");
		printf("|**************************************|\n\n");
		
		for(i = 0; i < n; i++){
			if(procurar_produto == 0){
				
				printf("nao ha no estoque. \n");
				break;
			}
			
			if(strcmp(escolhido[i].nome, nome_produto) == 0){
				procurar_produto = 1;
				
				if(escolhido[i].estoque < quantidade){
				 
					printf(" Quantidade INDISPONIVEL no momento \n\n");
					printf(" Quantidade em estoque: %d\n\n", escolhido[i].estoque);
					break;
				
				}else{
					
					escolhido[i].estoque = escolhido[i].estoque - quantidade;
				 	printf(" VENDA realizada com sucesso \n\n");
					
					Clientes ex = ler_(i, quantidade, *nome_produto);
					insere_clientes(ex);		
				}
				
				if(escolhido[i].estoque == 0){
					remove_produto(nome_produto);
				}
		
			}	
		}	
	}else if(opcao == 2){
		chama_menu();
	}else if(opcao < 1 || opcao > 2) printf("Opção inválida.\n");	
}	
