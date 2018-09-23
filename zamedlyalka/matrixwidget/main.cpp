#include <QApplication>
#include <stdio.h>
#include <stdlib.h>

#include "matrixwidget.h"
#include "matrix_data.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    struct MatrixData md;
    {
        md.xLabel = "Частота возбуждения";
        md.yLabel = "Собственная частота контура";
        md.count = 8;
        md.data = malloc(md.count * md.count * sizeof(double));
        md.comments = malloc(md.count * md.count * MATRIXDATA_COMMENT_BUF_LENGTH);
        for (size_t x = 0 ; x < md.count; ++x)
        {
            for (size_t y = 0 ; y < md.count ; ++y)
            {
                size_t index = x * md.count + y;
                md.data[index] =
            }
        }
    }
    MatrixWidget mw((&md));
    mw.show();
    //printf("md.xLabel: %s\n", md.xLabel);
    //printf("md.yLabel: %s\n", md.yLabel);
    return app.exec();
}
