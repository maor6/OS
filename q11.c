#include<stdio.h>
#include<unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>

#define MAX_NUM 5
int fd[2];
pid_t pid;
pid_t parrent_pid;

void child_Handler(int signumber){
	if(signumber == SIGUSR1) {
		//printf("SIGUSR1 catched by child.\n");
    		int read_data = 0;
    		//close(fd[1]);//???????????
    		read(fd[0], &read_data, sizeof(read_data)); //read from pipe
    		printf("Received data by parent : %d\n", read_data);
		if (read_data < MAX_NUM){
			read_data += 1;
			write(fd[1], &read_data, sizeof(read_data));
			kill(parrent_pid,SIGUSR1); // send signal to parent
			sleep(2);
		}
   	}else {
		printf("SIGQUIT");
		exit(3);
	
		}
}


void parent_Handler(int signumber){
    if (signumber == SIGUSR1){
    	//printf("SIGUSR1 catched by father.\n");
    	int read_data = 0;
    	//close(fd[1]);//???????????
    	read(fd[0], &read_data, sizeof(read_data)); //read from pipe
    	printf("Received data by child : %d\n", read_data);
    	if (read_data < MAX_NUM) {
		read_data += 1;
		write(fd[1], &read_data, sizeof(read_data));
		kill(pid,SIGUSR1);
		sleep(2);
         } 
    }else {
	kill(pid,SIGQUIT);
	//exit(1);
	}
}

int main() {
   int returnstatus;
   //char readmessage[20];
   returnstatus = pipe(fd);	

   if (returnstatus == -1) {
      printf("Unable to create pipe\n");
      return 1;
   }

   pid = fork();
   parrent_pid = getpid();

   // Child process
   if (pid == 0) {
      int buff = 0;
      signal(SIGUSR1,child_Handler);
      write(fd[1], &buff, sizeof(buff));
      kill(parrent_pid,SIGUSR1);
      while(1){
	//kill(pid,SIGUSR1); // send signal
      	//buff += 1;
	//printf("Child Process - Reading and Writing from pipe – num is %d\n", buff);
      	//read(pipefds[0], readmessage, sizeof(buff));
      }

   } else { //Parent process
      int buff = 0;
      signal(SIGUSR1,parent_Handler);
      sleep(2);
      while(1){
	//printf("Parent Process - Reading and Writing to pipe -num is %d\n", 2);
      	//read(fd[0], &buff, sizeof(buff));
	//printf("the num from parent %d\n",buff);
	//sleep(2);

	//buff += 1;
      	//write(pipefds[1], &buff, sizeof(buff));
      }
   }
   return 0;
}
