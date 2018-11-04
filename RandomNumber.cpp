#include "RandomNumber.h"
#include <iostream>
#include <math.h>

static const double EPS = 1e-8;
double RandomUniformContinuous()
{
	return (double)rand() / RAND_MAX ;
}

double RandomUniformContinuous(double lower_bound, double upper_bound)
{
	return lower_bound + RandomUniformContinuous()*(upper_bound - lower_bound);
}
int RandomUniformDiscrete(int lower_bound, int upper_bound)
{
	return lower_bound + rand() % (upper_bound - lower_bound);
}

int RandomPoisson(double lamdba)
{
	const int MAX_RESULT = 10000;
	double probability_culmulate = exp(-lamdba);
	double u0_1 = RandomUniformContinuous();
	double probability = 0;
	int result = -1;

	do
	{
		result++;
		probability += probability_culmulate;
		probability_culmulate *= lamdba / (result + 1);
	} while (u0_1 > probability&& result<MAX_RESULT);
	return result;
}

int RandomBernoulli(double probability)
{
	if (RandomUniformContinuous() < probability)
		return 1;
	else
		return 0;
}

int RandomBinary(double probability, int experiment_count)
{
	int i;
	int result=0;
	for (i = 1; i <= experiment_count; i++)
		result += RandomBernoulli(probability);
	return result;
}

int RandomGeometry(double probability)
{
	int result = 1;
	while (RandomBernoulli(probability) == 0)
		result++;
	return result;
}

int RandomNegativeBinomial(double probability, int success_count)
{
	int result=0,i;
	for (i = 1; i <= success_count; i++)
		result += RandomGeometry(probability);
	return result;
}

double RandomNormal()
{
	int i;
	double sum = 0;
	for (i = 1; i <= 12; i++)
		sum += RandomUniformContinuous();
	return sum - 6;
}

double RandomNormal(double mean, double variance)
{
	return mean + sqrt(variance)*RandomNormal();
}

double RandomExpotential(double lamdba)
{
	const double MAX_RESULT = 1e10;
	double result = -log(1 - RandomUniformContinuous()) / lamdba;
	while (result > MAX_RESULT)
		result = -log(1 - RandomUniformContinuous()) / lamdba;
	return result;
}

double RandomGamma(double alpha, double beta)
{
	int i;
	double result = 0;
	int end = int(alpha + EPS);
	for (i = 0; i < end; i++)
	{
		result += RandomExpotential(beta);
	}
	if (i < alpha + EPS)
		result += RandomExpotential(beta)*(alpha - (int)alpha);
	return result;
}

double RandomChiSquare(int degree_of_freedom)
{
	//return RandomGamma(degree_of_freedom/2,0.5);
	int i;
	double result = 0,temp;
	for (i = 1; i <= degree_of_freedom; i++)
	{
		temp = RandomNormal();
		result += temp*temp;
	}
	return result;
}

