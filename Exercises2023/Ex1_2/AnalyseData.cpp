/*
    File: AnalyseData.cpp
    Author: Andrew Cheyne - based on execise and Github fork by Jonathon Jamieson
    Date: 2023-11-15
    Purpose: SUPA C++ Exercise to read in data from a file, and perform some basic analysis on it.
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
//#include "gnuplot-iostream.h"


//syntax to run
//g++ CustomSource.cpp Main.cpp -o MyProgram
//to copy and paste beacause I'm lazy - g++ CustomFunctions.cpp AnalyseData.cpp -o MyProgram

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


std::tuple<double, double, double> fitLine(std::pair<std::vector<double>, std::vector<double>> xy, std::pair<std::vector<double>, std::vector<double>> xy_err)
{
    int N = xy.first.size();
    double p, q, chi;
    
    double sum_xi = 0;
    double sum_yi = 0; 
    double sum_xisq = 0;
    double sum_xiyi = 0;
    
  for(int i = 0; i < N; i++) 
    {
        sum_xi += xy.first[i];
        sum_yi += xy.second[i];
        sum_xisq += xy.first[i]*xy.first[i];
        sum_xiyi += xy.first[i]*xy.second[i];
    }

    p = ((N*sum_xiyi)-(sum_xi*sum_yi)) / ((N*sum_xisq)-(sum_xi*sum_xi));
    q = ((sum_xisq*sum_yi)-(sum_xiyi*sum_xi)) / ((N*sum_xisq)-(sum_xi*sum_xi));

    // debuggin steps - left for reference
    // std::cout << "Sum of xi: " << sum_xi << std::endl;
    // std::cout << "Sum of yi: " << sum_yi << std::endl;
    // std::cout << "Sum of xiyi: " << sum_xiyi << std::endl;
    // std::cout << "Sum of xisquared: " << sum_xisq << std::endl;
    
    std::cout << "For this set of x,y data. The straight line fit (y = px + q) have the parameters: " << std::endl;
    std::cout << "p = " << p << std::endl;
    std::cout << "q = " << q << std::endl;

    //used to work, now broken
    // expect - p = 0.126266, q = 0.405255
    // chi squared = 311.694    (sum of chi squared)    
    // N = 25   (number of data points)         
    // nParameters = 2 (number of parameters in fit)    
    // NDF = N - nParameters = 23 (degrees of freedom)
    // Goodness of fit = chi squared / NDF = 311.694/23 = 13.5519
   



    //calculating chi squared
    double chiSum;
    for(int i = 0; i < N; i++) 
    {
        double expected = (xy.first[i] * p) + q;    //expected y value for given x - based on fit
        double diff = xy.second[i] - expected;      //difference between expected and actual y value
        double numerator = diff * diff;
        double denominator = (p * p * xy_err.first[i] * xy_err.first[i]) + (xy_err.second[i] * xy_err.second[i]);   //error on y value - (from data in file and error from fit)
        chiSum += numerator / denominator;          //sum of chi squared for each point

    // for(int i = 0; i < N; i++) 
    // {
    //    chiSum = chiSum + ( (xy.second[i] - ((xy.first[i]*p) + q))*(xy.second[i] - ((xy.first[i]*p) + q)) ) / ( sqrt( (p*p*xy_err.first[i]*xy_err.first[i]) + (xy_err.second[i]*xy_err.second[i])  ));
    // }

    }

    int nParameters = 2;
    int NDF = N - nParameters;
    double GoodofFit = chiSum/(NDF); //goodness of fit - chi squared divided by degrees of freedom

    std::cout << "Sum of chisq: " << chiSum << std::endl;
    std::cout << "As we have "<< N <<" data points, and " << nParameters << " parameters to our fit. Thus, we have " << N-nParameters << " Degrees of freedom." << std::endl;
    std::cout << "ChiSquared/NDF = " << chiSum << "/" << NDF << " = " << GoodofFit << std::endl;

    std::ofstream myfile; //output file stream
    myfile.open ("fitParams.txt"); //open file to write to 
    myfile << "p = " << p << std::endl;
    myfile << "q = " << q << std::endl;
    myfile << "ChiSquared/NDF = " << chiSum << "/" << N-2 << " = " << GoodofFit << std::endl;
    myfile.close(); //close file


    return std::make_tuple(p,q,GoodofFit);

}

int main()
{

std::string filePath =  "/workspaces/SUPA_CPP_Labs/Exercises2023/Ex1_2/input2D_float.txt";
std::string filePath_err = "/workspaces/SUPA_CPP_Labs/Exercises2023/Ex1_2/error2D_float.txt";


std::pair<std::vector<double>, std::vector<double>> xy = readFile(filePath); //defining the input paired x,y
std::pair<std::vector<double>, std::vector<double>> xy_err = readFile(filePath_err); //defining the input paired x,y

int i, j; //for user input switches
bool go = true;
while (go){

    int n_lines = xy.first.size();
    std::printf("\nYou have read in a file with %i lines of data, corresponding to %i x,y coordinates. \n", n_lines, n_lines);
    std::printf("To print some lines of the data, enter 1. \n");
    std::printf("To calculate the magnitude of each point, press 2. \n");
    std::printf("To output fit parameters for this data, enter 3. \n");
    std::printf("To calculate x^y for this data, enter 4. \n");
    std::printf("To exit, enter 0. \n");
    std::cout << std::endl;

    std::cin >> i;

    switch (i) {

        case 0: 
            std::cout << "Exiting." << std::endl;
            go = false;
            break;
        case 1: 
            std::cout << std::endl;
            lineprint(xy);
            std::cout << std::endl;

            std::cout << "If you woud like perform another function, press 1." << std::endl;     
            std::cout << "Otherwise, press 0 to exit." << std::endl;
           
            std::cin >> j;
              switch (j)
                {
                case 1:
                    std::cout << std::endl;
                    break;
                
                case 0: 
                    std::cout << "Exiting." << std::endl;
                     go = false;
                    break;

                default:
                    std::cout << "invalid choice. Exiting." << std::endl;
                    go = false;
                    break;
                }
            break;

        case 2: 
            std::cout << std::endl;
            vectorCalc(xy);
            std::cout << std::endl;
            
            std::cout << "If you woud like perform another function, press 1." << std::endl;     
            std::cout << "Otherwise, press 0 to exit." << std::endl;
           
            std::cin >> j;
              switch (j)
                {
                case 1:
                    std::cout << std::endl;
                    break;
                
                case 0: 
                    std::cout << "Exiting." << std::endl;
                     go = false;
                    break;

                default:
                    std::cout << "invalid choice. Exiting." << std::endl;
                    go = false;
                    break;
                }
            break;
        case 3: 
            std::cout << std::endl;
            fitLine(xy, xy_err);
            std::cout << std::endl;
            
            std::cout << "If you woud like perform another function, press 1." << std::endl;     
            std::cout << "Otherwise, press 0 to exit." << std::endl;
           
            std::cin >> j;
              switch (j)
                {
                case 1:
                    std::cout << std::endl;
                    break;
                
                case 0: 
                    std::cout << "Exiting." << std::endl;
                     go = false;
                    break;

                default:
                    std::cout << "invalid choice. Exiting." << std::endl;
                    go = false;
                    break;
                }
            break;
        case 4:   
            std::cout << std::endl;
            XsupYCalc(xy);
            std::cout << std::endl;
            
            std::cout << "If you woud like perform another function, press 1." << std::endl;     
            std::cout << "Otherwise, press 0 to exit." << std::endl;
           
            std::cin >> j;
              switch (j)
                {
                case 1:
                    std::cout << std::endl;
                    break;
                
                case 0: 
                    std::cout << "Exiting." << std::endl;
                     go = false;
                    break;

                default:
                    std::cout << "invalid choice. Exiting." << std::endl;
                    go = false;
                    break;
                }
            break;
        
        default:{
            std::cout << "invalid choice. Exiting." << std::endl;
            go = false;
            break;
        }


    }
}


return 0;
}