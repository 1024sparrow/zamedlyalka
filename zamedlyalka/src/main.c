#include <stdio.h> // printf()
#include <string.h> // strcmp()
//#include <stdlib.h> // system()
#include <signal.h>
#include <sys/types.h>
#include <unistd.h> // pipe(), fork()

#define ERR(T) {fprintf(stderr, T);return 1;}
#define COMMAND_BUF_SIZE 1024

static int received = 0;
static int fdPipe[2];
static char commandBuf[COMMAND_BUF_SIZE];
static char commandDebug[1024];
//https://habr.com/post/141206/
//https://stackoverflow.com/questions/36234703/send-signal-from-parent-process-to-child-in-c
// в функциях-обработчиках сигналов не работает printf()

{%% main__process_command.c %%}

{%% main__sigcallbacks.c %%}

const char *help = {%% help %%};

int main()
{
    printf("1234\n");
    //system("stty raw");//seting the terminal in raw mode
    
    if (pipe(fdPipe) < 0)
        ERR("не смог открыть канал (внутрення ошибка)")


    pid_t pidChild = fork();
    if (pidChild < 0)
        ERR("не смог породить дочерний процесс (внутренняя ошибка)")
    else if (pidChild == 0) // дочерний процесс
    {
        printf("начат дочерний процесс\n");
        if (signal(SIGUSR1, sigintHandler) < 0)
            ERR("Не смог привязать обработчик к сигналу");
        //
        //printf("Process2, pid=%d\n",getpid());
        //while (!received)
        //    ;
        //printf("SIGUSR1 received: %s\n", commandBuf);
    }
    else // родительский процесс
    {
        char command[COMMAND_BUF_SIZE];
        while (strcmp(fgets(command, COMMAND_BUF_SIZE, stdin), "quit\n") != 0)
        {
            size_t l = strlen(command);
            if (write(fdPipe[1], command, l) < 0 )
                ERR("не смог записать в канал (внутренняя ошибка)")
            if (kill(pidChild, SIGUSR1) < 0)
                ERR("не смог сэмитировать сигнал\n")

            //printf("command: %s", command);
            //if (*command == 'q')
            //{
            //    printf("Q!!\n");
            //    const char * command = "play";
            //    size_t l = strlen(command);
            //    if (write(fdPipe[1], command, l) < 0 )
            //        ERR("не смог записать в канал (внутренняя ошибка)")
            //    if (kill(pidChild, SIGUSR1) < 0)
            //        ERR("не смог сэмитировать сигнал\n")
            //    printf("послан сигнал\n");
            //}
            //else if (*command == 'w')
            //{
            //    printf("W!!\n");
            //}
        }
    }

    return 0;

    //system("stty cooked"); // возвращаем консоль в нормальный режим работы
}
