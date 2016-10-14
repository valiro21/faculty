#include "hill_climbing.h"
#include <iostream>
#include <queue>

using namespace std;


#define DEBUG 0
#define epsilon 0.00000000001
double min_step = 0.0000000001;

double mabs (double a) {
	return a < 0 ? -a : a;
}

void trim (double lower, double upper, double &val) {
	if (val < lower) val = lower;
	if (val > upper) val = upper;
}

double* hillClimbing (uint e, double direction, double step, double gamma_step, double *start, double (*eval)(double*), double lowerLimit, double upperLimit) {
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
			newP[i] += direction * gradient[i] * gamma_step;
			trim (lowerLimit, upperLimit, newP[i]);
		}

		double newEval = eval (newP);
		
		if (DEBUG) {
			for (int i = 0; i < e; i++) cout << newP[i] << ' ';
			cout << " -> ";
			cout << newEval << '\n';
		}
		
		if (mabs (newEval - before) < epsilon) step /= 2;
	} while (step > min_step);
	return newP;
}
