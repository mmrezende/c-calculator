#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "pilha.h"
#include "fila.h"

#define TAMANHO_MAXIMO 255

int main() {
    fila_t* p = fila_cria();
    dado_t dado;
    // dado.eh_operador = false;
    dado = 12;
    fila_insere(p, dado);
    printf("%f\n", fila_proximo(p));
    dado = 5;
    fila_insere(p, dado);
    printf("%f\n", fila_proximo(p));
    dado = 5;
    printf("%f\n", fila_remove(p));
    printf("%f\n", fila_proximo(p));
    dado = 3;
    fila_insere(p, dado);
    printf("%f\n", fila_proximo(p));
    dado = 8;
    fila_insere(p, dado);
    printf("%f\n", fila_proximo(p));
    dado = 9;
    fila_insere(p, dado);
    printf("%f\n", fila_proximo(p));

    while(!fila_vazia(p)) {
        printf("%f\n", fila_remove(p));
    }

    // pilha_t* p = pilha_cria();
    // dado_t dado;
    // dado = 12;
    // pilha_insere(p, dado);
    // printf("%f\n", pilha_topo(p));
    // dado = 5;
    // pilha_insere(p, dado);
    // printf("%f\n", pilha_topo(p));
    // dado = 5;
    // printf("%f\n", pilha_remove(p));
    // printf("%f\n", pilha_topo(p));
    // dado = 3;
    // pilha_insere(p, dado);
    // printf("%f\n", pilha_topo(p));
    // dado = 8;
    // pilha_insere(p, dado);
    // printf("%f\n", pilha_topo(p));
    // dado = 9;
    // pilha_insere(p, dado);
    // printf("%f\n", pilha_topo(p));

    // while(!pilha_vazia(p)) {
    //     printf("%f\n", pilha_remove(p));
    // }

    return EXIT_SUCCESS;
}