#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>




int main() {
    int N = 4;
    int pipefds[N-1][2];
    pid_t pid;
    int status[N];
    char* comandos[] = {"ls", "cat", "tail", "wc"};
    int i,fd,res;
   


    for(i=0;i<N;i++){
        // caso do primeiro filho
        if(i==0){
            fd=pipe(pipefds[i]);
            if(fd != 0){
                perror("erro ao criar o pipe");
                _exit(0);
                }
            pid = fork();
            if(pid == -1){
                    perror("erro");
                    _exit(0);
                }
            if(pid == 0){
                close(pipefds[i][0]);
                if(dup2(pipefds[i][1],1) != 0){
                    printf("deu erro no primeiro caso");
                }
                close(pipefds[i][1]);
                res=execlp(comandos[i], comandos[i], NULL);
                _exit(res);
            } else{
                //pai
                close(pipefds[i][1]);
                } 
        // caso do ultimo filho
        } else if(i== N-1){
                pid=fork();
                if(pid == -1){
                    perror("erro");
                    _exit(0);
                }
                if(pid == 0){
                    if(dup2(pipefds[i-1][0],0) != 0){
                        printf("deu erro no ultimo caso");
                    }
                    close(pipefds[i-1][0]);
                    res=execlp(comandos[i],comandos[i],NULL);
                    _exit(res);
                }else{
                    //pai
                    close(pipefds[i][0]);
                }
        // caso para o meio da pipeline
        } else {
                    pipe(pipefds[i]);
                    pid = fork();
                    if(pid == -1){
                    perror("erro");
                    _exit(0);
                    }   
                    if(pid == 0){
                        close(pipefds[i][0]);
                        if(dup2(pipefds[i-1][0],0) != 0){
                            printf("erro a ler do pipe anterior");
                        }
                        close(pipefds[i-1][0]);
                        if(dup2(pipefds[i][1],1) != 0){
                            printf(" erro a escrever para o pipe seguinte");
                        }
                        close(pipefds[i][1]);
                        res=execlp(comandos[i],comandos[i],NULL);
                        _exit(res);
                    }else{
                        // fecha descritor do pipe anterior
                        close(pipefds[i-1][0]);
                        // fecha o descritor de escrita do pipe onde vai escrever
                        close(pipefds[i][1]);
                    }
        }
    }
    
    for(i = 0; i < N; i++){
        wait(&status[i]);
    }

return 0;
}
