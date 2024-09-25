
struct TpCode {
	char token[15];
	struct TpCode *prox;
}; typedef struct TpCode TpCode;

struct TpLista {
	struct TpLista *prox, *ant;
	TpCode *tokens;
}; typedef struct TpLista TpLista;

union TpInfo {
    float valor;
    char operacao[3];
    char funcao[20];
};

struct listagen {
    char terminal;
    union TpInfo info;
    struct listagen *cabeca, *cauda;
}; typedef struct listagen ListaGen;

struct TpTermo {
	char termo[15];
	struct TpTermo *prox;
}; typedef struct TpTermo TpTermo;

struct Pilha {
	ListaGen *info;
	struct Pilha *prox;
}; typedef struct Pilha Pilha;

struct Fila {
	ListaGen *info;
	struct Fila *prox;
}; typedef struct Fila Fila;

union TpIdentificador
{
	char variavel[10];
	struct PilhaM *ponteiro;
};

struct PilhaMemoria {
	char terminal;
	union TpIdentificador ident;
	char valor[10];
	TpLista *ponteiro;
	struct PilhaMemoria *prox;
}; typedef struct PilhaMemoria PilhaM;


//---------------TAD PILHA---------------------

void init(Pilha **p) {
	*p = NULL;
}

void push(Pilha **p, ListaGen *info) {
	Pilha *novo = (Pilha*)malloc(sizeof(Pilha));
	novo->info = info;
	novo->prox = *p;
	*p = novo;
}

void pop(Pilha **p, ListaGen **info) {
	Pilha *aux = *p;
	*info = aux->info;
	*p = aux->prox;
	free(aux);
}

char isEmpty(Pilha *p) {
	return p == NULL;
}

//-------------TAD PILHA MEMORIA----------------
void initM(PilhaM **p) {
	*p = NULL;
}

void pushM(PilhaM **p, char *variavel, char *valor, PilhaM *ponteiro) {
	PilhaM *novo = (PilhaM*)malloc(sizeof(PilhaM));

	novo->terminal = 'V';
	strcpy(novo->ident.variavel, variavel);
	strcpy(novo->valor, valor);
	novo->ponteiro = ponteiro;
	novo->prox = *p;
	*p = novo;
}

char isEmptyM(PilhaM *p) {
	return p == NULL;
}

//----------------TAD FILA---------------------

void initF(Fila **f) {
	*f = NULL;
}

void enqueue(Fila **f, ListaGen *info){
	Fila *novo = *f, *aux;
	if (*f == NULL) {
		// A fila esta vazia, inicializa o primeiro no
		*f = (Fila*)malloc(sizeof(Fila));
		(*f)->info = info;
		(*f)->prox = NULL;
	} 
	else {
	    while (novo->prox != NULL) 
	        novo = novo->prox;
	    
	    aux = (Fila*)malloc(sizeof(Fila));
	    aux->info = info;
	    aux->prox = NULL;
		novo->prox = aux;
	}
}

void dequeue (Fila **f, ListaGen **info){
	Fila *aux = *f;
	*info = aux->info;
	*f = aux->prox;
	free(aux);
}

char IsEmptyF(Fila *f){
	return f == NULL;
}

//----------------------------------------------
int isNumber(char termo[]) {
    int i;
    
    for (i = 0; termo[i] != '\0'; i++)  //Percorre cada caractere da string até o caractere nulo
        if (!isdigit(termo[i]) && termo[i] != '.') //Se o caractere atual não é um dígito e não é um ponto decimal
            return 0;

    return 1;
}

int isOperation(char termo[]) {
    return (strcmp(termo, "+") == 0 || strcmp(termo, "-") == 0 || 
            strcmp(termo, "*") == 0 || strcmp(termo, "/") == 0 || 
			strcmp(termo, "//") == 0 || strcmp(termo, "**") == 0 ||
			strcmp(termo, "%") == 0);
}

