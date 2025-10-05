#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>





//Protopipo das funções
void bubbleSort(int *V, int N);
void selectionSort(int *V, int N);
void insertionSort(int *V, int N);
void merge(int *V, int inicio, int meio, int fim);
void mergeSort(int *V, int inicio, int fim);
int particiona(int *V, int inicio, int final);
void quickSort(int *V, int inicio, int fim);


void preencherVetorAleatorio(int *vetor, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        
        vetor[i] = rand() ;
    }
}

int main() {
    // Vetor com os tamanhos de entrada para os testes
    int tamanhos[] = {10, 50, 100, 500, 1000, 5000, 10000, 30000, 50000, 70000, 100000, 300000, 500000, 700000, 1000000, 2000000, 3000000};
    int num_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    for (int i = 0; i < num_tamanhos; i++) {
        int N = tamanhos[i];
        printf("====================================================\n");
        printf("INICIANDO TESTES PARA N = %d\n", N);
        printf("====================================================\n");

        // Aloca memória para o vetor original e uma cópia de trabalho
        int *vetorOriginal = (int *)malloc(N * sizeof(int));
        int *vetorCopia = (int *)malloc(N * sizeof(int));

        if (vetorOriginal == NULL || vetorCopia == NULL) {
            printf("Erro de alocacao de memoria!\n");
            return 1;
        }

        // Preenche o vetor original com números aleatórios
        preencherVetorAleatorio(vetorOriginal, N);

        clock_t inicio, fim;
        double tempo_gasto;

        // --- Bubble Sort ---
        memcpy(vetorCopia, vetorOriginal, N * sizeof(int));
        inicio = clock();
        bubbleSort(vetorCopia, N);
        fim = clock();
        tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        printf("  -> Bubble Sort:    %f segundos\n", tempo_gasto);
        
        // --- Selection Sort ---
        memcpy(vetorCopia, vetorOriginal, N * sizeof(int));
        inicio = clock();
        selectionSort(vetorCopia, N);
        fim = clock();
        tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        printf("  -> Selection Sort: %f segundos\n", tempo_gasto);
        
        // --- Insertion Sort ---
        memcpy(vetorCopia, vetorOriginal, N * sizeof(int));
        inicio = clock();
        insertionSort(vetorCopia, N);
        fim = clock();
        tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        printf("  -> Insertion Sort: %f segundos\n", tempo_gasto);
        
        // --- Merge Sort ---
        memcpy(vetorCopia, vetorOriginal, N * sizeof(int));
        inicio = clock();
        mergeSort(vetorCopia, 0, N - 1);
        fim = clock();
        tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        printf("  -> Merge Sort:     %f segundos\n", tempo_gasto);

        // --- Quick Sort ---
        memcpy(vetorCopia, vetorOriginal, N * sizeof(int));
        inicio = clock();
        quickSort(vetorCopia, 0, N - 1);
        fim = clock();
        tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        printf("  -> Quick Sort:     %f segundos\n", tempo_gasto);

        // Libera a memória alocada para esta iteração
        free(vetorOriginal);
        free(vetorCopia);
        printf("\n");
    }

    return 0;
}


// 1. Bubble Sort
void bubbleSort(int *V, int N) {
    int i, continua, aux, fim = N;
    do {
        continua = 0;
        for (i = 0; i < fim - 1; i++) {
            if (V[i] > V[i + 1]) {
                aux = V[i];
                V[i] = V[i + 1];
                V[i + 1] = aux;
                continua = i;
            }
        }
        fim--;
    } while (continua != 0);
}

// 2. Selection Sort
void selectionSort(int *V, int N) {
    int i, j, menor, troca;
    for (i = 0; i < N - 1; i++) {
        menor = i;
        for (j = i + 1; j < N; j++) {
            if (V[j] < V[menor]) {
                menor = j;
            }
        }
        if (i != menor) {
            troca = V[i];
            V[i] = V[menor];
            V[menor] = troca;
        }
    }
}

// 3. Insertion Sort
void insertionSort(int *V, int N) {
    int i, j, aux;
    for (i = 1; i < N; i++) {
        aux = V[i];
        for (j = i; (j > 0) && (aux < V[j - 1]); j--) {
            V[j] = V[j - 1];
        }
        V[j] = aux;
    }
}

// 4. Merge Sort
void merge(int *V, int inicio, int meio, int fim) {
    int *temp, p1, p2, tamanho, i, j, k;
    int fim1 = 0, fim2 = 0;
    tamanho = fim - inicio + 1;
    p1 = inicio;
    p2 = meio + 1;
    temp = (int *)malloc(tamanho * sizeof(int));
    if (temp != NULL) {
        for (i = 0; i < tamanho; i++) {
            if (!fim1 && !fim2) {
                if (V[p1] < V[p2])
                    temp[i] = V[p1++];
                else
                    temp[i] = V[p2++];
                
                if (p1 > meio) fim1 = 1;
                if (p2 > fim) fim2 = 1;
            } else {
                if (!fim1)
                    temp[i] = V[p1++];
                else
                    temp[i] = V[p2++];
            }
        }
        for (j = 0, k = inicio; j < tamanho; j++, k++)
            V[k] = temp[j];
    }
    free(temp);
}

void mergeSort(int *V, int inicio, int fim) {
    int meio;
    if (inicio < fim) {
        meio = floor((inicio + fim) / 2);
        mergeSort(V, inicio, meio);
        mergeSort(V, meio + 1, fim);
        merge(V, inicio, meio, fim);
    }
}

// 5. Quick Sort
int particiona(int *V, int inicio, int final) {
    int esq, dir, pivo, aux;
    esq = inicio;
    dir = final;
    pivo = V[inicio];
    while (esq < dir) {
        while (esq <= final && V[esq] <= pivo)
            esq++;
        while (dir >= 0 && V[dir] > pivo)
            dir--;
        if (esq < dir) {
            aux = V[esq];
            V[esq] = V[dir];
            V[dir] = aux;
        }
    }
    V[inicio] = V[dir];
    V[dir] = pivo;
    return dir;
}

void quickSort(int *V, int inicio, int fim) {
    int pivo;
    if (fim > inicio) {
        pivo = particiona(V, inicio, fim);
        quickSort(V, inicio, pivo - 1);
        quickSort(V, pivo + 1, fim);
    }
}
