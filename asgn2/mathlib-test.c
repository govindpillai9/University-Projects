#include "mathlib.h"

#include <math.h>
#include <stdio.h>
#include <unistd.h>

#define OPTIONS "asctl"

static void printheader(int n) {
    if (n == 0) {
        printf("%7s %16s %16s %16s\n", "x", "arcSin", "Library", "Difference");
    } else if (n == 1) {
        printf("%7s %16s %16s %16s\n", "x", "arcCos", "Library", "Difference");
    } else if (n == 2) {
        printf("%7s %16s %16s %16s\n", "x", "arcTan", "Library", "Difference");
    } else if (n == 3) {
        printf("%7s %16s %16s %16s\n", "x", "Log", "Library", "Difference");
    }
    printf("%7s %16s %16s %16s\n", "-", "------", "-------", "----------");
}

int main(int argc, char **argv) {
    int opt = 0;
    int arcsin = 0;
    int arccos = 0;
    int arctan = 0;
    int logCheck = 0;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            arcsin = 1;
            arccos = 1;
            arctan = 1;
            logCheck = 1;
            break;
        case 's': arcsin = 1; break;
        case 'c': arccos = 1; break;
        case 't': arctan = 1; break;
        case 'l': logCheck = 1; break;
        default: printf("invalid input"); return 1;
        }
    }

    if (arcsin == 1) {
        printheader(0);
        for (double i = -1.0; i < 1.0; i += 0.1) {
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", i, arcSin(i), asin(i),
                arcSin(i) - asin(i));
        }
    }
    if (arccos == 1) {
        printheader(1);
        for (double j = -1.0; j < 1.0; j += 0.1) {
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", j, arcCos(j), acos(j),
                arcCos(j) - acos(j));
        }
    }
    if (arctan == 1) {
        printheader(2);
        for (double k = 1.0; k < 10.0; k += 0.1) {
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", k, arcTan(k), atan(k),
                arcTan(k) - atan(k));
        }
    }
    if (logCheck == 1) {
        printheader(3);
        for (double m = 1.0; m < 10.0; m += 0.1) {
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", m, Log(m), log(m), Log(m) - log(m));
        }
    }
}
