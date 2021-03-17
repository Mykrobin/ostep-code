//
// Created by Lenovo on 2021/2/26.
//
// environment Linux/Unix
// 操作系统导论 p1.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    printf("hello world (pid:%d)\n", (int)getpid());
    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (0 == rc) {
        printf("hello, I am child (pid: %d)\n", (int)getpid());
    } else {
        printf("Sorry, I am parent of %d (pid: %d)\n", rc, (int)getpid());
    }

    return 0;
}
