#ifndef DSP_H
#define DSP_H

#include <sys/types.h>

struct DSP_RESONATOR_DATA {
    int stub; // stub
};

struct DSP_DATA {
    size_t count;
    int processingChannels;
    int discretFreq; //     частота дискретизации
    double *data_0; // исходный сигнал
    double power; // мощность считается как сумма квадратов отсчётов. Считается по обоим каналам.
    struct DSP_RESONATOR_DATA *resonators;

    double *data_1; // тот сигнал, который будем записывать в выходной WAV-файл

    size_t freqCount;
    double *frequences;
    double *spectrogram;
};

/* Parameters:
 * dsp_data
 * p_startFreq
 * p_endFreq
 * p_freqStepKoeff - шаг по частоте примоделировании резонаторов вычисляется по формуле частота * p_freqStepKoeff
 * p_q - добротность моделируемых контуров. У всех контуров (для всех частот) она одна и та же. Подбирается эмпирическим путём.
 */
int process_signal(struct DSP_DATA *dsp_data, double p_startFreq, double p_endFreq, double p_freqStepKoeff, double p_q);
int dsp_test(struct DSP_DATA *dsp_data);

#endif // DSP_H
