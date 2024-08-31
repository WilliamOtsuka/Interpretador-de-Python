
struct TpCode {
	char token[15];
	struct TpCode *prox;
}; typedef struct TpCode TpCode;

struct TpLista {
	struct TpLista *prox,*ant;
	TpCode *tokens;
}; typedef struct TpLista TpLista;

void CriaL (TpLista**nova){
	*nova=(TpLista*)malloc(sizeof(TpLista));
	(*nova)->ant=NULL;
	(*nova)->prox=NULL;
	(*nova)->tokens=NULL;
}

void InsereL(TpLista** pProgram){
	TpLista *aux,*nova;
	CriaL(&nova);
	if(*pProgram==NULL)
		*pProgram=nova;
	
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

void CriaT (TpCode**nova,char token[15]){
	*nova=(TpCode*)malloc(sizeof(TpCode));
	strcpy((*nova)->token,token);
	(*nova)->prox=NULL;
}

void InsereT(TpLista**pProgram,TpCode*nova){
	TpLista *auxL=*pProgram;
	TpCode *aux;
	
	while(auxL->prox!=NULL)
		auxL=auxL->prox;
	if(auxL->tokens==NULL)
		auxL->tokens=nova;
	else
	{
		aux=auxL->tokens;
		while(aux->prox!=NULL)
			aux=aux->prox;
		aux->prox=nova;
	}
}

char VerifaVazia(TpLista*pProgram){
	TpLista *aux=pProgram;
	while(aux->prox!=NULL)
		aux=aux->prox;
	if(aux->tokens==NULL)
		return 1;
	else
		return 0;
}

void exibe(TpLista*pProgram){
	TpLista *aux=pProgram;
	TpCode *auxT;
	while(aux->prox!=NULL)
	{
		auxT=aux->tokens;
		while(auxT!=NULL)
		{
			printf("%s ",auxT->token);
			auxT=auxT->prox;
		}
		printf("\n");
		aux=aux->prox;
	}
}

void CarregaL(TpLista**pProgram){
	FILE *arq;
	int i,j;
	char token[15],nome[15],auxS[50];
	TpCode *nova;
	printf("Digite o nome do arquivo: ");
	scanf("%s",nome);
	arq=fopen(nome,"r");

	if(arq==NULL)
	{
		printf("Erro ao abrir o arquivo\n");
	}
	else
	{
		while(!feof(arq))
		{
			fgets(auxS,50,arq);
			InsereL(&pProgram);
			for(i=0;i<strlen(auxS);i++)
			{
				for(j=0;auxS[i]!=' ' && auxS[i]!='\n';j++,i++)
				{
					token[j]=auxS[i];
				}
				token[j]='\0';
				CriaT(&nova,token);
				InsereT(pProgram,nova);
			}
		}
	}
	fclose(arq);
}
