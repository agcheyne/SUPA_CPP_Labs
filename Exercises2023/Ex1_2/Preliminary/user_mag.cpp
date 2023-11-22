#include<iostream>
#include<cmath>

int main()

{

    double x,y;

    std::cout << "Input x value: " << std::endl;
    std::cin >> x;
    std::cout << "Input y value: " << std::endl;
    std::cin >> y;

    double V_mag = sqrt(x*x + y*y);

    std::cout << V_mag << std::endl;

    return 0;
}
