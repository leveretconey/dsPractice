#pragma once



int RandomUniformDiscrete(int lower_bound, int upper_bound);
int RandomPoisson(double lamdba);
int RandomBernoulli(double probability);
int RandomBinary(double probability,int experiment_count);
int RandomGeometry(double probability);
int RandomNegativeBinomial(double probability, int success_count);

double RandomUniformContinuous();
double RandomUniformContinuous(double lower_bound , double upper_bound );
double RandomNormal();
double RandomNormal(double mean , double variance );
double RandomExpotential(double lamdba);
double RandomGamma(double alpha, double beta);//当alpha不是正整数的时候结果不正确
double RandomChiSquare(int degree_of_freedom);