
/*
Desenvolva um programa em linguagem C que leia a matriz de adjacência de um grafo conexo G(V,E):

a) Implementar a busca em profundidade e apresentar a listagem dos vértices;
b) Idem para busca em largura.

*/



#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int chave;
} TItem;

typedef struct celula {
	struct celula *pProx;
	TItem item;
} TCelula;

typedef struct {
	TCelula *pInicio, *pFim;
	int tamanho;
} TFila;

void iniciarFila (TFila *pFila);
int isVazia (TFila *pFila);
int enqueue (TFila *pFila, TItem x);
int dequeue (TFila *pFila, TItem *pX);
int peek (TFila *pFila, TItem *pX);
int tamanho (TFila *pFila);

void iniciarFila (TFila *pFila) {
	pFila->pInicio = NULL;
	pFila->pFim = NULL;
	pFila->tamanho = 0;
}

int isVazia (TFila *pFila) {
	return pFila->pInicio == NULL;
}

int enqueue (TFila *pFila, TItem x) {
	TCelula *novo = (TCelula *) malloc (sizeof (TCelula));
	novo->item = x;
	novo->pProx = NULL;

	if (isVazia (pFila)) {
		pFila->pInicio = novo;
	} else {
		pFila->pFim->pProx = novo;
	}

	pFila->pFim = novo;
	pFila->tamanho++;

	return 1;
}

int dequeue (TFila *pFila, TItem *pX) {
	if (isVazia (pFila))
		return 0;

	TCelula *pAux = pFila->pInicio;
	*pX = pAux->item;

	pFila->pInicio = pAux->pProx;
	free (pAux);

	pFila->tamanho--;

	return 1;
}

int peek (TFila *pFila, TItem *pX) {
	if (isVazia (pFila))
		return 0;

	*pX = pFila->pInicio->item;

	return 1;
}

int tamanho (TFila *pFila) {
	return pFila->tamanho;
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

int teste(int **matriz,int n){
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d ", matriz[i][j]  );
    }
    printf("\n");

  }

  return 0;
}

void BuscaProfundidade(int **m,int *v, int n,int vertice){
  v[vertice] ++;
  printf("%d\n",vertice );
  for (int i = 0; i < n; i++) {
    
    if (v[i] == 0 && m[vertice][i] != 0){

      BuscaProfundidade(m,v,n,i);
    }
  }
}

void BuscaLargura(int **m,int *v, int n,int vertice){

  TFila fila;
  iniciarFila(&fila);
  printf("%d\n",vertice );
  v[vertice] ++;

  TItem item;
	item.chave = vertice;
	enqueue (&fila, item);

  while (!isVazia(&fila)){
    peek(&fila,&item);
    for (int i = 0; i < n; i++) {
      if (v[i] == 0 && m[item.chave][i] != 0){
        printf("%d\n",i );
        v[i] ++;
        item.chave = i;
        enqueue (&fila, item);
        peek(&fila,&item);
      }
    }
    dequeue(&fila,&item);
  }
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

int main() {
  int vertices,i,j,k;
	printf("Digite a quantidade de vertices: ");
	scanf("%d", &vertices);
	int x,y = 0;
	int **matriz;
  matriz = Alocar_matriz_int (vertices, vertices);
  int *verificados;
  verificados = Alocar_vetor_int(vertices);

  for (i = 0; i < vertices; i++) {
    for (j = 0; j < vertices; j++) {
      scanf("%d", &matriz[i][j]);
    }
  }
  printf("Busca em profundidade: \n");



  BuscaProfundidade(matriz,verificados,vertices,0);
  printf("Busca em largura: \n");
  verificados = Liberar_vetor_int(vertices,verificados);
  BuscaLargura(matriz,verificados,vertices,0);

  return 0;
}
