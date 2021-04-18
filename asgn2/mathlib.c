#include <stdio.h>
#include "mathlib.h"
#include <math.h>

#define EPSILON 1e-10

static double abs(double x) {
	if( x < 0) {
		return -x;
	}
	return x;
}
//Darrell Long's square root function from Piazza
static double sqrt(double x) {
	double new = 1.0;
	double old = 0.0;
	while(abs(new-old) > EPSILON) {
		old = new;
		new = 0.5 * (new + (x/new));
	}
	return new;
}
//Darrell Long's Exp function from Piazza
static double Exp(double x) {
	double term = 1;
	double sum = 1;
	for(int k = 1; abs(term) > EPSILON; k++) {
		term *= x/k;
		sum += term;
	}
	return sum;
}

double arcSin(double x) {
	double sum = x;
	double term = x;
	for(int k = 1; abs(term) > EPSILON; k += 2) {
		term = term * (x * x) * ((k * k)/((k+1)*(k+2)));
		sum += term;
	}
	return sum;
}
double arcCos(double x) {
	return ((M_PI/2) - (arcSin(x)));
}

double arcTan(double x) {
	return arcSin(x/sqrt((x*x)+1));
}
double Log(double x) {
	double guess = 1.0;
	while(abs(Exp(guess) - x) > EPSILON) {
		guess = guess + ((x-Exp(guess))/Exp(guess));
	}
	return guess;
}
