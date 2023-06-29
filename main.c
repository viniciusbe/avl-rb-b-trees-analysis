#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "avl/avl.h"
#include "rn/rn.h"
#include "b/b.h"
#include "utils/utils.h"

#define REPETICOES 10
#define TAM_MIN 1
#define TAM_MAX 2000

int main() {
    printf("Inicio\n");

    FILE *arquivoAdicao = fopen("graph/adicao.csv", "w+");
    FILE *arquivoRemocao = fopen("graph/remocao.csv", "w+");

    if(arquivoAdicao == NULL || arquivoRemocao == NULL) {
        printf("Erro ao abrir arquivo(s)");
        return 0;
    }

    srand(time(NULL));

    for (int tamChaves = TAM_MIN; tamChaves <= TAM_MAX; tamChaves++)
    {
        long int contadorAVL = 0;
        long int contadorRN = 0;
        long int contadorB1 = 0;
        long int contadorB5 = 0;
        long int contadorB10 = 0;

        long int contadorRemocaoAVL = 0;
        long int contadorRemocaoRN = 0;
        long int contadorRemocaoB1 = 0;
        long int contadorRemocaoB5 = 0;
        long int contadorRemocaoB10 = 0;

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
                contadorAVL += adicionarValorAVL(arvoreAVL, chaves[k]);
                contadorRN += adicionarValorRN(arvoreRN, chaves[k]);
                contadorB1 += adicionarValorB(arvoreB1, chaves[k]);
                contadorB5 += adicionarValorB(arvoreB5, chaves[k]);
                contadorB10 += adicionarValorB(arvoreB10, chaves[k]);
            }

            for (size_t i = tamChaves; i > 0; i--)
            {
                int indice = rand() % i;
                int valor = chaves[indice];
                contadorRemocaoAVL += removerValorAVL(arvoreAVL, valor);
                contadorRemocaoRN += removerValorRN(arvoreRN, valor);
                contadorRemocaoB1 += removerValorB(arvoreB1, valor);
                contadorRemocaoB5 += removerValorB(arvoreB5, valor);
                contadorRemocaoB10 += removerValorB(arvoreB10, valor);
                chaves[indice] = chaves[i - 1];
            }
            
            free(arvoreAVL);
            free(arvoreRN);
            free(arvoreB1);
            free(arvoreB5);
            free(arvoreB10);
            free(chaves);
        }

        fprintf(arquivoAdicao, 
            "%d, %ld, %ld, %ld, %ld, %ld \n", 
            tamChaves, 
            contadorAVL / REPETICOES, 
            contadorRN / REPETICOES, 
            contadorB1 / REPETICOES, 
            contadorB5 / REPETICOES, 
            contadorB10 / REPETICOES
        );

        fprintf(arquivoRemocao, 
            "%d, %ld, %ld, %ld, %ld, %ld \n", 
            tamChaves, 
            contadorRemocaoAVL / REPETICOES,
            contadorRemocaoRN / REPETICOES,
            contadorRemocaoB1 / REPETICOES,
            contadorRemocaoB5 / REPETICOES,
            contadorRemocaoB10 / REPETICOES
        );

        fflush(arquivoAdicao);
        fflush(arquivoRemocao);
    }
    
    fclose(arquivoAdicao);
    fclose(arquivoRemocao);

    printf("\nFim\n");
    system("pause");

    return 1;
}