#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "pilha.h"

#define TAMANHO_MAXIMO 255

pilha_t* operacoes;
pilha_t* numeros;

bool eh_operador(char c) {
    const char operadores[] = "+-*/^()";

    return strchr(operadores, c) != NULL;
}

bool eh_algarismo(char c) {
    const char algarismos[] = "0123456789.";

    return strchr(algarismos, c) != NULL;
}

int prescedencia_operador(char c) {
    switch(c) {
        case '+': case '-':
            return 0;
        case '*': case '/':
            return 1;
        case '^': 
            return 2;
        default:
            return -1;
    }
}

bool prescede(char c1, char c2) {
    return prescedencia_operador(c1) > prescedencia_operador(c2);
}

void mensagem_erro() {
    printf("\nErro: Expressão mal-formada\n");
    exit(EXIT_FAILURE);
}

void opera(char op) {
    if(op == '(' || op == ')') {
        printf("\nAtenção! Esqueceu de fechar parênteses\n");
        return;
    }

    // printf("\nOperação realizada (%c): ", op);

    float n1, n2;
    dado_t res;
    
    if(!pilha_vazia(numeros)) {
        n2 = pilha_remove(numeros).numero;
    }else mensagem_erro();

    if(!pilha_vazia(numeros)) {
        n1 = pilha_remove(numeros).numero;
    }else mensagem_erro();

    // printf("%f e %f", n1, n2);

    switch (op) {
        case '+':
            res.numero = n1 + n2;
            break;
        case '-':
            res.numero = n1 - n2;
            break;
        case '*':
            res.numero = n1 * n2;
            break;
        case '/':
            res.numero = n1 / n2;
            break;
        case '^':
            res.numero = pow(n1,n2);
            break;
    }

    // printf(" = %f\n", res.numero);

    pilha_insere(numeros, res);
}

void fecha_parenteses() {
    char op;
    while (!pilha_vazia(operacoes) && pilha_topo(operacoes).operador != '(') {
        op = pilha_remove(operacoes).operador;
        opera(op);
    };

    if(pilha_vazia(operacoes)) {
        mensagem_erro();
    }

    pilha_remove(operacoes);
}

float encerra_expressao() {
    while (!pilha_vazia(operacoes)) {
        opera(pilha_remove(operacoes).operador);
    }

    return pilha_topo(numeros).numero;
}

void gerencia_operador(dado_t op) {
    if(op.operador == '(') {
        pilha_insere(operacoes, op);
        return;
    }
    
    if(op.operador == ')') {
        fecha_parenteses();
        return;
    }

    if(!pilha_vazia(operacoes)) {
        if(!prescede(op.operador, pilha_topo(operacoes).operador)) {
            opera(pilha_remove(operacoes).operador);
        }
        pilha_insere(operacoes, op);
    }else {
        pilha_insere(operacoes, op);
    }
}

int main(void) {
    // Leitura da expressão
    char expressao[TAMANHO_MAXIMO];
    printf("\nInsira a expressão a ser calculada: ");
    fgets(expressao, sizeof(expressao), stdin);

    // Interpretação de cada token
    operacoes = pilha_cria();
    numeros = pilha_cria();
    
    for(int c=0; expressao[c] != '\0'; c++) {
        int primeiro_algarismo;
        dado_t atual;
        atual.operador = expressao[c];
        char algarismos[TAMANHO_MAXIMO];

        if(eh_operador(atual.operador)) {
            gerencia_operador(atual);
        }else if(eh_algarismo(atual.operador)) {
            if(c==0 || !eh_algarismo(expressao[c-1])) {
                primeiro_algarismo = c;
            }

            if(!eh_algarismo(expressao[c+1])) {
                // Lê os algarismos do número atual os armazena
                strncpy(algarismos, expressao + primeiro_algarismo, c - primeiro_algarismo + 1);
                atual.numero = atof(algarismos);

                pilha_insere(numeros, atual);

                // Limpa o array
                memset(algarismos, 0, sizeof algarismos);
            }
        }
    }

    printf("\nResposta: %f\n", encerra_expressao());

    // Libera memória alocada para as pilhas
    pilha_destroi(operacoes);
    pilha_destroi(numeros);

    return EXIT_SUCCESS;
}