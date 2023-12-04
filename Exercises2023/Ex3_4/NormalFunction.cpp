#include "FiniteFunctions.h"
#include "NormalFunction.h"

// Empty constructor
NormalFunction::NormalFunction() : FiniteFunction() {
    m_stddev = 1.0;
    m_mean = 0.0;
    this->checkPath("NormalFunction");
}

// Initialized constructor for normal distribution
NormalFunction::NormalFunction(double range_min, double range_max, std::string outfile, double stddev, double mean)
    : FiniteFunction(range_min, range_max, outfile) {
    m_stddev = stddev;
    m_mean = mean;
}

// Setters
void NormalFunction::setStdDev(double stddev) {
    m_stddev = stddev;
}

void NormalFunction::setMean(double mean) {
    m_mean = mean;
}

// Getters
double NormalFunction::getStdDev() {
    return m_stddev;
}

double NormalFunction::getMean() {
    return m_mean;
}

// Normal distribution function
double NormalFunction::normalDistribution(double x) {
    if (m_stddev == 0.0) {
        // Handle the error, for example, throw an exception
        throw std::invalid_argument("For normal distribution, standard deviation must be non-zero");
    }
    return 1.0 / (m_stddev * sqrt(2 * M_PI)) * exp(-0.5 * pow((x - m_mean) / m_stddev, 2));
}

// Override the callFunction method
double NormalFunction::callFunction(double x) {
    return this->normalDistribution(x);
}


//Override the base class printInfo function
void NormalFunction::printInfo(){ //Override the base class printInfo function
  FiniteFunction::printInfo(); //Call the base class printInfo function
  std::cout << "stddev: " << m_stddev << std::endl; //add the extra info for the normal distribution
  std::cout << "mean: " << m_mean << std::endl;
  }
// maybe need if n_args
