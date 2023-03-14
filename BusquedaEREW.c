#include <stdio.h>
#include <math.h>
#include <omp.h>

#define INFINITY 1000000000

int main(){
    //El arreglo debe ser de logitud 2^n, con n=1,2,3,...

    int A[]={2,-1,23,-4,2,5,-2,0,5,1,5,-5,8,5,3,-2};
    int n = (int) sizeof(A)/ sizeof(A[0]);
    int x = 5;

    printf("Elemento a buscar: %i \n",x);
    printf("Arreglo \n");
    mostrarArreglo(A,n);
    printf("\n");
    printf("\n");

    busqueda(A,n,5);

    return 0;
}

void broadcast(int A[], int x, int n){
    A[0]=x;

    for(int i = 1;i <= log2(n);i++){

        int gap = (int) pow(2,i-1);

        #pragma omp parallel for
        for(int j = gap+1;j <= n; j++){

            A[j-1]=A[j-1-gap];
        }
    }

    //ya jala ni le muevas
    printf("Difucion: \n");
    mostrarArreglo(A,n);
    printf("\n");
}

void minimo(int L[], int n){

    for(int j=1;j<=log2(n);j++){

        #pragma omp parallel for
        for(int i = 1; i<= n/(int)pow(2,j);i++){
            if(L[(i*2)-2]>L[(i*2)-1]){
                L[i-1]=L[(i*2)-1];
            }else{
                L[i-1] = L[(i*2)-2];
            }
        }
    }
    printf("\n");
    printf("Elemento minimo \n");
    mostrarArreglo(L,n);
    printf("\n");
    printf("\n");
    printf("El elemento esta en la posicion %i del arreglo",L[0]-1);

}

void busqueda(int L[], int n, int x){

    int Temp[n];
    int retorno=0;
    broadcast(Temp,x,n);

    #pragma omp parallel for
    for(int i=0;i<=n;i++){

        if (L[i]==Temp[i]){
            Temp[i] = i+1;

        }
         else {
            Temp[i] = INFINITY;
        }
    }
    printf("\n");
    printf("Comparacion \n");
    mostrarArreglo(Temp,n);
    printf("\n");

    minimo(Temp,n);

}

void mostrarArreglo(int arr[],int longitud){

    for(int i =0;i<longitud;i++){
        printf("%i ",arr[i]);
    }
}


