#include <sys/types.h>

/*
 * Быстрое локальное усреднение (прямоугольным окном).
 * В качествеи p_resltArray можно указать тот же указатель, что и в p_array.
 */
int averageArray(double *p_array, size_t p_arrayCount, size_t p_averageWidth, double *p_resultArray);
