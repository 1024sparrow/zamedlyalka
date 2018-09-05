#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h> // execve()
#include <stdlib.h> // malloc

void
process(size_t *pout_count, double **pout_array, double **pout_timeArray);

int
main()
{
    // ... (получаем массив данных)
    /*
     * 1. Получаем массив данных
     * 2. Записываем данные в файл data.dat
     * 3. Запускаем (синхронно) gnuplot. Пусть gnuplot читает данные из data.dat и пишет svg-картинку в image.svg
     * 4. Обновляем отображение нашей отображалки SVG-файла wCanvas.
     */
    size_t sz = 0;
    double *array, *timeArray;
    process(&sz, &array, &timeArray);
    //return 0;//

    int fdDat = open("data.dat",  O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR|S_IWUSR);
    const char *h = "#t i\n";
    write(fdDat, h, strlen(h));
    for (size_t i = 0 ; i < sz ; i++)
    {
        dprintf(fdDat, "%f %f\n", timeArray[i], array[i]);
    }
    // fork -> execute "gnuplot plot.plt" into "bin/"
    char curdir[1024];
    char *curdirS = getcwd(curdir, 1024);
    const char *filenameS = "/plot.plt";
    char *paramS = malloc(strlen(curdirS) + strlen(filenameS) + 1);
    strcpy(paramS, curdirS);
    strcat(paramS, filenameS);
    execl("/usr/bin/gnuplot", "/usr/bin/gnuplot", paramS, (char*)NULL);
    free(paramS);
    printf("asdasdasd\n");
    perror("execl error:");
    return 1;
}
