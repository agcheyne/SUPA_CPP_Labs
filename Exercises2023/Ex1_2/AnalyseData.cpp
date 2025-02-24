/*
    File: AnalyseData.cpp
    Author: Andrew Cheyne - https://github.com/agcheyne/
    Title: Submission for Labs 1 & 2
    Course: SUPA Graduate C++ Course (SUPACOO)
    Original fork from: Jonathon Jamieson - https://github.com/jjamieson12/SUPA_CPP_Labs/
    Date: 2023-11-15
    Purpose: Exercise 1 & 2. To read in a file of x,y data and perform various functions on it in order to demonstrate topics taught in the course.
*/

#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <boost/tuple/tuple.hpp>
#include <algorithm>

#include "CustomFunctions.h"

//to run from terminal:
//cd /workspaces/SUPA_CPP_Labs/Exercises2023/Ex1_2                                      //change directory to where the files are
//g++ CustomFunctions.cpp AnalyseData.cpp -o AnalyseData && ./AnalyseData               //compile and run

std::pair<std::vector<double>, std::vector<double>> readFile(const std::string& filePath)
{
    //reading input file & assigning variables
   
    std::fstream inFile;
    inFile.open(filePath, std::ios::in);
    //inFile.open("/workspaces/SUPA_CPP_Labs/Exercises2023/Ex1_2/input2D_float.txt", std::ios::in);
    //inFile.open("/workspaces/SUPA_CPP_Labs/Exercises2023/Ex1_2/input2D_float.txt");

    std::string inputLine;
    std::vector<std::string> xin, yin;
    std::vector<double> x, y;
    
    std::getline(inFile, inputLine); //to get past the first whitespace - i.e. skip x,y heading

 while(1)
{
    std::getline(inFile, inputLine, ',');
    xin.push_back(inputLine);     

    std::getline(inFile, inputLine);
    yin.push_back(inputLine); 
    
    if(inFile.eof()) break;
}

int n_lines = xin.size() - 1;
// std::cout << "Total number of lines of data in file: " << n_lines << std::endl;

for(int i=0; i < n_lines; i++)
{
x.push_back(std::stod(xin[i]));
y.push_back(std::stod(yin[i]));
}

 return std::make_pair(x, y);

}





int main()
{
//defining the input file paths
std::string filePath =  "/workspaces/SUPA_CPP_Labs/Exercises2023/Ex1_2/input2D_float.txt";
std::string filePath_err = "/workspaces/SUPA_CPP_Labs/Exercises2023/Ex1_2/error2D_float.txt";

//reading in the data 
//these will be paired vectors of x,y coordinates for use in all functions
std::pair<std::vector<double>, std::vector<double>> xy = readFile(filePath); //defining the input paired x,y
std::pair<std::vector<double>, std::vector<double>> xy_err = readFile(filePath_err); //defining the input paired x,y


//user input section
int i, j; //for user input switches
bool go = true;

while (go){
   
   int n_lines = xy.first.size();
    
    std::printf("\nYou have read in a file with %i lines of data, corresponding to %i x,y coordinates. \n", n_lines, n_lines);
    std::printf("Choose from the following options:\n");
    std::printf("1. Prints a chosen number of lines of the data file. \n");
    std::printf("2. Calculates the magnitude of each data point. \n");
    std::printf("3. Fits the data to a straight line. \n");
    std::printf("4. Calculates x^y for the data. \n");
    std::printf("To exit, enter 0. \n");
    std::cout << std::endl;

    std::cin >> i;

    switch (i) {

        case 0: 
            std::cout << "Exiting program..." << std::endl;
            go = false;
            break;

        case 1: 
            std::cout << std::endl;
            lineprint(xy);
            break;

        case 2: 
            std::cout << std::endl;
            vectorCalc(xy);        
            break;

        case 3: 
            std::cout << std::endl;
            fitLine(xy, xy_err);
            break;

        case 4:   
            std::cout << std::endl;
            XsupYCalc(xy);
            break;
        
        default:
            std::cout << "invalid choice. Exiting..." << std::endl;
            break;
    }

    if (go) {
        std::cout << std::endl;
        std::cout << "Would you like to perform another function? (1 for Yes, 0 for No)" << std::endl;
        std::cin >> j;
        if (j != 1) {
            std::cout << "Exiting program...\n";
            go = false;
        }
    }  
}


return 0;
}