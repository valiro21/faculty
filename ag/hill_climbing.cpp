#include "hill_climbing.h"
#include <iostream>
#include <queue>

using namespace std;

#define epsilon 0.00000000000001
#define MAX_HISTORY_SIZE 12
double min_step = 0.000000001;
double gamma_step = 0.02;

double mabs (double a) {
	return a < 0 ? -a : a;
}

double* hillClimbing (uint e, double direction, double step, double *start, double (*eval)(double*), double (*comp)(double, double)) {
	double *gradient = new double[e];
	double *newP = new double[e];
	for (int i = 0; i < e; i++) newP[i] = start[i];

	double before;
	do {
		before = eval (newP);

		for (int i = 0; i < e; i++) {
			newP[i] = newP[i] + step;
			double derivative = (eval(newP) - before) / step;

			gradient[i] = derivative;

			newP[i] = newP[i] - step;
		}

		for (int i = 0; i < e; i++) {
			newP[i] = direction * gradient[i] * gamma_step;
		}

		double newEval = eval (newP);
				
		cout << newEval << '\n';
		
		if (mabs (newEval - before) < epsilon) step /= 2;
	} while (step > min_step);
	return newP;
}
