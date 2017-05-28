
/*

Desenvolva um programa em linguagem C para implementar um codificador de Huffman. O programa deve:


a) Ler uma cadeia de caracteres de entrada (codificação ASC II) e construir a árvore de Huffman;
b) Apresentar a árvore de Huffman;
c) Apresentar a tabela de códigos para todos caracteres;
d) Calcular e apresentar a taxa de compressão aproximada;

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct item {
  double chave;
  char valor;
} TItem;

typedef struct No {
	TItem item;
	struct No *pEsq, *pDir;
} TNo;

typedef struct celula {
	struct celula *pProx;
	TNo *no;
} TCelula;


typedef struct {
	TCelula *pPrimeiro, *pUltimo;
} TLista;



void iniciarLista (TLista *pLista);
void iniciarItem (TItem *pItem);
int isVazia (TLista *pLista);
int inserirFim (TLista *pLista, TNo *no);
int removerPrimeiro (TLista *pLista);
int removerDois (TLista *pLista);
int removerUltimo (TLista *pLista, TItem *pX);
void imprimir (TLista *pLista);
int inserirInicio (TLista *pLista, TNo *no);
int buscarE (TLista *pLista,  char e);
TNo* retornaPrimeiro (TLista *pLista);
TNo* retornaSegundo (TLista *pLista);
TNo* criarNo (TItem x);
int inserir (TLista *pLista, TNo *no) ;
void preOrdem (TNo *p);
int busca(TNo *no, char valor);
void retornacodigo(TNo *no, char valor,int *cont);

TNo* criarNo (TItem x) {
	TNo *pAux = (TNo*) malloc (sizeof(TNo));
	pAux->item = x;
	pAux->pEsq = NULL;
	pAux->pDir = NULL;
	return pAux;
}


void iniciarLista (TLista *pLista) {
	pLista->pPrimeiro = NULL;
	pLista->pUltimo = NULL;
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




int inserirInicio (TLista *pLista, TNo *no) {
	TCelula *novo = (TCelula *) malloc (sizeof (TCelula));
	novo->no = no;
	novo->pProx = NULL;

	if (isVazia (pLista)) {
		pLista->pPrimeiro = novo;
    	pLista->pUltimo = novo;
    	return 1;
	}

  	TCelula *pAux = pLista->pPrimeiro;
  	pLista->pPrimeiro = novo;
  	novo->pProx = pAux;

	return 1;
}



int buscarE (TLista *pLista, char e) {
	TCelula *pAux = pLista->pPrimeiro;
	while (pAux != NULL && pAux->no->item.valor != e) {
		pAux = pAux->pProx;
	}

	if (pAux == NULL) {
		return 0;
	}

	return 1;
}


int inserir (TLista *pLista, TNo *no) {
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

TNo* retornaSegundo (TLista *pLista){
  TCelula* aux = pLista->pPrimeiro->pProx;
  return aux->no;
}

void imprimir (TLista *pLista) {
	TCelula *pAux = pLista->pPrimeiro;

	printf ("Itens na lista:\n");
	while (pAux != NULL) {
		printf ("possui %.2lf e char %c  \n",pAux->no->item.chave,pAux->no->item.valor);
		pAux = pAux->pProx;
	}
}


void preOrdem (TNo *p) {
	if (p == NULL)
		return;
	if(p->item.valor != '\0')
		printf("chave: %lf e char: %c \n", p->item.chave,p->item.valor);
	else
		printf("chave: %lf \n", p->item.chave);
	preOrdem (p->pEsq);
	preOrdem (p->pDir);
}

int busca(TNo *no, char valor){
	if (no == NULL)
		return 0;

	if(no->item.valor == valor)
		return 1;

	if (busca(no->pEsq,valor))
		return busca(no->pEsq,valor);

	return busca(no->pDir,valor);
}

void retornacodigo(TNo *no, char valor, int *cont){
	if (no == NULL){
		return ;

	}

	if(no->item.valor == valor){
		return ;
	}

	if (busca(no->pEsq,valor)){
		printf("0");
		*cont = *cont + 1;
		retornacodigo(no->pEsq,valor,cont);
		retornacodigo(no->pDir,valor,cont);
	}
	if(busca(no->pDir,valor)){
		printf("1");
		*cont = *cont + 1;
		retornacodigo(no->pDir,valor,cont);
		retornacodigo(no->pEsq,valor,cont);
	}
}

int main() {
  	int i = 1,j;
  	double cont = 1,valor = 0;
	TLista lista;
	iniciarLista (&lista);


  int n;
  printf("Digite o tamanho da string: ");
  scanf("%d", &n );
  char palavra[n+1];

  getchar();

  scanf ("%[^\n]", palavra);
  char valores[n+1];
  int contador=0;
  for (i = 0; i < n; i++) {
    if (!buscarE(&lista,palavra[i])){
      TItem item;
      item.valor = palavra[i];

      for (j = i+1; j < n; j++) {
        if (palavra[i] == palavra[j])
          cont++;
      }
      item.chave = (cont / (double) n) * 100;
      TNo *no = criarNo(item);
      cont = 1;
      valores[contador] = palavra[i];
      contador++;
      inserir(&lista,no);
      printf("%c\n", palavra[i] );
    }
  }

  imprimir (&lista);
  while(valor != 100 && !isVazia(&lista)){
    TItem itemresu;
    TNo *no1 = retornaPrimeiro(&lista);
    TNo *no2 = retornaSegundo(&lista);
    itemresu.chave = no1->item.chave + no2->item.chave;
    TNo *resu = criarNo(itemresu);
    valor = itemresu.chave;
    resu->pEsq = no1;
    resu->pDir = no2;
    resu->item.valor = '\0';
    inserir(&lista,resu);
    removerDois(&lista);
  }

  TNo *no1 = retornaPrimeiro(&lista);


  printf("Árvore usando pré-ordem: --------------------------------------- \n");
  preOrdem (no1);

  printf("Codificação-------------------------------------");
  printf("\n");


  int contadorb = 0;
  for (i = 0; i < contador; ++i){
  	printf("Valor de %c = ",valores[i]);
  	retornacodigo(no1,valores[i],&contadorb);
  	printf("\n");
  }
  printf("%d\n",contadorb);

  double compressao;

  compressao =  (1 -(double) contadorb / ((double) n * 8)) * 100;
  char teste = '%';
  printf("Compressão = %.2lf %c\n",compressao,teste);

}



