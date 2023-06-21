#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "avl/avl.h"
#include "utils/utils.h"

#define REPETICOES 10 
#define TAM_MIN 1 
#define TAM_MAX 10000

void main() {
    extern long int contadorAVL;

    for (size_t i = TAM_MIN; i < TAM_MAX; i++)
    {
        //  Adição
        int mediaAVL = 0;

        for (size_t j = 0; j < REPETICOES; j++)
        {
            int *vetor = geraVetor(i);

            ArvoreAVL* arvoreAVL = criarArvoreAVL();

            for (size_t k = 0; k < i; k++)
            {
                /* code */
            }
            

            mediaAVL += contadorAVL;

        }

        mediaAVL /= REPETICOES;
        
        printf("%d", mediaAVL);

        //  Remoção
    }
    
    
}