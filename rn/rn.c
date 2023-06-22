#include <stdlib.h> 
#include <stdio.h> 
#include <time.h>
#include "rn.h"

unsigned long int contadorRN = 0; 

static NoRN* criarNo(ArvoreRN* arvore, NoRN* pai, int valor); 
static NoRN* adicionarNo(ArvoreRN* arvore, NoRN* no, int valor);
static void balancear(ArvoreRN* arvore, NoRN* no); 
static void rotacionarEsquerda(ArvoreRN* arvore, NoRN* no); 
static void rotacionarDireita(ArvoreRN* arvore, NoRN* no); 

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
        contadorRN++;
        if (no->direita == arvore->nulo) { 
            no->direita = criarNo(arvore, no, valor);      
            no->direita->cor = Vermelho;        
            return no->direita; 
        } else { 
            return adicionarNo(arvore, no->direita, valor); 
        } 

    } else { 
        contadorRN++;
        if (no->esquerda == arvore->nulo) { 
            no->esquerda = criarNo(arvore, no, valor); 
            no->esquerda->cor = Vermelho; 
            return no->esquerda; 
        } else { 
            return adicionarNo(arvore, no->esquerda, valor); 
        } 
    } 
} 
  
NoRN* adicionarValorRN(ArvoreRN* arvore, int valor) { 
    contadorRN++; 
    if (arvore->raiz == NULL) { 
        arvore->raiz = criarNo(arvore, arvore->nulo, valor); 
        arvore->raiz->cor = Preto; 
         
        return arvore->raiz; 
    } else { 
        NoRN* no = adicionarNo(arvore, arvore->raiz, valor); 
        balancear(arvore, no); 
        return no; 
    } 
} 

void balancear(ArvoreRN* arvore, NoRN* no) { 
    contadorRN++;
    while (no->pai->cor == Vermelho) { 
        contadorRN++; 
        if (no->pai == no->pai->pai->esquerda) { 
            NoRN *tio = no->pai->pai->direita; 

            contadorRN++;
            if (tio->cor == Vermelho) { 
                tio->cor = Preto; //Caso 1 
                no->pai->cor = Preto;  
                no->pai->pai->cor = Vermelho; //Caso 1 
                no = no->pai->pai; //Caso 1 
            } else { 
                contadorRN++;
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

            contadorRN++;
            if (tio->cor == Vermelho) { 
                tio->cor = Preto; //Caso 1 
                no->pai->cor = Preto;  
                no->pai->pai->cor = Vermelho; //Caso 1 
                no = no->pai->pai; //Caso 1 
            } else { 
                contadorRN++;
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

        contadorRN++;
    } 

    arvore->raiz->cor = Preto; // Conserta possível quebra regra 2 
} 

void rotacionarEsquerda(ArvoreRN* arvore, NoRN* no) { 
    NoRN* direita = no->direita; 
    no->direita = direita->esquerda;  
    contadorRN++; 
    if (direita->esquerda != arvore->nulo) { 
        direita->esquerda->pai = no; 
    }
    direita->pai = no->pai; 

    if (no->pai == arvore->nulo) { 
        contadorRN++;
        arvore->raiz = direita; 
    } else if (no == no->pai->esquerda) { 
        contadorRN += 2;
        no->pai->esquerda = direita; 
    } else { 
        contadorRN += 2;
        no->pai->direita = direita; 
    } 
    direita->esquerda = no; 
    no->pai = direita; 
} 

void rotacionarDireita(ArvoreRN* arvore, NoRN* no) { 
    NoRN* esquerda = no->esquerda; 
    no->esquerda = esquerda->direita; 
    contadorRN++; 
    if (esquerda->direita != arvore->nulo) { 
        esquerda->direita->pai = no; 
    } 
    esquerda->pai = no->pai; 

    if (no->pai == arvore->nulo) { 
        contadorRN++; 
        arvore->raiz = esquerda; 
    } else if (no == no->pai->esquerda) { 
        contadorRN+=2;
        no->pai->esquerda = esquerda; 
    } else { 
        contadorRN+=2;
        no->pai->direita = esquerda; 
    } 
    esquerda->direita = no; 
    no->pai = esquerda; 
} 