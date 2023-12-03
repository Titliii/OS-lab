#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int pid = fork();
    if(pid<0)
    {
        printf("Unsuccessful fork\n");
        exit(1);
    }
    else if(pid==0)
        printf("Child\n");
    else 
        printf("Parent\n");
}

//2

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int n=5;
    int pid = fork();
    if(pid<0)
    {
        printf("Unsuccessful fork\n");
        exit(1);
    }
    else if(pid==0)
    {
        printf("Child : %d\n",++n);
        exit(0);
    }
    else 
    {
        printf("Parent : %d\n",--n);
        exit(0);
    }
}

//3

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    fork();
    fork();
    fork();
    printf("%d %d\n", getpid(),getppid());
    exit(0);
}