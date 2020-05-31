#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

#define MAX_NUM 5

int fd[2];
pid_t pid, ppid;
static int flag = 1;

//can be 1 handler they do the same

// parent handler
void sig_usr(int signo)
{ 
  if (signo == SIGUSR1)
  {
    int read_data = 0;
    read(fd[0], &read_data, sizeof(read_data)); //read from pipe
    if (read_data < MAX_NUM)
    {
      printf("Signal parent! :%d\n", read_data);
      read_data += 1;
      write(fd[1], &read_data, sizeof(read_data));
      sleep(1);
      kill(pid, SIGUSR1);
    }
    else
    {
      //printf("parent is going to be terminated\n");
      //kill(pid,SIGKILL);
      printf("Child is going to be terminated\n");
      flag = 0;
    }
  }
}
// child handler
void sig_usr2(int signo)
{ 
  if (signo == SIGUSR1)
  {
    int read_data = 0;
    read(fd[0], &read_data, sizeof(read_data)); //read from pipe
    if (read_data <= MAX_NUM)
    {
      printf("Signal child! :%d\n", read_data);
      read_data += 1;
      write(fd[1], &read_data, sizeof(read_data)); //write to pipe
      sleep(1);
      kill(ppid, SIGUSR1);
    }

    else
    {
      //kill(ppid,SIGUSR1);
      flag = 0;
    }
  }
}

int main(void)
{
  int returnstatus;
  returnstatus = pipe(fd);
  if (returnstatus == -1)
  {
    printf("Unable to create pipe\n");
    return 1;
  }

  ppid = getpid();

  if ((pid = fork()) == 0)
  { //child
    signal(SIGUSR1, sig_usr2);
    int data_read = 0;
    write(fd[1], &data_read, sizeof(data_read));
    kill(ppid, SIGUSR1);
    while (flag)
    {
    }
  }

  else
  { // parent
    signal(SIGUSR1, sig_usr);
    while (flag)
    {   
    }
    sleep(1); // wait for child
    printf("parent is going to be terminated\n");
  }

  close(fd[0]); // close pipe
  close(fd[1]);
  return 0;
}
