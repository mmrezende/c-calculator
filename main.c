#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "tipos.h"
#include "pilha.h"
#include "fila.h"
#include "edb.h"

#define TAMANHO_MAXIMO 255
#define OPERADORES "+-*/()^\0="
#define ALGARISMOS "0123456789."
#define CARACTERES "abcdefghijklmnopqrstuvwxyz"

void erro(char* mensagem) {
    printf("Erro: ");
    printf(mensagem);
    printf("\n");
    exit(EXIT_FAILURE);
}

fila_t* processa_expressao(char* exp) {
    fila_t* atomos = fila_cria();
    dado_t atomo;

    bool lendo_numero = false;
    bool lendo_variavel = false;

    char buffer[TAMANHO_MAXIMO];
    buffer[0] = '\0';

    for(char* c = exp; *c != '\0'; c++) {
        if(strchr(OPERADORES, *c) != NULL) {
            if(lendo_variavel){
                atomo.tipo = VARIAVEL;
                strcpy(atomo.variavel, buffer);
                fila_insere(atomos, atomo);

                lendo_variavel = false;
                buffer[0] = '\0';
            }else if(lendo_numero) {
                atomo.tipo = NUMERO;
                atomo.numero = atof(buffer);
                fila_insere(atomos, atomo);

                lendo_numero = false;
                buffer[0] = '\0';
            }
            atomo.tipo = OPERADOR;
            atomo.operador = *c;
            fila_insere(atomos, atomo);
        }else if(isalpha(*c) != 0 || (lendo_variavel && (strchr(ALGARISMOS, *c) != NULL || *c == '_'))) {
            if(lendo_numero) {
                erro("Falta de operador");
            }
            lendo_variavel = true;
            strcat(buffer, c);
        }else if(strchr(ALGARISMOS, *c) != NULL){
            if(lendo_variavel) {
                erro("Falta de operador");
            }
            lendo_numero = true;
            strcat(buffer, c);
        }
    }

    // Insere o conteúdo do buffer, caso esteja sendo lido
    if(lendo_variavel) {

    }else if(lendo_numero) {
        atomo.tipo = NUMERO;
        atomo.numero = atof(buffer);
        fila_insere(atomos, atomo);
    }

    // Insere o operador de fim de expressão
    atomo.tipo = OPERADOR;
    atomo.operador = '\0';
    fila_insere(atomos, atomo);

    return atomos;
}

void opera(char op, pilha_t* numeros) {
    if(pilha_vazia(numeros)) {
        erro("Falta de operandos");
    }
    double n2 = pilha_remove(numeros).numero;

    if(pilha_vazia(numeros)) {
        erro("Falta de operandos");
    }
    double n1 = pilha_remove(numeros).numero;

    dado_t resultado;
    resultado.tipo = NUMERO;
    switch (op) {
        case '+':
            resultado.numero = n1 + n2;
            break;
        case '-':
            resultado.numero = n1 - n2;
            break;
        case '*':
            resultado.numero = n1 * n2;
            break;
        case '/':
            resultado.numero = n1 / n2;
            break;
        case '^':
            resultado.numero = pow(n1,n2);
            break;
        default:
            printf("%c", op);
            erro("Operador não suportado");
    }

    pilha_insere(numeros, resultado);
}

// Retorna true caso a entrada tenha precedência sobre o operador da pilha
bool precede(char entrada, char pilha) {
    if(pilha == '(') {
        return true;
    }
    switch(entrada) {
        case '^':
            return true;
        case '*': case '/':
            return (pilha == '+') || (pilha == '-');
        default:
            return false;
    }
}

// Lógica da calculadora
dado_t calcula(char* exp) {
    fila_t* expressao = processa_expressao(exp);

    pilha_t* operadores = pilha_cria();
    pilha_t* numeros = pilha_cria();
    edb_t* variaveis = edb_cria();

    while(!fila_vazia(expressao)) {
        dado_t atomo = fila_remove(expressao);
        char operador;
        if(atomo.tipo == OPERADOR) {
            switch (atomo.operador)
            {
            case '(':
                pilha_insere(operadores, atomo);
                break;
            case ')':
                while(!pilha_vazia(operadores)) {
                    operador = pilha_remove(operadores).operador;
                    if(operador == '(') break;
                    opera(operador, numeros);
                }

                if(pilha_vazia(operadores) && operador != '(') {
                    erro("Falta de abertura de parênteses");
                }
                break;
            case '\0':
                while(!pilha_vazia(operadores)) {
                    operador = pilha_remove(operadores).operador;
                    if(operador == '(') {
                        erro("Falta de abertura de parênteses");
                    }
                    opera(operador, numeros);
                }
                break;
            default:
                while(!pilha_vazia(operadores) && !precede(atomo.operador, pilha_topo(operadores).operador)) {
                    operador = pilha_remove(operadores).operador;
                    opera(operador, numeros);
                }
                pilha_insere(operadores, atomo);
                break;
            }
        }else {
            pilha_insere(numeros, atomo);
        }
    }
    
    if(pilha_vazia(numeros)) {
        erro("Falta de operandos");
    }

    dado_t resultado = pilha_remove(numeros);
    
    if(!pilha_vazia(numeros)) {
        erro("Falta de operadores");
    }

    fila_destroi(expressao);
    pilha_destroi(numeros);
    pilha_destroi(operadores);
    edb_destroi(variaveis);

    return resultado;
}

int main() {
    // dado_t resultado = calcula("(1 + (1 + 2 * (3+5))^2)/2");

    // imprime_dado(resultado);
    // printf("\n");

    char entrada[TAMANHO_MAXIMO];

    printf("Digite a expressão desejada: ");
    fgets(entrada, sizeof(entrada), stdin);
    dado_t resultado = calcula(entrada);

    printf("\n");
    imprime_dado(resultado);
    printf("\n");

    return EXIT_SUCCESS;
}