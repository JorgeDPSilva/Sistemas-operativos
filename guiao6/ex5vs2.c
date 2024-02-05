#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>


int main() {
    int pipefd[2];
    pid_t pid1;
    pid_t pid2;
    int status;
   

    // Cria o pipe
    if (pipe(pipefd) != 0) {
        perror("pipe");
        return -1;
    }

    // Cria o primeiro processo filho
    pid1 = fork();
    if (pid1 == -1) {
        perror("fork1");
    }

    if (pid1 == 0) {
        // Processo filho 1

        // Fecha o descritor de leitura do primeiro pipe
        close(pipefd[0]);

        // Redireciona a saída padrão para o descritor de escrita do primeiro pipe
        dup2(pipefd[1], 1);

        // Fecha o descritor de escrita do primeiro pipe
        close(pipefd[1]);

        // Executa o comando "ls /etc"
        execlp("ls", "ls", "/etc", NULL);

        // Em caso de falha na execução do comando
        perror("execlp");


        } else {

            pid2 = fork();
            if (pid2 == 0) {
        // Processo filho 2

        // Fecha o descritor de leitura do primeiro pipe
        close(pipefd[0]);

        // Redireciona a saída padrão para o descritor de escrita do primeiro pipe
        dup2(pipefd[1], 1);

        // Fecha o descritor de escrita do primeiro pipe
        close(pipefd[1]);

        // Executa o comando "wc -l"
        execlp("wc", "wc", "-l", NULL);

        // Em caso de falha na execução do comando
        perror("execlp");
        _exit(0);


        }
        
        } else {
            // Processo pai

            // Fecha os descritores de escrita/leitura não utilizados
            close(pipefd[1]);

            // Fecha o descritor de leitura do primeiro pipe
            close(pipefd[0]);

         if(WIFEXITED(status)){
            printf("[PAI] filho terminou com %d\n",WEXITSTATUS(status));
         }
        if(WIFEXITED(status)){
            printf("[PAI] filho terminou com %d\n",WEXITSTATUS(status));
        }
        }

return 0;

}