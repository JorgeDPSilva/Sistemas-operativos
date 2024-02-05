#include "headers.h"

int contapalavras(char *argv){
    char guarda[strlen(argv)];
    strcpy(guarda,argv);
    int i, conta=0,tamanho=strlen(argv);
    for (i = 0; i< tamanho; i++)
    {
        if ((!isspace(guarda[i]) && guarda[i] != '\t' && guarda[i] != '\n') && guarda[i + 1]=='\0')//para contar a ultima palavra      
            conta=conta+1;
        
        else if ((!isspace(guarda[i]) && guarda[i] != '\t' && guarda[i] != '\n') && isspace(guarda[i + 1]))//para contar quando passa de uma para a outra
            conta=conta+1;
    }
    return conta;
}

void correcomandos(char *argv) { 
    pid_t rc = fork();
    int status;
    char *comando[contapalavras(argv)+1];
    int i = 0;
    if (rc == 0) {
        //processo filho
        if (contapalavras(argv) == 1) {
            execlp(argv, argv, NULL);
        } else{
            //contapalavras(>2)
            char *token = strtok(argv, " ");
            while (token != NULL) {
                comando[i] = token;
                i++;
                token = strtok(NULL, " ");
            }
            comando[i] = NULL;
            execvp(comando[0], comando);  
        }
        comando[i] = NULL;
        execvp(comando[0], comando);
        // Ocorreu um erro no fork()
        perror("Erro no fork()");
        exit(1);
        }      
     else {  
        //pai  
        wait(&status);
    } 
}


int main(int argc, char * argv[]){

char buf[MAXSIZE];
int fd;
pid_t pid;
struct timeval tempo_inicial,tempo_final;
time_t inicial_timestamp;

// Abre o FIFO para escrita
fd = open("../tmp/fifo", O_WRONLY);

if(fd == -1){
    perror("open");
    _exit(0);
}

// obter o pid para passar como informação para o servidor
pid = getpid();

//obter o programa que vai executar para passar para o servidor
char *nome_programa = argv[3];

// Obtém o timestamp atual
gettimeofday(&tempo_inicial, NULL);
inicial_timestamp = tempo_inicial.tv_sec;




switch (argc) {
        case 2:
            if (strcmp(argv[1], "status") == 0) {
                char status[100];
                sprintf(status, "%d", pid);
                write(fd,status,strlen(status));
            }
            break;
        case 4:
        // Cria uma string com as informações a serem enviadas ao servidor
        // snprintf = garantir que a string de saída não ultrapasse o tamanho máximo do buffer
        snprintf(buf,sizeof(pid)+ sizeof(nome_programa)+ sizeof(inicial_timestamp)+3,"%d %s %ld",pid,nome_programa,inicial_timestamp);
        write(fd, buf, strlen(buf));
            if (strcmp(argv[2], "-u") == 0) {
                // executar o programa e medir o tempo
                printf("Running PID: %d\n",pid);
                fflush(stdout);
                correcomandos(argv[3]);
                gettimeofday(&tempo_final, NULL);
                int tempo_em_ms = (int)((tempo_final.tv_sec - tempo_inicial.tv_sec) * 1000 + (tempo_final.tv_usec - tempo_inicial.tv_usec) / 1000);
                printf("Ended in: %d ms\n",tempo_em_ms);
            }
            break;
        default:
            printf("Argumentos invalidos\n");
            return 0;
    }

// fecha o descritor
close(fd);
return 0;
}


