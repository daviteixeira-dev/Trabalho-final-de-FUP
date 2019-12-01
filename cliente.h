#ifndef CLIENTE_H
#define CLIENTE_H

typedef struct{
	char nome_cliente[50];
	char nome_produto[50];
	int qtd;
}Clientes;

void ver_cliente();

Clientes ler_(int i, int quantidade, char nome);

Clientes* remove_clientes(char *nome_cliente);

void insere_clientes(Clientes novo);

void menu_historico();

void clientes_para_arquivo();

void imprime_clientes_arquivo();

#endif
