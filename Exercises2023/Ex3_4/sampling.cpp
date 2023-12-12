//Sampling
#include <iostream>
#include <random>
#include <cmath>
#include <algorithm>
#include "FiniteFunctions.h"

double runMetropolisAlgorithm(FiniteFunction* function) {

std::random_device rd;
std::mt19937 gen{rd()};

double sigma = 0.5;

//generate a random number x_i on a range where the fucntion is defined
double x_i = std::uniform_real_distribution<double>(0,7)(gen);

//generate a random number y from a normal distribution with mean x_i and arbitrary sigma
std::normal_distribution<double> gaussianPDF(x_i, sigma);
double y = gaussianPDF(gen); 


double A, T;
for (int i = 0; i < 100000; i++) {

    std::normal_distribution<double> gaussianPDF{x_i, sigma};
                                        //generate a point, y, from a normal distribution with mean x_i and arbitrary sigma
    double f_xi = function->callFunction(x_i);    //compute f(x_i)
    double f_y = function->callFunction(y);       //compute f(y)
    A = std::min((f_y / f_xi), 1.0);     //compute A = min(f(y)/f(x_i), 1) where f is the function to sample
    T = std::uniform_real_distribution<double>(0,1)(gen);    //generate a random number T between 0 and 1 and 
                            
                            //if T < A accept the new point, otherwise reject it
    if (T < A) {            //if y is accepted, set x_i+1 = y, otherwise set x_i+1 = x_i
        x_i = y;
        double y = gaussianPDF(gen);    //generate a new y from the normal distribution with mean x_i and arbitrary sigma
   }
//    if (i % 10000 == 0) {                                                                  //print out the value of x_i every 10000 iterations to check convergence
//             std::cout << "Iteration " << i << ": x_i = " << x_i << std::endl;
//     }
}
//std::cout << "x_i+1 = " << x_i << std::endl;                                               //print out the final value of x_i
return x_i;
}

