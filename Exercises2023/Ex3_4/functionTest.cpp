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

//script to test the FiniteFunction class
//beginning with testing the default class constructor

int main()
{
    FiniteFunction test1;   // test1 is an object of class FiniteFunction
                            // the default constructor sets the range to -5 to 5 and integral to null
                            // and sets the output file to DefaultFunction

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

    std::cout << "Read in " << points.size() << " points from " << file << std::endl;


    test1.printInfo();      // print the info about the function
    test1.plotData(points, 40, true);
    test1.plotFunction(); // plot the function

    //setters are: setRangeMin(), setRangeMax(), setOutfile()
    //getters are: rangeMin(), rangeMax()

    return 0;
}