#ifndef _ABB_H_
#define _ABB_H_

#include "tipos.h"

// ABB - Árvore Binária de Busca

typedef struct abb abb_t;

// operações do TAD (interface pública)

abb_t *abb_cria(void);

void abb_destroi(abb_t *abb);

void abb_insere(abb_t *abb, chave_t chave);

void abb_remove(abb_t *abb, chave_t chave);

valor_t abb_busca(abb_t *abb, chave_t chave);

#endif // _ABB_H_
