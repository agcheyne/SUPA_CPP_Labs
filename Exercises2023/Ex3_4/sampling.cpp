#include <iostream>
#include <random>
#include <cmath>
#include <algorithm>
#include <vector>
#include "FiniteFunctions.h"


std::vector<double> runMetropolisAlgorithm(FiniteFunction* function, int numPoints, double initialSigma, int maxIterations) {
    std::random_device rd;
    std::mt19937 gen(rd());

    // Generate a random number x_i on a range where the function is defined
    std::uniform_real_distribution<double> uniformPDF(function->rangeMin(), function->rangeMax());
    double starting_x = uniformPDF(gen);

    // Declare a normal distribution with mean x_i and arbitrary sigma
    std::normal_distribution<double> gaussianPDF(starting_x, initialSigma);

    std::vector<double> samples; // Vector to store the samples once accepted

    // Declare uniform distribution for acceptance/rejection
    std::uniform_real_distribution<double> uniformAcceptance(0, 1);

   
          //double A = std::min(function->callFunction(y) / function->callFunction(x_i), 1.0);


    while (samples.size() < numPoints) {
        
        double x_i = starting_x;
        double current_y = function->callFunction(x_i);

        for (int i = 0; i < maxIterations; i++) {
            // Calculate the acceptance ratio
  
            double next_x = x_i + gaussianPDF(gen);
            double next_y = function->callFunction(next_x);

            double A = std::min(next_y / current_y, 1.0);


            // Calculate the transition ratio
            double T = uniformAcceptance(gen);

            if (T < A) {
                x_i = next_x;
                current_y = next_y;
                samples.push_back(x_i);
            }
        }
    }

    return samples;
}
