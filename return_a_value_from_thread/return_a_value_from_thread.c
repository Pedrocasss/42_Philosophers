#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

void    *roll_dice()
{
    int value = (rand() % 6) + 1;
    int *result = malloc(sizeof(int));
    *result = value;

    printf("Thread result %p\n", result);
    return (void *) result;
}

int main(void)
{
    int *res;
    srand(time(NULL));
    pthread_t   t1;
    pthread_create(&t1, NULL, &roll_dice, NULL);
    pthread_join(t1, (void **)&res);
    printf("Main res: %p\n", res);
    printf("Value: %d\n", *res);
    free(res);
}