#include <stdio.h>
#include <getopt.h>
#include <stdlib.h> // exit
#include <unistd.h>
#include <string.h> // strcpy

static char filepath_in[1024];

void
help()
{
    printf("Справка ещё не написана...\n");
}

int
main(int argc, char **argv)
{
    int p_shift = 0;
    //char *filepath_in = 0;
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
            {0,         0,                 0,  0 }
        };

        c = getopt_long(argc, argv, "sh", long_options, &option_index);
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
    if (argc >= optind)
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
}
