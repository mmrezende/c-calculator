#include <stdlib.h>
#include <stdio.h>
#include "fila.h"

typedef struct no no_t;

struct no {
    dado_t dado;
    no_t* prox;
};

struct fila {
    no_t* ult;
};

// cria uma fila vazia, retorna um ponteiro para ela
fila_t* fila_cria(void) {
    fila_t* nova_fila = malloc(sizeof(fila_t));
    nova_fila->ult = NULL;

    return nova_fila;
}

// destroi a fila f (libera a memória ocupada por ela)
void fila_destroi(fila_t *f){
    while(!fila_vazia(f)) {
        fila_remove(f);
    }
    
    free(f);
}

// retorna true se a fila f não contiver nenhum dado
bool fila_vazia(fila_t *f){
    return(f->ult == NULL);
}

// coloca o dado d no final da fila f
void fila_insere(fila_t *f, dado_t d){
    no_t* novo = malloc(sizeof(no_t));

    // Novo dado se torna o último
    novo->dado = d;
    if(fila_vazia(f)) {
        novo->prox = novo;
    }else {
        novo->prox = f->ult->prox;
        f->ult->prox = novo;
    }
    
    f->ult = novo;
}

// remove e retorna o dado no topo da fila f aborta com erro brabo se a fila estiver vazia
dado_t fila_remove(fila_t *f){
    if(fila_vazia(f)){
        printf("\nErro: Tentativa de remoção em fila vazia\n");
        exit(EXIT_FAILURE);
    }

    no_t* vitima = f->ult->prox;
    dado_t removido = vitima->dado;
    if(vitima == f->ult) {
        f->ult = NULL;
    }else {
        f->ult->prox = vitima->prox;
    }

    free(vitima);

    return removido;
}

// retorna o dado no topo da fila p, sem removê-lo aborta com erro brabo se a fila estiver vazia
dado_t fila_proximo(fila_t *p){
    if(fila_vazia(p)){
        printf("\nErro: Tentativa de leitura em fila vazia\n");
        exit(EXIT_FAILURE);
    }

    return p->ult->prox->dado;
}

void fila_imprime(fila_t *f) {
    if(fila_vazia(f)) {
        printf("\n");
    }
    no_t* atual = f->ult;
    do {
        atual = atual->prox;
        printf("%f ",atual->dado);
    }while(atual != f->ult);
    printf("\n");
}