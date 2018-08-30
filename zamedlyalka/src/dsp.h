#ifndef DSP_H
#define DSP_H

#include <sys/types.h>

struct DSP_RESONATOR_DATA {
    int stub; // stub
};

struct DSP_DATA {
    size_t count;
    int processingChannels;
    double *data_0;
    double power; // мощность считается как сумма квадратов отсчётов. Считается по обоим каналам.
    struct DSP_RESONATOR_DATA *resonators;

    int freqCountPerSegment; // сколько частот в интервале от 20Гц до 40Гц (столько же частот в интервале от 1кГц до 2кГц)
    double q; // добротность колебательных контуров

    double spectrogram;
};

int process_signal(struct DSP_DATA *dsp_data);

#endif // DSP_H
