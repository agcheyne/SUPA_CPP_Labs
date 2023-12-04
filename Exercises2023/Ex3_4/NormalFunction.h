#pragma once

#include "FiniteFunctions.h"

class NormalFunction : public FiniteFunction {
public:
    NormalFunction(); // Default constructor
    NormalFunction(double range_min, double range_max, std::string outfile, double stddev, double mean); // Parameterized constructor

    void setStdDev(double stddev);
    void setMean(double mean);

    virtual double callFunction(double x) override; // overriding the callFunction from FiniteFunction
    virtual void printInfo() override; // overriding the printInfo from FiniteFunction

    // Getters
    double getStdDev();
    double getMean();

protected:
    double m_stddev;
    double m_mean;

private:
    double normalDistribution(double x);
};
