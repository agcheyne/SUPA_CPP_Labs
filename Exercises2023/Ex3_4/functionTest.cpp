/*
    File: functionTest.cpp
    Author: Andrew Cheyne - https://github.com/agcheyne/
    Title: Submission for Labs 3 & 4
    Course: SUPA Graduate C++ Course (SUPACOO)
    Original fork from: Jonathon Jamieson - https://github.com/jjamieson12/SUPA_CPP_Labs/
    Date: 2023-11-29
    Purpose: Exercise 3 & 4. To ...
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include "FiniteFunctions.h"
#include "NormalFunction.h"
#include "CLFunction.h"
#include "NegCrystalBallFunction.h"
#include "sampling.h"

//script to test the FiniteFunction class
//beginning with testing the default class constructor

int main()
{
    FiniteFunction test1;   // test1 is an object of class FiniteFunction
                            // the default constructor sets the range to -5 to 5 and integral to null
                            // and sets the output file to DefaultFunction

                            //for reference...
                            //setters are: setRangeMin(), setRangeMax(), setOutfile()
                            //getters are: rangeMin(), rangeMax()


    // Read in the data and storing in points vector for plotting
    std::string file = "/workspaces/SUPA_CPP_Labs/Exercises2023/Ex3_4/Outputs/data/MysteryData03102.txt";
    std::ifstream inputFile(file);
        if (!inputFile.is_open()) {
            std::cerr << "Error opening file: " << file << std::endl;
            return 1; // Return an error code
        }

    
    std::vector<double> points; // Define the points container
    double x;
    while (inputFile >> x) {
        points.push_back(x);
    }
    inputFile.close();
    std::cout << "************************************" << std::endl;
    std::cout << "Read in " << points.size() << " points from " << file << std::endl;
    std::cout << std::endl;
    std::cout << "************************************" << std::endl;







    test1.setRangeMax(7);   // change the max range to 7 as data was outside the plot range    
    test1.printInfo();      // print the info about the function to the terminal
    test1.plotFunction(); 
    test1.plotData(points, 40, true);  // plot the data with 20 bins. The true denotes that it is data
    std::vector<double> samples1;
    samples1 = runMetropolisAlgorithm(&test1, 100, 1.5, 100);
    test1.plotData(samples1, 20, false);  // plot the data with 20 bins. The false denotes that it is sampled data

    
    NormalFunction test2;
    test2.setRangeMax(7); 
    test2.setMean(1.0);
    test2.setStdDev(1.5);
    test2.printInfo();
    test2.plotFunction();
    test2.plotData(points, 40, true);   
    
    std::vector<double> samples2;
    samples2 = runMetropolisAlgorithm(&test2, 10000, 2, 100); // 10000 points, initial sigma of 2, max 100 iterations
    test2.plotData(samples2, 100, false);  // plot the samples with 20 bins. The false denotes that it is sampled data


    
    CLFunction test3;
    test3.setRangeMax(7); 
    test3.setGamma(1.2);    // gamma is the scale parameter - like the standard deviation of a gaussian
    test3.setX0(1.0);       // x0 is the location parameter - like the mean of a gaussian
    test3.printInfo();
    test3.plotFunction();
    test3.plotData(points, 40, true);   
    std::vector<double> samples3;
    samples3 = runMetropolisAlgorithm(&test3, 10000, 1.5, 100);
    test3.plotData(samples3, 65, false);  // plot the data with 20 bins. The false denotes that it is sampled data
    
     
    NegCrystalBallFunction test4;
    test4.setRangeMax(7);
    test4.setStdDev(1.5);
    test4.setMean(1.0);  
    test4.setN(2);       // n is a "power" shape parameter - it influences the tail behaviour, specifically how quickly the function falls off. Larger n means a sharper fall off.
    test4.setAlpha(1);   // alpha is another shape parameter - it controls the point at which the function transitions from a gaussian to a power law tail. It must be greater than 0 for the power law tail to be negative.
    test4.printInfo();
    test4.plotFunction();
    test4.plotData(points, 40, true);
    std::vector<double> samples4;
    samples4 = runMetropolisAlgorithm(&test4, 10000, 1.5, 100);
    test4.plotData(samples4, 65, false);  // plot the data with 20 bins. The false denotes that it is sampled data


    

  
   


    return 0;
}