#ifndef _TIPOS_H_
#define _TIPOS_H_

typedef struct valor valor_t;
struct valor {
  char nome[16];
  int nota1;
  int nota2;
};

typedef char *chave_t;

// função para comparar uma chave e um valor -- retorna:
// =0 - se chave corresponde ao valor
// <0 - se chave corresponde a valor que deve estar antes do valor 
// >0 - se chave corresponde a valor que deve estar depois do valor 
int compara_chave_valor(chave_t chave, valor_t valor);

#endif // _TIPOS_H_
