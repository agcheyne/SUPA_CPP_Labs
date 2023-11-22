#include<iostream>
#include<cmath>

int main()

{

    double x = 2.3;
    double y = 4.5;

    double V_mag = sqrt(x*x + y*y);

    std::cerr << V_mag << std::endl;

    return 0;
}
