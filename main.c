#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "avl/avl.h"
#include "utils/utils.h"

#define REPETICOES 10
#define TAM_MIN 1 
#define TAM_MAX 1000

int main() {
    extern unsigned long int contadorAVL;

    printf("Inicio\n");

    FILE *arquivoAdicao;
    FILE *arquivoRemocao;
    arquivoAdicao = fopen("graph/adicao.csv", "w+");
    arquivoRemocao = fopen("graph/remocao.csv", "w+");

    if(arquivoAdicao == NULL || arquivoRemocao == NULL) {
        printf("Erro ao abrir arquivo(s)");
        return 0;
    }

    for (size_t tamChaves = TAM_MIN; tamChaves <= TAM_MAX; tamChaves++)
    {
        contadorAVL = 0;

        for (size_t j = 0; j < REPETICOES; j++)
        {
            int *chaves = geraVetor(tamChaves);

            ArvoreAVL* arvoreAVL = criarArvoreAVL();

            for (size_t k = 0; k < tamChaves; k++)
            {
                adicionarValorAVL(arvoreAVL, chaves[k]);
            }

            free(arvoreAVL);
            free(chaves);
        }

        // Adição

        fprintf(arquivoAdicao, "%d, %lu\n", tamChaves, contadorAVL / REPETICOES);

        //  Remoção

        // TODO

        fflush(arquivoAdicao);
    }
    
    fclose(arquivoAdicao);
    fclose(arquivoRemocao);

    printf("Fim\n");

    system("pause");
    return 1;
}