#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//functions to print output of any function acting on our x,y data
// void printResult()
// {
//      std::cout << "line " << i  << ". x = " << xy.first[i-1] << ", y = " << xy.second[i-1] << std::endl
// }
//      std::cout <<"The magnitude from (0,0) of position "<< j+1 << " is "<< vectorData[j] << std::endl;


//     std::cout << "For point " << i << ": " << "x^y" << " = " << result[i] << std::endl; //output with formula and results

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//function to print lines of data from a file
void lineprint(std::pair<std::vector<double>, std::vector<double>> xy)
{
    //asking user for number of lines to print
    std::cout << "Please enter the number lines to print " << "(note: a maximum of 5 lines will be printed)." << std::endl;

    int userN;
    std::cin >> userN;

    //printing lines
    for (int i=1; i<=userN; i++){
     if (i>5) break;    
     std::cout << "line " << i  << ". x = " << xy.first[i-1] << ", y = " << xy.second[i-1] << std::endl; 
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//function calculate magnitude of vectors from a file
void vectorCalc(std::pair<std::vector<double>, std::vector<double>> xy)
{
 std::vector<double> vectorData;
    int size = xy.first.size();
    for(int i=0; i<size; i++)
    {
        double V_mag = sqrt((xy.first[i]*xy.first[i]) + (xy.second[i]*xy.second[i]));
        vectorData.push_back(V_mag);
    }

    for (auto j = 0; j<vectorData.size(); j++)
    {
        std::cout <<"The magnitude from (0,0) of position "<< j+1 << " is "<< vectorData[j] << std::endl;
    }     

}

//function to plot data from a file and fit a line
    double ls ()
    {
        int N = xy.first.size();
        double p;
        double sum_xiyi, sum_xi, sum_yi, sum_xisq, 
    
        for (int i = 0; i<N;i++)
        {
            sum_xi = sum_xi + (xy.first[i]);

        }

         std::cout << "Sum of xi: " << sum_xi << std::endl;
    }



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//function to do x^y without pow or loop

//plan - rewrite ln(x^y) = y*ln(x) (then take inverse log.. hopefully this doesn't count as a pow function :) )
//then transform the vector using this function as the operation
void XsupYCalc(std::pair<std::vector<double>, std::vector<double>> xy)
{
   std::vector<double> result;
  
    //Creating a custom function to use for the operation in the transform below
    auto powerFunction = [](double x, double y) 
    {
        return std::exp(y * std::log(x));
    };
    // Calculating x^y without using pow or a loop
    // syntax for tranform (in1first, in1last, in2first, outfirst, operation) 
    std::transform(xy.first.begin(), xy.first.end(), xy.second.begin(), std::back_inserter(result), powerFunction);
    //std::transform (xy.first.begin(), xy.first.end(), xy.second.begin(), std::back_inserter(result), std::exp(xy.second) * std::log(xy.first)));  // this was first attempt that I couldnt get to work as a single line
    
    // Display the results - I dont know how to do this without a loop though
    for (int i = 0; i < result.size(); i++) {
        //std::cout << "For point " << i << ": " << xy.first[i] << "^" << xy.second[i] << " = " << result[i] << std::endl; //output with numeric values
        std::cout << "For point " << i << ": " << "x^y" << " = " << result[i] << std::endl; //output with formula and results
    }

  
}