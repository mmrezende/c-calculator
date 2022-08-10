#ifndef _PILHA_H_
    #define _PILHA_H_

    #include <stdbool.h>

    #include "tipos.h"  // para a definição de dado_t

    // o tipo de dados que representa uma pilha
    typedef struct pilha pilha_t;

    // cria uma pilha vazia, retorna um ponteiro para ela
    pilha_t *pilha_cria(void);

    // destroi a pilha p (libera a memória ocupada por ela)
    void pilha_destroi(pilha_t *p);

    // retorna true se a pilha p não contiver nenhum dado
    bool pilha_vazia(pilha_t *p);

    // empilha o dado d no topo da pilha p
    void pilha_insere(pilha_t *p, dado_t d);

    // remove e retorna o dado no topo da pilha p; aborta com erro brabo se a pilha estiver vazia
    dado_t pilha_remove(pilha_t *p);

    // retorna o dado no topo da pilha p, sem removê-lo; aborta com erro brabo se a pilha estiver vazia
    dado_t pilha_topo(pilha_t *p);

    // imprime todo o conteúdo da pilha p
    void pilha_imprime(pilha_t *p);
#endif