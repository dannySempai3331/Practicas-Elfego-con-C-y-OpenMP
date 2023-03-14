#include <stdio.h>
#include <omp.h>

int main(){

     /*This pragma creates a parallel region where
      the code inside the block is executed in parallel
      by multiple threads*/
    #pragma omp parallel
    {
        printf("Hola \n");
    }
     printf("\n");

     /* This pragma parallelizes a for loop
     by distributing the iterations of the loop
     among multiple threads.*/

    #pragma omp parallel for
    for (int i = 0; i < 3; i++) {
        printf("Hola \n");
    }
     printf("\n");

    int sum = 0;

    /*This pragma performs a reduction operation
    on a variable across multiple threads.*/

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < 8; i++) {
         sum += i;
         printf("%i \n",sum);
        }
        printf("\n");
        printf("%i \n",sum);

    /*The reduction operation ensures that each thread computes its own partial sum,
    and the results are combined at the end to obtain the final sum.

    A reduction operation is an operation that
    combines the values of a set of variables into a single value.

    The purpose of a reduction operation is to compute a global result from
    local results computed by multiple threads or processes.
    */


    return 0;
}
