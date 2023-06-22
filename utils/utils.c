#include "utils.h"

void embaralha(int *array, int n) {
    if (n > 1) {
        int i;
        for (i = 0; i < n - 1; i++) {
            int j = i + rand() / (RAND_MAX / (n - i) + 1);
            int temp = array[j];
            array[j] = array[i];
            array[i] = temp;
        }
    }
}

int *geraVetor(int n) {
    int *vetor = (int *)malloc(n * sizeof(int));

    for (size_t i = 0; i < n; i++) {
        vetor[i] = i + 1;
    }

    srand(time(NULL));
    embaralha(vetor, n);

    return vetor;
}
