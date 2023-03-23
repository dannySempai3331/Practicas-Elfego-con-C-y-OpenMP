#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main(){
    //El arreglo debe que tener una longitud de 2^n (con n= 1,2,3,...) y comenzar con un 0.

    int A[]={0,1,1,1,1,1,1,1,1};
    int n = (int) sizeof(A)/ sizeof(A[0]);
    printf("Elementos a sumar: \n");
    mostrarArreglo(A,n);
    printf("\n");
    printf("\n");

    for (int i = 1; i <= log2(n); i++) {

        #pragma omp parallel for
        for (int j = 1; j <= n/2; j++) {

            if ((2*j) % (int)pow(2,i) == 0) {

                A[2*j] =A[2*j] + A[2*j - (int)pow(2,i-1)];
            }

        }
            printf("Iteracion %i: \n",i);
            mostrarArreglo(A,n);
            printf("\n");
    }

    printf("\n");
    printf("El resultado de la suma es: %i",A[n-1]);

    return 0;
}

void mostrarArreglo(int arr[],int longitud){

    for(int i =0;i<longitud;i++){
        printf("%i ",arr[i]);
    }
}


