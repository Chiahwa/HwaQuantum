#pragma once
#include "QPanda.h"
#include <vector>
USING_QPANDA

class ConvectionSolver
{
private:
	double norm;
	int n_qubits;
	double dt;

	QVec qubits;
	QProg *prog;
	DensityMatrixSimulator *qvm;
	cmatrix_t densityMatrix;
	prob_vec probabilities;

	QCircuit oneTimeStepCircuit();
	//DensityMatrixSimulator qvm;
public:
	ConvectionSolver(double c = 1.0, double L = 2 * PI) : c(c), L(L) {};
	~ConvectionSolver() {
		qvm->finalize();
		delete qvm;
	}
	double c;
	
	double L;
	
	double (*InitCondition)(double);
	void InitQVM(int n_qubits, double dt, double (*f)(double));
	void InitQVM(int n_qubits, double dt, vector<double> initState);

	void Run(int n_timestep, const NOISE_MODEL& model, double p);
	std::vector<double> GetResultU() const;
	std::vector<double> GetX() const;
};

