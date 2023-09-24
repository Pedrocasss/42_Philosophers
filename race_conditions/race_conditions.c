#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

int to_see = 0;

void    *routine()
{
   int i = 0;
   while (i < 1000000)
   {
        i++;
        to_see++;
   }
}

int main(void)
{
    pthread_t t1, t2;

    pthread_create(&t1, NULL, routine, NULL);
    pthread_create(&t2, NULL, routine, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("Qual e o numero do to_see agora? %d\n", to_see);
}

