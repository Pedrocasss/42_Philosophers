#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

int to_see = 0;
pthread_mutex_t mutex;

void    *routine()
{
    int i = 0;
    while (i < 1000000)
    {
        pthread_mutex_lock(&mutex);
        to_see++;
        i++;
        pthread_mutex_unlock(&mutex);
    }
}

int main(void)
{
    pthread_t   t1, t2;
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&t1, NULL, routine, NULL);
    pthread_create(&t2, NULL, routine, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_mutex_destroy(&mutex);
    printf("Agora o to_see sera: %d\n", to_see);
}