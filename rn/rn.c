#include <stdlib.h> 
#include <stdio.h> 
#include <time.h>
#include "rn.h"

long int contadorRN = 0; 

static NoRN* criarNo(ArvoreRN* arvore, NoRN* pai, int valor); 
static NoRN* adicionarNo(ArvoreRN* arvore, NoRN* no, int valor);
static void balancearAdicao(ArvoreRN* arvore, NoRN* no); 
static void rotacionarEsquerda(ArvoreRN* arvore, NoRN* no); 
static void rotacionarDireita(ArvoreRN* arvore, NoRN* no);
static void transplantar(ArvoreRN* arvore, NoRN* atual, NoRN* novo);
static NoRN* encontrarMinimoRN(NoRN* no, NoRN* nulo);
static NoRN* localizar(ArvoreRN* arvore, int valor);
static void balancearRemocao(ArvoreRN* arvore, NoRN* no);

ArvoreRN* criarArvoreRN() { 
    ArvoreRN *arvore = malloc(sizeof(ArvoreRN)); 
    arvore->nulo = NULL; 
    arvore->raiz = NULL;

    arvore->nulo = criarNo(arvore, NULL, 0); 
    arvore->nulo->cor = Preto; 

    return arvore; 
} 

NoRN* criarNo(ArvoreRN* arvore, NoRN* pai, int valor) { 
    NoRN* no = malloc(sizeof(NoRN)); 

    no->pai = pai;     
    no->valor = valor; 
    no->direita = arvore->nulo; 
    no->esquerda = arvore->nulo; 
    return no; 
} 

NoRN* adicionarNo(ArvoreRN* arvore, NoRN* no, int valor) { 
    contadorRN++; 
    if (valor > no->valor) { 
        if (no->direita == arvore->nulo) { 
            no->direita = criarNo(arvore, no, valor);      
            no->direita->cor = Vermelho;        
            return no->direita; 
        } else { 
            return adicionarNo(arvore, no->direita, valor); 
        } 

    } else { 
        if (no->esquerda == arvore->nulo) { 
            no->esquerda = criarNo(arvore, no, valor); 
            no->esquerda->cor = Vermelho; 
            return no->esquerda; 
        } else { 
            return adicionarNo(arvore, no->esquerda, valor); 
        } 
    } 
} 

long int removerValorRN(ArvoreRN* arvore, int valor) {
    contadorRN = 0;
    NoRN* no = localizar(arvore, valor);
    removerNoRN(arvore, no);

    return contadorRN;
}

NoRN* localizar(ArvoreRN* arvore, int valor) {
    if (arvore->raiz != NULL) {
        NoRN* no = arvore->raiz;

        while (no != arvore->nulo) {
            contadorRN++;
            if (no->valor == valor) {
                return no;
            } else {
                no = valor < no->valor ? no->esquerda : no->direita;
            }
        }
    }

    return NULL;
}
  
long int adicionarValorRN(ArvoreRN* arvore, int valor) { 
    contadorRN = 1; 
    if (arvore->raiz == NULL) { 
        arvore->raiz = criarNo(arvore, arvore->nulo, valor); 
        arvore->raiz->cor = Preto; 
         
        return contadorRN; 
    } else { 
        NoRN* no = adicionarNo(arvore, arvore->raiz, valor); 
        balancearAdicao(arvore, no); 
        return contadorRN; 
    } 
} 

void removerNoRN(ArvoreRN* arvore, NoRN* no) {
    if (arvore == NULL || arvore->raiz == NULL || no == NULL) {
        return;
    }
    contadorRN++;

    NoRN* y = no;
    NoRN* x;
    Cor corOriginalY = y->cor;

    if (no->esquerda == arvore->nulo) {
        x = no->direita;
        transplantar(arvore, no, no->direita);
    } else if (no->direita == arvore->nulo) {
        x = no->esquerda;
        transplantar(arvore, no, no->esquerda);
    } else {
        y = encontrarMinimoRN(no->direita, arvore->nulo);
        corOriginalY = y->cor;
        x = y->direita;

          if (y->pai == no) {
            x->pai = y;
        } else { 
            transplantar(arvore, y, y->direita);
            y->direita = no->direita;
            y->direita->pai = y;
        }

        transplantar(arvore, no, y);
        y->esquerda = no->esquerda;
        y->esquerda->pai = y;
        y->cor = no->cor;
    }

    if (corOriginalY == Preto) {
        balancearRemocao(arvore, x);
    }

    free(no);
}

void transplantar(ArvoreRN* arvore, NoRN* atual, NoRN* novo) {
    contadorRN++;

    if (atual->pai == arvore->nulo) {
        arvore->raiz = novo;
    } else if (atual == atual->pai->esquerda) {
        atual->pai->esquerda = novo;
    } else {
        atual->pai->direita = novo;
    }
    
    novo->pai = atual->pai;
}

NoRN* encontrarMinimoRN(NoRN* no, NoRN* nulo) {
    while (no->esquerda != nulo) {
        contadorRN++;
        no = no->esquerda;
    }
    return no;
}

