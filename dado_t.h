#ifndef _DADO_T_H_
    #define _DADO_T_H_

    #include <stdbool.h>

    typedef struct {
        bool eh_operador;
        char operador;
        float numero;
    } dado_t;

    // Imprime o conteúdo de um dado_t
    void imprime_dado(dado_t dado);
#endif