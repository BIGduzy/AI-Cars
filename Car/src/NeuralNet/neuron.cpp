#include "neuron.hpp"

double Neuron::eta = 0.15;
double Neuron::alpha = 0.5;

Neuron::Neuron(unsigned numOutputs, unsigned index) {
	for (unsigned i = 0; i < numOutputs; ++i) {
		m_outputWeights.push_back(Connection());
		m_outputWeights.back().weight = randomWeight();
	}

	m_index = index;
}

void Neuron::feedForward(const Layer& prevLayer) {
	double sum = 0.0;

	// sum the previous layer's outputs (incuding bias)
	for (unsigned i = 0; i < prevLayer.size(); ++i) {
		sum += prevLayer[i].m_outputval * prevLayer[i].m_outputWeights[m_index].weight;
	}
	m_outputval = Neuron::transferFunction(sum);
}

void Neuron::calcOutputGradients(double targetVal) {
	double delta = targetVal - m_outputval;
	m_gradient = delta * Neuron::transferFunctionDerivtive(m_outputval);
}

void Neuron::calcHiddenGradients(const Layer& nextLayer) {
	double dow = sumDOW(nextLayer);
	m_gradient = dow * Neuron::transferFunctionDerivtive(m_outputval);
}

void Neuron::updateInputWeights(Layer& prevLayer) {
	// The weights to be updated are in the Connection container
	// in the neurons in the preceding layer

	for (unsigned i = 0; i < prevLayer.size(); ++i) {
		Neuron& neuron = prevLayer[i];
		double oldDeltaWeight = neuron.m_outputWeights[m_index].deltaWeight;

		double newDeltaWeight =
			// Individual unput, magnified by the gradient and train rate
			eta *
			neuron.m_outputval *
			m_gradient +
			// Also add momentum = a fraction of the previous delta weight
			alpha *
			oldDeltaWeight;

		neuron.m_outputWeights[m_index].deltaWeight = newDeltaWeight;
		neuron.m_outputWeights[m_index].weight += newDeltaWeight;
	}

}

double Neuron::transferFunction(double x) {
	// tanh - output range [-1.0..1.0]
	return tanh(x);
}

double Neuron::transferFunctionDerivtive(double x) {
	// tanh derivative 
	return 1.0 - x * x;
}

double Neuron::sumDOW(const Layer& nextLayer) const {
	double sum = 0.0;

	// Sum the contrubutions of the errors at the nodes given
	for (unsigned i = 0; i < nextLayer.size() - 1; ++i) { // Exclude bias
		sum += m_outputWeights[i].weight * nextLayer[i].m_gradient;
	}

	return sum;
}
