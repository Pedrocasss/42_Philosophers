#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

pthread_mutex_t mutex;
pthread_cond_t  cond;
int fuel = 0;

void    *fuel_car(void  *arg)
{
    int i = -1;

    while (++i < 5)
    {
        pthread_mutex_lock(&mutex);
        fuel += 15;
        printf("Filled fuel: %d\n", fuel);
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond);
        sleep(1);
    }
}


//Permite esperar para que o tanque tenha 40 litros
//deixando só encher o carro após fuel_car encher pelo menos 40litros
void    *car(void   *arg)
{
    pthread_mutex_lock(&mutex);
    while (fuel < 40)
    {
        printf("No fuel. Wait!\n");
        pthread_cond_wait(&cond, &mutex);
        // Equivalent to:
        // pthread_mutex_lock(&mutex);
        // wait for signal on condFuel
        // pthread_mutex_unlock(&mutex);
    }
    fuel -= 40;
    printf("Got fuelled, now left!: %d\n", fuel);
    pthread_mutex_unlock(&mutex);

}
int main(int argc, char **argv)
{
    int i = -1;
    pthread_t t[2];
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    while (++i < 2)
    {
        if (i == 1)
        {
            if (pthread_create(&t[i], NULL, &fuel_car, NULL) != 0)
                perror("Failed to create thread\n");
        }
        else
        {
            if (pthread_create(&t[i], NULL, &car, NULL) != 0)
                perror("Failed to create thread\n");
        }
    }
    i = -1;
    while (++i < 2)
    {
        if (pthread_join(t[i], NULL) != 0)
            perror("Failed to finish thread\n");
    }
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
}
