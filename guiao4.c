#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>


void pai_to_filho(){
int fork_ret = fork();
int status;
int p[2];

if (pipe(p) == -1){
    perror("erro ao criar o pipe\n");
}

    if (fork_ret == 0){
        int res = 0;
        close(p[1]);
        if (read(p[0], &res,sizeof(int)) == 1){
            perror("FILHO| erro ao ler do pipe \n");
        }
        printf("FILHO | li o valor %d\n",res);
        close(p[0]);
        _exit(0);
    
    } else {
        int value = 940;
        close(p[0]);
        printf("PAI | vou enviar o valor %d\n",value);
       if (write(p[1],&value,sizeof(int)) == -1){
            perror("PAI | erro ao escrever para o pipe\n");
       }
        close(p[1]);
        wait(&status);
    }
}


void filho_to_pai(){
    int status;
    int p[2];

    if(pipe(p) == -1){
        perror("erro ao criar o pipe \n");
    }

    int fork_ret = fork();
    if (fork_ret == 0){
        int value = 934;
        close(p[0]);
        printf("FILHO | vou enviar o valor %d\n",value);
        if(write(p[1],&value,sizeof(int)) == 1){
            perror("FILHO| erro ao ler do pipe \n");
        }
        close(p[1]);
        _exit(0);
     } else {
        int res = 0;
        close(p[1]);
        if(read(p[0],&res,sizeof(int)) == 1){
             perror("PAI| erro ao ler do pipe \n");
        }
        printf("PAI | li o valor %d\n",res);
        close(p[0]);
        wait(&status)
     }
}




int main (){

    //pai_to_filho();
    filho_to_pai();

return 0;
}

