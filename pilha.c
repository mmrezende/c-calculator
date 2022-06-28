#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"

typedef struct no no_t;

struct no {
    dado_t dado;
    no_t* prox;
};

struct pilha {
    no_t* prim;
};

// cria uma pilha vazia, retorna um ponteiro para ela
pilha_t* pilha_cria(void) {
    pilha_t* nova_pilha = malloc(sizeof(pilha_t));
    nova_pilha->prim = NULL;

    return nova_pilha;
}

// destroi a pilha p (libera a memória ocupada por ela)
void pilha_destroi(pilha_t *p){
    while(!pilha_vazia(p)) {
        pilha_remove(p);
    }
    
    free(p);
}

// retorna true se a pilha p não contiver nenhum dado
bool pilha_vazia(pilha_t *p){
    return(p->prim == NULL);
}

// empilha o dado d no topo da pilha p
void pilha_insere(pilha_t *p, dado_t d){
    no_t* novo = malloc(sizeof(no_t));
    
    // Novo dado se torna o primeiro
    novo->dado = d;
    novo->prox = p->prim;
    p->prim = novo;
}

// remove e retorna o dado no topo da pilha p aborta com erro brabo se a pilha estiver vazia
dado_t pilha_remove(pilha_t *p){
    if(pilha_vazia(p)){
        printf("\nErro: Tentativa de remoção em pilha vazia\n");
        exit(EXIT_FAILURE);
    }

    no_t* vitima = p->prim;
    dado_t removido = vitima->dado;

    p->prim = vitima->prox;
    free(vitima);

    return removido;   
}

// retorna o dado no topo da pilha p, sem removê-lo aborta com erro brabo se a pilha estiver vazia
dado_t pilha_topo(pilha_t *p){
    if(pilha_vazia(p)){
        printf("\nErro: Tentativa de leitura em pilha vazia\n");
        exit(EXIT_FAILURE);
    }

    return p->prim->dado;
}

void pilha_imprime(pilha_t *p) {
    if(pilha_vazia(p)) {
        printf("\n");
    }

    no_t* atual = p->prim;
    while(atual != NULL) {
        imprime_dado(atual->dado);
        atual = atual->prox;
    }
    printf("\n");
}