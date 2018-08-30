//  sudo apt install libasound2-dev (Ubuntu)
//  sudo apt-get install libalsa-devel (ALT-linux)

#include <stdio.h> // printf()
#include <getopt.h>
#include <string.h> // strcmp(), strcpy()
#include <stdlib.h> // exit
//#include <stdlib.h> // system()
#include <signal.h>
#include <sys/types.h>
#include <unistd.h> // pipe(), fork()
#include "../src/wav.h" // read and write WAV
#include "../src/dsp.h" // signal processing
#include "../src/sound.h" // ALSA interaction

#define ERR(T) {fprintf(stderr, T);return 1;}
#define COMMAND_BUF_SIZE 1024
#define PIPEDEBUG_BUF_SIZE 1024
#define debug(T) {printf(T);}

static char filepath_in[1024];

/*
SIGUSR1 - от родительского к дочернему
*/

static pid_t pidParent;
static int received = 0;
static int fdPipe[2];
static char commandBuf[COMMAND_BUF_SIZE];
static int fdPipeDebug[2];// канал для отсылки отладочных сообщений из дочернего процесса (из callback-ов, в частности)
static char pipeDebug[1024];
//https://habr.com/post/141206/
//https://stackoverflow.com/questions/36234703/send-signal-from-parent-process-to-child-in-c
// в функциях-обработчиках сигналов не работает printf()

{%% main__process_command.c %%}

{%% main__child_proc_signal_callback.c %%}

{%% main__parent_proc_signal_callback.c %%}

//const char *help = {%% help %%};

void
help()
{
    printf("{%% help %%}\n");
}

int
main(int argc, char **argv)
{
    struct DSP_DATA dsp_data;

    int p_shift = 0;
    *filepath_in = 0;
    int argCounter = argc;
    // ----------------------------------
    int c;
    while (1)
    {
        int this_option_optind = optind ? optind : 1;
        int option_index = 0;
        static struct option long_options[] = {
            {"shift",     no_argument, 0,  's' },
            {"help",     no_argument, 0,  'h' },
            {"silent-mode",     no_argument, 0,  'S' },
            {0,         0,                 0,  0 }
        };

        c = getopt_long(argc, argv, "Ssh", long_options, &option_index);
        if (c == -1)
            break;

        switch (c) {
        case 0:
            printf("case 0\n");
            printf("параметр %s", long_options[option_index].name);
            if (optarg)
                printf(" со значением %s", optarg);
            printf("\n");
            break;
        case 's':
            p_shift = 1;
            break;
        case 'S':
            // врубаем режим "тишины" - в консоль пишем только когда произошёл запрос на определение текущего момента времени на звуковой дорожке.
            break;
        case 'h':
            help();
            return 0;
        case '?':
            printf("Для справки по программе вызовите программу с ключом --help.\n");
            exit(1);
        default:
            printf("--%c--\n", c);
        }
    }
    if (argc > optind)
        strcpy(filepath_in, argv[optind]);
    if (*filepath_in == 0)
    {
        printf("Не задан входной wav-файл\n");
        printf("Для справки по программе вызовите программу с ключом --help.\n");
        exit(1);
    }
    // ==================================
    printf("Начинаю предобработку со следующими парметрами:\n");
    printf("  Входной файл: %s\n", filepath_in);
    printf("  Режим работы со смещениями каналов: %s\n", p_shift ? "Активирован" : "Не активирован");

    if (readWav(filepath_in, &dsp_data, p_shift))
        return 1;
    double freqStepKoeff = 1/40.;
    if (process_signal(&dsp_data, 20, 20000, freqStepKoeff, 20))
        return 1;
    return 0;//
    //system("stty raw");//seting the terminal in raw mode
    
    if (pipe(fdPipe) < 0)
        ERR("не смог открыть канал (внутрення ошибка)")
    if (pipe(fdPipeDebug) < 0)
        ERR("не смог открыть отладочный канал (внутренняя ошибка)")

    pidParent = getpid();
    printf("pidParent: %i\n", pidParent);
    pid_t pidChild = fork();
    printf("pidChild: %i\n", pidChild);
    if (pidChild < 0)
        ERR("не смог породить дочерний процесс (внутренняя ошибка)")
    else if (pidChild == 0) // дочерний процесс
    {
        //printf("начат дочерний процесс\n");
        if (signal(SIGUSR1, childProcSignalCallback) < 0)
            ERR("Не смог привязать обработчик к сигналу");
        return 0;//
        sound_start();

        //
        //printf("Process2, pid=%d\n",getpid());
        //while (!received)
        //    ;
        //printf("SIGUSR1 received: %s\n", commandBuf);
    }
    else // родительский процесс
    {
        //if (signal(SIGUSR1, parentProcSignalCallback) < 0)
        //    ERR("Не смог привязать обработчик к сигналу");
        char command[COMMAND_BUF_SIZE];
        printf(">> ");
        while (strcmp(fgets(command, COMMAND_BUF_SIZE, stdin), "quit\n") != 0)
        {
            if (strcmp(command, "help\n") == 0){
                help();
                printf(">> ");
                continue;
            }
            size_t l = strlen(command);
            if (write(fdPipe[1], command, l) < 0 )
                ERR("не смог записать в канал (внутренняя ошибка)")
            if (kill(pidChild, SIGUSR1) < 0)
                ERR("не смог сэмитировать сигнал\n")
            printf(">> ");

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
