#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#define MAXSIZE 1024

struct Node {
    char* pid;
    char* comandos;
    char* tempoinicial;
    struct Node* prox;
};