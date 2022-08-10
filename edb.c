#include "edb.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct no no_t;

struct no {
    valor_t valor;
    no_t* esq;
    no_t* dir;
    int altura;
};

struct edb {
    no_t* raiz;
};

// -------------------------------- Funções auxiliares --------------------------------
#ifndef max
    #define max(a,b) ((a) > (b) ? (a) : (b))
#endif
bool edb_vazia(edb_t* edb) {
	return edb->raiz == NULL;
}

bool no_folha(no_t* no) {
    return no->esq == NULL && no->dir == NULL;
}

// ---------------------------------------- Funções da árvore de busca -------------------------------------------------

// Aloca e inicia um nó folha
no_t* arv_cria(valor_t valor) {
    no_t* novo = malloc(sizeof(no_t));
    novo->valor = valor;
    novo->dir = NULL;
    novo->esq = NULL;
    novo->altura = 0;

    return novo;
}

// Retorna true se o nó é uma árvore vazia, e false, caso contrário
bool arv_vazia(no_t* no) {
    return no == NULL;
}


int altura(no_t *no)
{
    if (arv_vazia(no)) return 0;
    return no->altura;
}

void calcula_altura(no_t *no)
{
    int alt_esq = altura(no->esq);
    int alt_dir = altura(no->dir);
    no->altura = max(alt_esq, alt_dir) + 1;
}

int fator_balanceamento(no_t* no) {
    return altura(no->esq) - altura(no->dir);
}

no_t* rotacao_esquerda(no_t* x)
{
    no_t *y = x->esq;
    no_t *b = y->dir;

    x->esq = b;
    y->dir = x;

    calcula_altura(x);
    calcula_altura(y);

    return y;
}

no_t* rotacao_direita(no_t* x)
{
    no_t *y = x->dir;
    no_t *b = y->esq;

    x->dir = b;
    y->esq = x;

    calcula_altura(x);
    calcula_altura(y);

    return y;
}

no_t* rotacao_dupla_esquerda(no_t* no)
{
    no->esq = rotacao_direita(no->esq);
    return rotacao_esquerda(no);
}

no_t* rotacao_dupla_direita(no_t* no)
{
    no->dir = rotacao_esquerda(no->dir);
    return rotacao_direita(no);
}

// Reequilibra a árvore usando o fator de balanceamento (FB) a partir de um nó
no_t* arv_equilibra(no_t* no) {
    if(arv_vazia(no)) return no;

    calcula_altura(no);

    int fb = fator_balanceamento(no);
    if(abs(fb) <= 1) return no; // Nó já está balanceado

    if (fb > 1) {
        if (fator_balanceamento(no->esq) <= -1) {
            return rotacao_dupla_esquerda(no);
        }
        return rotacao_esquerda(no);
    }else {
        if (fator_balanceamento(no->dir) >= 1) {
            return rotacao_dupla_direita(no);
        }
        return rotacao_direita(no);
    }
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

// Retorna o ponteiro para o nó mais à direita a partir de outro nó
no_t* maior_no(no_t* no) {
    no_t* prox = no->dir;
    if(prox == NULL) return no;

    return maior_no(prox);
}

// Retorna o ponteiro para o nó mais à esquerda a partir de outro nó
no_t* menor_no(no_t* no) {
    no_t* prox = no->esq;
    if(prox == NULL) return no;

    return menor_no(prox);
}

// Insere um valor na árvore, respeitando a hierarquia e retorna um ponteiro para o nó inserido
no_t* arv_insere(no_t* no, chave_t chave, valor_t valor) {
    if(arv_vazia(no)){
        no = arv_cria(valor);
        return no;
    }

    int comp = compara_chave_valor(chave, no->valor);
    if(comp == 0) { // Substitui o valor do nó atual
        no->valor = valor;
    }else if(comp < 0) {
        no->esq = arv_insere(no->esq, chave, valor);
    }else {
        no->dir = arv_insere(no->dir, chave, valor);
    }

    return arv_equilibra(no);
}

// Encontra e remove um nó e reestrutura a árvore (com balanceamento AVL)
no_t* arv_remove(no_t* no, chave_t chave) {
    if(arv_vazia(no)) {
        return NULL;
    }
    int comp = compara_chave_valor(chave, no->valor);
    if(comp == 0) {
        if(no_folha(no)) {
            free(no);
            no = NULL;
        }else {
            if(!arv_vazia(no->esq)) {
                // Encontra o nó substituto (maior da sub-árvore esquerda)
                no_t* substituto = maior_no(no->esq);

                // Troca o valor do substituto com o nó vítima (a ser removido)
                valor_t aux = no->valor;
                no->valor = substituto->valor;
                substituto->valor = aux;

                // Continua a remoção recursivamente
                arv_remove(no->esq, chave);
            }else {
                // Encontra o nó substituto (menor da sub-árvore direita)
                no_t* substituto = menor_no(no->dir);

                // Troca o valor do substituto com o nó vítima (a ser removido)
                valor_t aux = no->valor;
                no->valor = substituto->valor;
                substituto->valor = aux;

                // Continua a remoção recursivamente
                arv_remove(no->dir, chave);
            }
        }
    }else if(comp < 0) {
        no->esq = arv_remove(no->esq, chave);
    }else {
        no->dir = arv_remove(no->dir, chave);
    }

    return arv_equilibra(no);
}

// Percurso em profundidade com pré-visita à esquerda
void arv_imprime(no_t* no, int tabs) {
    if(no == NULL) return;

    printf("%*s", tabs * 5, "");
    imprime_valor(no->valor);

    arv_imprime(no->dir, tabs+1);
    arv_imprime(no->esq, tabs+1);
}

// -------------------------------- Funções da interface do TAD --------------------------------

edb_t *edb_cria(void) {
	edb_t* edb = malloc(sizeof(edb_t));
	edb->raiz = NULL;

	return edb;
}

void edb_destroi(edb_t *edb) {
    arv_destroi(edb->raiz);
    free(edb);
}

// Insere o valor associado à chave
void edb_insere(edb_t *edb, chave_t chave, valor_t valor) {
    edb->raiz = arv_insere(edb->raiz, chave, valor);
}

// Remove o valor associado à chave
void edb_remove(edb_t *edb, chave_t chave) {
    edb->raiz = arv_remove(edb->raiz, chave);
};

// Retorna (por ref.) o valor associado a chave (e true) ou nao (false)
bool edb_busca(edb_t *edb, chave_t chave, valor_t *pvalor) {

    if(edb_vazia(edb)) return false;

    no_t* encontrado = arv_busca(edb->raiz, chave);
    
    if(encontrado == NULL) return false;

    *pvalor = encontrado->valor;
    return true;
}

// Imprime a árvore usada pela estrutura de busca
void edb_arv_imprime(edb_t* edb) {
    no_t* raiz = edb->raiz;

    arv_imprime(raiz, 0);
}