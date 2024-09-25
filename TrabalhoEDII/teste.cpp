#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defini��o da estrutura do n� da pilha
typedef struct PilhaMemoria {
    char variavel[10];
    float valor;
    struct PilhaMemoria *prox;
} PilhaM;

// Defini��o da estrutura do n� da fila
typedef struct FilaNode {
    char funcao[20];
    struct FilaNode *prox;
} FilaNode;

// Defini��o da estrutura da fila
typedef struct Fila {
    FilaNode *frente, *tras;
} Fila;

// Fun��o para inicializar a pilha
void initPilha(PilhaM **topo) {
    *topo = NULL;
}

// Fun��o para inicializar a fila
void initFila(Fila *fila) {
    fila->frente = fila->tras = NULL;
}

// Fun��o para verificar se a pilha est� vazia
int isEmptyPilha(PilhaM *topo) {
    return topo == NULL;
}

// Fun��o para verificar se a fila est� vazia
int isEmptyFila(Fila *fila) {
    return fila->frente == NULL;
}

// Fun��o para adicionar um n� no topo da pilha
void pushPilha(PilhaM **topo, char variavel[], float valor) {
    PilhaM *novo = (PilhaM*)malloc(sizeof(PilhaM));
    strcpy(novo->variavel, variavel);
    novo->valor = valor;
    novo->prox = *topo;
    *topo = novo;
}

// Fun��o para remover o n� do topo da pilha
void popPilha(PilhaM **topo) {
    if (isEmptyPilha(*topo)) {
        printf("Pilha est� vazia\n");
        return;
    }
    PilhaM *temp = *topo;
    *topo = (*topo)->prox;
    free(temp);
}

// Fun��o para adicionar um n� no final da fila
void enqueueFila(Fila *fila, char funcao[]) {
    FilaNode *novo = (FilaNode*)malloc(sizeof(FilaNode));
    strcpy(novo->funcao, funcao);
    novo->prox = NULL;
    if (isEmptyFila(fila)) {
        fila->frente = fila->tras = novo;
    } else {
        fila->tras->prox = novo;
        fila->tras = novo;
    }
}

// Fun��o para remover o n� da frente da fila
void dequeueFila(Fila *fila) {
    if (isEmptyFila(fila)) {
        printf("Fila est� vazia\n");
        return;
    }
    FilaNode *temp = fila->frente;
    fila->frente = fila->frente->prox;
    if (fila->frente == NULL) {
        fila->tras = NULL;
    }
    free(temp);
}

// Fun��o para ler o programa e armazenar as vari�veis na pilha
void processaPrograma(char *programa[], int tamanho) {
    PilhaM *pilha;
    Fila fila;
    initPilha(&pilha);
    initFila(&fila);

    for (int i = 0; i < tamanho; i++) {
        if (strstr(programa[i], "var") != NULL) {
            char variavel[10];
            float valor;
            sscanf(programa[i], "var %s = %f", variavel, &valor);
            pushPilha(&pilha, variavel, valor);
        } else if (strstr(programa[i], "func") != NULL) {
            char funcao[20];
            sscanf(programa[i], "func %s", funcao);
            enqueueFila(&fila, funcao);
        } else if (strstr(programa[i], "end-func") != NULL) {
            // Processar a fun��o e retornar o valor
            // Aqui voc� pode adicionar o c�digo para calcular o valor da fun��o
            // e armazenar o resultado na vari�vel apropriada
            dequeueFila(&fila);
        }
    }
}

// Fun��o principal para testar o c�digo
int main() {
    char *programa[] = {
        "var x = 10",
        "var y = 20",
        "func soma",
        "var z = x + y",
        "end-func",
        "var resultado = soma"
    };
    int tamanho = sizeof(programa) / sizeof(programa[0]);

    processaPrograma(programa, tamanho);

    return 0;
}
