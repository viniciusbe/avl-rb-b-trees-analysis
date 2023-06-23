#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "avl/avl.h"
#include "rn/rn.h"
#include "b/b.h"
#include "utils/utils.h"

#define REPETICOES 10
#define TAM_MIN 1 
#define TAM_MAX 1000


int main() {
    extern unsigned long int contadorAVL;
    extern unsigned long int contadorRN;
    extern long int contadorB;
    long int contadorB1;
    long int contadorB5;
    long int contadorB10;

    printf("Inicio\n");

    FILE *arquivoAdicao;
    FILE *arquivoRemocao;
    arquivoAdicao = fopen("graph/adicao.csv", "w+");
    arquivoRemocao = fopen("graph/remocao.csv", "w+");

    if(arquivoAdicao == NULL || arquivoRemocao == NULL) {
        printf("Erro ao abrir arquivo(s)");
        return 0;
    }

    for (int tamChaves = TAM_MIN; tamChaves <= TAM_MAX; tamChaves++)
    {
        contadorAVL = 0;
        contadorRN = 0;
        contadorB = 0;

        contadorB1 = 0;
        contadorB5 = 0;

        for (size_t j = 0; j < REPETICOES; j++)
        {
            int *chaves = geraVetor(tamChaves);

            ArvoreAVL* arvoreAVL = criarArvoreAVL();
            ArvoreRN* arvoreRN = criarArvoreRN();
            ArvoreB* arvoreB1 = criarArvoreB(1);
            ArvoreB* arvoreB5 = criarArvoreB(5);
            ArvoreB* arvoreB10 = criarArvoreB(10);

            for (size_t k = 0; k < tamChaves; k++)
            {
                adicionarValorAVL(arvoreAVL, chaves[k]);
                
                
                adicionarValorRN(arvoreRN, chaves[k]);
                //B1

                contadorB = 0;
                adicionarValorB(arvoreB1, chaves[k]);
                contadorB1 += contadorB;

                contadorB = 0;
                adicionarValorB(arvoreB5, chaves[k]);
                contadorB5 += contadorB;


            }

            free(arvoreAVL);
            free(arvoreRN);
            free(arvoreB1);
            free(arvoreB5);
            free(arvoreB10);
            free(chaves);
        }

        // Adição

        fprintf(arquivoAdicao, "%d, %lu, %ld, %ld, %ld \n", tamChaves, contadorAVL / REPETICOES, contadorRN / REPETICOES, contadorB1 / REPETICOES, contadorB5 / REPETICOES);

        //  Remoção

        // Gerar numero aleatorio para remover

        fflush(arquivoAdicao);
    }
    
    fclose(arquivoAdicao);
    fclose(arquivoRemocao);

    printf("Fim\n");


    return 1;
}