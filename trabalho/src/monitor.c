#include "headers.h"

struct Node* inserecliente(char* buffer, struct Node* tracers) {
    char* token = strtok(buffer, " "); 
    struct Node *l = tracers;
    struct Node *new_client = (struct Node*)malloc(sizeof(struct Node));
    new_client->pid = (char*)malloc(strlen(token) + 1);
    new_client->pid = strdup(token);
    token = strtok(NULL, " ");
    new_client->comandos = (char*)malloc(strlen(token) + 1);
    new_client->comandos = strdup(token);
    token = strtok(NULL, " ");
    new_client->tempoinicial = (char*)malloc(strlen(token) + 1);
    new_client->tempoinicial = strdup(token);
    new_client->prox = NULL;
    if (l == NULL) {
        tracers = new_client;
    } else {
        while (l->prox != NULL) {
            l = l->prox;
        }
        l->prox = new_client;
    }
    return tracers;
}




int main(int argc, char * argv[]){
char buffer[4096];
int bytes_read;
mkfifo("../tmp/fifo",0666);
char path[] = "../tmp/";
struct Node *tracers=NULL;


int fd = open("../tmp/fifo",O_RDONLY);
// para o servidor estar sempre aberto
//int fd2 = open("../tmp/fifo1",O_WRONLY);
while(1){
    while((bytes_read = read(fd,buffer,4096)) > 0){
    char aux[100] = "";
    strcpy(aux,path);
    tracers = inserecliente(buffer, tracers); 
    char* token = strtok(buffer," ");
    strcat(aux,token);
    mkfifo(aux,0666);
     }
            
    }

//close(fd2);
printf("sai do while leitor\n");
close(fd);
// unlink("fifo");
return 0;

}
