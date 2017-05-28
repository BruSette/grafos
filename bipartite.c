
/*
Desenvolva um programa em linguagem C que leia o conjunto de vértices e arestas de um grafo não direcionado G(V,E):

• Construa e escreva a matriz de adjacências do grafo.
• Apresentar uma lista com o grau de cada vértice;
• Classificar o grafo em: bipartipe ou não bipartite; caso bipartite, apresentar os 2 subconjuntos de vértices.
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

int main()
{
	int vertices,i,j,k;
	printf("Digite a quantidade de vertices: ");
	scanf("%d", &vertices);
	int x,y = 0;
	int **matriz;


  matriz = Alocar_matriz_int (vertices, vertices);

	while (x != -1){
		printf("Digite uma aresta ou -1 para finalizar a leitura de arestas\n ");
		printf("Digite um vertice: ");
		scanf("%d", &x);
		while (x > vertices){
			printf("Valor de vertice inválido, digite novamente: ");
			scanf("%d", &x);
		}

		if (x != -1){
			printf("Digite outro vertice: ");
			scanf("%d", &y);
			while (y > vertices){
				printf("Valor de vertice inválido, digite novamente: ");
				scanf("%d", &y);
			}
			if (y != -1){
				matriz[x][y] +=  1;
				if (x != y)
					matriz[y][x] +=  1;
			}
		}
	}

	for (i = 0; i < vertices; ++i)
	{
		int soma = 0;
		for (int j = 0; j < vertices; ++j)
		{
			soma += matriz[i][j];
		}
		printf("\nVertice %d possui grau %d ", i,soma);
	}
  printf("\n");
  printf("   ");
  for (i = 0; i < vertices; i++) {
    printf("%d ", i );
  }
  printf("\n   ");
  for (i = 0; i < vertices; i++) {
    printf("_ ");
  }
  printf("\n");
	for ( i = 0; i < vertices; i++) {
    printf("%d |", i );
		for ( j = 0; j < vertices; j++) {
			printf("%d ", matriz[i][j] );
		}
		printf("\n");
	}

	//Verifica se o grafo possui laços
	i = 0;
	int laco = 0;
	while (i < vertices){
		if (matriz[i][i] == 1){
			laco = 1;
			break;
		}
		i++;
	}

	if (laco){
		printf("Não é bipartite\n");
    return 0;
	}

  i = 0;
	for (i = 0; i < vertices; i++) {
    int desconexo = 0;
    for (j = 0; j < vertices; j++) {
  	  desconexo = desconexo + matriz[i][j];
    }
    if (desconexo == 0){
  		printf("Não é bipartite\n");
      return 0;
  	}
	}


  //Verifica se o grafo possui um cilco de tamanho 3, se sim, não é bipartite
	int valores[vertices];
	int tamanho = 0;
	for (i = 0; i < vertices; i++) {
		for (j = 0; j < vertices; j++) {
			if (matriz[i][j] == 1){
				valores[tamanho] = j;
				tamanho ++;
			}
		}

		if (tamanho > 1){
			for (k = 0; k < tamanho-1; k++) {
				for (y = 1; y < tamanho; y++) {
					if (matriz[valores[k]][valores[y]] == 1){
						printf("Não bipartite\n");
						return 0;
					}
				}
			}
		}

		for (k = 0; k < tamanho; k++) {
			valores[k] = 0;
		}
		tamanho = 0;
	}


  //Realiza verificações para definir os conjuntos e invalidar em caso de não bipartite

  int *lado1,*lado2,*verificados,*adjverticeatual,*verifica;


  lado1 = Alocar_vetor_int (vertices);
  lado2 = Alocar_vetor_int (vertices);
  verificados = Alocar_vetor_int (vertices);
  adjverticeatual = Alocar_vetor_int (vertices);

  lado1[0] = 1;
  int lado = 2;
  for (i = 0; i < vertices; i++) {
    if (verificados[i] == 0){
      for (j = 0; j < vertices; j++) {
        if(matriz[i][j] != 0)
          adjverticeatual[j]++;
      }
      if (lado == 2){
        lado = 1;
        for (k = 0; k < vertices; k++) {
          if (adjverticeatual[k] != 0 &&  lado2[k] == 0){
            //printf("Inseriu %d no lado 2\n",k );
            lado2[k]++;
          }
        }
      }else{
        lado = 2;
        for (k = 0; k < vertices; k++) {
          if (adjverticeatual[k] != 0 && lado1[k] == 0){
            //printf("Inseriu %d no lado 1\n",k );
            lado1[k]++;
          }
        }
      }

      int terminou = 0;
      verifica = Alocar_vetor_int (vertices);
      while(!terminou){
        verifica = Liberar_vetor_int(vertices,verifica);
        for (k = 0; k < vertices; k++) {
          verifica[k] = adjverticeatual[k];
        }
        adjverticeatual = Liberar_vetor_int(vertices,adjverticeatual);

        terminou = 1;
        for (k = 0; k < vertices; k++) {
          if (verifica[k] != 0 && verificados[k] == 0){
            terminou = 0;
            verificados[k] ++;
            for (y = 0; y < vertices; y++) {
              if(matriz[k][y] != 0){
                adjverticeatual[y]++;
              }
            }
          }
        }

        if (!terminou){
          if (lado == 2){
            lado = 1;
            for (k = 0; k < vertices; k++) {
              if (adjverticeatual[k] != 0 && lado2[k] == 0){
                lado2[k]++;
              }
            }
          }else{
            lado = 2;
            for (k = 0; k < vertices; k++) {
              if (adjverticeatual[k] != 0 && lado1[k] == 0){
                lado1[k]++;
              }
            }
          }
        }
      }
    }
    if (verificados[i] == 0)
      verificados[i]++;

  }

  for (i = 0; i < vertices; i++) {

    if (lado1[i] != 0 && lado2[i]!= 0){
      printf("Não Bipartite\n");
      return 0;
    }
  }
  printf("Lado 1 \n");
  for (i = 0; i < vertices; i++){
    if (lado1[i] != 0){
      printf("%d\n",i );
    }
  }
  printf("Lado 2 \n");
  for (i = 0; i < vertices; i++){
    if (lado2[i] != 0){
      printf("%d\n",i );
    }
  }
	printf("Bipartite\n");




	return 0;
}
