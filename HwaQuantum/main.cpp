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
		auto resultU = solver.GetResultU();
		auto resultX = solver.GetX();

		char filename_u[100] = "result/u.txt";
		std::ofstream fout_u(filename_u, ios::out);
		char filename_x[100] = "result/x.txt";
		std::ofstream fout_x(filename_x, ios::out);
		
		for (size_t i = 0; i < resultU.size(); ++i) {
			fout_u << resultU[i] << std::endl;
			fout_x << resultX[i] << std::endl;
		}
		fout_u.close();
		fout_x.close();
	}
	return 0;
}