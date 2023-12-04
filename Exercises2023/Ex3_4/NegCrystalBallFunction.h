#pragma once

#include "FiniteFunctions.h"

class NegCrystalBallFunction : public NormalFunction {
public:
    NegCrystalBallFunction(); // Default constructor
    NegCrystalBallFunction(double range_min, double range_max, std::string outfile, double stddev, double mean, double n, double alpha); // Parameterized constructor

    void setN(double n);
    void setAlpha(double alpha);

    virtual double callFunction(double x) override; // overriding the callFunction from FiniteFunction
    virtual void printInfo() override; // overriding the printInfo from FiniteFunction

    // Getters
    double getN();
    double getAlpha();

protected:
    double m_n;
    double m_alpha;
    
private:
    double negCBDistribution(double x);
};
