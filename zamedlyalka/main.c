#include <stdio.h> // printf()
#include <string.h> // strcmp()
//#include <stdlib.h> // system()
#include <signal.h>
#include <sys/types.h>
#include <unistd.h> // pipe(), fork()

#define ERR(T) {fprintf(stderr, T);return 1;}
#define COMMAND_BUF_SIZE 1024

void sigintHandler(int p)
{
    printf("sigint catched");
}

int main()
{
    printf("1234\n");
    //system("stty raw");//seting the terminal in raw mode
    
    int fdPipe[2];
    if (pipe(fdPipe) < 0)
        ERR("не смог открыть канал (внутрення ошибка)")

    //https://habr.com/post/141206/
    //{{
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = sigintHandler;
    sigset_t   set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    sigaddset(&set, SIGUSR2);
    act.sa_mask = set;
    sigaction(SIGUSR1, &act, 0);
    //}}

    pid_t pidChild = fork();
    if (pidChild < 0)
        ERR("не смог породить дочерний процесс (внутренняя ошибка)")
    else if (pidChild == 0) // дочерний процесс
    {
        printf("начат дочерний процесс\n");
        //if (signal(SIGUSR1, sigintHandler) < 0)
        //    ERR("Не смог привязать обработчик к сигналу");
        //struct sigaction act;
        //memset(&act, 0, sizeof(act));
        //act.sa_handler = sigintHandler;
        //sigset_t   set;
        //sigemptyset(&set);
        //sigaddset(&set, SIGUSR1);
        //sigaddset(&set, SIGUSR2);
        //act.sa_mask = set;
        //sigaction(SIGUSR1, &act, 0);
    }
    else // родительский процесс
    {
        char command[COMMAND_BUF_SIZE];
        while (strcmp(fgets(command, COMMAND_BUF_SIZE, stdin), "quit\n") != 0)
        {
            printf("command: %s", command);
            if (*command == 'q')
            {
                printf("Q!!\n");
                raise(SIGUSR1);//
                if (kill(pidChild, SIGUSR1) < 0)
                    ERR("не смог сэмитировать сигнал\n")
                printf("послан сигнал\n");
            }
            else if (*command == 'w')
            {
                printf("W!!\n");
            }
        }
    }

    return 0;

    //system("stty cooked"); // возвращаем консоль в нормальный режим работы
}
