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
std::cout << "Total number of lines of data in file: " << n_lines << std::endl;

for(int i=0; i < n_lines; i++)
{
x.push_back(std::stod(xin[i]));
y.push_back(std::stod(yin[i]));
}

 return std::make_pair(x, y);

}



// void plotgraph()
// {
//     Gnuplot gp;

// 	// Gnuplot vectors (i.e. arrows) require four columns: (x,y,dx,dy)
// 	std::vector<boost::tuple<double, double, double, double> > pts_A;

// }





int main()
{

std::string filePath =  "/workspaces/SUPA_CPP_Labs/Exercises2023/Ex1_2/input2D_float.txt";
std::string filePath_err = "/workspaces/SUPA_CPP_Labs/Exercises2023/Ex1_2/error2D_float.txt";


std::pair<std::vector<double>, std::vector<double>> xy = readFile(filePath); //defining the input paired x,y
std::pair<std::vector<double>, std::vector<double>> xy_err = readFile(filePath_err); //defining the input paired x,y


//vectorCalc(xy); 
//lineprint(xy);
//XsupYCalc(xy);

    int N = xy.first.size();
    double p, q, chi;
    double sum_xiyi = 0;
    double sum_xi = 0;
    double sum_yi = 0; 
    double sum_xisq = 0;
    
  for(int i = 0; i < N; i++) 
    {
        sum_xi = sum_xi + xy.first[i];
        sum_yi = sum_yi + xy.second[i];
        sum_xisq = sum_xisq + xy.first[i]*xy.first[i];
        sum_xiyi = sum_xiyi + xy.first[i]*xy.second[i];
    }

    p = ((N*sum_xiyi)-(sum_xi*sum_yi))/((N*sum_xisq)-(sum_xi*sum_xi));
    q =  ((sum_xisq*sum_yi)-(sum_xiyi*sum_xi))/((N*sum_xisq)-(sum_xi*sum_xi));

    std::cout << "Sum of xi: " << sum_xi << std::endl;
    std::cout << "Sum of yi: " << sum_yi << std::endl;
    std::cout << "Sum of xiyi: " << sum_xiyi << std::endl;
    std::cout << "Sum of xisquared: " << sum_xisq << std::endl;
    std::cout << "p = " << p << std::endl;
    std::cout << "q = " << q << std::endl;

    
    std::vector<double> ytest;
    double chiSum;
    
    for(int i = 0; i < N; i++) 
    {
       chiSum = chiSum + ( (xy.second[i] - ((xy.first[i]*p) + q))*(xy.second[i] - ((xy.first[i]*p) + q)) ) / ( sqrt( (xy_err.first[i]*xy_err.first[i]) + (xy_err.second[i]*xy_err.second[i])  ));
    }

    std::cout << "Sum of chisq: " << chiSum << std::endl;
    std::cout << "As we have "<< N <<" data points, and 2 parameters to our fit, " << "we have " << N-2 << " Degrees of freedom." << std::endl;
    std::cout << "Therefor, ChiSquared/NDF = " << chiSum << "/" << N-2 << " = " << chiSum/(N-2) << std::endl;



return 0;
}