#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>




int main(int argc, char * argv[]){
char buffer[4096];
int bytes_read;
int res = mkfifo("fifo",0666);


int fd = open("fifo",O_RDONLY);
// para o servidor estar sempre aberto
int fd2 = open("fifo",O_WRONLY);





while((bytes_read = read(fd,buffer,4096)) > 0){
        write(1,buffer,bytes_read);
        close(fd2);
}

        printf("sai do while leitor\n");
        close(fd);
        unlink("fifo");
        return 0;



}
