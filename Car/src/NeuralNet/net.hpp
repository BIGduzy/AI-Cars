#include <vector>
#include "neuron.hpp"

#ifndef NET_H
#define NET_H

typedef std::vector<Neuron> Layer;

class Net {
public:
	Net(const std::vector<unsigned> &topology);
	void getResults(std::vector<double>& resultVals) const;
	void feedForward(const std::vector<double>& inputVals);
	void backProp(const std::vector<double>& targetVals);

private:
	std::vector<Layer> m_layers; // m_layers[layerNum][neuronNum]
	// double m_error;
	//double m_recentAverageError;
	//double m_recentAverageSmoothingFactor;
};

#endif // !NET_H
