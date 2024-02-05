#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>



int main(int argc, char * argv[]){


int fd = open("fifo",O_WRONLY);

if(argc <= 1){
    printf("Missing argument");
}

if(fd == -1){
    perror("open");
} else {
    printf("opened fifo for writing\n");
}

write(fd,argv[1],strlen(argv[1]));

close(fd);
return 0;
}