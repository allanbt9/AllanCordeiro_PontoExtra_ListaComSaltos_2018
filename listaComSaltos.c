#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Nodo *PNodo;
PNodo CriarNodo(char* x,int niv);
int gerarNivelAleatorio(int maxNiv);
PNodo criaLista(char* x,int maxNiv);
PNodo liberaNodo(PNodo p);
void destroiLista(PNodo Pcab);
int busca(PNodo Pcab, char *x);
PNodo *PesquisarAnterior (PNodo PCab, char* X);

struct Nodo{
	char elemento[40];
	int niveis;
	PNodo *PtProx;
};

PNodo CriarNodo(char* x,int niv){
	int k;
	PNodo p;

	p = (PNodo)malloc(sizeof(struct Nodo));
	if(p == NULL)
		return NULL;

	p->PtProx = (PNodo*)malloc(niv * sizeof(PNodo));
	if(p->PtProx == NULL)
		return NULL;

	strcpy(p->elemento,x);
	p->niveis = niv;

	for(k=0;k<niv;k++){
		p->PtProx[k] = NULL;
	}

	return p;
}

//gerar o nivel de um nodo da lista
//usando fatores

int gerarNivelAleatorio(int maxNiv){
	int niv = maxNiv;
	float aux = (pow(2,maxNiv)) - 1;
	float t;
	float fator = 1 / aux;

	srand(time(NULL));
	t = rand();

	int i;
	for(i=0;i<maxNiv-1;i++){
		float aux2 = pow(2,i) * fator;
		if(t <= aux2)
			return niv;
		niv--;
	}

	return 1;
}


//cria um nodo que será a cabeça da lista
PNodo criaLista(char* x,int maxNiv){
	PNodo p;
	p = CriarNodo(x,maxNiv);

	return p;
}

PNodo liberaNodo(PNodo p){
	int i;
	for(i=0;i<p->niveis;i++){
		p->PtProx[i] = NULL;
	}	
	free(p->PtProx);
	free(p);
	p = NULL;

	return p;
}

void destroiLista(PNodo Pcab){
	PNodo Paux;
	PNodo p = Pcab->PtProx[0];

	while(p != NULL){
		Paux = p;
		p = p->PtProx[0];
		Paux = liberaNodo(Paux);
	}

	//a partir da fica fica apenas a cabeça da lista
	//logo será feito de forma sequencial
	int i;
	for(i=0;i<Pcab->niveis;i++){
		Pcab->PtProx[i] = NULL;
	}

}

int busca(PNodo Pcab, char *x){
	PNodo p = Pcab;
	
	int i;
	for(i=Pcab->niveis;i>0;i--){
		while(p->PtProx[i-1] != NULL && strcmp((p->PtProx[i-1])->elemento,x) < 0)
			p = p->PtProx[i-1];

		if(p->PtProx[i-1] != NULL && strcmp((p->PtProx[i-1])->elemento,x) == 0)
			return 1; 

	}

	return 0;
}

PNodo *PesquisarAnterior(PNodo PCab, char* X) {
	int k;
	PNodo *PAnt, P = PCab;
	PAnt = (PNodo*) malloc(PCab->niveis * sizeof(PNodo));

	if (PAnt == NULL)
		return NULL;


	for (k = PCab->niveis; k > 0; k--) {
		while (P->PtProx[k-1] != NULL && strcmp((P->PtProx[k-1])->elemento,X) < 0)
			P = P->PtProx[k-1];
	 		PAnt[k-1] = P;
	 	}

	return PAnt;
} 

void insereNovoElemento(PNodo Pcab, char *elemento){
	PNodo p, *Pant;

	if(strcmp(Pcab->elemento,elemento) < 0)
		strcpy(Pcab->elemento,elemento);

	int nivel = gerarNivelAleatorio(Pcab->niveis);

	p = CriarNodo(elemento,nivel);

	if(p == NULL)//erro ao criar o nó
		return;

	Pant = PesquisarAnterior(Pcab,elemento);

	int i;
	for(i=nivel;i>0;i--){
		p->PtProx[i-1] = Pant[i-1]->PtProx[i-1];
		Pant[i-1]->PtProx[i-1] = p;
	}
}


int main(){
	

	return 0;
}
