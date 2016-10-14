#define _USE_MATH_DEFINES
#include <iostream>
#include "hill_climbing.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <utility>
#include <algorithm>
#include <string.h>
#include <cstring>

#define EPOCH 1000

using namespace std;

#define LOWER -100
#define UPPER 100
#define N 2
double easom(double *vars) {
 	return -cos(vars[0])*cos(vars[1])*exp(-1 * pow((vars[0] - M_PI), 2.0) - pow((vars[1] - M_PI), 2.0));
}

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

double* generate (int n, int lower, int upper) {
	double *v = new double[n];
	for (int i = 0; i < n; i++)
		v[i] = fRand (lower, upper) ;
	return v;
}

void print (int n, double *v) {
	for (int i = 0; i < n; i++)
		cout << v[i] << ' ';
}

void print_time (clock_t t) {
	printf ("%.8lf seconds", (double)t / (double)CLOCKS_PER_SEC);
}

bool comp (double a, double b) {
	return a < b ? true : false;
}

int main () {
	srand (time (NULL));
	double *result, *start, *bestResult = new double[N];
	vector<clock_t> tm;
	vector<double> ve;
	clock_t total_t;
	double total_e = 0;
	double min;
	bool minSet = false;

	for (int i = 0; i < EPOCH; i++) {
		start = generate(N, LOWER, UPPER);
		cout << i << "  ";
		print (N, start);
		clock_t c = clock ();
		result = hillClimbing (N, -1, 0.5, 0.2, start, easom, LOWER, UPPER);
		clock_t t = clock () - c;
		tm.push_back (t);
		total_t += t;
	
		cout << " -> ";
		print (N, result);
		double e = easom (result);
		ve.push_back (e);
		total_e += e;
		cout << "  =  " << e << '\n';
		if (!minSet || e < min) {
			minSet = true;
			min = e;
			memcpy (bestResult, result, sizeof (result) * N);
		}
		delete[] result;
		delete[] start;
	}
	
	sort (tm.begin (), tm.end (), comp);
	sort (ve.begin (), ve.end (), comp);
	cout << "\nBest time: "; print_time (tm[0]); cout << "\n";
	cout << "Average time: "; print_time (total_t / EPOCH); cout << "\n";
	cout << "Worst time: "; print_time (tm.back ()); cout << "\n\n";

	cout << "\nBest solution: "; printf ("%.8lf\n",ve[0]);
	cout << "Average solution: "; printf ("%.8lf\n", total_e / (double)EPOCH);
	cout << "Worst solution: "; printf ("%.8lf\n\n", ve.back ());

	print (N, bestResult);
	cout << "\n";

	return 0;
}
