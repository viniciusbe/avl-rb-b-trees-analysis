#include <stdlib.h>
#include <stdio.h>
#include "avl.h"

long int contadorAVL = 0;

ArvoreAVL* criarArvoreAVL() {
    ArvoreAVL *arvore = malloc(sizeof(ArvoreAVL));
    arvore->raiz = NULL;
  
    return arvore;
}

No* adicionarValorAVL(ArvoreAVL* arvore, int valor) {
    if (arvore->raiz == NULL) {
        printf("Adicionando %d\n",valor);
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
    No* no = localizarValor(arvore, valor);
    if(no == NULL) return;
    removerNo(arvore, no);
}

void removerNo(ArvoreAVL* arvore, No* no) {
    if (no->esquerda != NULL) {
        removerNo(arvore, no->esquerda);
    }

    if (no->direita != NULL) {
        removerNo(arvore, no->direita);
    }

    if (no->pai == NULL) {
        arvore->raiz = NULL;
    } else {
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
    if (valor > no->valor) {
        if (no->direita == NULL) {
            printf("Adicionando %d\n",valor);
            No* novo = criarNo(valor);
            novo->pai = no;
            no->direita = novo;
				
            return novo;
        } else {
            return adicionarNo(no->direita, valor);
        }
    } else {
        if (no->esquerda == NULL) {
            printf("Adicionando %d\n",valor);
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
    while (no != NULL) {
        int fator = fb(no);

        if (fator > 1) { //arvore mais profunda a esquerda
            //rotacao a direita
            if (fb(no->esquerda) > 0) {
                printf("RSD(%d)\n", no->valor);
                rsd(a, no);
            } else {
                printf("RDD(%d)\n", no->valor);
                rdd(a, no);
            }
        } else if (fator < -1) {
            //rotacao a esquerda
            if (fb(no->direita) < 0) {
                printf("RSE(%d)\n", no->valor);
                rse(a, no);
            } else {
                printf("RDE(%d)\n", no->valor);
                rde(a, no);
            }
        }

        no = no->pai;
    }
}

No* localizarValor(No* no, int valor) {
    if (no->valor == valor) {
        return no;
    } else {
        if (valor < no->valor) {
            if (no->esquerda != NULL) {
                return localizarValor(no->esquerda, valor);
            }
        } else {
            if (no->direita != NULL) {
                return localizarValor(no->direita, valor);
            }
        }
    }

    return NULL;
}



int altura(No* no){
    int esquerda = 0,direita = 0;

    if (no->esquerda != NULL) {
        esquerda = altura(no->esquerda) + 1;
    }

    if (no->direita != NULL) {
        direita = altura(no->direita) + 1;
    }
  
    return esquerda > direita ? esquerda : direita; //max(esquerda,direita)
}

int fb(No* no) {
    int esquerda = 0,direita = 0;
  
    if (no->esquerda != NULL) {
        esquerda = altura(no->esquerda) + 1;
    }

    if (no->direita != NULL) {
        direita = altura(no->direita) + 1;
    }
  
    return esquerda - direita;
}

No* rse(ArvoreAVL* arvore, No* no) {
    No* pai = no->pai;
    No* direita = no->direita;

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

No* rsd(ArvoreAVL* arvore, No* no) {
    No* pai = no->pai;
    No* esquerda = no->esquerda;

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

No* rde(ArvoreAVL* arvore, No* no) {
    no->direita = rsd(arvore, no->direita);
    return rse(arvore, no);
}

No* rdd(ArvoreAVL* arvore, No* no) {
    no->esquerda = rse(arvore, no->esquerda);
    return rsd(arvore, no);
}

int main() {
    ArvoreAVL* a = criarArvoreAVL();
   
    int i;
    for (i = 1; i <= 9; i++) {
        adicionarValorAVL(a, i);
    }

    printf("Altura: %d\n", altura(a->raiz) + 1);
    printf("In-order: ");
    printf("\n");
}