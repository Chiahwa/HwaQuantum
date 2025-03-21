#include "QPanda.h"
#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <fstream>
#include <sstream>
#include "ConvectionSolver.h"
#include "params.h"


int main()
{
	std::cout << "Please input c:" << std::endl;
	std::cin >> c;
	std::cout << "Please input L:" << std::endl;
	std::cin >> L;
	std::cout << "Please input lambda:" << std::endl;
	std::cin >> lambda;
	std::cout << "Please input offset:" << std::endl;
	std::cin >> offset;
	std::cout << "Please input dt:" << std::endl;
	std::cin >> dt;
	std::cout << "Please input nsteps:" << std::endl;
	std::cin >> nsteps;
	std::cout << "Please input nqubits:" << std::endl;
	std::cin >> nqubits;
	NX = 1LL << nqubits;
	std::cout << "Please input noise_type:" << std::endl;
	std::cin >> noise_type_str;
	std::cout << "Please input noise_p:" << std::endl;
	std::cin >> noise_p;



    ConvectionSolver solver(c, L);
	
	char filename_u[100] = "result/u.txt";
	std::ofstream fout_u(filename_u, ios::out);
	char filename_x[100] = "result/x.txt";
	std::ofstream fout_x(filename_x, ios::out);
	char filename_spectrum[100] = "result/spectrum.txt";
	std::ofstream fout_spectrum(filename_spectrum, ios::out);
	

	for (size_t i = 0; i < NX; ++i) {
		fout_x << i * L / NX << " ";
	}

	for (int k = 0;k <= nsteps;++k) {
		double t = k * dt;
		solver.InitQVM(nqubits, dt, f);
		NOISE_MODEL noise_model;
		if (noise_type_str == "BITFLIP") {
			noise_model = NOISE_MODEL::BITFLIP_KRAUS_OPERATOR;
			noise_type = 0;
		}
		else if (noise_type_str == "DEPOLARIZING") {
			noise_model = NOISE_MODEL::DEPOLARIZING_KRAUS_OPERATOR;
			noise_type = 1;
		}
		else if (noise_type_str == "DEPHASING") {
			noise_model = NOISE_MODEL::DEPHASING_KRAUS_OPERATOR;
			noise_type = 2;
		}
		else if (noise_type_str == "AMPLITUDE_DAMPING") {
			noise_model = NOISE_MODEL::DAMPING_KRAUS_OPERATOR;
			noise_type = 3;
		}
		else {
			std::cerr << "Unknown noise type" << std::endl;
			exit(1);
		}
		solver.SimulateDensityMatrix(k, noise_model, noise_p);
		auto resultU = solver.GetResultU();
		auto resultUSpectrum = solver.GetResultUSpectrum();
		auto resultX = solver.GetX();

		
		for (size_t i = 0; i < resultU.size(); ++i) {
			fout_u << resultU[i] << " ";
			fout_spectrum << resultUSpectrum[i] << " ";
		}
		fout_u << std::endl;
		fout_spectrum << std::endl;
	}
	fout_u.close();
	fout_x.close();

	char filename_params[100] = "result/params.txt";
	std::ofstream fout_params(filename_params, ios::out);
	fout_params << "c L lambda offset dt nqubits nsteps noise_type noise_p" << std::endl;
	fout_params << c << " " << L << " " << lambda << " " << offset << " " << dt << " " << nqubits << " " << nsteps << " " << noise_type << " " << noise_p << std::endl;
	fout_params.close();
	return 0;
}