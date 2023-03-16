#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int n = 2;
int i, j, k;
int a[2][2];
int b[2][2]; 
int c[2][2][2];

int main(){
    printf("\nMatriz A\n");

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++){
            printf("Ingresa el elemento %d,%d :", i, j);
            scanf("%d", &a[i][j]);
        }

    printf("\nMatriz B\n");

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++){
            printf("Ingresa el elemento %d,%d : ", i, j);
            scanf("%d", &b[i][j]);
        }

    printf("\n Elementos matriz A: \n");

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++){
            printf("%d\t", a[i][j]);
        }
        printf("\n");
    }

    printf("\nElementos matriz B: \n");

    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++) {
            printf("%d\t", b[i][j]);
        }
        printf("\n");
    }

    MatMultCREW();
    Imprimir();

    return 0;
}

void MatMultCREW(){

#pragma omp parallel for
    for (int i = 1; i <= n; i++) {
#pragma omp parallel for
        for (int j = 1; j <= n; j++){
#pragma omp parallel for
            for (int k = 1; k <= n; k++){
                c[i][j][k] = a[i][k] * b[k][j];
            }
        }
    }

    for (int L = 1; L <= (log2(n)); L++){
#pragma omp parallel for
        for (int i = 1; i <= n; i++) {
#pragma omp parallel for
            for (int j = 1; j <= n; j++){
#pragma omp parallel for
                for (int k = 1; k <= n / 2; k++){
                    if (((int)(pow(2, (k))) % (int)(pow(2, (L)))) == 0){
                        c[i][j][2 * k] = c[i][j][2 * k] + c[i][j][2 * k - (int)(pow(2, (L - 1)))];
                    }
                }
            }
        }
    }
} 

void Imprimir(){
    printf("\n\nMultiplicacion de A*B\n");
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            printf(" %d\t", c[i][j][n]);
        }
        printf("\n");
    }
}