#pragma once

// Default parameters
double c = 1.0;
double L = 2 * PI;

double dt = 0.15;
int nsteps = 30;
int nqubits;
size_t NX = 1LL << nqubits;

double lambda = 2.0;
double offset = 2.5;


string noise_type_str = "BITFLIP";
int noise_type = 0;
// 0: BITFLIP
// 1: DEPOLARIZING
// 2: DEPHASING
double noise_p = 0.03;


inline double f(double x) {
	return sin(lambda * x) + sin(2 * lambda * x) + offset;
	// return 1;
	// return -x * (x - L);
}

inline double g(double x) {
	return 1;
}