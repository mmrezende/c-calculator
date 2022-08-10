#ifndef _TIPOS_H_
#define _TIPOS_H_

typedef double valor_t;
typedef char* chave_t;

enum TIPOS {OPERADOR, NUMERO, VARIAVEL};

typedef struct {
    TIPOS tipo;
    char operador;
    valor_t numero;
    chave_t variavel;
} dado_t;

// Imprime o conteúdo de um dado_t
void imprime_dado(dado_t dado);

// Imprime o conteúdo de um valor_t
void imprime_valor(valor_t valor);

/**
 * Função para comparar dois valores, que retorna:
 * =0 - se são iguais
 * <0 - se chave corresponde a valor que deve estar antes do valor
 * >0 - se chave corresponde a valor que deve estar depois do valor
 */
int compara_chave_valor(chave_t chave, valor_t valor);

#endif // _TIPOS_H_
