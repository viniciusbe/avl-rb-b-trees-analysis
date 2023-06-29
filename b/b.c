#include "b.h"

long int contadorB = 0;

static void removerValorFolha(ArvoreB* arvore, NoB* no, int valor);
static void removerValorNaoFolha(ArvoreB* arvore, NoB* no, int valor);
static void resolverSubfluxo(ArvoreB* arvore, NoB* no);
static void fusaoNo(ArvoreB* arvore, NoB* pai, int posicaoFilho);
static NoB* localizaNoRecursivo(NoB* no, int chave);

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

NoB* localizaNoRecursivo(NoB* no, int chave) {
    if (no == NULL) {
        return NULL; // Nó não encontrado
    }

    int posicao = pesquisaBinaria(no, chave);

    if (posicao < no->total && chave == no->chaves[posicao]) {
        return no; // Nó encontrado
    }

    if (no->filhos[posicao] != NULL) {
        return localizaNoRecursivo(no->filhos[posicao], chave); // Chama recursivamente nos filhos
    }

    return NULL; // Nó não encontrado
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

int temOrdemMinima(ArvoreB* arvore, NoB* no) {
    return no->total >= arvore->ordem;
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

int removerValorB(ArvoreB* arvore, int valor) {
    contadorB++;
    printf("\nRemovendo %d", valor);
    if (arvore == NULL || arvore->raiz == NULL) {
    printf("\nteste");
        return contadorB;
    }
    NoB* noRemover = localizaNoRecursivo(arvore->raiz, valor);
    if (noRemover == NULL) {
    printf("\nteste2");
        return contadorB;
    }

    
    // Verifique se o nó é uma folha
    if (noRemover->filhos[0] == NULL) {
    printf("\nteste3");
        removerValorFolha(arvore, noRemover, valor);
    } else {
    printf("\nteste4");
        removerValorNaoFolha(arvore, noRemover, valor);
    }

    return contadorB;
}

void removerValorFolha(ArvoreB* arvore, NoB* no, int valor) {
    contadorB++;
    int posicao = pesquisaBinaria(no, valor);

    // Verifique se o valor está presente no nó
    if (posicao != -1) {
        // Desloque os valores para preencher o espaço do valor removido
        for (int i = posicao; i < no->total - 1; i++) {
            no->chaves[i] = no->chaves[i + 1];
        }

        no->total--;

        // Verifique se ocorreu um subfluxo no nó
        if (!temOrdemMinima(arvore, no)) {
            printf("\nmenorrre");
            resolverSubfluxo(arvore, no);
        }
    }
}

void removerValorNaoFolha(ArvoreB* arvore, NoB* no, int valor) {
    contadorB++;
    int posicao = pesquisaBinaria(no, valor);
    NoB* filhoEsquerda = no->filhos[posicao];
    NoB* filhoDireita = no->filhos[posicao + 1];

    // Verifique se o valor está presente no nó
    if (posicao != -1) {
        // Encontre o predecessor do valor
        NoB* predecessor = filhoEsquerda;
        while (predecessor->filhos[predecessor->total] != NULL) {
            predecessor = predecessor->filhos[predecessor->total];
        }

        // Substitua o valor pelo predecessor
        no->chaves[posicao] = predecessor->chaves[predecessor->total - 1];

        // Remova o valor recursivamente no filho esquerdo
        removerValorB(arvore, predecessor->chaves[predecessor->total - 1]);
    } else {
        // Verifique se o filho esquerdo tem pelo menos a ordem mínima
        if (temOrdemMinima(arvore, filhoEsquerda)) {
            // Encontre o sucessor do valor
            NoB* sucessor = filhoDireita;
            while (sucessor->filhos[0] != NULL) {
                sucessor = sucessor->filhos[0];
            }

            // Substitua o valor pelo sucessor
            no->chaves[posicao] = sucessor->chaves[0];

            // Remova o valor recursivamente no filho direito
            removerValorB(arvore, sucessor->chaves[0]);
        } else if (temOrdemMinima(arvore, filhoDireita)) {
            // Encontre o predecessor do valor
            NoB* predecessor = filhoEsquerda;
            while (predecessor->filhos[predecessor->total] != NULL) {
                predecessor = predecessor->filhos[predecessor->total];
            }

            // Substitua o valor pelo predecessor
            no->chaves[posicao] = predecessor->chaves[predecessor->total - 1];

            // Remova o valor recursivamente no filho esquerdo
            removerValorB(arvore, predecessor->chaves[predecessor->total - 1]);
        } else {
            // Realize a fusão do filho esquerdo com o filho direito
            fusaoNo(arvore, no, posicao);
            removerValorB(arvore, valor);
        }
    }
}

void resolverSubfluxo(ArvoreB* arvore, NoB* no) {
    contadorB++;
    if (no == arvore->raiz) {
        // Caso especial: o nó é a raiz
        if (no->total == 0) {
            // A raiz ficou vazia, então substitua-a pelo único filho
            arvore->raiz = no->filhos[0];
            free(no);
        }
    } else {
        // Encontre a posição do nó pai
        int posicaoPai = 0;
        while (no->pai->filhos[posicaoPai] != no) {
            posicaoPai++;
        }

        NoB* pai = no->pai;
        NoB* irmaoEsquerda = NULL;
        NoB* irmaoDireita = NULL;

        // Verifique se o nó pai tem um irmão esquerdo
        if (posicaoPai > 0) {
            irmaoEsquerda = pai->filhos[posicaoPai - 1];
        }

        // Verifique se o nó pai tem um irmão direito
        if (posicaoPai < pai->total) {
            irmaoDireita = pai->filhos[posicaoPai + 1];
        }

        // Verifique se é possível emprestar uma chave do irmão esquerdo
        if (irmaoEsquerda != NULL && irmaoEsquerda->total > arvore->ordem) {
            // Desloque as chaves no nó para a direita para fazer espaço para a chave emprestada
            for (int i = no->total; i > 0; i--) {
                no->chaves[i] = no->chaves[i - 1];
            }

            // Desloque o último filho do nó para a direita
            for (int i = no->total + 1; i > 0; i--) {
                no->filhos[i] = no->filhos[i - 1];
            }

            // Atribua a chave emprestada do irmão esquerdo ao nó
            no->chaves[0] = irmaoEsquerda->chaves[irmaoEsquerda->total - 1];
            no->filhos[0] = irmaoEsquerda->filhos[irmaoEsquerda->total];

            // Atualize o total de chaves nos nós
            no->total++;
            irmaoEsquerda->total--;

            // Atualize o pai
            pai->chaves[posicaoPai - 1] = irmaoEsquerda->chaves[irmaoEsquerda->total - 1];
        } else if (irmaoDireita != NULL && irmaoDireita->total > arvore->ordem) {
            // Desloque a chave do pai para a direita para fazer espaço para a chave emprestada
            no->chaves[no->total] = pai->chaves[posicaoPai];
            no->filhos[no->total + 1] = irmaoDireita->filhos[0];
            no->total++;

            // Atribua a chave emprestada do irmão direito ao pai
            pai->chaves[posicaoPai] = irmaoDireita->chaves[0];

            // Desloque as chaves no irmão direito para a esquerda
            for (int i = 0; i < irmaoDireita->total - 1; i++) {
                irmaoDireita->chaves[i] = irmaoDireita->chaves[i + 1];
            }

            // Desloque os filhos no irmão direito para a esquerda
            for (int i = 0; i < irmaoDireita->total; i++) {
                irmaoDireita->filhos[i] = irmaoDireita->filhos[i + 1];
            }

            // Atualize o total de chaves nos nós
            irmaoDireita->total--;
        } else {
            // Fusão com o irmão esquerdo
            if (irmaoEsquerda != NULL) {
                fusaoNo(arvore, pai, posicaoPai - 1);
            }
            // Fusão com o irmão direito
            else if (irmaoDireita != NULL) {
                fusaoNo(arvore, pai, posicaoPai);
            }
        }

        // Verifique se ocorreu um subfluxo no nó pai
        if (!temOrdemMinima(arvore, pai)) {
            resolverSubfluxo(arvore, pai);
        }
    }
}

void fusaoNo(ArvoreB* arvore, NoB* pai, int posicaoFilho) {
    contadorB++;
    NoB* filhoEsquerda = pai->filhos[posicaoFilho];
    NoB* filhoDireita = pai->filhos[posicaoFilho + 1];

    // Mova a chave do pai para o filho esquerdo
    filhoEsquerda->chaves[filhoEsquerda->total] = pai->chaves[posicaoFilho];
    filhoEsquerda->total++;

    // Copie as chaves e filhos do filho direito para o filho esquerdo
    for (int i = 0; i < filhoDireita->total; i++) {
        filhoEsquerda->chaves[filhoEsquerda->total] = filhoDireita->chaves[i];
        filhoEsquerda->filhos[filhoEsquerda->total] = filhoDireita->filhos[i];
        filhoEsquerda->total++;
    }
    filhoEsquerda->filhos[filhoEsquerda->total] = filhoDireita->filhos[filhoDireita->total];

    // Desloque as chaves e filhos no pai para a esquerda
    for (int i = posicaoFilho; i < pai->total - 1; i++) {
        pai->chaves[i] = pai->chaves[i + 1];
        pai->filhos[i + 1] = pai->filhos[i + 2];
    }
    pai->total--;

    free(filhoDireita);
}