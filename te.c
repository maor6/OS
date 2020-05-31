#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
#include <sys/types.h>

#define MAX_NUM 5

int fd[2];
pid_t pid, ppid;
int pflag =1;
int flag = 1;

void sig_usr(int signo){
    if(signo == SIGUSR1){
    	int read_data = 0;
    	read(fd[0], &read_data, sizeof(read_data)); //read from pipe
    	printf("Signal parent! :%d\n",read_data);
    	if (read_data < MAX_NUM) {
          read_data += 1;
	  write(fd[1], &read_data, sizeof(read_data));
	  sleep(1);
    	  kill(pid,SIGUSR1);
    	}
	else {
	  printf("parent is going to be terminated");
	  kill(pid,SIGKILL);	
	}
    }
    return;
}

void sig_usr2(int signo){
    if(signo == SIGUSR1){
      
      }
      else {
	flag = 0;
      }
    }
    return;
}

int main(void){
    int returnstatus;
    returnstatus = pipe(fd);	
    if (returnstatus == -1) {
      printf("Unable to create pipe\n");
      return 1;
   }

    ppid = getpid();

    if((pid = fork()) == 0){  //child 
	signal(SIGUSR1,sig_usr2);
        sleep(1); // Wait for parent to finish setting up
	int data_read = 0;
	int run = 0;
	write(fd[1], &data_read, sizeof(data_read));
        kill(ppid, SIGUSR1);
	while(flag){
	   if (run){
	      int read_data = 0;
	      read(fd[0], &read_data, sizeof(read_data)); //read from pipe
      	      printf("Signal parent! :%d\n",read_data);
      	      if (read_data < MAX_NUM) {
              read_data += 1;
	      write(fd[1], &read_data, sizeof(read_data)); //read to pipe
	      sleep(1);
	      kill(ppid,SIGUSR1); 
	   }
	}
    }
    else{ // parent
       // printf("%d %d ",ppid, pid);
        signal(SIGUSR1,sig_usr);
	//sleep(1);
	while(1){}
	
    }
    close(fd[0]);
    close(fd[1]);
    return 0;
}
