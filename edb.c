#include "edb.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct no no_t;

struct no {
    valor_t valor;
    no_t* esq;
    no_t* dir;
};

struct edb {
    no_t* raiz;
};

// -------------------------------- Funções auxiliares --------------------------------
bool edb_vazia(edb_t* edb) {
	return edb->raiz == NULL;
}

bool no_folha(no_t* no) {
    return no->esq == NULL && no->dir == NULL;
}

char* get_chave_valor(valor_t* valor) {
  return valor->nome;
}

// -------------------------------- Funções da árvore de busca --------------------------------

// Aloca e inicia um nó folha
no_t* arv_cria(valor_t valor) {
    no_t* novo = malloc(sizeof(no_t));
    novo->valor = valor;
    novo->dir = NULL;
    novo->esq = NULL;

    return novo;
}

// Busca e retorna um nó na estrutura da árvore, retorna NULL se não encontrado
no_t* arv_busca(no_t *no, chave_t chave) {
    if(no == NULL) return NULL;

    int comp = compara_chave_valor(chave, no->valor);
    if(comp == 0) {
        return no;
    }

    if(comp > 0) {
        return arv_busca(no->dir, chave);
    }

    return arv_busca(no->esq, chave);
}

// Desaloca todos os nós da árvore
void arv_destroi(no_t *no) {
    if(no == NULL) return;

    arv_destroi(no->esq);
    arv_destroi(no->dir);
    free(no);
}

// Retorna um ponteiro para o nó mais à direita a partir de outro nó
no_t* maior_no(no_t* no) {
    no_t* prox = no->dir;
    if(prox == NULL) return no;

    return maior_no(prox);
}

// Retorna um ponteiro para o nó mais à esquerda a partir de outro nó
no_t* menor_no(no_t* no) {
    no_t* prox = no->esq;
    if(prox == NULL) return no;

    return menor_no(prox);
}

// Insere um valor na árvore, respeitando a hierarquia
void arv_insere(no_t* no, chave_t chave, valor_t valor) {
    int comp = compara_chave_valor(chave, no->valor);
    if(comp == 0) { // Substitui o valor do nó atual
        no->valor = valor;
    }

    if(comp < 0) {
        if(no->esq == NULL) {
            no->esq = arv_cria(valor);
            return;
        }
        arv_insere(no->esq, chave, valor);
    }

    if(no->dir == NULL) {
        no->dir = arv_cria(valor);
        return;
    }
    arv_insere(no->dir, chave, valor);
}

// Encontra e remove um nó e reestrutura a árvore (sem balanceamento, por enquanto)
no_t* arv_remove(no_t* no, chave_t chave) {
    if(no == NULL) return NULL;

    int comp = compara_chave_valor(chave, no->valor);
    if(comp == 0) {
        if(no->esq != NULL) {
            no->valor = maior_no(no->esq)->valor;
            no->esq = arv_remove(no->esq, get_chave_valor(&no->valor));
        }else if(no->dir != NULL) {
            no->valor = menor_no(no->dir)->valor;
            no->dir = arv_remove(no->dir, get_chave_valor(&no->valor));
        }else {
            free(no);
            return NULL;
        }
        
    }else if(comp > 0) {
        no->dir = arv_remove(no->dir, chave);
    }else {
        no->esq = arv_remove(no->esq, chave);
    }
    
    return no;
}

// -------------------------------- Funções da interface do TAD --------------------------------

edb_t *edb_cria(void) {
	edb_t* edb = malloc(sizeof(edb_t));
	edb->raiz = NULL;

	return edb;
};

void edb_destroi(edb_t *edb) {
    arv_destroi(edb->raiz);
    free(edb);
};

// Insere o valor associado à chave
void edb_insere(edb_t *edb, chave_t chave, valor_t valor) {
    if(edb_vazia(edb)) {
        edb->raiz = arv_cria(valor);
        return;
    }

    arv_insere(edb->raiz, chave, valor);
};

// Remove o valor associado à chave
void edb_remove(edb_t *edb, chave_t chave) {
    if(edb_vazia(edb)) {
        return;
    }

    edb->raiz = arv_remove(edb->raiz, chave);
};

// Retorna (por ref) o valor associado a chave (e true) ou nao (false)
bool edb_busca(edb_t *edb, chave_t chave, valor_t *pvalor) {

    if(edb_vazia(edb)) return false;

    no_t* encontrado = arv_busca(edb->raiz, chave);
    
    if(encontrado == NULL) return false;

    *pvalor = encontrado->valor;
    return true;
}