#include "Vector.h"
#include <iostream>
#include <iomanip>

using namespace std;
static const double EPS = 1e-8;
Vector * Vector::CreateVectorFromArray(int count_row, double * data)
{
	VectorP v= new Vector;
	v->count_column = 1;
	v->count_row = count_row;
	v->data = new double[count_row];
	int i;
	for (i = 0; i < count_row; i++)
		v->data[i] = data[i];
	return v;
}

Vector * Vector::CreateMatrixColumn(MatrixP m, int column)
{
	return (VectorP)m->CreateSubMatrix(0,m->GetCountRow()-1,column,column);
}

Vector * Vector::CreateMatrixRow(MatrixP m, int row)
{
	MatrixP temp = m->CreateSubMatrix(row, row, 0, m->GetCountColumn() - 1);
	if (temp == NULL)
		return NULL;
	else
		return (VectorP)(temp->TransformTransposition());

}


double Vector::InnerProduct(Vector *v1, Vector *v2)
{
	if (v1->count_row != v2->count_row)
		return 0;
	double sum = 0;
	int i;
	for (i = 0; i < v1->count_row; i++)
		sum += v1->data[i] * v2->data[i];
	return sum;
}

void Vector::Show()
{
	int i;
	cout << '(';
	for (i = 0; i < count_row; i++)
	{
		if (i != 0)
			cout << "  ";
		if (fabs(data[i]) < EPS)
			cout << '0';
		else
			cout << setprecision(4)<<data[i];
	}
	cout << ')';
}

Vector::Vector()
{
}


Vector::~Vector()
{
}
