#include <stdlib.h>
#include <stdio.h>
#include "avl.h"

long int contadorAVL = 0;

ArvoreAVL* criarArvoreAVL() {
    ArvoreAVL *arvore = malloc(sizeof(ArvoreAVL));
    arvore->raiz = NULL;
  
    return arvore;
}

long int adicionarValorAVL(ArvoreAVL* arvore, int valor) {
    contadorAVL = 1;
    if (arvore->raiz == NULL) {
        NoAVL* novo = criarNo(NULL, valor);
        arvore->raiz = novo;
			
        return contadorAVL;
    } else {
        NoAVL* no = adicionarNo(arvore->raiz, valor);
        balancearAdicao(arvore, no);
        return contadorAVL;
    }
}

NoAVL* encontrarMinimoAVL(NoAVL* no) {
    if (no->esquerda == NULL) {
        return no;
    }

    return encontrarMinimoAVL(no->esquerda);
}

long int removerValorAVL(ArvoreAVL* arvore, int valor) {
    contadorAVL = 0;
    if(arvore->raiz == NULL) printf("\nRaiz nula");
    printf("\nRemovendo Valor %d\n",valor);
    arvore->raiz = removerNo(arvore, arvore->raiz, valor);
    
    return contadorAVL;
}

NoAVL* removerNo(ArvoreAVL* arvore, NoAVL* raiz, int chave) {
    contadorAVL++;

    if(raiz == NULL) return raiz;

    if(chave < raiz->valor) {
        raiz->esquerda = removerNo(arvore, raiz->esquerda, chave);
    } else if (chave > raiz->valor) {
        raiz->direita = removerNo(arvore, raiz->direita, chave);
    } else {
        if (raiz->esquerda == NULL) {
            NoAVL* temp = raiz->direita;
            if(temp != NULL) {
                temp->pai = raiz->pai;
            }
            free(raiz);
            return temp;
        }
        else if (raiz->direita == NULL) {
            NoAVL* temp = raiz->esquerda;
            if(temp != NULL) {
                temp->pai = raiz->pai;
            }
            free(raiz);
            return temp;
        }
        NoAVL* temp = encontrarMinimoAVL(raiz->direita);
        raiz->valor = temp->valor;
        raiz->direita = removerNo(arvore, raiz->direita, temp->valor);
    }
    
    NoAVL* noBalanceado = balancear(arvore, raiz);
    if(noBalanceado != NULL) {
        return noBalanceado;
    }

    return raiz;
}

NoAVL* criarNo(NoAVL* pai, int valor) {
    NoAVL* no = malloc(sizeof(NoAVL));
    no->valor = valor;
    no->pai = pai;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

NoAVL* adicionarNo(NoAVL* no, int valor) {
    contadorAVL++;
    if (valor > no->valor) {
        if (no->direita == NULL) {
            NoAVL* novo = criarNo(no, valor);
            no->direita = novo;
				
            return novo;
        } else {
            return adicionarNo(no->direita, valor);
        }
    } else {
        if (no->esquerda == NULL) {
            NoAVL* novo = criarNo(no, valor);
			no->esquerda = novo;
			
            return novo;
        } else {
            return adicionarNo(no->esquerda, valor);
        }
    }
}

void balancearAdicao(ArvoreAVL* a, NoAVL* no) {
    while (no != NULL) {
        contadorAVL++;
        int fator = fb(no);

        if (fator > 1) { //arvore mais profunda a esquerda
            if (fb(no->esquerda) > 0) {
                rsd(a, no);
            } else {
                rdd(a, no);
            }
        } else if (fator < -1) {
            if (fb(no->direita) < 0) {
                rse(a, no);
            } else {
                rde(a, no);
            }
        }

        no = no->pai;
    }
}

NoAVL* balancear(ArvoreAVL* a, NoAVL* no) {
    contadorAVL++;
    int fator = fb(no);

    if (fator > 1) { //arvore mais profunda a esquerda
        if (fb(no->esquerda) > 0) {
            return rsd(a, no);
        } else {
            return rdd(a, no);
        }
    } else if (fator < -1) {
        if (fb(no->direita) < 0) {
            return rse(a, no);
        } else {
            return rde(a, no);
        }
    }

    return NULL;
}

int altura(NoAVL* no){
    int esquerda = 0,direita = 0;

    if (no->esquerda != NULL) {
        esquerda = altura(no->esquerda) + 1;
    }

    if (no->direita != NULL) {
        direita = altura(no->direita) + 1;
    }
  
    return esquerda > direita ? esquerda : direita; //max(esquerda,direita)
}

int fb(NoAVL* no) {
    contadorAVL++;
    int esquerda = 0,direita = 0;

    if (no->esquerda != NULL) {
        esquerda = altura(no->esquerda) + 1;
    }

    if (no->direita != NULL) {
        direita = altura(no->direita) + 1;
    }
  
    return esquerda - direita;
}

NoAVL* rse(ArvoreAVL* arvore, NoAVL* no) {
    contadorAVL++;
    NoAVL* pai = no->pai;
    NoAVL* direita = no->direita;

    printf("\nRot a esquerda: %d\n",no->valor);

    if (direita->esquerda != NULL) {
        direita->esquerda->pai = no;
    } 
  
    no->direita = direita->esquerda;
    no->pai = direita;

    direita->esquerda = no;
    direita->pai = pai;

    if (pai == NULL) {
        arvore->raiz = direita;
    } else {
        if (pai->esquerda == no) {
            pai->esquerda = direita;
        } else {
            pai->direita = direita;
        }
    }

    return direita;
}

NoAVL* rsd(ArvoreAVL* arvore, NoAVL* no) {
    contadorAVL++;
    NoAVL* pai = no->pai;
    NoAVL* esquerda = no->esquerda;

    printf("\nRot a direita: %d\n",no->valor);

    if (esquerda->direita != NULL) {
        esquerda->direita->pai = no;
    } 
  
    no->esquerda = esquerda->direita;
    no->pai = esquerda;
  
    esquerda->direita = no;
    esquerda->pai = pai;

    if (pai == NULL) {
        arvore->raiz = esquerda;
    } else {
        if (pai->esquerda == no) {
            pai->esquerda = esquerda;
        } else {
            pai->direita = esquerda;
        }
    }

    return esquerda;
}

NoAVL* rde(ArvoreAVL* arvore, NoAVL* no) {
    no->direita = rsd(arvore, no->direita);
    return rse(arvore, no);
}

NoAVL* rdd(ArvoreAVL* arvore, NoAVL* no) {
    no->esquerda = rse(arvore, no->esquerda);
    return rsd(arvore, no);
}
