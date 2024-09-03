#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Pilha.h"

// Função para calcular a expressão em notação polonesa reversa
float rpn(char *sequencia){
    PILHA *pilha = pilha_criar(); // Cria nova pilha
    if (pilha == NULL) {
        printf("Erro ao criar pilha!\n");
        return -1; 
    }

    for(int i = 0; sequencia[i] != '\0'; i++){ // Itera sobre cada caractere da sequência
        char digito = sequencia[i]; // Caractere atual

        if(digito >= '0' && digito <= '9'){ // Se o caractere é um dígito 
            float *num = (float *)malloc(sizeof(float));
            if (num == NULL){
                printf("Erro na alocação de memória para número.\n");
                pilha_apagar(&pilha); 
                return -1; 
            }
            *num = (float)(digito - '0'); // Converte o dígito para float e armazena
            ITEM *item = item_criar(0, (void*)num); // Cria um item para o número
            if (item == NULL) {
                printf("Erro ao criar item para número.\n");
                free(num); 
                pilha_apagar(&pilha); 
                return -1; 
            }
            pilha_empilhar(pilha, item); // Empilha o item na pilha

        } else { // Se o caractere é um operador
            if(digito == '+' || digito == '-' || digito == '/' || digito == '*'){ 
                if (pilha_vazia(pilha)) { // Verificar se a pilha tem pelo menos dois elementos
                    printf("Erro: pilha vazia antes do operador!\n");
                    pilha_apagar(&pilha);
                    return -1; 
                }

                ITEM *op2 = pilha_desempilhar(pilha); // Desempilha o segundo operando
                if (op2 == NULL) {
                    printf("Erro ao desempilhar o segundo operando!\n");
                    pilha_apagar(&pilha);
                    return -1; 
                }
                float *op2_comp = (float*)item_get_dados(op2); // OBtém o dado do item
                free(op2); 

                if (pilha_vazia(pilha)) { // Verificar se a pilha tem pelo menos um elemento
                    printf("Erro: pilha vazia antes de processar o operador!\n");
                    pilha_apagar(&pilha);
                    return -1; 
                }

                ITEM *op1 = pilha_desempilhar(pilha); // Desempilha o primeiro operando
                if (op1 == NULL) { 
                    printf("Erro ao desempilhar o primeiro operando!\n");
                    pilha_apagar(&pilha);
                    return -1; 
                }
                float *op1_comp = (float*)item_get_dados(op1); // OBtém o dado do item
                free(op1); 

                float resultado; // Armazenar o resultado da operação
                switch(digito){ // Realizar as operações
                    case '+':
                        resultado = *op1_comp + *op2_comp;
                        break;
                    case '-':
                        resultado = *op1_comp - *op2_comp;
                        break;
                    case '*':
                        resultado = *op1_comp * *op2_comp;
                        break;
                    case '/':
                        if(*op2_comp == 0){
                            printf("Erro: Divisao invalida\n");
                            free(op1_comp);
                            free(op2_comp);
                            pilha_apagar(&pilha);
                            return -1; 
                        }
                        resultado = *op1_comp / *op2_comp;
                        break;
                }
                free(op1_comp); 
                free(op2_comp);

                float *resultado_temp = (float*)malloc(sizeof(float)); 
                if(resultado_temp == NULL){
                    printf("Erro na alocacao de memoria para resultado!\n");
                    pilha_apagar(&pilha);
                    return -1; 
                }
                *resultado_temp = resultado; // Armazena o resultado
                ITEM *item_resultado = item_criar(0, (void*)resultado_temp); // Item para o resultado
                if(item_resultado == NULL){
                    printf("Erro ao criar item para o resultado!\n");
                    free(resultado_temp);
                    pilha_apagar(&pilha);
                    return -1; 
                }
                pilha_empilhar(pilha, item_resultado); // Empilha o resultado na pilha
            }
        }
    }

    if (pilha_vazia(pilha)) { // Verificar se a pilha contém um item
        printf("Erro: Pilha vazia após processamento!\n");
        pilha_apagar(&pilha);
        return -1; 
    }

    ITEM *resultado_item = pilha_desempilhar(pilha); // DEsempilha o resultado final
    if (resultado_item == NULL) {
        printf("Erro ao desempilhar o resultado final!\n");
        pilha_apagar(&pilha);
        return -1; 
    }

    float *resultado = (float*)item_get_dados(resultado_item); // Obtem o resultado
    float valor_final = *resultado;

    free(resultado);
    pilha_apagar(&pilha);

    return valor_final; // REtorna o valor final
}
