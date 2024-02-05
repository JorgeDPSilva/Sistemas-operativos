#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

int main () {
int pipefd[2];
pid_t pid;
char buffer[1024];
int res=0;
int status;

// criar o pipe
    if (pipe(pipefd) != 0) {
        perror("pipe");
        return -1;
    }

// criar um processo filho
pid = fork();
 if (pid == -1) {
        perror("fork");
    }

// fechar o descritor de escrita do pipe no proceso filho  
    if (pid == 0) { 
        close(pipefd[1]);
        dup2(pipefd[0],0);
        close(pipefd[0]);
        execlp("wc", "/bin/wc", NULL);
        _exit(0);
    }else{
        printf("[PAI] pid %d, filho tem pid %d\n",getpid(),pid);
        close(pipefd[0]);
        while((res=read(0,buffer,1024))>0){
            write(pipefd[1],buffer,res);
        }
    
    close(pipefd[1]);
    wait(&status);
    if(WIFEXITED(status)){
            printf("[PAI] filho terminou com %d\n",WEXITSTATUS(status));
    }

    }
     return 0;
}