#pragma once
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>
using namespace std;
namespace NN 
{

	struct Connection
	{
		double weight;
		double deltaWeight;
	};

	class Neuron;

	typedef vector<Neuron> Layer;

	// ****************** class Neuron ******************

	class Neuron
	{
	public:
		Neuron(unsigned numOutputs, unsigned myIndex);
		void setOutputVal(double val) { m_outputVal = val; }
		double getOutputVal(void) const { return m_outputVal; }
		void feedForward(const Layer &prevLayer);
		void calcOutputGradients(double targetVals);
		void calcHiddenGradients(const Layer &nextLayer);

	private:
		static double eta; // [0.0...1.0] overall net training rate
		static double alpha; // [0.0...n] multiplier of last weight change [momentum]
		static double transferFunction(double x);
		static double transferFunctionDerivative(double x);
		// randomWeight: 0 - 1
		static double randomWeight(void) { return rand() / double(RAND_MAX); }
		double sumDOW(const Layer &nextLayer) const;
		double m_outputVal;
		vector<Connection> m_outputWeights;
		unsigned m_myIndex;
		double m_gradient;
	};

	// ****************** class Net ******************
	class Net
	{
	public:
		Net(const vector<unsigned> &topology);
		void feedForward(const vector<double> &inputVals);
		void getResults(vector<double> &resultVals) const;

	private:
		vector<Layer> m_layers; //m_layers[layerNum][neuronNum]
		double m_error;
	};


}