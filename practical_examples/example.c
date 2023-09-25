#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *routine(void *arg)
{
    int *ptr = (int *)arg;
    int index = *ptr;
    int j = -1;
    int sum = 0;

    while (++j < 5)
    {
        sum+= primes[index + j];
    }
    *(int *)arg = sum;
    printf("Let me see %d\n", sum);
    return arg;
}


int main(void)
{
    pthread_t t[2];
    int i = -1; 

    while (++i < 2)
    {
        int *a = malloc(sizeof(int));
        *a = i * 5;
        if (pthread_create(&t[i], NULL, &routine, a) != 0)
            perror("Failed to create a thread\n");
    }
    
    i = -1;
    int globalSum = 0;
    while (++i < 2)
    {
        int* r;
        if (pthread_join(t[i], (void **) &r) != 0)
            perror("Failed to finish execution of thread\n");
        globalSum += *r;
        free(r);
    }
    printf("globalSum: %d\n", globalSum);
}

//Este codigo nada mais é do que uma demonstraçao do "poder" que as threads têm.
//Neste exemplo fazemos com que a primeira thread some os 5 primeiros numeros e a segunda thread
//os outros 5 numeros, sendo o resultado final 28+101 = 129!