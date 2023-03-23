
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main(){

    int A[]={0,1,1,1,1,1,1,1,1};
    int n =((int) sizeof(A)/ sizeof(A[0]))-1;
    int log = log2(n);

    printf("Elementos a sumar: \n");
    mostrarArreglo(A,n);
    printf("\n");
    printf("\n");

    for(int i =1;i<(int)n/2;i++){
        #pragma omp parallel for num_threads(8)
        for(int j=n;j>=((int)pow(2,i-1));j--){
            A[j]=A[j]+A[j-(int)pow(2,i-1)];
        }
        printf("Iteracion numero %i \n",i);
        mostrarArreglo(A,n+1);
            printf("\n");
    }
    printf("\n");
    printf("La suma de los elementos del arreglo es: %i",A[n]);

    return 0;

}

void mostrarArreglo(int arr[],int longitud){
    for(int i =0;i<longitud;i++){
        printf("%i ",arr[i]);
    }
}
