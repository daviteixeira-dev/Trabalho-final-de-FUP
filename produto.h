#ifndef PRODUTO_H
#define PRODUTO_H

typedef struct{
	int estoque;
	char nome[50];
} Produto;

Produto ler();

Produto* remove_produto(char *nome);

void cadastrar_produto(Produto novo);

void menu_cadastros();

void produto_para_arquivo();

void imprime_produto_arquivo();

void menu_consultas();

int chama_menu();

void menu_vendas();

#endif