void balancearAdicao(ArvoreRN* arvore, NoRN* no) { 
    while (no->pai->cor == Vermelho) { 
        contadorRN++; 
        if (no->pai == no->pai->pai->esquerda) { 
            NoRN *tio = no->pai->pai->direita; 

            if (tio->cor == Vermelho) { 
                tio->cor = Preto; //Caso 1 
                no->pai->cor = Preto;  
                no->pai->pai->cor = Vermelho; //Caso 1 
                no = no->pai->pai; //Caso 1 
            } else { 
                if (no == no->pai->direita) {
                    no = no->pai; //Caso 2
                    rotacionarEsquerda(arvore, no); //Caso 2 
                } else { 
                    no->pai->cor = Preto;  
                    no->pai->pai->cor = Vermelho; //Caso 3 
                    rotacionarDireita(arvore, no->pai->pai); //Caso 3 
                } 
            } 
        } else { 
            NoRN *tio = no->pai->pai->esquerda; 

            if (tio->cor == Vermelho) { 
                tio->cor = Preto; //Caso 1 
                no->pai->cor = Preto;  
                no->pai->pai->cor = Vermelho; //Caso 1 
                no = no->pai->pai; //Caso 1 
            } else { 
                if (no == no->pai->esquerda) {
                    no = no->pai; //Caso 2 
                    rotacionarDireita(arvore, no); //Caso 2 
                } else {
                    no->pai->cor = Preto;  
                    no->pai->pai->cor = Vermelho; //Caso 3 
                    rotacionarEsquerda(arvore, no->pai->pai); //Caso 3 
                } 
            } 
        } 
    } 

    arvore->raiz->cor = Preto; // Conserta possível quebra regra 2 
} 

void balancearRemocao(ArvoreRN* arvore, NoRN* no) {
    while (no != arvore->raiz && no->cor == Preto) {
        contadorRN++;
        if (no == no->pai->esquerda) {
            NoRN* irmao = no->pai->direita;
            
            if (irmao->cor == Vermelho) {
                irmao->cor = Preto;
                no->pai->cor = Vermelho;
                rotacionarEsquerda(arvore, no->pai);
                irmao = no->pai->direita;
            }
            
            if (irmao->esquerda->cor == Preto && irmao->direita->cor == Preto) {
                irmao->cor = Vermelho;
                no = no->pai;
            } else {
                if (irmao->direita->cor == Preto) {
                    irmao->esquerda->cor = Preto;
                    irmao->cor = Vermelho;
                    rotacionarDireita(arvore, irmao);
                    irmao = no->pai->direita;
                }
                
                irmao->cor = no->pai->cor;
                no->pai->cor = Preto;
                irmao->direita->cor = Preto;
                rotacionarEsquerda(arvore, no->pai);
                no = arvore->raiz;
            }
        } else {
            NoRN* irmao = no->pai->esquerda;
            
            if (irmao->cor == Vermelho) {
                irmao->cor = Preto;
                no->pai->cor = Vermelho;
                rotacionarDireita(arvore, no->pai);
                irmao = no->pai->esquerda;
            }
            
            if (irmao->direita->cor == Preto && irmao->esquerda->cor == Preto) {
                irmao->cor = Vermelho;
                no = no->pai;
            } else {
                if (irmao->esquerda->cor == Preto) {
                    irmao->direita->cor = Preto;
                    irmao->cor = Vermelho;
                    rotacionarEsquerda(arvore, irmao);
                    irmao = no->pai->esquerda;
                }
                
                irmao->cor = no->pai->cor;
                no->pai->cor = Preto;
                irmao->esquerda->cor = Preto;
                rotacionarDireita(arvore, no->pai);
                no = arvore->raiz;
            }
        }
    }
    
    no->cor = Preto;
}

void rotacionarEsquerda(ArvoreRN* arvore, NoRN* no) { 
    contadorRN++;
    NoRN* direita = no->direita; 
    no->direita = direita->esquerda;  
    
    if (direita->esquerda != arvore->nulo) { 
        direita->esquerda->pai = no; 
    }
    direita->pai = no->pai; 

    if (no->pai == arvore->nulo) { 
        arvore->raiz = direita; 
    } else if (no == no->pai->esquerda) { 
        no->pai->esquerda = direita; 
    } else { 
        no->pai->direita = direita; 
    } 
    direita->esquerda = no; 
    no->pai = direita; 
} 

void rotacionarDireita(ArvoreRN* arvore, NoRN* no) { 
    contadorRN++;
    NoRN* esquerda = no->esquerda; 
    no->esquerda = esquerda->direita; 

    if (esquerda->direita != arvore->nulo) { 
        esquerda->direita->pai = no; 
    } 

    esquerda->pai = no->pai; 

    if (no->pai == arvore->nulo) { 
        arvore->raiz = esquerda; 
    } else if (no == no->pai->esquerda) { 
        no->pai->esquerda = esquerda; 
    } else { 
        no->pai->direita = esquerda; 
    } 
    esquerda->direita = no; 
    no->pai = esquerda; 
} 