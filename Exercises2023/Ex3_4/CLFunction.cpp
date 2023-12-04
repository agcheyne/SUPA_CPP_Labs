#include "FiniteFunctions.h"
#include "CLFunction.h"

// Empty constructor
CLFunction::CLFunction() : FiniteFunction() {
    m_gamma = 1.0; // gamma is the scale parameter
    m_x0 = 0.0; // x0 is the location parameter
    this->checkPath("CLFunction");

}

// Initialized constructor for normal distribution
CLFunction::CLFunction(double range_min, double range_max, std::string outfile, double gamma, double x0)
    : FiniteFunction(range_min, range_max, outfile) {
    m_gamma = gamma;
    m_x0 = x0;
}

// Setters

void CLFunction::setGamma(double gamma) {
    m_gamma = gamma;
}

void CLFunction::setX0(double x0) {
    m_x0 = x0;
}

// Getters
double CLFunction::getGamma() {
    return m_gamma;
}

double CLFunction::getX0() {
    return m_x0;
}

// Cauchy-Lorentz distribution function definition
double CLFunction::clDistribution(double x) {
    if (m_gamma == 0.0) {
        // If the standard deviation is zero, the distribution is a delta function and not defined by this class. Throw an exception.
        throw std::invalid_argument("For Cauchy-Lorentz function, gamma must be non-zero");
    }
    return 1.0 / (M_PI * m_gamma * (1.0 + ((x - m_x0) / m_gamma) * ((x - m_x0) / m_gamma)));
}
    

// Override the callFunction method for Cauchy-Lorentz distribution defined above
double CLFunction::callFunction(double x) {
    return this->clDistribution(x);
}


//Override the base class printInfo function
void CLFunction::printInfo(){ //Override the base class printInfo function
    FiniteFunction::printInfo(); //Call the base class printInfo function
    std::cout << "gamma: " << m_gamma << std::endl; //add the extra info for the normal distribution
    std::cout << "x0: " << m_x0 << std::endl;

  }
