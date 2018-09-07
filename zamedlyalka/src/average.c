#include "average.h"

#include <string.h>

int averageArray(double *p_array, size_t p_arrayCount, size_t p_averageWidth, double *p_resultArray)
{
    size_t i;
    if (p_averageWidth == 0)
    {
        if (p_resultArray != p_array)
            memcpy(p_resultArray, p_array, p_arrayCount * sizeof(double));
        return 0;
    }
    double mean;
    if (p_averageWidth >= p_arrayCount)
    {
        // усредняем всё
        mean = 0;
        for (i = 0 ; i < p_arrayCount ; i++)
        {
            mean += p_array[i];
        }
        mean /= (double)p_arrayCount;
        for (i = 0 ; i < p_arrayCount ; i++)
        {
            p_resultArray[i] = mean;
        }
    }
    else
    {
        long a, b, prevA = 0;
        for (i = 0 ; i < p_arrayCount ; i++)
        {
            a = i - p_averageWidth / 2;
            b = i + p_averageWidth / 2;
            if (a < 0)
            {
                b += -a;
                a = 0;
            }
            if (b > p_arrayCount)
            {
                a -= (b - p_arrayCount);
                b = p_arrayCount;
            }
            if (i == 0)
            {
                mean = 0;
                for (i = 0 ; i < p_averageWidth ; i++)
                {
                    mean += p_array[i];
                }
                mean /= (double)p_averageWidth;
            }
            if (prevA != a)
            {
                mean += (p_array[b - 1] - p_array[a - 1]) / (double)p_averageWidth;
            }
            p_resultArray[i] = mean;
            prevA = a;
        }
    }
    return 0;
}
