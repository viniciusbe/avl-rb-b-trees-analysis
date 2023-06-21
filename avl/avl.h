#include <stdlib.h>
#include <stdio.h>

typedef struct no {
    struct no* pai;
    struct no* esquerda;
    struct no* direita;
    int valor;
} No;

typedef struct arvore {
    struct no* raiz;
} ArvoreAVL;

ArvoreAVL* criarArvoreAVL();
No* adicionarValorAVL(ArvoreAVL* arvore, int valor);
void removerValorAVL(ArvoreAVL* arvore, int valor);

No* criarNo(int valor);
No* adicionarNo(No* no, int valor);
void removerNo(ArvoreAVL* arvore, No* no);
No* localizarValor(No* no, int valor);
void balancear(ArvoreAVL*, No*);
int altura(No*);
int fb(No*);
No* rse(ArvoreAVL*, No*);
No* rsd(ArvoreAVL*, No*);
No* rdd(ArvoreAVL*, No*);
No* rde(ArvoreAVL*, No*);