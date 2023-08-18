//#define _GNU_SOURCE

#include <fcntl.h>
#include <sched.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

#include <sched.h>
#include <fstream>
#include <cstdlib>
#include<unistd.h>
#include <sys/types.h>
#include <iostream>
#include <sys/wait.h>

using namespace std;

#define STACK_SIZE (1024 * 1024)    /* Stack size for cloned child */

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                        } while (0)
                        
static char child_stack[STACK_SIZE];

int child_func(void *arg) {
    printf("In clone function");
    sleep(100);
    return 0;
}

int main() {
    int i;
    pid_t pid;
    pid_t child_pid;
  
  child_pid = clone(&child_func, 
                    child_stack + STACK_SIZE,   
                    CLONE_NEWPID | SIGCHLD, NULL);
char buffer[50];
	sprintf(buffer, "/proc/%d/ns/pid", child_pid);
	 int fd;
	 printf("%s", buffer);
    fd = open(buffer, O_RDONLY);   /* Get descriptor for namespace */
    if (fd == -1)
        errExit("open");

    if (setns(fd, 0) == -1)         /* Join that namespace */
        errExit("setns");
        
	chdir("/home/oai/vcc_a4/newroot/");
	    if (chroot("/home/oai/vcc_a4/newroot/") != 0)
	    {
		perror("chroot /rootfs/");
		return 1;
	    }
	
    for(int i=0;i<5;i++){
        int pid=fork();
        if(pid == 0){
            
            execv("./bin/q3test", NULL);
            perror("execv error");

        }else{
            printf("Child pid %d\n",pid);
        }
    }
   

    // Wait for all child processes to exit
    for (i = 0; i < 5; i++) {
        wait(NULL);
    }

return 0;
}
