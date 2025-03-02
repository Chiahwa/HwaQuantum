#include "ConvectionSolver.h"

inline QCircuit ConvectionSolver::oneTimeStepCircuit()
{
	if (n_qubits < 1) throw exception("less than one qubit");
	QCircuit circuit;
	circuit << RZ(qubits[n_qubits - 1], -c * dt * 2 * PI / L * (1LL << (n_qubits - 1)));
	for (int j = 0;j < n_qubits - 1;++j) {
		circuit << RZ(qubits[j], c * dt * 2 * PI / L * (1 << (j)));
	}
	return circuit;
}

void ConvectionSolver::InitQVM(int n_qubits, double(*f)(double))
{
	size_t Nx = 1LL << n_qubits;
	double dx = L / Nx;
	vector<double> initState(Nx);
	for (int k = 0;k < Nx;++k) {
		initState[k] = f(k * dx);
	}
	InitQVM(n_qubits, initState);
}

void ConvectionSolver::InitQVM(int n_qubits, vector<double> initState)
{
	// TODO: delete old qvm
	this->qvm = new DensityMatrixSimulator();
	this->prog = new QProg();
	qvm->init();
	this->n_qubits = n_qubits;
	this->qubits = qvm->qAllocMany(n_qubits);

	size_t Nx = 1LL << n_qubits;
	double sum = 0.0;
	for (int k = 0;k < Nx;++k) {
		sum += initState[k] * initState[k];
	}
	this->norm = sqrt(sum);
	for (int k = 0;k < Nx;++k) {
		initState[k] /= this->norm;
	}
	*(this->prog) << amplitude_encode(qubits, initState);
}

void ConvectionSolver::Run(int n_timestep, const NOISE_MODEL &model, double p)
{
	*prog << QFT(qubits);
	for (int k = 0;k < n_timestep;++k) {
		*prog << oneTimeStepCircuit();
	}
	*prog << QFT(qubits).dagger();
	qvm->set_noise_model(model, GateType::RZ_GATE, p);
	this->probabilities = qvm->get_probabilities(*prog);
	//this->densityMatrix = qvm->get_density_matrix(prog); // TODO: densityMatrix can be removed
}

std::vector<std::pair<double, double>> ConvectionSolver::GetResult()
{
	size_t Nx = 1LL << n_qubits;
	std::vector<std::pair<double, double>> result(Nx);
	for (int k = 0;k < Nx;++k) {
		result[k].first = k * L / Nx;
		result[k].second = sqrt(probabilities[k]) * norm;
	}
	return result;
}
