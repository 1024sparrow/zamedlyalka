#include <stdio.h> // printf()
#include <stdlib.h> // malloc()
#include <sys/types.h>
#include <math.h> // M_PI

#include "dsp.h"
double *sinus_gen(double *p_retval, size_t p_count, double p_w, double p_wDiscr, double p_power); // implemented in sinus_gen.c

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

    size_t iChannel, iFreq, iData0, o, i;
    int l = dsp_data->processingChannels;
    double *p = malloc(dsp_data->count * sizeof(double)); // сила тока от времени
    double *q = malloc(dsp_data->count * sizeof(double)); // заряд от времени
    double k1, k2, k3, k4;
    double h = 1. / (double)(dsp_data->discretFreq);
    double e, w; // ЭДС вынуждения и собств. частота контура соответвенно
    int periodCount;

    //{{ test
    //
    /*{
        size_t i;
        double power0 = 0;
        double mean0 = 0;
        for (i = 0 ; i < dsp_data->count ; i++)
        {
            mean0 += dsp_data->data_0[i];
        }
        mean0 /= (double)dsp_data->count;
        for (i = 0 ; i < dsp_data->count ; i++)
        {
            mean0 += dsp_data->data_0[i];
            double sq = dsp_data->data_0[i] - mean0;
            power0 += sq * sq;
        }
        //for (iFreq = 0 ; iFreq < dsp_data->freqCount ; iFreq++)
        {
            //w = dsp_data->frequences[iFreq];
            w = 50.;
            double *sinus = sinus_gen(0, dsp_data->count, w, dsp_data->discretFreq, power0);
            p[0] = 0;
            q[0] = dsp_data->data_0[0];
            double mean = p[0], power = 0;
            periodCount = dsp_data->discretFreq / w / 2;//
            for (iData0 = 1; iData0 < dsp_data->count ; iData0++)
            {
                //e = dsp_data->data_0[iData0 - 1];
                //e = (dsp_data->data_0[(iData0 - 1) * l + o] + dsp_data->data_0[(iData0) * l + o])/2.;// / 1e16;
                //e = (sinus[iData0] + sinus[iData0 - 1]) / 2. / 999999999999.;
                e = sinus[iData0];
                //printf(" %g", e);
                k1 = 2.*(double)M_PI*h * (e - w * p[iData0 - 1] / p_q - w * w * q[iData0]);
                k2 = 2.*(double)M_PI*h * (e - w * (p[iData0 - 1] + k1 / 2.) / p_q - w * w * q[iData0 - 1]);
                k3 = 2.*(double)M_PI*h * (e - w * (p[iData0 - 1] + k2 / 2.) / p_q - w * w * q[iData0 - 1]);
                k4 = 2.*(double)M_PI*h * (e - w * (p[iData0 - 1] + k3) / p_q - w * w * q[iData0 - 1]);
                p[iData0] = p[iData0 - 1] + (k1 + 2. * (k2 + k3) + k4) / 6.;
                mean += p[iData0];
                k1 = 2.*(double)M_PI*h * p[iData0 - 1];
                k2 = 2.*(double)M_PI*h * (p[iData0 - 1] + k1/2.);
                k3 = 2.*(double)M_PI*h * (p[iData0 - 1] + k2/2.);
                k4 = 2.*(double)M_PI*h * (p[iData0 - 1] + k3);
                q[iData0] = q[iData0 - 1] + (k1 + 2. * (k2 + k3) + k4) / 6.;
            }
            mean /= (double)dsp_data->count;
            for (iData0 = 0 ; iData0 < dsp_data->count ; iData0++)
            {
                double sq = p[iData0] - mean;
                power += sq * sq;
            }
            //printf("freq %f Гц, mean %g, powerKoeff %e, h=%g, preioCount=%i\n", w, mean, power0/power, h, periodCount);
            //for (i = 0; i < dsp_data->count ; i++)
            //{
            //    p[i] *= power0 / power;
            //}
            double powerKoeff = power0 / power;
            printf("***%g", powerKoeff);

            p[0] = 0;
            q[0] = 0;
            
            free(sinus);
            for (w = 20. ; w < 100. ; w += 1.)
            {
                double *sinus = sinus_gen(0, dsp_data->count, 50., dsp_data->discretFreq, 0);//, power0);
                mean = 0;
                for (iData0 = 1; iData0 < dsp_data->count ; iData0++)
                {
                    e = sinus[iData0 - 1];// * powerKoeff;
                    //e = (dsp_data->data_0[(iData0 - 1) * l + o] + dsp_data->data_0[(iData0) * l + o])/2.;// / 1e16;
                    //e = (sinus[iData0] + sinus[iData0 - 1]) / 2. / 999999999999.;
                    //printf(" %g", e);
                    k1 = 2.*(double)M_PI*h * (e - w * p[iData0 - 1] / p_q - w * w * q[iData0]);
                    k2 = 2.*(double)M_PI*h * (e - w * (p[iData0 - 1] + k1 / 2.) / p_q - w * w * q[iData0 - 1]);
                    k3 = 2.*(double)M_PI*h * (e - w * (p[iData0 - 1] + k2 / 2.) / p_q - w * w * q[iData0 - 1]);
                    k4 = 2.*(double)M_PI*h * (e - w * (p[iData0 - 1] + k3) / p_q - w * w * q[iData0 - 1]);
                    p[iData0] = p[iData0 - 1] + (k1 + 2. * (k2 + k3) + k4) / 6.;
                    mean += p[iData0];
                    k1 = 2.*(double)M_PI*h * p[iData0 - 1];
                    k2 = 2.*(double)M_PI*h * (p[iData0 - 1] + k1/2.);
                    k3 = 2.*(double)M_PI*h * (p[iData0 - 1] + k2/2.);
                    k4 = 2.*(double)M_PI*h * (p[iData0 - 1] + k3);
                    q[iData0] = q[iData0 - 1] + (k1 + 2. * (k2 + k3) + k4) / 6.;
                }
                free(sinus);
                mean /= (double)dsp_data->count;
                power = 0;
                for (iData0 = 0 ; iData0 < dsp_data->count ; iData0++)
                {
                    double sq = (p[iData0] - mean);
                    //printf("        %f\n", sq);
                    power += sq * sq;// * powerKoeff;
                }
                printf("freq %f (%f) Гц -- power %e, mean %g\n", w, w * 2. * M_PI, power, mean);
            }
            //for (iData0 = 0 ; iData0 < dsp_data->count ; iData0++)
            //{
            //    p[i] *= powerKoeff;
            //}
            //printf("freq %f Гц, mean %g, powerKoeff %e, h=%g, preioCount=%i\n", w * 2. * M_PI, mean, power, h, periodCount);
            //printf("freq %f (%f) Гц, mean %g, powerKoeff %e, h=%g, preioCount=%i\n", w, w * 2. * M_PI, mean, power, h, periodCount);
        }
    }*/
    //}} test

    for (o = 0 ; o < dsp_data->processingChannels ; o++)
    {
        double mean = 0;
        double powerWhole = 0;
        for (i = 0 ; i < dsp_data->count ; i++)
        {
            mean += dsp_data->data_0[i];
        }
        mean /= (double)dsp_data->count;
        double meanWhole = mean;
        for (i = 0 ; i < dsp_data->count ; i++)
        {
            double sq = (dsp_data->data_0[i] - mean);
            powerWhole += (sq * sq);
        }
        for (iFreq = 0 ; iFreq < dsp_data->freqCount ; iFreq++)
        {
            double *oSpectr = dsp_data->spectrogram + o * (dsp_data->freqCount * dsp_data->count) + iFreq * dsp_data->count;
            w = dsp_data->frequences[iFreq];
            double *sinus = sinus_gen(0, dsp_data->count, w, dsp_data->discretFreq, 1000);
            periodCount = dsp_data->discretFreq / w / 2;
            p[0] = 0;
            q[0] = sinus[0];
            mean = 0;
            double dvapi = 2.*(double)M_PI;
            //dvapi = 1;//
            for (iData0 = 1; iData0 < dsp_data->count ; iData0++)
            {
                //e = dsp_data->data_0[iData0 - 1];
                e = sinus[iData0 - 1];
                //e = (dsp_data->data_0[(iData0 - 1) * l + o] + dsp_data->data_0[(iData0) * l + o])/2.;// / 1e16;
                //printf(" %g", e);
                k1 = dvapi*h * (e - w * p[iData0 - 1] / p_q - w * w * q[iData0]);
                k2 = dvapi*h * (e - w * (p[iData0 - 1] + k1 / 2.) / p_q - w * w * q[iData0 - 1]);
                k3 = dvapi*h * (e - w * (p[iData0 - 1] + k2 / 2.) / p_q - w * w * q[iData0 - 1]);
                k4 = dvapi*h * (e - w * (p[iData0 - 1] + k3) / p_q - w * w * q[iData0 - 1]);
                p[iData0] = p[iData0 - 1] + (k1 + 2. * (k2 + k3) + k4) / 6.;
                mean += p[iData0];
                k1 = dvapi*h * p[iData0 - 1];
                k2 = dvapi*h * (p[iData0 - 1] + k1/2.);
                k3 = dvapi*h * (p[iData0 - 1] + k2/2.);
                k4 = dvapi*h * (p[iData0 - 1] + k3);
                q[iData0] = q[iData0 - 1] + (k1 + 2. * (k2 + k3) + k4) / 6.;
            }
            mean /= (double)dsp_data->count;
            double power0 = 0;
            for (i = 0 ; i < dsp_data->count ; i++)
            {
                double sq = p[iData0] - mean;
                power0 += (sq * sq);
            }
            double powerKoeff = power0 / powerWhole;
            printf("%f Hz powerKoeff: %e\t", w, powerKoeff);
            free(sinus);
            p[0] = 0;
            q[0] = dsp_data->data_0[0];
            mean = 0;
            for (iData0 = 1; iData0 < dsp_data->count ; iData0++)
            {
                //e = (dsp_data->data_0[iData0 - 1] - meanWhole) * powerKoeff;
                e = (dsp_data->data_0[iData0 - 1] - meanWhole);
                //e = (dsp_data->data_0[iData0] + dsp_data->data_0[iData0 - 1])/2. - meanWhole;
                k1 = dvapi*h * (e - w * p[iData0 - 1] / p_q - w * w * q[iData0]);
                k2 = dvapi*h * (e - w * (p[iData0 - 1] + k1 / 2.) / p_q - w * w * q[iData0 - 1]);
                k3 = dvapi*h * (e - w * (p[iData0 - 1] + k2 / 2.) / p_q - w * w * q[iData0 - 1]);
                k4 = dvapi*h * (e - w * (p[iData0 - 1] + k3) / p_q - w * w * q[iData0 - 1]);
                p[iData0] = p[iData0 - 1] + (k1 + 2. * (k2 + k3) + k4) / 6.;
                mean += p[iData0];
                k1 = dvapi*h * p[iData0 - 1];
                k2 = dvapi*h * (p[iData0 - 1] + k1/2.);
                k3 = dvapi*h * (p[iData0 - 1] + k2/2.);
                k4 = dvapi*h * (p[iData0 - 1] + k3);
                q[iData0] = q[iData0 - 1] + (k1 + 2. * (k2 + k3) + k4) / 6.;
            }
            mean /= (double)dsp_data->count;
            double power1 = 0;
            for (i = 0 ; i < dsp_data->count ; i++)
            {
                double sq = p[iData0] - mean;
                power1 += (sq * sq);
            }
            //power1 /= (powerKoeff);
            printf("--------> выходная мощность на резонаторе: %g\t", power1);
            //printf("\n");continue;


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
                        double sq = (p[i] - mean) / (double)(periodCount);
                        cand += (sq * sq);
                    }
                    prevA = a;
                }
                else
                {
                    if (a != prevA)
                    {
                        double sq = (p[prevA] - mean) / (double)(periodCount);
                        cand -= sq * sq;
                        sq = (p[b - 1] - mean) / (double)(periodCount);
                        cand += sq * sq;
                        prevA = a;
                    }
                }
                //cand = p[iData0] / (w * w);// / w / w / w;//
                if (w > 49 && w < 51)
                    ;//printf("--- %g\n", cand);
                if (w > 53 && w < 54)
                    ;//printf("=== %g\n", cand);
                if (cand > maxPowerForFreq)
                    maxPowerForFreq = cand;
                if (w > 499 && w < 520)
                    ;//printf("+++ %g\n", cand);
                oSpectr[iData0] = cand;
            }
            printf("Пишу спектрограмму по частоте %f Гц. пиковая плотность мощности: %g\n", w, maxPowerForFreq);//
        }
    }

    printf("Предобработка завершена.\n");
    return 0;
}
