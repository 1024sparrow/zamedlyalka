#include <stdio.h> // printf()
#include <stdlib.h> // malloc()
#include <math.h> // M_PI

#include "dsp.h"

int process_signal(struct DSP_DATA *dsp_data, double p_startFreq, double p_endFreq, double p_freqStepKoeff, double p_q)
{
    printf("Начинаю предобработку.\n");
    {// Составляем набор частот, по которым будет работать
        double i;
        int counter = 0;
        
        //printf("----------------------\n");
        for (i = p_startFreq ; i < p_endFreq ; i+= i*p_freqStepKoeff)
        {
            //printf("freq %i: %f Hz\n", counter, i);
            counter++;
        }
        //printf("======================\n");
        dsp_data->freqCount = counter;
        dsp_data->frequences = malloc(counter * sizeof(double));
        counter = 0;
        for (i = p_startFreq ; i < p_endFreq ; i+= i*p_freqStepKoeff)
        {
            dsp_data->frequences[counter] = i;
            counter++;
        }
    }

    dsp_data->spectrogram = malloc(dsp_data->freqCount * dsp_data->count * dsp_data->processingChannels * sizeof(double));

    int iChannel, iFreq, iData0, l = dsp_data->processingChannels, o;
    double *p = malloc(dsp_data->count * sizeof(double)); // сила тока от времени
    double *q = malloc(dsp_data->count * sizeof(double)); // заряд от времени
    double k1, k2, k3, k4;
    double h = 2. * M_PI / (double)(dsp_data->discretFreq);
    double e, w; // ЭДС вынуждения и собств. частота контура соответвенно
    int periodCount;
    for (o = 0 ; o < dsp_data->processingChannels ; o++)
    {
        for (iFreq = 0 ; iFreq < dsp_data->freqCount ; iFreq++)
        {
            double *oSpectr = dsp_data->spectrogram + o * (dsp_data->freqCount * dsp_data->count) + iFreq * dsp_data->count;
            w = dsp_data->frequences[iFreq];
            periodCount = dsp_data->discretFreq / w / 2;
            p[0] = 0;
            q[0] = 1;
            for (iData0 = 1; iData0 < dsp_data->count ; iData0++)
            {
                //e = dsp_data->data_0[iData0 - 1];
                e = dsp_data->data_0[(iData0 - 1) * l + o];
                k1 = h * (e - w * p[iData0 - 1] / p_q - w * w * q[iData0]);
                k2 = h * (e - w * (p[iData0 - 1] + k1 / 2.) / p_q - w * w * q[iData0 - 1]);
                k3 = h * (e - w * (p[iData0 - 1] + k2 / 2.) / p_q - w * w * q[iData0 - 1]);
                k4 = h * (e - w * (p[iData0 - 1] + k3) / p_q - w * w * q[iData0 - 1]);
                p[iData0] = p[iData0 - 1] + (k1 + 2. * (k2 + k3) + k4) / 6.;
                k1 = h * p[iData0 - 1];
                k2 = h * (p[iData0 - 1] + k1/2.);
                k3 = h * (p[iData0 - 1] + k2/2.);
                k4 = h * (p[iData0 - 1] + k3);
                q[iData0] = q[iData0 - 1] + (k1 + 2. * (k2 + k3) + k4) / 6.;
            }
            // Записываем усреднённые по perioCount отсчётам значения мгновенной мощности сигнала (сумма квадратов значений p)
            //if (iFreq > 0)
            //    break;
            //printf("Пишу спектрограмму по частоте %f Гц\n", w);//
            double cand, maxPowerForFreq = 0;
            size_t prevA;
            for (iData0 = 0; iData0 < dsp_data->count ; iData0++)
            {
                int a = iData0 - periodCount;
                int b = iData0 + periodCount;
                if (a < 0 )
                {
                    b += -a;
                    a = 0;
                }
                if (b > dsp_data->count)
                {
                    a -= (b - dsp_data->count);
                    b = dsp_data->count;
                }
                if (a < 0)
                {
                    printf("Слишком маленькая выборка для такой частоты.");
                    return 1;
                }
                if (iData0 == 0)
                {
                    cand = 0;
                    for (int i = a ; i < b ; i++)
                    {
                        double sq = p[i];
                        cand += sq * sq;
                    }
                    prevA = a;
                }
                else
                {
                    if (a != prevA)
                    {
                        double sq = p[prevA];
                        cand -= sq * sq;
                        sq = p[b - 1];
                        cand += sq * sq;
                        prevA = a;
                    }
                }
                if (cand > maxPowerForFreq)
                    maxPowerForFreq = cand;
                oSpectr[iData0] = cand;
            }
            printf("Пишу спектрограмму по частоте %f Гц. пиковая плотность мощности: %g\n", w, maxPowerForFreq);//
        }
    }

    printf("Предобработка завершена.\n");
    return 0;
}
