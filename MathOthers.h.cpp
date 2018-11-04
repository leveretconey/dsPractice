#include "MathOthers.h"
#include <math.h>
#include <iostream>

static const double EPS = 1e-8;
double SolveEquationBinarySearch(double(*f)(double), double low, double high)
{
	double mid;
	while (fabs(f(low)) >= EPS)
	{
		if (f(low)*f(high) > 0)
			break;
		mid = (low + high) / 2;
		if (f(low)*f(mid) < 0)
			high = mid;
		else
			low = mid;
		if (fabs(low - high) < EPS)
			break;
	}
	if (fabs(f(low)) < 1e-4)
		return low;
	else
		return ERROR;
}

double SolveEquationNewton(double(*f)(double), double x)
{
	int count = 0;
	double last_x;
	do
	{
		count++;
		if (count >= MAX_RECURSION_TIMES)
			return ERROR;
		last_x = x;
		x = x - f(x) / Derivative(f, x);	
	} while (fabs(x-last_x)> EPS);
	return x;
}

double Derivative(double(*f)(double), double x, double dx)
{
	return (f(x + dx) - f(x)) / dx;
}

double GetArea(int(*curve)(double,double), double up, double down, double left, double right)
{
	int count_in_area = 0;
	int count_total;
	double x, y;
	for (count_total = 1; count_total <= AREA_TRY_COUNT; count_total++)
	{
		x = left + (double)rand() / RAND_MAX*(right - left);
		y = down + (double)rand() / RAND_MAX*(up - down);
		if (curve(x, y))
			count_in_area++;
	}
	return (double)count_in_area / AREA_TRY_COUNT*(right - left)*(up - down);
}
