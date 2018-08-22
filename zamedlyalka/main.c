#include <stdio.h>
//#include <stdlib.h>
int main()
{
    //system("stty raw");//seting the terminal in raw mode
    char a;// = getch();
    while ((a = getchar()) != 27)
    {
        printf("%c(%i)\n", a, a);
    }
    //system("stty cooked"); // возвращаем консоль в нормальный режим работы
    //printf("%i", a);
    return 0;
}
