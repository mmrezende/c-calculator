#include "dado_t.h"
#include <stdio.h>

// Imprime o conteúdo de um dado_t
void imprime_dado(dado_t dado) {
    if(dado.eh_operador) {
        printf("%c ", dado.operador);
    }else {
        printf("%f ", dado.numero);
    }
}