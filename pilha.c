#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"

typedef struct no_t no_t;

struct no_t {
    dado_t dado;
    no_t* prox;
};

struct pilha_t {
    int tamanho;
    no_t* sent;
};

// cria uma pilha vazia, retorna um ponteiro para ela
pilha_t* pilha_cria(void) {
    pilha_t* nova_pilha = malloc(sizeof(pilha_t));
    nova_pilha->tamanho = 0;

    no_t* sent = malloc(sizeof(no_t));
    sent->prox = sent;

    nova_pilha->sent = sent;

    return nova_pilha;
}

// destroi a pilha p (libera a memória ocupada por ela)
void pilha_destroi(pilha_t *p){
    while(!pilha_vazia(p)) {
        pilha_remove(p);
    }
    
    free(p->sent);
    free(p);
}

// retorna true se a pilha p não contiver nenhum dado
bool pilha_vazia(pilha_t *p){
    return(p->tamanho == 0);
}

// empilha o dado d no topo da pilha p
void pilha_insere(pilha_t *p, dado_t d){
    no_t* novo = malloc(sizeof(no_t));
    
    // Insere o dado após o sentinela e antes do topo da pilha
    novo->dado = d;
    novo->prox = p->sent->prox;
    p->sent->prox = novo;

    p->tamanho++;
}

// remove e retorna o dado no topo da pilha p aborta com erro brabo se a pilha estiver vazia
dado_t pilha_remove(pilha_t *p){
    if(p->tamanho == 0){
        printf("\nErro: Tentativa de remoção em pilha vazia\n");
        exit(EXIT_FAILURE);
    }

    no_t* vitima = p->sent->prox;
    dado_t removido = vitima->dado;

    p->sent->prox = vitima->prox;
    free(vitima);

    p->tamanho--;

    return removido;   
}

// retorna o dado no topo da pilha p, sem removê-lo aborta com erro brabo se a pilha estiver vazia
dado_t pilha_topo(pilha_t *p){
    if(p->tamanho == 0){
        printf("\nErro: Tentativa de remoção em pilha vazia\n");
        exit(EXIT_FAILURE);
    }

    return p->sent->prox->dado;
}