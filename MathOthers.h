#pragma once


static const double ERROR = -9999.0;
static const int AREA_TRY_COUNT = 100000000;

const int MAX_RECURSION_TIMES = 100;
double SolveEquationBinarySearch(double(*f)(double), double low, double high);
double SolveEquationNewton(double(*f)(double), double initial_x);
static double Derivative(double(*f)(double), double x, double dx = 1e-6);
double GetArea(int(*curve)(double,double), double up, double down, double left, double right);
