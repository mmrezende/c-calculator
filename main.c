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
#define OPERADORES "+-*/()^="
#define ALGARISMOS "0123456789."
#define CARACTERES "abcdefghijklmnopqrstuvwxyz"

void erro(char* mensagem) {
    printf("Erro: %s\n", mensagem);
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
                atomo.variavel = strdup(buffer);

                fila_insere(atomos, atomo);
                lendo_variavel = false;
            }else if(lendo_numero) {
                atomo.tipo = NUMERO;
                atomo.numero = atof(buffer);

                fila_insere(atomos, atomo);
                lendo_numero = false;
            }

            atomo.tipo = OPERADOR;
            atomo.operador = *c;
            buffer[0] = '\0';
            fila_insere(atomos, atomo);
        }else if(isalpha(*c) != 0 || (lendo_variavel && (isalnum(*c) || *c == '_'))) {
            if(lendo_numero) {
                erro("Falta de operador");
            }
            lendo_variavel = true;
            strncat(buffer, c, 1);
        }else if(strchr(ALGARISMOS, *c) != NULL){
            if(lendo_variavel) {
                erro("Falta de operador");
            }
            lendo_numero = true;
            strncat(buffer, c, 1);
        }
    }

    // Insere o conteúdo do buffer, caso esteja sendo lido
    if(lendo_variavel){
        atomo.tipo = VARIAVEL;
        atomo.variavel = strdup(buffer);

        fila_insere(atomos, atomo);
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

// Gerencia o acesso, obtenção e conversão de uma variável para um número qualquer
dado_t resolve_operando(dado_t operando, edb_t* variaveis) {
    if(operando.tipo == NUMERO) {
        return operando;
    }

    valor_t aux;
    aux.variavel = operando.variavel;
//    printf("Buscando variável: %s\n", operando.variavel);
    if(!edb_busca(variaveis, operando.variavel, &aux)) {
        erro("Variável não definida");
    }

    dado_t encontrado;
    encontrado.tipo = NUMERO;
    encontrado.numero = aux.numero;
    return encontrado;
}

void opera(char op, pilha_t* operandos, edb_t* variaveis) {
    double n2,n1;
    dado_t resultado;
    resultado.tipo = NUMERO;

    if(pilha_vazia(operandos)) {
        erro("Falta de operandos");
    }
    n2 = resolve_operando(pilha_remove(operandos), variaveis).numero;

    if(pilha_vazia(operandos)) {
        erro("Falta de operandos");
    }
    dado_t d1 = pilha_remove(operandos);

    if(op == '=') {
        if (d1.tipo != VARIAVEL) {
            erro("Atribuição só é permitida para variáveis (ex: x = 23 + 2*b)");
        }

        resultado.numero = n2;
        valor_t aux;
        aux.numero = n2;
        aux.variavel = d1.variavel;

//        printf("Atribuindo valor: %lf à variável: %s\n", n2, d1.variavel);
        edb_insere(variaveis, d1.variavel, aux);

        pilha_insere(operandos, resultado);
        return;
    }

    n1 = resolve_operando(d1, variaveis).numero;

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

    pilha_insere(operandos, resultado);
}

// Retorna true caso a entrada tenha precedência sobre o operador da pilha
bool precede(char entrada, char pilha) {
    if(pilha == '(' || pilha == '=') {
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
dado_t calcula(char* exp, edb_t* variaveis) {
    fila_t* expressao = processa_expressao(exp);
    pilha_t* operadores = pilha_cria();
    pilha_t* operandos = pilha_cria();

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
                    opera(operador, operandos, variaveis);
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
                    opera(operador, operandos, variaveis);
                }
                break;
            default:
                while(!pilha_vazia(operadores) && !precede(atomo.operador, pilha_topo(operadores).operador)) {
                    operador = pilha_remove(operadores).operador;
                    opera(operador, operandos, variaveis);
                }
                pilha_insere(operadores, atomo);
                break;
            }
        }else {
            pilha_insere(operandos, atomo);
        }
    }
    
    if(pilha_vazia(operandos)) {
        erro("Falta de operandos");
    }

    dado_t resultado = resolve_operando(pilha_remove(operandos), variaveis);

    if(!pilha_vazia(operandos)) {
        erro("Falta de operadores");
    }

    fila_destroi(expressao);
    pilha_destroi(operandos);
    pilha_destroi(operadores);

    return resultado;
}

void calculadora_inicia() {
    char entrada[TAMANHO_MAXIMO];
    edb_t* variaveis = edb_cria();

    while(true) {
        printf("Digite a expressão desejada (fim para encerrar): ");
        fgets(entrada, sizeof(entrada) - 1, stdin);

        if(strcmp(entrada,"fim\n") == 0) break;

        dado_t resultado = calcula(entrada, variaveis);

        printf("\nResultado: ");
        imprime_dado(resultado);
        printf("\n");
    }

    edb_destroi(variaveis);
}

int main() {
    calculadora_inicia();
    return EXIT_SUCCESS;
}