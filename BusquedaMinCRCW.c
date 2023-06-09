#include <stdio.h>
#include <math.h>
#include <omp.h>

int main(){

    int L[]={55,41,100,20};
    int n = (int) sizeof(L)/sizeof(L[0]);

    printf("\n Arreglo en donde se debe buscar su elemento minimo \n");
    mostrarArreglo(L,n);
    printf("\n");
    printf("Elemento minimo del arreglo: %i",minCRCW(L,n));

    return 0;
}

int minCRCW(int L[],int n){
    int win[n];
    int indexMin=0;

    #pragma omp parallel for
    for(int i = 0;i<n;i++){
        win[i]=0;
    }
    printf("Inicializacion del arreglo win con todos sus elementos en 0 \n");
    mostrarArreglo(win,n);
    printf("\n");


    #pragma omp parallel for
    for(int i =0; i<n;i++){
        #pragma omp parallel for
        for(int j=i+1; j<n;j++){

                if(L[i]>L[j]){
                    #pragma omp critical
                    {
                    win[i]=1;
                    }
                }
                 else{
                    #pragma omp critical
                    {
                      win[j]=1;
                    }
                 }

        }
    }
    printf("Comparacion \n");
    mostrarArreglo(win,n);
    printf("\n");
    
    #pragma omp parallel for
    for(int i=0;i<n;i++){
        if(win[i]==0){
            indexMin=i;
        }
    }

    return (L[indexMin]);

}

void mostrarArreglo(int arr[],int longitud){

    for(int i =0;i<longitud;i++){
        printf("%i ",arr[i]);
    }
}
