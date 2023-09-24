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

int    ft_atoi(char *str)
{
    int i = 0;
    int signal = 1;
    int res = 0;

    while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            signal *= -1;
        i++;
    }
    while(str[i] >= '0' && str[1] <= '9')
    {
        res = res * 10 + str[i] - '0';
        i++;
    }
    return (res * signal);

}
int main(int argc, char **argv)
{
    int i = -1;
    int number_of_threads = ft_atoi(argv[1]);
    pthread_t   *thread = malloc(sizeof(pthread_t) * number_of_threads);
    pthread_mutex_init(&mutex, NULL);
    while (++i <= number_of_threads)
    {
        if (pthread_create(&thread[i] , NULL, routine, NULL)!= 0)
            perror("Failed to create a thread.\n");
        printf("Thread %d has created!\n", i);
    }
    i = -1;
    while (++i <= number_of_threads)
    {
        if (pthread_join(thread[i], NULL) != 0)
            perror("Failed to finish a thread.\n");
        printf("Thread %d has finished execution.\n", i);
    }
    pthread_mutex_destroy(&mutex);
    
}