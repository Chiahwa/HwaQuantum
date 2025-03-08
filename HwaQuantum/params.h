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

string noise_type_str = "BITFLIP";
int noise_type = 0;
// 0: BITFLIP
// 1: DEPOLARIZING
// 2: DEPHASING
double noise_p = 0.03;