//sigkill orphan 


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

int main(){
	pid_t ppid, pid, cpid;
	ppid = getpid();
	pid = fork();
	if(ppid == getpid())
		printf("Parent\n");
	else if(cpid == getpid())
		printf("Child\n");
	if(pid > 0){
		int i = 0;
		while(i++ < 5){
			printf("In the parent process.\n");
			sleep(1);
		}
	}
	else if(pid == 0){
		int i = 0;
		while(i++ < 10){
			printf("In the child process.\n");
			sleep(1);
			if(i==3){
				kill(ppid, SIGKILL);
				printf("Parent killed. I'm orphan!!!\n");
			}
		}
	}
	else{
		printf("Something bad happened\n");
		exit(EXIT_FAILURE);
	}
}


//sigstop orphan

#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
#include<sys/wait.h>

int main()
{
	int ppid, pid, i;
	ppid = (int)getpid();
	pid = fork();
	

	if(pid > 0)
	{
	    printf("child process id %d\t parent process id %d\n", pid, ppid);
	    
		i = 0;
		while(i++ < 20)
		{
			printf("in the parent process \n");
			sleep(1); 

		}

	} 

	else if(pid == 0) 
	{	
		i = 0; 
		while(i++ < 20) 
		{
			printf("in the child process \n");
			sleep(1);
			if (i == 5)
			{
			    printf("Parent stopped\n");
				kill(ppid, SIGSTOP);
			}
			
			if (i == 11)
			{
			    printf("Parent Resumed\n");
				kill(ppid, SIGCONT);
			}
		}
	}

 	else
	{
		printf("Something bad happened.");
		exit(0);
	}
	return 0;

}	

//resotr ctrl+c


#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
void oh(int sig){
	printf("OH! I have got a signal %d\n",sig);
	//signal(SIGINT, oh); //recalls oh() on ^C
	signal(SIGINT,SIG_DFL);
}
int main(){
	signal(SIGINT,oh);
	while(1){
		printf("Hello World!\n");
		sleep(1);
	}
}
