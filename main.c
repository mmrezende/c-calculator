#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "pilha.h"
#include "fila.h"

#define TAMANHO_MAXIMO 255

int main() {
    // fila_t* f = fila_cria();

    // fila_insere(f, 2);
    // fila_imprime(f);

    // fila_insere(f, 5);
    // fila_imprime(f);

    // fila_remove(f);
    // fila_imprime(f);

    // fila_insere(f, 3);
    // fila_imprime(f);

    // fila_insere(f, 8);
    // fila_imprime(f);

    // fila_remove(f);
    // fila_imprime(f);

    // fila_insere(f, 9);
    // fila_imprime(f);

    // while(!fila_vazia(f)) {
    //     fila_remove(f);
    //     fila_imprime(f);
    // }

    pilha_t* p = pilha_cria();

    pilha_insere(p, 2);
    pilha_imprime(p);

    pilha_insere(p, 5);
    pilha_imprime(p);

    pilha_remove(p);
    pilha_imprime(p);

    pilha_insere(p, 3);
    pilha_imprime(p);

    pilha_insere(p, 8);
    pilha_imprime(p);

    pilha_remove(p);
    pilha_imprime(p);

    pilha_insere(p, 9);
    pilha_imprime(p);

    while(!pilha_vazia(p)) {
        pilha_remove(p);
        pilha_imprime(p);
    }

    return EXIT_SUCCESS;
}