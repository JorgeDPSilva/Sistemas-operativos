#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char** argv){
int ret;
char *exec_args [] = {"/bin/ls","-l",NULL};
//ex1

ret = execl("/bin/ls","/bin/ls","-l",NULL);
ret = exclp("ls","ls","-l",NULL);
ret = execv ("/bin/ls",exec_args);
ret = execvp("ls",exec_args);

//ex 2  
execlp("ls","ls","-l",NULL);
perror("ls");
_exit(1);

//ex3
int res;
int status;
for(int i = 1; i < argc ; i++){
if (fork() == 0){
    printf( "Sou o filho %d e vou executar o comando %s",getpid(),argv[i]);
    res=execlp(argv[i],argv[i],NULL);
    perror("reached return");
    _exit(res);
    }
}
  for(int i = 1 ; i< argc, i++){  
    printf("Sou o pai e estou à espera dos filhos\n");
    int pid = wait(&status);
    printf("Terminou o processo: %d", pid,WEXITSTATUS(status));
  } 
  printf("todos os filhos executaram \n"); 

//ex 4

int mysystem (char* command){
  int fork_ret,exec_ret,status,res;
  // estamos a assumir numero maximo de argumentos 
  char *exec_args[20];
  char *string= NULL;
  int i =0;
  char *cmd=strdup(command);

  string=strsep(&cmd," ");

  while(string!=NULL){
    exec_args[i]= string;
    string=strsep(&cmd," ");
    i++;
  }
  exec_args[i]=NULL;

fork_ret= fork();
  if (fork_ret == -1){
    return -1;
}
else{
      if(fork_ret == 0){
        exec_ret=execvp(exec_args[0],exec_args);
        perror(exec_args[0]);
        _exit(exec_ret);
    }
    wait(&status);
    //para ir buscar o valor do filho
    free(cmd);
    return WEXITSTATUS(status);
}
}


}
