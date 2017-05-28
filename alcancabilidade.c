
/*
Desenvolva um programa em linguagem C que leia a matriz de adjacências de um grafo direcionado D(V,E) e:

a) Calcule e apresente as matrizes de alcançabilidade A(1), A(2),..., A(N) e a matriz de alcançabilidade geral R utilizando multiplicações booleanas;

b) Calcule e apresente a matriz de alcançabilidade geral M utilizando o algoritmo de Warshall.

*/



#include <stdio.h>
#include <stdlib.h>


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


int main(int argc, char const *argv[])
{
  int vertices,i,j,k,l;
  printf("Digite a quantidade de vertices: ");
  scanf("%d", &vertices);
  int x,y = 0;
  int **matriz,**matrizR,**matrizRA,**matrizA;
  matriz = Alocar_matriz_int (vertices, vertices);
  matrizR = Alocar_matriz_int (vertices, vertices);
  matrizA = Alocar_matriz_int (vertices, vertices);
  matrizRA = Alocar_matriz_int (vertices, vertices);


  for (i = 0; i < vertices; i++)
  {
    for (j = 0; j < vertices; j++)
    {
      scanf("%d", &matriz[i][j]);
      matrizA[i][j] = matriz[i][j];
    }
  }

  l = 0;
  while(l < vertices){
    for (i=0;i<vertices; i++) {
       for (j=0; j<vertices; j++) {
         for (k=0; k<vertices; k++) {
           matrizRA[i][j] = matrizRA[i][j] + (matrizA[i][k] * matriz[k][j]);
         }
       }
     }
     l++;
     printf("Matriz A%d : \n",l );
     for (i = 0; i < vertices; i++) {
       for (j = 0; j < vertices; j++) {
         printf("%d ",matrizA[i][j] );
         matrizR[i][j] = matrizR[i][j] || matrizRA[i][j];
         matrizA[i][j] = matrizRA[i][j];
         matrizRA[i][j] = 0;
       }
       printf("\n");
     }
  }

  printf("Matriz R : \n");
  for (i = 0; i < vertices; i++) {
       for (j = 0; j < vertices; j++) {
         printf("%d ",matrizR[i][j] );
       }
       printf("\n");
     
  }

  for (i=0;i<vertices; i++) {
       for (j=0; j<vertices; j++) {
         for (k=0; k<vertices; k++) {
           matriz[i][j] = matriz[i][j] || (matriz[i][k] && matriz[k][j]);
         }
       }
  }


  printf("Matriz M : \n");
  for (i = 0; i < vertices; i++) {
       for (j = 0; j < vertices; j++) {
         printf("%d ",matriz[i][j] );
       }
       printf("\n");
     
  }



  return 0;
}
