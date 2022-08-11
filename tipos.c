#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "tipos.h"

// Imprime o conteúdo de um valor_t
void imprime_valor(valor_t valor) {
    printf("%lf\n", valor.numero);
}

// Imprime o conteúdo de um dado_t
void imprime_dado(dado_t dado) {
    if(dado.tipo == OPERADOR) {
        printf("(operador) %c\n", dado.operador);
    }else if(dado.tipo == NUMERO){
        printf("(número) %lf\n", dado.numero);
    }else {
        printf("(variável) %s\n",dado.variavel);
    }
}

// Desaloca o conteúdo armazenado num valor_t (caso necessário)
void libera_valor(valor_t valor) {
    free(valor.variavel);
}

/**
 * Função para comparar dois valores, que retorna:
 * =0 - se são iguais
 * <0 - se chave corresponde a valor que deve estar antes do valor
 * >0 - se chave corresponde a valor que deve estar depois do valor
 */
int compara_chave_valor(chave_t c, valor_t v)
{
    return strcmp(c, v.variavel);
}