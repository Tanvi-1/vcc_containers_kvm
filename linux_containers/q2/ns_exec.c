/* ns_exec.c 

   Copyright 2013, Michael Kerrisk
   Licensed under GNU General Public License v2 or later

   Join a namespace and execute a command in the namespace
*/
#define _GNU_SOURCE
#include <fcntl.h>
#include <sched.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/* A simple error-handling function: print an error message based
   on the value in 'errno' and terminate the calling process */

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                        } while (0)

int
main(int argc, char *argv[])
{
    int fd;

    if (argc < 3) {
        fprintf(stderr, "%s <pid> cmd [arg...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char procfile[1024];
    sprintf(procfile, "/proc/%s/ns/pid", argv[1]);

    fd = open(procfile, O_RDONLY);   /* Get descriptor for namespace */
    if (fd == -1)
        errExit("open");

    if (setns(fd, 0) == -1)         /* Join that namespace */
        errExit("setns");

    if(fork()==0){
        execvp(argv[2], &argv[2]); 
    }     /* Execute a command in namespace */
    wait(NULL);
    errExit("execvp");
}
