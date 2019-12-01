#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cliente.h"
#include "produto.h"

int main(){ //Função Principal
	printf("Este e o trabalho final da disciplina de Fundamentos de Programacao. \n");
	printf("Professor: Atilio Gomes.\n");
	printf("Sistema para controle de estoque.\n");
	
	imprime_produto_arquivo();
	imprime_clientes_arquivo();
	
	int comando = 1;
	
	while(comando){
		comando = chama_menu();
	}
	return 0;
}
