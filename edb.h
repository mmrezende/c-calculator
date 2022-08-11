#ifndef _EDB_H_
#define _EDB_H_

// edb - estrutura de dados de busca

// permite a inclusão de dados associados a chaves, a busca e remoção de
//   dados a partir da chave

#include <stdbool.h>
#include "tipos.h"

// tipo principal (opaco)
typedef struct edb edb_t;

// operações do TAD (interface pública)

edb_t *edb_cria(void);
void edb_destroi(edb_t *edb);

// insere o valor associado a chave
void edb_insere(edb_t *edb, chave_t chave, valor_t valor);
// remove o valor associado a chave
void edb_remove(edb_t *edb, chave_t chave);
// retorna (por ref.) o valor associado a chave (e true) ou nao (e false)
bool edb_busca(edb_t *edb, chave_t chave, valor_t *pvalor);

// Imprime a árvore usada pela estrutura de busca
void edb_arv_imprime(edb_t *edb);

#endif // _EDB_H_
