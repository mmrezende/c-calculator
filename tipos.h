#ifndef _TIPOS_H_
#define _TIPOS_H_

typedef struct valor valor_t;
struct valor {
  char nome[16];
  int nota1;
  int nota2;
};

typedef char *chave_t;

/** Função para comparar dois valores -- retorna:
  =0 - se são iguais
  <0 - se chave corresponde a valor que deve estar antes do valor 
  >0 - se chave corresponde a valor que deve estar depois do valor */
int compara_chave_valor(chave_t chave, valor_t valor);

void imprime_valor(valor_t valor);

#endif // _TIPOS_H_
