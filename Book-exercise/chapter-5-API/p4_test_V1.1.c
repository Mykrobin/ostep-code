//
// Created by Lenovo on 2021/2/26.
//
// environment Linux/Unix
// 操作系统导论 p4.c
// 采用dup() 的方式进行文件重定向
// 注：在close(STDOUT_FILENO) 命令执行之后，关闭标准输入输出，从而将指令信息输出到文件中

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int)getpid());
    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (0 == rc) { // redirect standard output to a file
        close(STDOUT_FILENO);
        // open("./p4.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);  // 覆盖写
        // int fd_stdout_bak = dup(1);    // 覆盖写 
        int fd_file1 = creat("ccc.out", 0777);
        int fd_file = creat("bbb.out", 0777);
        // int fd_file1 = creat("ccc.out", 0777);
        // int fd = dup2(fd_file, 1); // 1 指向 file.dat

        printf("hello, I am child (pid: %d)\n", (int)getpid());
        char *myargs[4];
        myargs[0] = strdup("ifconfig");     // program: "ls"
        // myargs[0] = strdup("ls");     // program: "ls"
        // myargs[1] = strdup("-a");        // program: "ls"
        // myargs[2] = strdup("-l");        // program: "ls"
        //myargs[1] = strdup("p4_Fork.c");  // argument: file to count
        myargs[1] = NULL;                // marks end of array
        execvp(myargs[0], myargs);       // runs word count
        free(*myargs);
        // close(fd_stdout_bak);
        close(fd_file);
        close(fd_file1);

    } else {
        int wc = wait(NULL);
        printf("Sorry, I am parent of %d (wc:%d) (pid: %d)\n", rc, wc, (int)getpid());
    }

    return 0;
}