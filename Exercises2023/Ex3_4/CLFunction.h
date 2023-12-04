#pragma once

#include "FiniteFunctions.h"

class CLFunction : public FiniteFunction {
public:
    CLFunction(); // Default constructor
    CLFunction(double range_min, double range_max, std::string outfile, double gamma, double x0); // Parameterized constructor

    void setGamma(double gamma);
    void setX0(double x0);

    virtual double callFunction(double x) override; // overriding the callFunction from FiniteFunction
    virtual void printInfo() override; // overriding the printInfo from FiniteFunction

    // Getters
    double getGamma();
    double getX0();

protected:
    double m_gamma;
    double m_x0;
    
private:
    double clDistribution(double x);
};
