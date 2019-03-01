#include <vector>
#include <iostream>


#ifndef NEURON_H
#define NEURON_H

struct Connection {
	double weight;
	double deltaWeight;
};

class Neuron;
typedef std::vector<Neuron> Layer;

class Neuron {
public:
	Neuron(unsigned numOutputs, unsigned index);
	void setOutputVal(const double val) { m_outputval = val; }
	double getOutputVal() const { return m_outputval; }
	void feedForward(const Layer& prevLayer);
	void calcOutputGradients(double targetVal);
	void calcHiddenGradients(const Layer& nextLayer);
	void updateInputWeights(Layer& prevLayer);
	void print() {
		std::cout << "\t\tm_outputval: " << m_outputval << std::endl;
		std::cout << "\t\tm_gradient: " << m_gradient << std::endl;
		std::cout << "\t\tm_index: " << m_index << std::endl;
	};
private:
	static double transferFunction(double x);
	static double transferFunctionDerivtive(double x);
	static double randomWeight() { return rand() / double(RAND_MAX); }
	static double eta; // [0.0..1.0] overall net training rate
	static double alpha; // [0.0..1.0] multiplier of last weight change (momentum)
	double sumDOW(const Layer& nextLayer) const;
	double m_outputval;
	double m_gradient;
	unsigned m_index;
	std::vector<Connection> m_outputWeights;
};

#endif // !NEURON_H