int isFunction(char termo[]) {
    return (strcmp(termo, "math.sqrt") == 0 || strcmp(termo, "math.fabs") == 0);
}

ListaGen *CriaNo(char termo[]) {
    ListaGen *novo = (ListaGen*)malloc(sizeof(ListaGen));
    novo->cabeca = novo->cauda = NULL;

    if (isNumber(termo)) {
        novo->terminal = 'V';
        novo->info.valor = atof(termo);
    }
	if (isOperation(termo)) {
        novo->terminal = 'O';
        strcpy(novo->info.operacao, termo);
    } 
	if (isFunction(termo)) {
        novo->terminal = 'F';
        strcpy(novo->info.funcao, termo);
    } 
    return novo;
}


void CriaL (TpLista **nova) {
	*nova = (TpLista*)malloc(sizeof(TpLista));
	(*nova)->ant = NULL;
	(*nova)->prox = NULL;
	(*nova)->tokens = NULL;
}

void InsereL(TpLista **pProgram) {
	TpLista *aux, *nova;
	CriaL(&nova);
	if(*pProgram == NULL)
		*pProgram = nova;
	
	else
	{
		aux = *pProgram;
		while(aux->prox != NULL)
		{
			aux = aux->prox;
		}
		aux->prox = nova;
		nova->ant = aux;
	}
}

void CriaT (TpCode **nova,char token[15]) {
	*nova = (TpCode*)malloc(sizeof(TpCode));
	strcpy((*nova)->token, token);
	(*nova)->prox = NULL;
}

void InsereT(TpLista **pProgram, TpCode *nova) {
	TpLista *auxL = *pProgram;
	TpCode *aux;
	
	while(auxL->prox != NULL)
		auxL = auxL->prox;

	if(auxL->tokens == NULL)
		auxL->tokens = nova;

	else
	{
		aux = auxL->tokens;
		while(aux->prox != NULL)
			aux = aux->prox;
		aux->prox = nova;
	}
}

char VerifVazia(TpLista *pProgram) {
	TpLista *aux = pProgram;
	while(aux->prox != NULL)
		aux = aux->prox;

	if(aux->tokens == NULL)
		return 1;

	else
		return 0;
}

void exibe(TpLista *pProgram) {
	TpLista *aux = pProgram;
	TpCode *auxT;

	while(aux != NULL)
	{
		auxT = aux->tokens;
		while(auxT != NULL)
		{
			if(strcmp(auxT->token, "fim-def") == 0)
				printf("");

			else
			printf("%s ",auxT->token);
			auxT = auxT->prox;
		}
		printf("\n");
		aux = aux->prox;
	}
}

// void CarregaL(TpLista **pProgram) {
// 	FILE *arq;
// 	int i, j;
// 	char token[15], nome[15], auxS[50];
// 	TpCode *nova;
// 	printf("Digite o nome do arquivo: ");
// 	scanf("%s", nome);
// 	arq = fopen(nome, "r");

// 	if(arq == NULL)
// 	{
// 		printf("Erro ao abrir o arquivo\n");
// 	}
// 	else
// 	{
// 		while(!feof(arq))
// 		{
// 			fgets(auxS, 50, arq);
// 			InsereL(&pProgram);
// 			for(i = 0; i < strlen(auxS); i++)
// 			{
// 				for(j = 0; auxS[i] != ' ' && auxS[i] != '\n'; j++, i++)
// 				{
// 					token[j] = auxS[i];
// 				}
// 				token[j] = '\0';
// 				CriaT(&nova, token);
// 				InsereT(pProgram, nova);
// 			}
// 		}
// 	}
// 	fclose(arq);
// }

