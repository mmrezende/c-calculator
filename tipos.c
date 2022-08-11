#include <string.h>
#include <stdio.h>
#include <inttypes.h>

#include "tipos.h"
#include "edb.h"

// Imprime o conteúdo de um valor_t
void imprime_valor(valor_t valor) {
    printf("%lf", valor);
}

// Imprime o conteúdo de um dado_t
void imprime_dado(dado_t dado) {
    if(dado.tipo == OPERADOR) {
        printf("%c ", dado.operador);
    }else if(dado.tipo == NUMERO){
        printf("%lf ", dado.numero);
    }else {
        printf(dado.variavel);
    }
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