//main process creats a child and pipe parents writes into pipe and child reads


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main(){
	FILE *write_fp;
	char buffer[BUFSIZ+1];
	sprintf(buffer, "The Quick brown fox is sleep.\n");
	write_fp = popen("cat > newfile.txt", "w");
	if(write_fp!=NULL){
		fwrite(buffer, sizeof(char), strlen(buffer), write_fp);
		pclose(write_fp);
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}

//communication bw child parent

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main(){
	int data_processed;
	int file_pipes[2];
	const char some_data[] = "Hello World";
	char buffer[BUFSIZ + 1];
	pid_t fork_result;
	memset(buffer, '\0', sizeof(buffer));
	//printf("hi\n");
	if (pipe(file_pipes)==0){
		fork_result = fork();
		printf("hi\n");
		if(fork_result == -1){
			fprintf(stderr, "fork_failure");
			exit(EXIT_FAILURE);
		}
		else if(fork_result == 0){//child
			sleep(2);
			data_processed = read(file_pipes[0], buffer, BUFSIZ);
			printf("Child read %d bytes : %s\n", data_processed, buffer);
			exit(EXIT_SUCCESS);
		}
		else{//parent
			data_processed = write(file_pipes[1], some_data, strlen(some_data));
			printf("Parent wrote %d bytes : %s\n", data_processed, some_data);
		}
	}
	exit(EXIT_SUCCESS);
}


//simple or one way bw child and process

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main(){
	int data_processed;
	int file_pipes[2];
	const char some_data[] = "Hello World";
	char buffer[BUFSIZ + 1];
	pid_t fork_result;
	memset(buffer, '\0', sizeof(buffer));
	//printf("hi\n");
	if (pipe(file_pipes)==0){
		fork_result = fork();
		printf("hi\n");
		if(fork_result == -1){
			fprintf(stderr, "fork_failure");
			exit(EXIT_FAILURE);
		}
		else if(fork_result == 0){//child
			sleep(2);
			data_processed = read(file_pipes[0], buffer, BUFSIZ);
			printf("Child read %d bytes : %s\n", data_processed, buffer);
			exit(EXIT_SUCCESS);
		}
		else{//parent
			data_processed = write(file_pipes[1], some_data, strlen(some_data));
			printf("Parent wrote %d bytes : %s\n", data_processed, some_data);
		}
	}
	exit(EXIT_SUCCESS);
}

//both way communication 

#include<stdio.h>
#include<unistd.h>

int main(){
	int pipefds1[2], pipefds2[2];
	int returnstatus1, returnstatus2;
	int pid;
	char pipe1writemessage[20]="Hi";
	char pipe2writemessage[20]="Hello";
	char readmessage[20];
	returnstatus1 = pipe(pipefds1);
	if(returnstatus1 == -1){
		printf("Unable to create pipe 1 \n");
		return 1;
	}
	returnstatus2 = pipe(pipefds2);
	if(returnstatus2 == -1){
		printf("unable to create pipe 2 \n");
		return 1;
	}
	pid = fork();
	if(pid!=0){
		close(pipefds1[0]);
		close(pipefds2[1]);
		printf("In parent : writing to pipe 1 - Message is %s\n", pipe1writemessage);
		write(pipefds1[1], pipe1writemessage, sizeof(pipe1writemessage));
		read(pipefds2[0], readmessage, sizeof(readmessage));
		printf("in parent : reading from pipe 2 - Message is %s\n", readmessage);
	}
	else{
		close(pipefds1[1]);
		close(pipefds2[0]);
		read(pipefds1[0], readmessage, sizeof(readmessage));
		printf("In child : reading from pipe 1 - Message is %s\n", readmessage);
		printf("In child : writing to pipe 2 - Message is %s\n", pipe2writemessage);
		write(pipefds2[1], pipe2writemessage, sizeof(pipe2writemessage));
	}
	return 0;
}
