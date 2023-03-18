#include <omp.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main()
{
    int L[] = {16, 22, 35, 40, 53, 66, 70, 85, 15, 18, 23, 55, 60, 69, 72, 78};
    int n = (int) sizeof(L)/sizeof(L[0]);
    printf("Arreglo a ordenar: \n");
    mostrarArreglo(L,n);
    printf("\n");

    mergeSort(L, n);
    printf("Arreglo a ordenado: \n");
    mostrarArreglo(L,n);
   
    return 0;
}

void mergeSort(int L[], int n)
{
    if (n >= 2){
        
    #pragma omp critical 
        {
             mergeSort(L, n/2);
            mergeSort(L+n/2, n-n/2);
        }

        oddEvenMerge(L, n);
    }
}

void intercambio(int L[], int a, int b)
{
    int aux;
    aux = L[a];
    L[a] = L[b];
    L[b] = aux;
}

void oddEvenSplit(int L[], int odd[], int even[], int n)
{
#pragma omp parallel for
    for (int i = 0; i < (int)n / 2; i++)
    {
        odd[i] = L[2 * i];
        even[i] = L[2 * i + 1];
    }
}

void oddEvenMerge(int L[], int n)
{

    if (n == 2)
    {
        if (L[0] > L[1])
        {
            intercambio(L, 0, 1);
        }
    }
    else
    {
        int m = (int)n / 2;
        int odd[m];
        int even[m];

        oddEvenSplit(L, odd, even, n);

#pragma omp critical 
        {
            oddEvenMerge(odd, m);
            oddEvenMerge(even, m);
        }

#pragma omp parallel for
        for (int i = 0; i < (int)n / 2; i++)
        {
            L[2 * i] = odd[i];
            L[2 * i + 1] = even[i];
        }
#pragma omp parallel for
        for (int i = 0; i < n - 1; i++)
        {

            if ((L[i]) > (L[i + 1]))
            {
                intercambio(L, i, i + 1);
            }
        }
    }
}
void mostrarArreglo(int arr[],int longitud){

    for(int i =0;i<longitud;i++){
        printf("%i ",arr[i]);
    }
}
