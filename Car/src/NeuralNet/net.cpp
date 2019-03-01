#include "net.hpp"
#include <iostream>
#include "neuron.hpp"
#include <assert.h>


Net::Net(const std::vector<unsigned> &topology) {
	unsigned numLayers = topology.size();

	for (unsigned i = 0; i < numLayers; ++i) {
		m_layers.push_back(Layer());
		unsigned numOutputs = i == topology.size() - 1 ? 0 : topology[i + 1];

		// Add the neurons to the layer, <= because we need the bias neuron
		for (unsigned j = 0; j <= topology[i]; ++j) {
			m_layers.back().push_back(Neuron(numOutputs, j));
			std::cout << "A new Neuron created" << std::endl;
		}
		std::cout << std::endl;

		// Force the bias node's output value to 1.0
		m_layers.back().back().setOutputVal(1.0);
	}

}

void Net::getResults(std::vector<double>& resultVals) const {

	/*for (unsigned i = 0; i < m_layers.size(); i++) {
		std::cout << "Layer: " << i << std::endl;
		for (unsigned j = 0; j < m_layers[i].size(); j++) {
			Neuron neuron = m_layers[i][j];
			std::cout << "\tNeuron: " << j << std::endl;
			neuron.print();
			std::cout << std::endl;
		}
	}*/

	resultVals.clear();

	for (unsigned i = 0; i < m_layers.back().size() - 1; ++i) { // Exclude bias
		resultVals.push_back(m_layers.back()[i].getOutputVal());
	}
}

void Net::feedForward(const std::vector<double>& inputVals) {
	// First layer equals input layer
	assert(inputVals.size() == m_layers[0].size() - 1); // Exclude bias Neuron

	for (unsigned i = 0; i < inputVals.size(); ++i) {
		m_layers[0][i].setOutputVal(inputVals[i]);
	}

	// Forward propagation
	for (unsigned i = 1; i < m_layers.size(); ++i) { // Skip the input layer
		Layer& prevLayer = m_layers[i - 1];

		for (unsigned j = 0; j < m_layers[i].size() - 1; ++j) { // Exlude bias
			m_layers[i][j].feedForward(prevLayer);
		}
	}
}

void Net::backProp(const std::vector<double>& targetVals) {
	/* Calculate overall net error (RMS of output neuron errors) */

	Layer& outputLayer = m_layers.back();
	m_error = 0.0;

	for (unsigned i = 0; i < outputLayer.size() - 1; ++i) { // Exclude bias
		double delta = targetVals[i] - outputLayer[i].getOutputVal();

		m_error += delta * delta;
	}

	m_error /= outputLayer.size() - 1; // get avarage error squared
	m_error = sqrt(m_error); // RMS


	/* Implement a recent avarage measurement */

	m_recentAverageError = (m_recentAverageError * m_recentAverageSmoothingFactor + m_error) / (m_recentAverageSmoothingFactor + 1.0);


	/* Calculate output layer gradients */

	for (unsigned i = 0; i < outputLayer.size() - 1; ++i) { // Exclude bias
		outputLayer[i].calcOutputGradients(targetVals[i]);
	}


	/* Calculate gradients on hidden layers */

	// For every hidden layer from back to front
	for (unsigned i = m_layers.size() - 2; i > 0; --i) {
		Layer& currentLayer = m_layers[i];
		Layer& nextLayer = m_layers[i + 1];

		for (unsigned j = 0; j < currentLayer.size(); ++j) {
			currentLayer[j].calcHiddenGradients(nextLayer);
		}
	}


	// For all layers from outputs to first hidden layer
	// update connection weights

	for (unsigned i = m_layers.size() - 1; i > 0; --i) {
		Layer& layer = m_layers[i];
		Layer& prevLayer = m_layers[i - 1];

		for (unsigned j = 0; j < layer.size() - 1; ++j) { // Exclude bias
			layer[j].updateInputWeights(prevLayer);
		}
	}
}