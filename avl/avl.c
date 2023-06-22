#include <stdlib.h>
#include <stdio.h>
#include "avl.h"

unsigned long int contadorAVL = 0;

ArvoreAVL* criarArvoreAVL() {
    ArvoreAVL *arvore = malloc(sizeof(ArvoreAVL));
    arvore->raiz = NULL;
  
    return arvore;
}

No* adicionarValorAVL(ArvoreAVL* arvore, int valor) {
    contadorAVL++;
    if (arvore->raiz == NULL) {
        No* novo = criarNo(valor);
        arvore->raiz = novo;
			
        return novo;
    } else {
        No* no = adicionarNo(arvore->raiz, valor);
        balancear(arvore, no);
        return no;
    }
}

void removerValorAVL(ArvoreAVL* arvore, int valor) {
    No* no = localizarValor(arvore->raiz, valor);
    contadorAVL++;
    if(no == NULL) return;
    removerNo(arvore, no);
}

void removerNo(ArvoreAVL* arvore, No* no) {
    contadorAVL++;
    if (no->esquerda != NULL) {
        removerNo(arvore, no->esquerda);
    }

    contadorAVL++;
    if (no->direita != NULL) {
        removerNo(arvore, no->direita);
    }

    contadorAVL++;
    if (no->pai == NULL) {
        arvore->raiz = NULL;
    } else {
        contadorAVL++;
        if (no->pai->esquerda == no) {
            no->pai->esquerda = NULL;
        } else {
            no->pai->direita = NULL;
        }
    }

    free(no);
}

No* criarNo(int valor) {
    No* no = malloc(sizeof(No));
    no->valor = valor;
    no->pai = NULL;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

No* adicionarNo(No* no, int valor) {
    contadorAVL++;
    if (valor > no->valor) {
        contadorAVL++;
        if (no->direita == NULL) {
            No* novo = criarNo(valor);
            novo->pai = no;
            no->direita = novo;
				
            return novo;
        } else {
            return adicionarNo(no->direita, valor);
        }
    } else {
        contadorAVL++;
        if (no->esquerda == NULL) {
            No* novo = criarNo(valor);
			novo->pai = no;
			no->esquerda = novo;
			
            return novo;
        } else {
            return adicionarNo(no->esquerda, valor);
        }
    }
}



void balancear(ArvoreAVL* a, No* no) {
    contadorAVL++;
    while (no != NULL) {
        int fator = fb(no);

        contadorAVL += 2;
        if (fator > 1) { //arvore mais profunda a esquerda
            //rotacao a direita
            contadorAVL++;
            if (fb(no->esquerda) > 0) {
                rsd(a, no);
            } else {
                rdd(a, no);
            }
        } else if (fator < -1) {
            //rotacao a esquerda
            contadorAVL++;
            if (fb(no->direita) < 0) {
                rse(a, no);
            } else {
                rde(a, no);
            }
        }

        no = no->pai;
        contadorAVL++;
    }
}

No* localizarValor(No* no, int valor) {
    contadorAVL++;
    if (no->valor == valor) {
        return no;
    } else {
        contadorAVL++;
        if (valor < no->valor) {
            contadorAVL++;
            if (no->esquerda != NULL) {
                return localizarValor(no->esquerda, valor);
            }
        } else {
            contadorAVL++;
            if (no->direita != NULL) {
                return localizarValor(no->direita, valor);
            }
        }
    }

    return NULL;
}



int altura(No* no){
    int esquerda = 0,direita = 0;

    contadorAVL++;
    if (no->esquerda != NULL) {
        esquerda = altura(no->esquerda) + 1;
    }

    contadorAVL++;
    if (no->direita != NULL) {
        direita = altura(no->direita) + 1;
    }
  
    contadorAVL++;
    return esquerda > direita ? esquerda : direita; //max(esquerda,direita)
}

int fb(No* no) {
    int esquerda = 0,direita = 0;
  
    contadorAVL++;
    if (no->esquerda != NULL) {
        esquerda = altura(no->esquerda) + 1;
    }

    contadorAVL++;
    if (no->direita != NULL) {
        direita = altura(no->direita) + 1;
    }
  
    return esquerda - direita;
}

No* rse(ArvoreAVL* arvore, No* no) {
    No* pai = no->pai;
    No* direita = no->direita;

    contadorAVL++;
    if (direita->esquerda != NULL) {
        direita->esquerda->pai = no;
    } 
  
    no->direita = direita->esquerda;
    no->pai = direita;

    direita->esquerda = no;
    direita->pai = pai;

    contadorAVL++;
    if (pai == NULL) {
        arvore->raiz = direita;
    } else {
        contadorAVL++;
        if (pai->esquerda == no) {
            pai->esquerda = direita;
        } else {
            pai->direita = direita;
        }
    }

    return direita;
}

No* rsd(ArvoreAVL* arvore, No* no) {
    No* pai = no->pai;
    No* esquerda = no->esquerda;

    contadorAVL++;
    if (esquerda->direita != NULL) {
        esquerda->direita->pai = no;
    } 
  
    no->esquerda = esquerda->direita;
    no->pai = esquerda;
  
    esquerda->direita = no;
    esquerda->pai = pai;

    contadorAVL++;
    if (pai == NULL) {
        arvore->raiz = esquerda;
    } else {
        contadorAVL++;
        if (pai->esquerda == no) {
            pai->esquerda = esquerda;
        } else {
            pai->direita = esquerda;
        }
    }

    return esquerda;
}

No* rde(ArvoreAVL* arvore, No* no) {
    no->direita = rsd(arvore, no->direita);
    return rse(arvore, no);
}

No* rdd(ArvoreAVL* arvore, No* no) {
    no->esquerda = rse(arvore, no->esquerda);
    return rsd(arvore, no);
}
