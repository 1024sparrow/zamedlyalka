#ifndef TYPES_H
#define TYPES_H

#include <sys/types.h>

struct Params
{
    Params(){
        quality = 20;
        discretFreq = 44100;
        tickCountPerKick = 1000;
        freqCount = 6;
        maxVal = 400;
        COUNT = 5;
    }
    double quality;
    double discretFreq;
    int tickCountPerKick;
    int freqCount;
    double maxVal;
    int COUNT;
};

struct FreqSet
{
    size_t count;
    double *freq; // массив частот (count элементов)
    double *spectra; // мощность на разных частотах (count элементов в массиве)
};

enum NormParams__Variants
{
    //NormParams__Variants__
    NormParams__Variants__devR1 = 1,
    NormParams__Variants__devR2 = 2,
    NormParams__Variants__sinusDevR1 = 4,
    NormParams__Variants__sinusDevR2 = 8,
    NormParams__Variants__sinResDevR1 = 16,
    NormParams__Variants__sinResDevR2 = 32
};
struct NormParams
{
    int divideFlags;
    int multiplyFlags;
    void toggle(int p_flag, bool ifDivide){
        int *divide = ifDivide ? &divideFlags : &multiplyFlags;
        int *multiply = ifDivide ? &multiplyFlags : &divideFlags;
        if ((*divide) & p_flag)
            (*divide) &= ~p_flag;
        else{
            (*divide) |= p_flag;
            (*multiply) &= ~p_flag;
        }
    }
};

#endif // TYPES_H
