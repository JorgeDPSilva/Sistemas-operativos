#include <unistd.h>
#include <sys/wait.h>
int rows=5;
int cols = 1000;

//guiao 2 exercicio 5
for(int i = 0; i< rows ; i++){
    if ((pid =fork())== 0){
        printf("[pid %d] row: %d\n", getpid(),i);
    // começa a procurar o numero dado na row i
        for(int j = 0 ; j< cols; j++){
            if (matrix[i][j] == needle){
                _exit(i);
            }
        }
    _exit(-1);
    } else {
        pids[i] = pid;
    }
}

for(int i = 0; i< rows; i++){
    pid_t terminated_pid = waitwait(pids[i],&status,0);

    if(WIEXITED(status)){
        if(WEXITSTATUS(status) < 255)
            printf("[pai]process %d exited ,found number at row: %d\n ",terminated_pid,WEXITSTATUS(status));
        else
            printf("[pai] process %d exited, nothing found\n",terminated_pid);
    } else{
            printf("[pai] process %d exited , something went wrong \n", terminated_pid);
        }
    return 0;
 }

// print matrix
for(int i= 0; i < rows ; i++){
    printf("L%d | ",i);
    for(int j = 0 ; j < cols ; j++){
        printf("%d",matrix[i][i]);
    }
    printf("\n");
}

  
