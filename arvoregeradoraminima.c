
/*
Desenvolva um programa em linguagem C que leia a matriz de adjacência de um grafo ponderado conexo G(V,E) e:

a) Apresente a árvore geradora mínima e o respectivo peso utilizando o algoritmo de Kruskal;

b) Apresente a árvore geradora mínima e o respectivo peso, iniciando-se de qualquer vértice, utilizando o algoritmo de Prim;


*/

#include <stdio.h>
#include <stdlib.h>


typedef struct item{
	int verticex;
	int verticey;
	int chave;
}TItem;


typedef struct No {
	TItem item;
} TNo;

typedef struct celula {
	struct celula *pProx;
	TNo *no;
} TCelula;


typedef struct {
	TCelula *pPrimeiro, *pUltimo;
	int quant;
} TLista;


void iniciarLista (TLista *pLista) {
	pLista->pPrimeiro = NULL;
	pLista->pUltimo = NULL;
	pLista->quant = 0;
}

TNo* criarNo (TItem x) {
	TNo *pAux = (TNo*) malloc (sizeof(TNo));
	pAux->item = x;
	return pAux;
}

int isVazia (TLista *pLista) {
	return pLista->pPrimeiro == NULL;
}


int inserirFim (TLista *pLista, TNo *no) {
	TCelula *novo = (TCelula *) malloc (sizeof (TCelula));
	novo->no = no;
	novo->pProx = NULL;

	if (isVazia (pLista)) {
		pLista->pPrimeiro = novo;
	} else {
		pLista->pUltimo->pProx = novo;
	}
	pLista->pUltimo = novo;

	return 1;
}



int inserir (TLista *pLista, TNo *no) {
	pLista->quant ++;
	TCelula *pAux = pLista->pPrimeiro;
  	TCelula *pAnt = NULL;
	while (pAux != NULL && pAux->no->item.chave < no->item.chave) {
    pAnt = pAux;
		pAux = pAux->pProx;
	}

	if (pAux == NULL) {
		inserirFim(pLista,no);
		return 1;
	}


  	TCelula *novo = (TCelula *) malloc (sizeof (TCelula));
	novo->no = no;
	novo->pProx = pAux;

  	if (pAnt != NULL){
  	  pAnt->pProx = novo;
  	}else{
  	  pLista->pPrimeiro = novo;
 	}

	if (novo->pProx == NULL) {
		pLista->pUltimo = novo;
	}

	return 1;
}



int removerPrimeiro (TLista *pLista) {
	if (isVazia (pLista))
		return 0;
	TCelula *pAux;
	pAux = pLista->pPrimeiro;
	// *pX = pAux->item;
	pLista->pPrimeiro = pAux->pProx;
	pLista->quant --;
	return 1;
}

int removerDois (TLista *pLista) {
	removerPrimeiro(pLista);
  	removerPrimeiro(pLista);
  	return 1;
}

int removerUltimo (TLista *pLista, TItem *pX) {
	if (isVazia (pLista))
		return 0;

	TCelula *pAux = pLista->pPrimeiro;

	if (pAux->pProx == NULL) {
		*pX = pAux->no->item;
		free (pAux);
		pLista->pPrimeiro = NULL;
		pLista->pUltimo = NULL;
	} else {
		while (pAux->pProx != pLista->pUltimo) {
			pAux = pAux->pProx;
		}
		*pX = pAux->pProx->no->item;
		free (pAux->pProx);
		pAux->pProx = NULL;
		pLista->pUltimo = pAux;
	}

	return 1;
}

TNo* retornaPrimeiro (TLista *pLista){
  TCelula* aux = pLista->pPrimeiro;
  return aux->no;
}

int **Alocar_matriz_int (int m, int n)
{
  int **v;
  int   i;
  if (m < 1 || n < 1) {
     printf ("** Erro: Parametro invalido **\n");
     return (NULL);
     }

  v =  calloc (m, sizeof(int *));
  if (v == NULL) {
     printf ("** Erro: Memoria Insuficiente **");
     return (NULL);
     }

  for ( i = 0; i < m; i++ ) {
      v[i] =  calloc (n, sizeof(int));
      if (v[i] == NULL) {
         printf ("** Erro: Memoria Insuficiente **");
         return (NULL);
         }
      }
  return (v);
}


int *Alocar_vetor_int (int n)
{
  int *v;        /* ponteiro para o vetor */
  if (n < 1) {  /* verifica parametros recebidos */
     printf ("** Erro: Parametro invalido **\n");
     return (NULL);
     }
  /* aloca o vetor */
  v = (int *) calloc (n+1, sizeof(int));
  if (v == NULL) {
     printf ("** Erro: Memoria Insuficiente **");
     return (NULL);
     }
  return (v);    /* retorna o ponteiro para o vetor */
}

int *Liberar_vetor_int (int n, int *v)
{
  if (v == NULL) return (NULL);
  if (n < 1) { /* verifica parametros recebidos */
     printf ("** Erro: Parametro invalido **\n");
     return (NULL);
     }
  free(v);        /* libera o vetor */
  return (Alocar_vetor_int (n));  /* retorna o ponteiro */
}


int buscaaresta (TLista *pLista, int x, int y) {

	TCelula* aux = pLista->pPrimeiro;
	while (aux != NULL) {
		if ((aux->no->item.verticex == x || aux->no->item.verticey == x) && (aux->no->item.verticey == y || aux->no->item.verticex == y)){
			return 0;
		
		}else{
			aux = aux->pProx;
		}
	}
	return 1;
}


