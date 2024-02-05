#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h> 



int main(int argc , char* argv[]){
char buffer[1024];
int res;
int fdpass = open("/etc/passwd",O_RDONLY);
int fdsaida = open("saida.txt", O_CREAT | O_TRUNC | O_WRONLY , 0666);
int fderr = open("erros.txt", O_CREAT | O_TRUNC | O_WRONLY , 0666);
int fdout = dup(1);

dup2(fdpass,0);
close(fdpass);

dup2(fdsaida,1);
close(fdsaida);

dup2(fderr,2);
close(fderr);
    
    // ler do standard input
    while((res=read(0,buffer,1024))>0){
        write(1,buffer,res);
        write(2,buffer,res);
    }

dup2(fdout,1);
close(fdout);

printf("terminei\n");
    return 0;
}