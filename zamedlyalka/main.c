#include <stdio.h>
#include <string.h>
//#include <stdlib.h>
int main()
{
    printf("1234\n");
    //system("stty raw");//seting the terminal in raw mode

    char command[1024];
    while (strcmp(fgets(command, 1024, stdin), "quit\n") != 0)
    {
        printf("command: %s", command);
    }
    return 0;

    //system("stty cooked"); // возвращаем консоль в нормальный режим работы
}