int busca (TLista *pLista,TItem aresta) {

	if(isVazia(pLista)){
		return 0;
	}

	TCelula* aux = pLista->pPrimeiro;
	int x,y,t;
	x = aresta.verticex;
	y = aresta.verticey;

	//printf("x:%d e y:%d com valor: %d\n",x,y,aresta.chave );
	int valido = 1;
	while (aux != NULL ) {
		if (aux->no->item.verticex == x || aux->no->item.verticey == x ) {
			if (aux->no->item.verticex == x) 
				t = aux->no->item.verticey;
			else
				t = aux->no->item.verticex;

			//chama a busca para verificar se y possui aresta com t, caso sim, retorna 0
			valido = valido * buscaaresta (pLista, y, t);

			if(!valido)
				return 1;

		} 
		aux = aux->pProx;
		
	}
	
	return 0;
	
}

void imprimir (TLista *pLista) {
	TCelula *pAux = pLista->pPrimeiro;
	
	printf ("Itens na lista:\n");
	while (pAux != NULL) {
		printf("x:%d e y:%d com valor: %d\n",pAux->no->item.verticex,pAux->no->item.verticey,pAux->no->item.chave );
		//printf ("%d\n", pAux->no->item.chave);
		pAux = pAux->pProx;
	}
}

void inserirporvertices(TLista *pLista,TLista *f, TLista *t, TLista *vertices){
	if(isVazia(pLista) || isVazia(vertices)){
		return ;
	}
	//printf("%d\n",x );
	TCelula* pAux = vertices->pPrimeiro;
	TCelula* aux = pLista->pPrimeiro;
	while(pAux != NULL){
		aux = pLista->pPrimeiro;
		while (aux != NULL ) {
			if (aux->no->item.verticex == pAux->no->item.chave || aux->no->item.verticey == pAux->no->item.chave ) {
				//printf("x:%d e y:%d com valor: %d\n",aux->no->item.verticex,aux->no->item.verticey,aux->no->item.chave );
				if(aux->no->item.chave != 99){
					if (!busca(t,aux->no->item)){
						TNo *resu = criarNo(aux->no->item);
						inserir(f,resu);
					}
				}
			} 
			aux = aux->pProx;
		}

		pAux = pAux->pProx;
	}
}


void inserirporvertice(TLista *pLista,TLista *f, int x){
	if(isVazia(pLista)){
		return ;
	}
	TCelula* aux = pLista->pPrimeiro;
	while (aux != NULL ) {
			if (aux->no->item.verticex == x || aux->no->item.verticey == x) {
				//printf("x:%d e y:%d com valor: %d\n",aux->no->item.verticex,aux->no->item.verticey,aux->no->item.chave );
				if(aux->no->item.chave != 99){
					TNo *resu = criarNo(aux->no->item);
					inserir(f,resu);
				}
			} 
			aux = aux->pProx;
	}
}


void Kruskal(TLista *lista,TLista *t, int n);

void prim(TLista *lista,TLista *t, int n){
	TLista f,vertices;
	iniciarLista (&f);
	iniciarLista (&vertices);

	TItem item;
	printf("Digite o vertice: ");
	scanf("%d",&item.chave);
	inserirporvertice(lista,&f,item.chave);
	TNo *no = criarNo(item);
	inserir(&vertices,no);	
	//imprimir(&f);

	int vertice = item.chave;

	while (!isVazia(&f)){
		TNo *no = retornaPrimeiro(&f);
		inserir(t,no);

		if (vertice == no->item.verticex )
			vertice = no->item.verticey;
		else
			vertice = no->item.verticex;


		TItem itemvertice;
		itemvertice.chave = vertice;
		TNo *no2 = criarNo(itemvertice);
		inserir(&vertices,no2);
		iniciarLista (&f);
		//imprimir(&vertices);
		inserirporvertices(lista,&f,t,&vertices);
		//imprimir(&f);
		//break;

	}
	

}



void Kruskal(TLista *lista,TLista *t, int n){
	while(t->quant < n-1){
		TNo *no = retornaPrimeiro(lista);
		//printf("%d\n",no->item.chave );
		if (!busca(t,no->item)){
			//printf("%d\n", no->item.chave );
			TNo *resu = criarNo(no->item);
			inserir(t,resu);
		}
		removerPrimeiro(lista);
	}
	

}


int main(int argc, char const *argv[])
{
	int vertices,i,j,k;
	printf("Digite a quantidade de vertices: ");
	scanf("%d", &vertices);
	int **matriz;
  	matriz = Alocar_matriz_int (vertices, vertices);
  	TLista lista,listaprim;
	iniciarLista (&lista);
	iniciarLista (&listaprim);
    
    printf("Digite 99 para infinito\n");

	for (i = 0; i < vertices; i++) {
	   for (j = 0; j < vertices; j++) {
	     scanf("%d", &matriz[i][j]);
	     if (j>=i){
	     	TItem item;
		    item.verticex = i;
		    item.verticey = j;
		    item.chave = matriz[i][j];
		    TNo *resu = criarNo(item);
		    inserir(&lista,resu);
		    inserir(&listaprim,resu);
	     }
	   }
	}

	//imprimir(&lista);
	TLista t,p;
	iniciarLista (&t);
	iniciarLista (&p);
	
	printf("ALGORITMO DE Kruskal ---------------------------------------\n");	
	Kruskal(&lista,&t,vertices);
	printf("\n");
	imprimir(&t);


	printf("ALGORITMO DE PRIM ---------------------------------------\n");
	prim(&listaprim,&p,vertices);
	imprimir(&p);


	return 0;
}
