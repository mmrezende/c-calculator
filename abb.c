#include "abb.h"

struct abb {
    valor_t valor,
    abb_t esq,
    abb_t dir
}

abb_t *abb_cria(void);

void abb_destroi(abb_t *abb);

void abb_insere(abb_t *abb, chave_t chave);

void abb_remove(abb_t *abb, chave_t chave);

valor_t abb_busca(abb_t *abb, chave_t chave);
