// replacing one program with another

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
	char* command="ls";
	char* argument_list[]={"ls","-l",NULL};
	//char* argument_list[]={NULL};
	printf("Before calling execvp()\n");

	int status_code = execvp(command, argument_list);
	//execvp() will take control of the process
	if(status_code==-1){
		printf("Process did not terminate correctly\n");
		exit(1);
	}
	printf("This line will not be printed if execvp() runs correctly\n");
	return 0;
}

//process using fork & replacing & count

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
	char* command="ls";
	char* argument_list[]={"ls","-l",NULL};
	//char* argument_list[]={NULL};
	printf("Before calling execvp()\n");
	printf("Creating another process using fork()..\n");

	if(fork()==0){
		//sleep(2);
		int status_code = execvp(command, argument_list);
		//execvp() will take control of the process
		if(status_code==-1){
			printf("Process did not terminate correctly\n");
			exit(1);
		}
	}
	else{
		//parent
		printf("This line will be printed for parent");
	}
	return 0;
}

//replace parent

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
int main(){
	printf("I am parent process\n");
	
	char *arg_ptr[4];
	arg_ptr[0] = "childEXECV.c";
        arg_ptr[1] = "Hi from child";
        arg_ptr[2] = "Bye from child";
        arg_ptr[3] = NULL;

	int st = execvp("./Cexecv", arg_ptr);
	printf("Error: %i\n", errno);
}

// replace child

#include<stdio.h>

int main(int argc, char *argv[]){
	printf("I am child process\n");
	printf("Argument 1 : %s\n", argv[1]);
        printf("Argument 2 : %s\n", argv[2]);
        printf("Argument 3 : %s\n", argv[3]);
}

//use of excel() in Ip

#include<stdio.h>
#include<unistd.h>

int main()
{
	char *const evp[] = {"PATH=/bin:/usr/bin","TERM:console",0};
	printf("Before execl\n");
	execl("/bin/ps","ps","-a",NULL);
	printf("After execlp\n");
}