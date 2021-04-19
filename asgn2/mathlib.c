#include "mathlib.h"

#include <math.h>
#include <stdio.h>

#define EPSILON 1e-10

static double abs(double x) {
    if (x < 0) {
        return (x * -1);
    } else {
        return x;
    }
}
//Darrell Long's square root function from Piazza
double squareroot(double x) {
    double new = 1.0;
    double old = 0.0;
    while (abs(new - old) > EPSILON) {
        old = new;
        new = 0.5 * (new + (x / new));
    }
    return new;
}
//Darrell Long's Exp function from Piazza
static double Exp(double x) {
    double term = 1;
    double sum = 1;
    for (int k = 1; abs(term) > EPSILON; k++) {
        term *= x / k;
        sum += term;
    }
    return sum;
}

double arcSin(double x) {
    if (x <= -0.75) {
        return arcCos(squareroot(1 - (x * x))) * -1;
    } else if (x >= 0.75) {
        return arcCos(squareroot(1 - (x * x)));
    } else {
        double sum = x;
        double term = x;
        for (double k = 1; abs(term) > EPSILON; k += 2) {
            term = term * (x * x) * ((k * k) / ((k + 1) * (k + 2)));
            sum += term;
        }
        return sum;
    }
}
double arcCos(double x) {
    if (x <= -0.75) {
        return arcSin(squareroot(1 - (x * x))) * -1 + M_PI;
    } else if (x >= 0.75) {
        return arcSin(squareroot(1 - (x * x)));
    } else {
        return ((M_PI / 2) - (arcSin(x)));
    }
}

double arcTan(double x) {
    return arcCos(1 / squareroot((x * x) + 1));
}
double Log(double x) {
    double guess = 1.0;
    while (abs(Exp(guess) - x) > EPSILON) {
        guess = guess + ((x - Exp(guess)) / Exp(guess));
    }
    return guess;
}
