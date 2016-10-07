typedef unsigned int uint;

extern double* hillClimbing (uint e, double direction, double step, double *start, double (*eval)(double*), double (*comp)(double, double));
