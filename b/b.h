#include <stdio.h>
#include <stdlib.h>

typedef struct noB {
    int total;
    int* chaves;
    struct noB** filhos;
    struct noB* pai; 
} NoB;

typedef struct arvoreB {
  NoB* raiz;
  int ordem;
} ArvoreB;

ArvoreB* criarArvoreB(int);
NoB* criaNo(ArvoreB*);
int pesquisaBinaria(NoB*, int);
NoB* localizaNo(ArvoreB*, int);
void adicionaChaveNo(NoB*, NoB*, int);
int transbordo(ArvoreB*,NoB*);
NoB* divideNo(ArvoreB*, NoB*);
void adicionaChaveRecursivo(ArvoreB*, NoB*, NoB*, int);
int adicionarValorB(ArvoreB*, int);
long int removerValorB(ArvoreB*, int);