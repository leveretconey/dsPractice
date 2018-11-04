#pragma once
#include <iostream>

class Vector;
class Matrix
{
public:

	//set and get
	//行号列号从0开始
	int GetCountRow();
	int GetCountColumn();
	double GetData(int row,int column);

	int SetData(int row, int column, double data);

	//创建
	void Initialize();
	static Matrix *CreateAllSameNumber(int count_row, int count_column, double data);
	static Matrix *CreateDiagonalAllSameNumber(int count_row, double data=1.0);
	static Matrix *CreateFromFile(char *file_path);
	static Matrix *CreateFromArray(int count_row, int count_column, double *data);
	Matrix *CreateCopy();
	Matrix * Matrix::CopyData(Matrix * m1);

	Matrix *CreateCofactor(int row, int column);
	Matrix *CreateSubMatrix(int top, int down, int left, int right);
	Matrix *CreateAdjoint();
	Matrix *CreateReverseFromAdjoint();
	Matrix *CreateReverseFromElemTransform();
	Matrix *CreateTransposition();
	Matrix *CreateAugmentedMatrix(Vector *right=NULL);

	//矩阵变换
	Matrix * TransformElemRowSwap(int row1, int row2);
	Matrix * TransformElemRowMultiply(int row, double factor);
	Matrix * TransformElemRowMultiplyPlus(int row_origin, double factor,int row_target);
	Matrix * TransformTransposition();
	Matrix * TransformRowEchelon();
	Matrix * TransformRowEchelon(int &rank);
	
	//计算
	static Matrix *Plus(Matrix *m1, Matrix *m2);
	Matrix * Plus(Matrix *m1);
	static Matrix *Multiply(Matrix *m1, Matrix *m2);
	static Matrix *Multiply(Matrix *m1, double number);
	Matrix * Multiply(Matrix *m1);
	Matrix *Multiply(double number);
	static Matrix *Power(Matrix *m, int index);
	Matrix * Power(int index);


	double GetDeterminantExpansion();
	double GetDeterminantDefinition();
	double GetDeterminantElementaryTransformation();

	double GetTrace();
	int GetRank();
	//other
	static void Show(Matrix *p);
	void Show();
	void SolveEquation(Vector *v=NULL);
	Matrix();
	~Matrix();
	
protected:
	int count_row;
	int count_column;
	double *data;

	//check
	int IsRowLegal(int row);
	int IsColumnLegal(int column);
	int IsRowAndColumnLegal(int row,int column);
private:
	void DeterminantDefinitionRecursion(int *list,int *hash,int &index,double &sum);
	static long ReverseNumber(int *list, int length);
};
typedef Matrix *MatrixP;
