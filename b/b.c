#include "b.h"

long int contadorB = 0;

ArvoreB* criarArvoreB(int ordem) {
    ArvoreB* a = malloc(sizeof(ArvoreB));
    a->ordem = ordem;
    a->raiz = criaNo(a);

    return a;
}


NoB* criaNo(ArvoreB* arvore) {
    int max = arvore->ordem * 2;
    NoB* no = malloc(sizeof(NoB));

    no->pai = NULL;
        
    no->chaves = malloc(sizeof(int) * (max + 1));
    no->filhos = malloc(sizeof(NoB) * (max + 2));
    no->total = 0;

    for (int i = 0; i < max + 2; i++)
        no->filhos[i] = NULL;

    return no;
}

void percorreArvore(NoB* no) {
    if (no != NULL) {
        for (int i = 0; i < no->total; i++){
            percorreArvore(no->filhos[i]); //visita o filho a esquerda
            
            printf("%d ",no->chaves[i]);
        }

        percorreArvore(no->filhos[no->total]); //visita ultimo filho (direita)
    }
}

int pesquisaBinaria(NoB* no, int valor) {
    int inicio = 0, fim = no->total - 1, meio;		
    
    while (inicio <= fim) {	
        contadorB++;
        
        meio = (inicio + fim) / 2;
        
        if (no->chaves[meio] == valor) {	
		    return meio; //encontrou	
        } else if (no->chaves[meio] > valor) {
                fim	= meio - 1;	
        } else {
            inicio = meio + 1;
        }
    }
    return inicio; //não encontrou	
}

int localizaValor(ArvoreB* arvore, int valor) {	
    NoB *no = arvore->raiz;
    
    while (no != NULL) {
        int i = pesquisaBinaria(no, valor);

        if (i < no->total && no->chaves[i] == valor) {
            return 1; //encontrou
        } else {
            no = no->filhos[i];
        }
    }

    return 0; //não encontrou	
}

NoB* localizaNo(ArvoreB* arvore, int valor) {	
    NoB *no = arvore->raiz;
    
    while (no != NULL) {
        contadorB++;

        int i = pesquisaBinaria(no, valor);

        if (no->filhos[i] == NULL)
            return no; //encontrou nó
        else
            no = no->filhos[i];
    }

    return NULL; //não encontrou nenhum nó
}

void adicionaChaveNo(NoB* no, NoB* novo, int valor) {
    int i = pesquisaBinaria(no, valor);
    
    contadorB++;

    for (int j = no->total - 1; j >= i; j--) {
        no->chaves[j + 1] = no->chaves[j];
        no->filhos[j + 2] = no->filhos[j + 1];
    }
    
    no->chaves[i] = valor;
    no->filhos[i + 1] = novo;

    no->total++;
}

int transbordo(ArvoreB* arvore, NoB* no) {
    return no->total > arvore->ordem * 2;
}

NoB* divideNo(ArvoreB* arvore, NoB* no) {
    int meio = no->total / 2;
    NoB* novo = criaNo(arvore);
    novo->pai = no->pai;

    contadorB++;

    for (int i = meio + 1; i < no->total; i++) {
        novo->filhos[novo->total] = no->filhos[i];
        novo->chaves[novo->total] = no->chaves[i];
        if (novo->filhos[novo->total] != NULL) novo->filhos[novo->total]->pai = novo;
        
        novo->total++;
    }

    novo->filhos[novo->total] = no->filhos[no->total];
    if (novo->filhos[novo->total] != NULL) novo->filhos[novo->total]->pai = novo;    
    no->total = meio;
    return novo;
}

void adicionaChaveRecursivo(ArvoreB* arvore, NoB* no, NoB* novo, int valor) {
    contadorB++;
    
    adicionaChaveNo(no, novo, valor);
    
    if (transbordo(arvore, no)) {
        int promovido = no->chaves[arvore->ordem]; 
        NoB* novo = divideNo(arvore, no);

        contadorB++;
        
        if (no->pai == NULL) {
            NoB* pai = criaNo(arvore);            
            pai->filhos[0] = no;
            adicionaChaveNo(pai, novo, promovido);
            
            no->pai = pai;
            novo->pai = pai;
            arvore->raiz = pai;
        } else
            adicionaChaveRecursivo(arvore, no->pai, novo, promovido);
    }
}

int adicionarValorB(ArvoreB* arvore, int valor) {
    contadorB = 1;
    NoB* no = localizaNo(arvore, valor);

    adicionaChaveRecursivo(arvore, no, NULL, valor);

    return contadorB;
}


