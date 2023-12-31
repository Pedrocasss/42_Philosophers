#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    int pid = fork();
    if (pid == -1)
        return 1;
    printf("Process id: %d\n", getpid());
    if (pid != 0)
        wait(NULL);
    return (0);
}