void CarregaL(TpLista **pProgram) {
    FILE *arq;
    int i, j;
    char token[15], nome[15], auxS[50];
    TpCode *nova;
    printf("Digite o nome do arquivo: ");
    scanf("%s", nome);
    arq = fopen(nome, "r");

    if(arq == NULL) {
        printf("Erro ao abrir o arquivo\n");
    }
	else {
        while(fgets(auxS, 50, arq) != NULL) {
			InsereL(pProgram);

            if(strlen(auxS) == 1 && auxS[0] == '\n') {
                strcpy(token, "fim-def");
                CriaT(&nova, token);
                InsereT(pProgram, nova);
            } 
			else {
                for(i = 0; i < strlen(auxS); i++) {
                    for(j = 0; auxS[i] != ' ' && auxS[i] != '\n'; j++, i++) {
                        token[j] = auxS[i];
                    }
                    token[j] = '\0';
                    CriaT(&nova, token);
                    InsereT(pProgram, nova);
                }
            }
        }
    }
    fclose(arq);
}

//Armazenando as variaveis e seus valores na memoria
void ArmazenaMemoria(TpLista *pPrograma, PilhaM **pilhaM) {
	TpLista *auxL = pPrograma;
	TpCode *auxT, *auxT2;
	float valor;
	char variavel[10];

	while(auxL != NULL) {
		auxT = auxL->tokens;
		if(strcmp(auxT->token, "def") == 0) { //se for uma funcao pula para o fim da funcao
			while(strcmp(auxT->token, "fim-def") != 0) {
				auxL = auxL->prox;
				auxT = auxL->tokens;
			}
		}
		else {
			auxT2 = auxT;

			while(auxT2->prox != NULL) { //percorre a lista de tokens
				auxT2 = auxT2->prox;
				if(strcmp(auxT2->token, "=") == 0) { //se for uma atribuicao
					auxT2 = auxT2->prox; 
					if(auxT2->prox == NULL) { //se o proximo valor depois da atribuicao for nulo
						pushM(&(*pilhaM), auxT->token, auxT2->token, NULL); //é uma variavel com valor
					}
				}
			}
		}
		auxL = auxL->prox;
	}
}

void mostrarPilhaMem(PilhaM *pilhaM) {
	PilhaM *aux = pilhaM;
	printf("\n");

	while(aux != NULL) {
		if(aux->terminal == 'V') 
			printf("%s = %s\n", aux->ident.variavel, aux->valor);

		aux = aux->prox;
	}
}

//Funcao ListaGen para resolver expressoes aritmeticas

// float resolve(char equacao[100]) {
//     float result;
    
//     //construir a ListaGen com todas a expressao aritmetica
//     Pilha *p;
//     ListaGen *L = NULL, *atual;
//     Fila *f;

//     TpTermo *lista = separa(equacao);
    
//     init(&p);
//     initF(&f);

//     while(lista != NULL) {
//         if(L == NULL)
//             L = atual = CriaNo(lista->termo);

//         else {
//             if(strcmp(lista->termo, "(") == 0) {
//                 atual->cauda = CriaNo("0");
//                 atual = atual->cauda;
//                 lista = lista->prox;
//                 push(&p, atual);

//                 atual->cabeca = CriaNo(lista->termo);
//                 atual = atual->cabeca;
//             }
//             else
//                 if(strcmp(lista->termo,")") == 0)
//                     pop(&p, &atual);

//                 else {
//                     atual->cauda = CriaNo(lista->termo);
//                     atual = atual->cabeca;
//                 }
// 		}
//         lista = lista->prox;
//     }

//     //resolvendo a expressao
//     push(&p, L);
//     enqueue(&f, L);
    
//     while(!isEmpty(f)) {
//         dequeue(&f, &atual);
        
//         while(!Nula(atual)) {
//             if(atual->cabeca != NULL) {
//                 push(&p, atual->cabeca);
//                 enqueue(&f, atual->cabeca);
//             }   
//             atual = atual->cauda;
//         }
//     }

//     while(!isEmpty(p)) {
//         pop(&p, &atual);
//         if(atual != L)
//             atual->info.valor = calcula(atual->cabeca);

//         else 
//             result = calcula(atual);
//     }
//     return result;
// }
