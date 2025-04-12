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
// 0: No noise
// 1: BITFLIP
// 2: DEPOLARIZING
// 3: DEPHASING
// 4: DAMPING
double noise_p = 0.03;

int init_cond;
// 0: 2 wavenumers
// 1: single wvnumbers


inline double f(double x) {
	if (init_cond == 0)
		return sin(lambda * x) + sin(2 * lambda * x) + offset;
	else
		return sin(lambda * x) + offset;
	// return 1;
	// return -x * (x - L);
}

inline double g(double x) {
	return 1;
}