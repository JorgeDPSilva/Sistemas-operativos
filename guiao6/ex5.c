#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>


int main() {
    int pipefd[2];
    pid_t pid;
    int status;

    // Cria o pipe
    if (pipe(pipefd) != 0) {
        perror("pipe");
        return -1;
    }

    // Cria um novo processo filho
    pid = fork();
    if (pid == -1) {
        perror("fork");
    }

    // Processo filho
    if (pid == 0) {
       // Fecha o descritor de leitura do pipe
        close(pipefd[0]);
       
       //Redireciona a saída padrão para o descritor de escrita do pipe
        dup2(pipefd[1],1);

        //fecha o descritor de escrita do pipe
        close(pipefd[1]);

        // Executa o comando "ls /etc"
        execlp("ls", "ls", "/etc", NULL);

        // Em caso de falha na execução do comando
        perror("execlp");

    } else {
        // Processo pai

        // Fecha o descritor de escrita do pipe
        close(pipefd[1]);
        
        // Redireciona a entrada padrão para o descritor de leitura do pipe
        dup2(pipefd[0], 0);

        // Fecha o descritor de leitura do pipe 
        close(pipefd[0]);

        // Executa o comando "wc -l"
        execlp("wc", "wc", "-l", NULL);

        // Em caso de falha na execução do comando
        perror("execlp");

        
    }

    return 0;
}