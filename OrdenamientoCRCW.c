#include <stdio.h>
#include <math.h>
#include <omp.h>

int main(){
    
    int L[]={95,10,6,15};
    int n = (int) sizeof(L)/sizeof(L[0]);
    printf("Arreglo a ordenar: \n");
    mostrarArreglo(L,n);
    printf("\n");
    printf("\n");

    sortCRCW(L,n);

    return 0;
}

void sortCRCW(int L[], int n){

 int win[n];
 int L_aux[n];

#pragma omp parallel for
 for (int i = 0; i < n; i++){
    win[i]=0;
    L_aux[i]=0;
 }

 printf("Inicializacion del arreglo win: \n");
 mostrarArreglo(win,n);

 #pragma omp parallel for
 for (int i = 0; i < n; i++) {
    #pragma omp parallel for
    for (int j = i+1; j < n; j++) {

        if (L[i] > L[j]) {
            #pragma omp critical
            {
                win[i]=win[i]+1;
            }
        }
        else {
            #pragma omp critical
            {
             win[j]=win[j]+1;
            }
        }

    }
}
printf("\n");
printf("Arreglo de posiciones win: \n");
mostrarArreglo(win,n);
printf("\n");

#pragma omp parallel for
for (int i = 0; i<n; i++){
    L_aux[win[i]]=L[i];

    printf("Iteracion numero %i : \n",i);
    mostrarArreglo(L_aux,n);
    printf("\n");
}
printf("\n");
printf("Arreglo ordenado: \n");
mostrarArreglo(L_aux,n);

}


void mostrarArreglo(int arr[],int longitud){

    for(int i =0;i<longitud;i++){
        printf("%i ",arr[i]);
    }
}
