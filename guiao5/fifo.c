#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char * argv[]){

    int res = mkfifo("fifo",0666);
    if (res == -1){
        perror("erro ao criar fifo");
    }

}