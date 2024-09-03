#include "item.h"
#include <stdbool.h>
#include <stdlib.h>

#define TAM 1005

typedef struct pilha {
    ITEM *item[TAM];
    int tam;
} PILHA;

PILHA *pilha_criar(void) {
    PILHA *pilha = (PILHA *)malloc(sizeof(PILHA));
    if (pilha) {
        pilha->tam = 0;
        return pilha;
    }
    return NULL;
}

void pilha_apagar(PILHA **pilha) {
    if (pilha && *pilha) {
        free(*pilha);
        *pilha = NULL;
    }
}

bool pilha_vazia(PILHA *pilha) {
    return pilha && pilha->tam == 0;
}

bool pilha_cheia(PILHA *pilha) {
    return pilha && pilha->tam == TAM;
}

int pilha_tamanho(PILHA *pilha) {
    return pilha ? pilha->tam : -1;
}

ITEM *pilha_topo(PILHA *pilha) {
    if (pilha && !pilha_vazia(pilha)) {
        return pilha->item[pilha->tam - 1];
    }
    return NULL;
}

bool pilha_empilhar(PILHA *pilha, ITEM *item) {
    if (pilha && !pilha_cheia(pilha)) {
        pilha->item[pilha->tam] = item;
        pilha->tam++;
        return true;
    }
    return false;
}

ITEM *pilha_desempilhar(PILHA *pilha) {
    if (pilha && !pilha_vazia(pilha)) {
        ITEM *item = pilha_topo(pilha);
        pilha->tam--;
        return item;
    }
    return NULL;
}
