#pragma once

void lineprint(std::pair<std::vector<double>, std::vector<double>> xy);
void vectorCalc(std::pair<std::vector<double>, std::vector<double>> xy);
void XsupYCalc(std::pair<std::vector<double>, std::vector<double>> xy);
std::tuple<double, double, double> fitLine(std::pair<std::vector<double>, std::vector<double>> xy, std::pair<std::vector<double>, std::vector<double>> xy_err);
