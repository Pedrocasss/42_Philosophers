#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


//Passar argumentos para threads, neste caso cada thread irá receber um numero primo.


int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *routine(void *arg)
{
    int *ptr = (int *)arg;
    int index = *ptr;
    printf("number %d \n", primes[index]);
    free(arg);
    return NULL;
}
//Temos de alocar memória para cada thread, neste caso como é um int, garantimos 4 bytes
//para enviar para cada thread.
int main(void)
{
    pthread_t t[10];
    int i = -1; 

    while (++i < 10)
    {
        int *a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&t[i], NULL, &routine, a) != 0)
            perror("Failed to create a thread\n");
    }
    
    i = -1;
    while (++i < 10)
    {
        if (pthread_join(t[i], NULL) != 0)
            perror("Failed to finish execution of thread\n");
    }
}
