#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>





int main(int argc, char * argv[]){
    char buffer[4096];
    int bytes_read;
    int fd = open("fifo",O_WRONLY);
    printf("abri fifo escritor \n");
    
    while((bytes_read = read(0,buffer,4096)) > 0){
        
        write(fd,buffer,bytes_read);
    }
    printf("sai do while escritor \n");
    close(fd);

    return 0;
}