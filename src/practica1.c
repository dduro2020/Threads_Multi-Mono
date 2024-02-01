#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <err.h>
#include <unistd.h>

#ifdef DEBUG
    #define DEBUG_PRINTF(...) printf("DEBUG: "__VA_ARGS__)
#else
    #define DEBUG_PRINTF(...)
#endif

#define NUMTHREADS 4
#define NUMITERATIONS 5
#define MILLION 1e9
#define PERIOD 0.9

//funcion de apoyo para calcular el tiempo transcurrido
double
measure_time(double begin, double stop)
{
    double time = (stop - begin);
    return time;
}

void *
do_work(void *id)
{
    int *n_id = id;
    struct timespec begin, stop, needed, rest = {0, 0};
    volatile unsigned long long j;
    double ttime;
    int i;
    int iter[NUMTHREADS];

    for (i = 0; i < NUMITERATIONS; i++) {
        iter[*n_id]++;
        clock_gettime(CLOCK_MONOTONIC, &begin);

        //bucle de 0.5s aprox
        for (j=0; j < 370000000ULL; j++);

        clock_gettime(CLOCK_MONOTONIC, &stop);

        //calculamos el tiempo mandandole a la funcion la suma de segundos y nanosegundos
        ttime = measure_time(begin.tv_sec + (((double)begin.tv_nsec) / MILLION), stop.tv_sec + (((double)stop.tv_nsec) / MILLION));

        if (PERIOD - ttime < 0){
            printf("[%ld.%ld] Thread %d - Iteracion %d: Coste=%.2f s. (fallo temporal)\n",begin.tv_sec, begin.tv_nsec, (*n_id) + 1,iter[*n_id], ttime);
        }else{
            printf("[%ld.%ld] Thread %d - Iteracion %d: Coste=%.2f s.\n",begin.tv_sec, begin.tv_nsec, (*n_id) + 1,iter[*n_id], ttime);
            rest.tv_nsec = ((PERIOD - ttime)*MILLION);
            DEBUG_PRINTF("Tiempo de espera:  %f ns.\n",(PERIOD - ttime)*MILLION);

            //esperamos hasta completar el periodo
            if (nanosleep(&rest, &needed) < 0) {                         
                err(EXIT_FAILURE, "error: cannot execute nanosleep\n");
            } 
        }
    }
}

int main(){
    pthread_t thread[NUMTHREADS];
    int ids[NUMTHREADS];
    int i;

    //creamos los threads
    for (i = 0; i < NUMTHREADS; i++)
    {
        ids[i] = i;
        if (pthread_create(&thread[i], NULL, do_work, &ids[i]) != 0) {
            warnx("error: cannot create thread %d", i);
            return 1;
        } 
    }

    //utilizamos la ejecucion sincrona
    for (i = 0; i < NUMTHREADS; i++)
    {
        if (pthread_join(thread[i], NULL) != 0) {
            warnx("error: cannot join thread %d", i);
            return 1;
        } 
    }
}