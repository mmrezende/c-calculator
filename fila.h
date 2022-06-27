#ifndef _FILA_H_
    #define _FILA_H_

    #include "dado_t.h"  // para a definição de dado_t

    #include <stdbool.h>

    // o tipo de dados que representa uma fila
    typedef struct fila fila_t;

    // cria uma fila vazia, retorna um ponteiro para ela
    fila_t *fila_cria(void);

    // destroi a fila f (libera a memória ocupada por ela)
    void fila_destroi(fila_t *f);

    // retorna true se a fila f não contiver nenhum dado
    bool fila_vazia(fila_t *f);

    // insere o dado d na fila f
    void fila_insere(fila_t *f, dado_t d);

    // remove e retorna o próximo dado da fila f; aborta com erro brabo se a fila estiver vazia
    dado_t fila_remove(fila_t *f);

    // retorna o próximo dado da fila f, sem removê-lo; aborta com erro brabo se a fila estiver vazia
    dado_t fila_proximo(fila_t *f);
#endif