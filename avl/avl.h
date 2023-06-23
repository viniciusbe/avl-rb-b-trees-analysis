#include <stdlib.h>
#include <stdio.h>

typedef struct noAVL {
    struct noAVL* pai;
    struct noAVL* esquerda;
    struct noAVL* direita;
    int valor;
} NoAVL;

typedef struct arvoreAVL {
    struct noAVL* raiz;
} ArvoreAVL;

ArvoreAVL* criarArvoreAVL();
int adicionarValorAVL(ArvoreAVL* arvore, int valor);
void removerValorAVL(ArvoreAVL* arvore, int valor);

static NoAVL* criarNo(NoAVL* pai, int valor);
static NoAVL* adicionarNo(NoAVL* no, int valor);
static void removerNo(ArvoreAVL* arvore, NoAVL* no);
static NoAVL* localizarValor(NoAVL* no, int valor);
static void balancear(ArvoreAVL* arvore, NoAVL* no);
static int altura(NoAVL* no);
int fb(NoAVL* no);
NoAVL* rse(ArvoreAVL* arvore, NoAVL* no);
NoAVL* rsd(ArvoreAVL* arvore, NoAVL* no);
NoAVL* rdd(ArvoreAVL* arvore, NoAVL* no);
NoAVL* rde(ArvoreAVL* arvore, NoAVL* no);