#include <stdio.h> // printf()
#include <string.h> // strcmp()
//#include <stdlib.h> // system()
#include <sys/types.h>
#include <unistd.h> // pipe(), fork()

#define ERR(T) {fprintf(stderr, T);return 1;}
#define COMMAND_BUF_SIZE 1024

int main()
{
    printf("1234\n");
    //system("stty raw");//seting the terminal in raw mode
    
    int fdPipe[2];
    if (pipe(fdPipe) < 0)
        ERR("не смог открыть канал (внутрення ошибка)")

    pid_t pidChild = fork();
    if (pidChild < 0)
        ERR("не смог породить дочерний процесс (внутренняя ошибка)")
    else if (pidChild == 0) // дочерний процесс
    {
    }
    else // родительский процесс
    {
    }

    char command[COMMAND_BUF_SIZE];
    while (strcmp(fgets(command, COMMAND_BUF_SIZE, stdin), "quit\n") != 0)
    {
        printf("command: %s", command);
        if (*command == 'q')
        {
            printf("Q!!\n");
        }
        else if (*command == 'w')
        {
            printf("W!!\n");
        }
    }
    return 0;

    //system("stty cooked"); // возвращаем консоль в нормальный режим работы
}
