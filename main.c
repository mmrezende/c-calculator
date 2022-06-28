#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "pilha.h"
#include "fila.h"

#define TAMANHO_MAXIMO 255

fila_t* processa_expressao(char* exp) {
    fila_t* atomos = fila_cria();

    return atomos;
}

// Lógica da calculadora
dado_t calcula(char* exp) {
    fila_t* expressao = processa_expressao(exp);

    dado_t resultado;
    resultado.eh_operador = false;
    resultado.numero = -1;

    return resultado;
}

int main() {
    dado_t resultado = calcula("2 + 3 * 5");

    imprime_dado(resultado);

    return EXIT_SUCCESS;
}