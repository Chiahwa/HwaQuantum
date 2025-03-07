#pragma once

double c = 1.0;
double L = 2 * PI;

double dt = 0.15;
int nsteps = 30;
int nqubits = 9;
size_t NX = 1LL << nqubits;

double lambda = 2.0;
double offset = 2.0;
double f(double x) {
    return sin(lambda * x)+offset;
}