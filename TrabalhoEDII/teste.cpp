#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura do nó da pilha
typedef struct PilhaMemoria {
    char variavel[10];
    float valor;
    struct PilhaMemoria *prox;
} PilhaM;

// Definição da estrutura do nó da fila
typedef struct FilaNode {
    char funcao[20];
    struct FilaNode *prox;
} FilaNode;

// Definição da estrutura da fila
typedef struct Fila {
    FilaNode *frente, *tras;
} Fila;

// Função para inicializar a pilha
void initPilha(PilhaM **topo) {
    *topo = NULL;
}

// Função para inicializar a fila
void initFila(Fila *fila) {
    fila->frente = fila->tras = NULL;
}

// Função para verificar se a pilha está vazia
int isEmptyPilha(PilhaM *topo) {
    return topo == NULL;
}

// Função para verificar se a fila está vazia
int isEmptyFila(Fila *fila) {
    return fila->frente == NULL;
}

// Função para adicionar um nó no topo da pilha
void pushPilha(PilhaM **topo, char variavel[], float valor) {
    PilhaM *novo = (PilhaM*)malloc(sizeof(PilhaM));
    strcpy(novo->variavel, variavel);
    novo->valor = valor;
    novo->prox = *topo;
    *topo = novo;
}

// Função para remover o nó do topo da pilha
void popPilha(PilhaM **topo) {
    if (isEmptyPilha(*topo)) {
        printf("Pilha está vazia\n");
        return;
    }
    PilhaM *temp = *topo;
    *topo = (*topo)->prox;
    free(temp);
}

// Função para adicionar um nó no final da fila
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

// Função para remover o nó da frente da fila
void dequeueFila(Fila *fila) {
    if (isEmptyFila(fila)) {
        printf("Fila está vazia\n");
        return;
    }
    FilaNode *temp = fila->frente;
    fila->frente = fila->frente->prox;
    if (fila->frente == NULL) {
        fila->tras = NULL;
    }
    free(temp);
}

// Função para ler o programa e armazenar as variáveis na pilha
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
            // Processar a função e retornar o valor
            // Aqui você pode adicionar o código para calcular o valor da função
            // e armazenar o resultado na variável apropriada
            dequeueFila(&fila);
        }
    }
}

// Função principal para testar o código
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
