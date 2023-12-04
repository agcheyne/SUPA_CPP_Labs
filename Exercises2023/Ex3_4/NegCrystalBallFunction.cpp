#include "NormalFunction.h"
#include "NegCrystalBallFunction.h"

// Empty constructor
NegCrystalBallFunction::NegCrystalBallFunction() : NormalFunction() {   // Call the normal function constructor since we use mean and stddev from that class as well
    m_n = 1.0; // n is the shape parameter, it must be greater than 0
    m_alpha = 0.0; //  alpha is the transition parameter between the gaussian and power law tails 
    this->checkPath("NegCrystalBallFunction");

}

// Initialized constructor for negative crystal ball distribution
NegCrystalBallFunction::NegCrystalBallFunction(double range_min, double range_max, std::string outfile, double stddev, double mean, double n, double alpha)
    : NormalFunction(range_min, range_max, outfile, stddev, mean) {
    m_n = n;
    m_alpha = alpha;
}

// Setters

void NegCrystalBallFunction::setN(double n) {
    if (n < 1.0) {
        throw std::invalid_argument("For negative Crystal Ball function, n must be greater than 1");
    }
    m_n = n; // n is the power shape parameter, it must be greater than 1

}

void NegCrystalBallFunction::setAlpha(double alpha) {
    if (alpha < 0.0) {
        throw std::invalid_argument("For negative Crystal Ball function, alpha must be greater than 0");
    }
    m_alpha = alpha; // alpha is the transition parameter between the gaussian and power law tails. It must be greater than 0 for the power law tail to be negative.

}

//Getters
double NegCrystalBallFunction::getAlpha() {
    return m_alpha;
}

double NegCrystalBallFunction::getN() {
    return m_n;
}

// Cauchy-Lorentz distribution function definition
double NegCrystalBallFunction::negCBDistribution(double x) {

     if (m_stddev == 0.0) {
        // If the standard deviation is zero, the distribution is a delta function and not defined by this class. Throw an exception.
        throw std::invalid_argument("For negative Crystal Ball function, Standard deviation must be non-zero");
    }

    x = (x - m_mean) / m_stddev; // standardize the input, also helps for the if statement below.

    double A = pow(m_n / fabs(m_alpha), m_n) * exp(-0.5 * pow(m_alpha, 2));
    double B = m_n / fabs(m_alpha) - fabs(m_alpha);
    double C = m_n / fabs(m_alpha) * (1.0 / (m_n - 1.0)) * exp(-0.5 * pow(m_alpha, 2));
    double D = sqrt(M_PI / 2.0) * (1.0 + erf(fabs(m_alpha) / sqrt(2.0)));
    double N = 1.0 / (m_stddev * (C + D));

    if (x > -m_alpha) {
        return N * exp(-0.5 * x * x);
    }
    else {
        return N * A * pow(B - x, -m_n);
    }
}
    

// Override the callFunction method for Cauchy-Lorentz distribution defined above
double NegCrystalBallFunction::callFunction(double x) {
    return this->negCBDistribution(x);
}


//Override the base class printInfo function
void NegCrystalBallFunction::printInfo(){ //Override the base class printInfo function
    NormalFunction::printInfo(); //Call the base class printInfo function
    std::cout << "n: " << m_n << std::endl; //add the extra info for the normal distribution
    std::cout << "alpha: " << m_alpha << std::endl;

  }
