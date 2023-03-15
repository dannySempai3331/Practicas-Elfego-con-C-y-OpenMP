#include <stdio.h>
#include <math.h>
#include <omp.h>

int main(){

    int L[]={5,1,100,20};
    int n = (int) sizeof(L)/sizeof(L[0]);
    //https://610yilingliu.github.io/2020/07/01/DebugCwithOpenmpinVscode/

    printf("Arreglo en donde se debe buscar su elemento minimo \n");
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
