#pragma once
#include <iostream>
#include <random>
#include <cmath>
#include <algorithm>
#include "FiniteFunctions.h"

std::vector<double> runMetropolisAlgorithm(FiniteFunction* function, int numPoints, double initialSigma, int maxIterations);
