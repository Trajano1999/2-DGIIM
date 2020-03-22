#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char **argv)
{

    int i, n = 15, chunk, a[n], suma = 0;
    int *chunk_size;
    omp_sched_t *kind;

    if (argc < 2)
    {
        fprintf(stderr, "\nFalta chunk \n");
        exit(-1);
    }
    n = atoi(argv[1]);
    chunk = atoi(argv[2]);

    for (i = 0; i < n; i++)
        a[i] = i;

#pragma omp parallel
    {
#pragma omp single
        {
            printf("Antes\n");
            printf("dyn-var: %d \n", omp_get_dynamic());
            printf("nthreads-var: %d \n", omp_get_max_threads());
            printf("thread limit-var: %d \n", omp_get_thread_limit());
            omp_get_schedule(&kind, &chunk_size);
            printf("run-sched-var: (Kind: %d, Modifier: %d) \n", kind, chunk_size);

            omp_set_dynamic(3);
            omp_set_num_threads(8);
            omp_set_schedule(2, 2);

            printf("Después\n");
            printf("dyn-var: %d \n", omp_get_dynamic());
            printf("nthreads-var: %d \n", omp_get_max_threads());
            printf("thread limit-var: %d \n", omp_get_thread_limit());
            omp_get_schedule(&kind, &chunk_size);
            printf("run-sched-var: (Kind: %d, Modifier: %d) \n", kind, chunk_size);
        }
#pragma omp for firstprivate(suma) \
    lastprivate(suma) schedule(static, chunk)
        for (i = 0; i < n; i++)
        {
            suma = suma + a[i];
            printf(" thread %d suma a[%d] suma=%d \n",
                   omp_get_thread_num(), i, suma);
        }
    }
    printf("Fuera de 'parallel for' suma=%d\n", suma);

    return (0);
}