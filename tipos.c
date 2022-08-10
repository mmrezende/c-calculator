#include <string.h>
#include <stdio.h>
#include "tipos.h"

void imprime_valor(valor_t valor) {
    printf("%s\n", valor.nome);
}

int compara_chave_valor(chave_t c, valor_t v)
{
    return strcmp(c, v.nome);
}