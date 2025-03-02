#include "QPanda.h"
#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <fstream>
#include <sstream>
#include "ConvectionSolver.h"

int nsteps = 3;
int nqubits = 9;

double f(double x) {
    return sin(2 * x) + 1.5;
}

int main()
{
    ConvectionSolver solver(1.0, 0.1, 2 * PI);
	
	

	for (int k = 0;k <= nsteps;++k) {
		double t = k * solver.dt;
		solver.InitQVM(nqubits, f);
		solver.Run(k, NOISE_MODEL::BITFLIP_KRAUS_OPERATOR, 0.03);
		auto result = solver.GetResult();

		char filename[100];
		snprintf(filename, 100, "result_%.2lf.txt", t);
		std::ofstream fout(filename, ios::out);
		for (size_t i = 0; i < result.size(); ++i) {
			fout << result[i].first << " " << result[i].second << std::endl;
		}
		fout.close();
	}
	return 0;
}