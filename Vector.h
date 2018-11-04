#pragma once
#include "Matrix.h"
class Vector :
	public Matrix
{

public:
	static Vector *CreateVectorFromArray(int count_row, double *data);
	static Vector *CreateMatrixColumn(MatrixP m, int column);
	static Vector *CreateMatrixRow(MatrixP m, int row);
	static double InnerProduct(Vector* v1,Vector* v2);


	void Show();
	Vector();
	~Vector();
};
typedef Vector *VectorP;

