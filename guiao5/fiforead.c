#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>






int main (int argc, char * argv[]){

    char buffer[4096];
    int bytes_read;
    int fd = open("fifo", O_RDONLY);
    printf("abri fifo leitor\n");

    while((bytes_read = read(fd,buffer,4096)) > 0){
        write(1,buffer,bytes_read);    
        }
        printf("sai do while leitor\n");
        close(fd);

        return 0;

}