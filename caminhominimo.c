
/*

Desenvolva um programa em linguagem C que leia a matriz de adjacência de um grafo ponderado G(V,E) e:

a) Apresente o caminho mínimo e o respectivo peso, para um vértice x inicial e outro vértice y final, utilizando o algoritmo de Dijkstra;

b) Apresente os caminhos mínimos e os pesos, para um vértice x inicial e todos os outros vértices do grafo, utilizando o algoritmo de Bellman-Ford;

c) Apresente os pesos dos caminhos mínimos entre todos os pares de vértices utilizando o algoritmo de Floyd.

*/


#include <stdio.h>
#include <stdlib.h>


int BellmanFord(int **m,int n,int x);

int **Alocar_matriz_int (int m, int n);

int *Alocar_vetor_int (int n);

int *Liberar_vetor_int (int n, int *v);

int menor(int *d, int *N,int n);


void relax(int *t,int *s, int **w, int u, int v);

void floyd(int **A,int n);

int menor(int *d, int *N,int n){
	int i,menorvalor,atual,menorIndice;
	for (i = 0; i < n; ++i){
		if (N[i] != 1){
			menorvalor = d[i];
			atual,menorIndice = i;
			break;
		} 
	}

	for (i = atual+1; i < n; ++i){
		if (N[i] != 1){
			if (menorvalor > d[i] ){
				menorvalor = d[i];
				menorIndice = i;
			} 
		}	
	}
	N[menorIndice] = 1;
	return menorIndice;
}
	

void floyd(int **A,int n){
	int i,j,k;
	for (k=0;k<n;k++)
		for (i=0;i<n;i++)
			for (j=0;j<n;j++)
				if ((A[i][k] + A[k][j]) < A[i][j]) 
					A[i][j] = A[i][k]+A[k][j];
	

	for (i = 0; i < n; ++i){
		printf("%d |", i );
		for (j = 0; j < n; ++j){
			printf("%d ",A[i][j] );
		}
		printf("\n");
	}
			
		

}

void dijkstra();

void dijkstra(int **m,int n, int x, int y){
	int N[n],busca[n];
	int z,p,i,verifica;

	int d[n],s[n];
	N[x] = 1;
	d[x] = 0;
	for (i = 0; i < n; ++i){
		if(i != x)
			d[i] = m[x][i];

		s[i] = x;
	}

	while(p!=y){
		p = menor(d,N,n);
		if(p == y)
			break;

		for (z = 0; z < n; ++z){
			if (N[i] != 1){
				if(d[z] > d[p] + m[p][z]){
					d[z] = d[p] + m[p][z];
					s[z] = p;
				}	
			} 
		}
	}

	printf("Em ordem inversa, o caminho é: %d ", y);
	z = y;
	while(z != x){
		printf("%d ",s[z]);
		z = s[z];
	}
	/*
	printf("\nValores de D\n");

	for (int i = 0; i < n; ++i)
	{
		printf("%d ", d[i] );
	}

	printf("\nValores de S\n");

	for (int i = 0; i < n; ++i)
	{
		printf("%d ", s[i] );
	}
	*/

	printf("\nA distância do caminho é %d\n", d[y]);
}

void relax(int *t,int *s, int **w, int u, int v){
	if(t[v] > t[u] + w[u][v]) {
		t[v] = t[u]+ w[u][v];
		s[v] = u;
	}
}

int BellmanFord(int **m,int n,int x){
	int z,i,p,min;
	int d[n],s[n],t[n];


	d[x] = 0;


	for (z = 0; z < n; ++z){
		if(x != z){ 
			d[z] = m[x][z];
		}
		s[z] = x;
	}
	

	for (i = 1; i < n; ++i){
		for (z = 0; z < n; ++z)
			t[z] = d[z];
		
		for (z = 0; z < n; ++z){
			if(x != z){ 
				for (i = 0; i < n; ++i){
					if (t[z] > (t[i] + m[i][z])){
						t[z] = t[i] + m[i][z];
						s[z] = i;
					}	
				}
				//relax aqui
			}
		}

		for (z = 0; z < n; ++z)
			d[z] = t[z];

	}
	
	/*
	printf("\nValores de D\n");

	for (int i = 0; i < n; ++i)
	{
		printf("%d ", d[i] );
	}

	printf("\nValores de S\n");

	for (int i = 0; i < n; ++i)
	{
		printf("%d ", s[i] );
	}

	*/
	int y;
	printf("\n");
	for (i = 0; i < n; ++i){
		printf("--------------------------------------------------------\n");
		int y = i;
		printf("Em ordem inversa, o caminho para chegar em %d é: %d ", x, y);
		z = y;
		while(z != x){
			printf("%d ",s[z]);
			z = s[z];
		}	
		printf("\nA distância do caminho é %d\n", d[y]);
	}

	

}





int main(int argc, char const *argv[])
{

	int vertices,i,j;
	printf("Digite a quantidade de vertices: ");
	scanf("%d",&vertices);
	int **m,**A;
  	m = Alocar_matriz_int (vertices, vertices);
  	A = Alocar_matriz_int (vertices, vertices);
	printf("Digite a matriz:\n");
	printf("OBS: USE 99 PARA REPRESENTAR INFINITO\n");
	for (i = 0; i < vertices; ++i)
	{
		for (j = 0; j < vertices; ++j)
		{
			scanf("%d",&m[i][j]);
			A[i][j] = m[i][j];
		}
	}
	printf("A matriz é \n");
	for (i = 0; i < vertices; ++i)
	{
		printf("%d | ", i );
		for (j = 0; j < vertices; ++j)
		{
			printf("%d ",m[i][j]);
		}
		printf("\n");
	}

	int x,y;
	printf("--------------------------ALGORITMO DE DIJKSTRA --------------------------------");
	printf("Digite o valor de partida :");
	scanf("%d",&x);
	printf("Digite o valor de chegada :");
	scanf("%d",&y);

	dijkstra(m,vertices, x, y);

	printf("--------------------------ALGORITMO DE FLOYD --------------------------------\n");
	floyd(A,vertices);

	printf("--------------------------ALGORITMO DE BELLMAN --------------------------------\n");
	BellmanFord(m,vertices,x);	
	return 0;
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
