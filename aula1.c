#include <stdio.h>
#include <unistd.h>
#include "readln.h"

#define BUF_SIZE 1024

int main( int argc,char** argv){

int bytes_read;
char *buf = (char*) malloc (sizeof(char) * BUF_SIZE);

while((bytes_read = read(0,buf,BUF_SIZE) > 0)){
    //escrever para o stdout (fd=1)
    write(1,buf,bytes_read);
}

printf("received EOF\n");

free(buf);

return 0;
}


//lê um caracter de um dado descritor de ficheiro
int readch(int fd , char* buf){
    return read(fd,buf,1);
}

// a funcao termina se atingirmos o size (buffer cheio)
// ou se encontrarmos um \n
// devolve o nº de bytes lidos (posicao)
ssize_t readln(int fd,char *line, size_t size){
int pos = 0;

//lê caracter a caracter enquanto houver algo para ler
// e houver espaço no buffer( pos < size)
while( pos < size && readch(fd, &line[pos])>0){
    pos+=1;
    // se o caracter que acabamos de ler (pos-1) for igual a \n paramos de ler
    if(line[pos-1] == '\n'){
        break;
    }
}
//devolver o nº de bytes que lemos
return pos;
}

