
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

struct Fila{
	ListaGen *info;
	struct Pilha *prox;
}; typedef struct Fila Fila;

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

//----------------TAD FILA---------------------

void initF(Fila **f) {
	*f = NULL;
}

void enqueue(Fila **f, ListaGen *info){
	Fila *novo = *f;
	if (*f == NULL) {
    // A fila esta vazia, inicializa o primeiro no
    *f=(Fila*)malloc(sizeof(Fila));
    (*f)->prox=NULL;
    (*f)->info=info;
	} else {
	    while (novo->prox != NULL) {
	        novo = novo->prox;
	    }
	    novo->prox = (Fila*)malloc(sizeof(Fila));
	    novo->prox->info = info;
	    novo->prox->prox = NULL;
	}
}

void dequeue (Fila **f, ListaGen **info){
	Fila *aux= *f;
	*info = aux->info;
	*f = aux->prox;
	free(aux);
}

void IsEmptyF(Fila *f){
	return f==NULL;
}

//----------------------------------------------

int isNumber(char termo[]) {
    for (int i = 0; termo[i] != '\0'; i++) {
        if (!isdigit(termo[i]) && termo[i] != '.') {
            return 0;
        }
    }
    return 1;
}

int isOperation(char termo[]) {
    return (strcmp(termo, "+") == 0 || strcmp(termo, "-") == 0 || 
            strcmp(termo, "*") == 0 || strcmp(termo, "/") == 0 || 
			strcmp(termo, "//") == 0 || strcmp(termo, "**") == 0 ||
			strcmp(termo, "%") == 0);
}

int isFunction(char termo[]) {
    return (strcmp(termo, "math.sqrt") == 0 || strcmp(termo, "math.fabs") == 0)
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

char VerifaVazia(TpLista *pProgram) {
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

	while(aux->prox != NULL)
	{
		auxT = aux->tokens;
		while(auxT != NULL)
		{
			printf("%s ",auxT->token);
			auxT = auxT->prox;
		}
		printf("\n");
		aux = aux->prox;
	}
}

void CarregaL(TpLista **pProgram) {
	FILE *arq;
	int i, j;
	char token[15], nome[15], auxS[50];
	TpCode *nova;
	printf("Digite o nome do arquivo: ");
	scanf("%s", nome);
	arq = fopen(nome, "r");

	if(arq == NULL)
	{
		printf("Erro ao abrir o arquivo\n");
	}
	else
	{
		while(!feof(arq))
		{
			fgets(auxS, 50, arq);
			InsereL(&pProgram);
			for(i = 0; i < strlen(auxS); i++)
			{
				for(j = 0; auxS[i] != ' ' && auxS[i] != '\n'; j++, i++)
				{
					token[j] = auxS[i];
				}
				token[j] = '\0';
				CriaT(&nova, token);
				InsereT(pProgram, nova);
			}
		}
	}
	fclose(arq);
}

//Funcao ListaGen para resolver expressoes aritmeticas

float resolve(char equacao[100]) {
    float result;
    
    //construir a ListaGen com todas a expressao aritmetica
    Pilha *p;
    ListaGen *L = NULL, *atual;
    Fila *f;

    TpTermo *lista = separa(equacao);
    
    init(&p);
    initF(&f);

    while(lista != NULL) {
        if(L == NULL)
            L = atual = CriaNo(lista->termo);

        else {
            if(strcmp(lista->termo, "(") == 0) {
                atual->cauda = CriaNo("0");
                atual = atual->cauda;
                lista = lista->prox;
                push(&p, atual);

                atual->cabeca = CriaNo(lista->termo);
                atual = atual->cabeca;
            }
            else
                if(strcmp(lista->termo,")") == 0)
                    pop(&p, &atual);

                else {
                    atual->cauda = CriaNo(lista->termo);
                    atual = atual->cabeca;
                }
		}
        lista = lista->prox;
    }

    //resolvendo a expressao
    push(&p, L);
    enqueue(&f, L);
    
    while(!isEmpty(F)) {
        dequeue(&f, &atual);
        
        while(!Nula(atual)) {
            if(atual->cabeca != NULL) {
                push(&p, atual->cabeca);
                enqueue(&f, atual->cabeca);
            }   
            atual = atual->cauda;
        }
    }

    while(!isEmpty(P)) {
        pop(&p, &atual);
        if(atual != L)
            atual->info.valor = calcula(atual->cabeca);

        else 
            result = calcula(atual);
    }
    return result;
}
