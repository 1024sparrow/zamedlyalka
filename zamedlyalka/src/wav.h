#include "dsp.h"

int readWav(const char *p_filepath, struct DSP_DATA *dsp_data, int p_useShifting);
int writeWav(const char *filepath, const struct DSP_DATA *dsp_data);
