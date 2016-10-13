#include <iostream>
#include "hill_climbing.h"

using namespace std;

double function (double *vals) {
	return 3. * vals[0]*vals[0] - 5. * vals[1] * vals[2];
}

double comp (double a, double b) {
	return a < b ? true : false;
}

int start (int n, ...) {
	arg
}

int main () {
	double start[3];
	start[1] = 200;
	start[2] = 211;
	start[3] = -222;
	double *result = hillClimbing (3, -1, 0.2, start, function, comp);
	result = hillClimbing (3, -1, 0.2, start, function2, comp);
	for (int i = 0; i < 3; i++)
		cout << result[i] << ' ';
	return 0;
}
