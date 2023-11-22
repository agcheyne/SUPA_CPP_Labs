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


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// function to caluclate fit parameters and goodness of fit

// std::tuple<double, double, double> fitLine(std::pair<std::vector<double>, std::vector<double>> xy, std::pair<std::vector<double>, std::vector<double>> xy_err)
// {
//     int N = xy.first.size();
//     double p, q, chi;
//     double sum_xiyi = 0;
//     double sum_xi = 0;
//     double sum_yi = 0; 
//     double sum_xisq = 0;
    
//   for(int i = 0; i < N; i++) 
//     {
//         sum_xi = sum_xi + xy.first[i];
//         sum_yi = sum_yi + xy.second[i];
//         sum_xisq = sum_xisq + xy.first[i]*xy.first[i];
//         sum_xiyi = sum_xiyi + xy.first[i]*xy.second[i];
//     }

//     p = ((N*sum_xiyi)-(sum_xi*sum_yi))/((N*sum_xisq)-(sum_xi*sum_xi));
//     q =  ((sum_xisq*sum_yi)-(sum_xiyi*sum_xi))/((N*sum_xisq)-(sum_xi*sum_xi));

//     // debuggin steps - left for reference
//     // std::cout << "Sum of xi: " << sum_xi << std::endl;
//     // std::cout << "Sum of yi: " << sum_yi << std::endl;
//     // std::cout << "Sum of xiyi: " << sum_xiyi << std::endl;
//     // std::cout << "Sum of xisquared: " << sum_xisq << std::endl;
    
//     std::cout << "For this set of x,y data. The straight line fit (y = px + q) have the parameters: " << std::endl;
//     std::cout << "p = " << p << std::endl;
//     std::cout << "q = " << q << std::endl;

//     //used to work, now broken
//     // expect - p = 0.126266, q = 0.405255
//     // chi squared = 311.694    (sum of chi squared)    
//     // N = 25   (number of data points)         
//     // nParameters = 2 (number of parameters in fit)    
//     // NDF = N - nParameters = 23 (degrees of freedom)
//     // Goodness of fit = chi squared / NDF = 311.694/23 = 13.5519
   



//     //calculating chi squared
//     double chiSum;
//     for(int i = 0; i < N; i++) 
//     {
//         // double expected = (xy.first[i] * p) + q;    //expected y value for given x - based on fit
//         // double diff = xy.second[i] - expected;      //difference between expected and actual y value
//         // double numerator = diff * diff;
//         // double denominator = (p * p * xy_err.first[i] * xy_err.first[i]) + (xy_err.second[i] * xy_err.second[i]);   //error on y value - (from data in file and error from fit)
//         // chiSum += numerator / denominator;          //sum of chi squared for each point

//     for(int i = 0; i < N; i++) 
//     {
//        chiSum = chiSum + ( (xy.second[i] - ((xy.first[i]*p) + q))*(xy.second[i] - ((xy.first[i]*p) + q)) ) / ( sqrt( (p*p*xy_err.first[i]*xy_err.first[i]) + (xy_err.second[i]*xy_err.second[i])  ));
//     }

//     }

//     int nParameters = 2;
//     int NDF = N - nParameters;
//     double GoodofFit = chiSum/(NDF); //goodness of fit - chi squared divided by degrees of freedom

//     std::cout << "Sum of chisq: " << chiSum << std::endl;
//     std::cout << "As we have "<< N <<" data points, and " << nParameters << " parameters to our fit. Thus, we have " << N-nParameters << " Degrees of freedom." << std::endl;
//     std::cout << "ChiSquared/NDF = " << chiSum << "/" << NDF << " = " << GoodofFit << std::endl;

//     std::ofstream myfile; //output file stream
//     myfile.open ("fitParams.txt"); //open file to write to 
//     myfile << "p = " << p << std::endl;
//     myfile << "q = " << q << std::endl;
//     myfile << "ChiSquared/NDF = " << chiSum << "/" << N-2 << " = " << GoodofFit << std::endl;
//     myfile.close(); //close file


//     return std::make_tuple(p,q,GoodofFit);

// }





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