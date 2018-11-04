#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Vector.h"

using namespace std;

static const double EPS = 1e-8;
void Matrix::Initialize()
{
	count_row = 0;
	count_column = 0;
	if (data != NULL)
		delete[] data;
	data = NULL;
}

MatrixP Matrix::CreateAllSameNumber(int count_row, int count_column, double data)
{
	MatrixP p = new Matrix;
	p->count_column = count_column;
	p->count_row = count_row;
	p->data =new double[count_row*count_column];
	int i, j;
	for (i = 0; i < count_row; i++)
		for (j = 0; j < count_column; j++)
			p->SetData(i,j,data);
	return p;
}

Matrix * Matrix::CreateDiagonalAllSameNumber(int count_row, double data)
{
	MatrixP p = new Matrix;
	p->count_column = count_row;
	p->count_row = count_row;
	p->data =new double[count_row*count_row];
	int i,j;
	for (i = 0; i < count_row; i++)
		for (j = 0; j < count_row; j++)
		{
			if (i == j)
				p->SetData(i, j, data);
			else
				p->SetData(i, j, 0.0);
		}
	return p;
}

Matrix * Matrix::CreateFromFile(char * file_path)
{
	const int BUFFER_SIZE = 100;

	MatrixP p = new Matrix;
	ifstream *input_file = new ifstream;
	input_file->open(file_path, ios::in);
	char buffer[BUFFER_SIZE];
	char *buffer_pointer;

	input_file->getline(buffer, BUFFER_SIZE);

	//get two counts
	input_file->getline(buffer, BUFFER_SIZE);
	sscanf_s(buffer, "%d%d", &p->count_row, &p->count_column);
	p->data = new double[p->count_row*p->count_column];

	//get data
	int row, column;
	for (row = 0; row < p->count_row; row++)
	{
		column = 0;
		input_file->getline(buffer, BUFFER_SIZE);
		buffer_pointer = buffer;
		while (*buffer_pointer != '\0')
		{
			sscanf_s(buffer_pointer, "%lf", &p->data[p->count_column*row+column]);
			column++;
			while (*buffer_pointer != ' '&& *buffer_pointer != '\0')
				buffer_pointer++;
			while (*buffer_pointer == ' ')
				buffer_pointer++;
		}
	}

	input_file->close();
	return p;
}

Matrix * Matrix::CreateFromArray(int count_row, int count_column, double * data)
{
	MatrixP p = new Matrix;
	p->count_column = count_row;
	p->count_row = count_row;
	p->data = new double[count_row*count_row];
	int i, end = count_row*count_column;
	for (i = 0; i < end; i++)
		p->data[i] = data[i];
	return p;
}

Matrix * Matrix::CreateCopy()
{
	MatrixP p = new Matrix;
	p->count_column = count_column;
	p->count_row = count_row;
	p->data = new double[count_row*count_column];

	int row, column;
	for (row = 0; row < count_row; row++)
		for (column = 0; column < count_column; column++)
			p->SetData(row, column, GetData(row, column));
	return p;

}

Matrix * Matrix::CopyData(Matrix * m1)
{
	if (m1 == NULL)
	{
		return NULL;
	}
	else
	{
		count_row = m1->count_row;
		count_column = m1->count_column;
		delete []data;
		data = new double[count_row*count_column];
		int row, column;
		for (row = 0; row < count_row; row++)
			for (column = 0; column < count_column; column++)
				SetData(row, column, m1->GetData(row, column));
		return this;
	}
}

Matrix * Matrix::CreateCofactor(int row, int column)
{
	if (IsRowAndColumnLegal(row, column))
	{
		MatrixP p = new Matrix;
		p->count_column = count_column-1;
		p->count_row = count_row-1;
		p->data = new double[p->count_row*p->count_column];

		int i, j;
		for (i = 0; i < row; i++)//top left
			for (j = 0; j < column; j++)
				p->SetData(i, j, GetData(i,j));

		for (i = row+1; i < count_row; i++)//down left
			for (j = 0; j < column; j++)
				p->SetData(i-1, j, GetData(i, j));

		for (i = 0; i < row; i++)//top right
			for (j = column+1; j < count_column; j++)
				p->SetData(i, j-1, GetData(i, j));

		for (i = row + 1; i < count_row; i++)//down right
			for (j = column + 1; j < count_column; j++)
				p->SetData(i-1, j - 1, GetData(i, j));
		return p;
	}
	else
		return NULL;
}

Matrix * Matrix::CreateSubMatrix(int top, int down, int left, int right)
{
	if (!(IsRowLegal(top) && IsRowLegal(down) && IsColumnLegal(left) && IsColumnLegal(right)))
		return NULL;
	MatrixP p = new Matrix;
	p->count_column = right-left+1;
	p->count_row = down-top+1;
	p->data = new double[p->count_row*p->count_column];
	int row, column;
	for (row = 0; row < p->count_row; row++)
		for (column = 0; column < p->count_column; column++)
			p->SetData(row, column,GetData(top+row, left+column));
	return p;
}

Matrix * Matrix::TransformElemRowSwap(int row1, int row2)
{
	if (IsRowLegal(row1) && IsRowLegal(row2))
	{
		int i;
		double temp;
		for (i = 0; i < count_column; i++)
		{
			temp = GetData(row1, i);
			SetData(row1, i, GetData(row2, i));
			SetData(row2, i, temp);
		}
		return this;
	}
	return NULL;
}

Matrix * Matrix::TransformElemRowMultiply(int row, double factor)
{
	if (IsRowLegal(row))
	{
		int i;
		for (i = 0; i < count_column; i++)
		{
			SetData(row, i, GetData(row, i) * factor);
		}
		return this;
	}
	return NULL;
}

Matrix * Matrix::TransformElemRowMultiplyPlus(int row_origin, double factor, int row_target)
{
	if (IsRowLegal(row_origin) && IsRowLegal(row_target))
	{
		int i;
		for (i = 0; i < count_column; i++)
		{
			SetData(row_target, i, GetData(row_origin, i) * factor + GetData(row_target, i));
		}
		return this;
	}
	return NULL;
}

Matrix * Matrix::TransformTransposition()
{
	MatrixP m = CreateTransposition();
	CopyData(m);
	delete m;
	return this;
}

Matrix * Matrix::TransformRowEchelon()
{
	int a;
	TransformRowEchelon(a);
	return this;
}

Matrix * Matrix::TransformRowEchelon(int &rank)
{
	int row, column;
	rank = -1;
	for (column = 0; column < count_column && rank!=count_row; column++)
	{
		for (row = rank+1; row < count_row; row++)
		{
			if (abs(GetData(row, column)) > EPS)
				break;
		}
		if (row == count_row)
		{
			continue;
		}
		else
		{
			rank++;
			if (row != rank)
				TransformElemRowSwap(rank, row);
			TransformElemRowMultiply(rank, 1.0 / GetData(rank, column));
			for (row = rank + 1; row < count_row; row++)
				TransformElemRowMultiplyPlus(rank, -GetData(row, column), row);
		}
	}
	rank++;
	return this;
}

Matrix * Matrix::Plus(Matrix * m1, Matrix * m2)
{
	if (m1->GetCountColumn() != m2->GetCountColumn() || m1->GetCountRow() != m2->GetCountRow())
		return NULL;
	MatrixP result=new Matrix;
	result->count_column = m1->count_column;
	result->count_row = m1->count_row;
	result->data= new double[result->count_row*result->count_column];
	int row, column;
	for (row = 0; row < result->count_row; row++)
		for (column = 0; column < result->count_column; column++)
			result->SetData(row, column, m1->GetData(row, column) + m2->GetData(row, column));
	return result;
}

MatrixP Matrix::Plus(Matrix *m1)
{
	MatrixP temp = Plus(this, m1);
	if (temp != NULL)
	{
		CopyData(temp);
		delete temp;
		return this;
	}
	return NULL;
}

Matrix * Matrix::Multiply(Matrix * m1, Matrix * m2)
{
	if (m1->GetCountColumn() != m2->GetCountRow())
		return NULL;
	MatrixP result = new Matrix;
	result->count_column = m2->count_column;
	result->count_row = m1->count_row;
	result->data = new double[result->count_row*result->count_column];
	int row, column,i;
	double sum;
	for (row = 0; row < result->count_row; row++)
		for (column = 0; column < result->count_column; column++)
		{
			sum = 0;
			for (i = 0; i < m1->count_column; i++)
				sum += m1->GetData(row, i) * m2->GetData(i, column);
			result->SetData(row, column, sum);
		}
	return result;
}

Matrix * Matrix::Multiply(Matrix * m1, double number)
{
	MatrixP result = new Matrix;
	result->count_column = m1->count_column;
	result->count_row = m1->count_row;
	result->data = new double[result->count_row*result->count_column];
	int row, column;
	for (row = 0; row < result->count_row; row++)
		for (column = 0; column < result->count_column; column++)
			result->SetData(row, column, m1->GetData(row, column) *number);
	return result;
}

MatrixP Matrix::Multiply(Matrix * m1)
{
	MatrixP temp = Multiply(this, m1);
	if (temp != NULL)
	{
		CopyData(temp);
		delete[] temp;
		return this;
	}
	return NULL;
}

Matrix * Matrix::Multiply(double number)
{
	int row, column;
	for (row = 0; row < count_row; row++)
		for (column = 0; column < count_column; column++)
			SetData(row, column, GetData(row, column) *number);
	return this;
}

Matrix * Matrix::Power(Matrix * m, int index)
{
	if (index < 0 || m->count_column!=m->count_column)
		return NULL;

	switch (index)
	{
	case 0:
		return CreateDiagonalAllSameNumber(m->count_column, 1);
	default:
		MatrixP temp = m->CreateCopy(), result=CreateDiagonalAllSameNumber(m->count_column, 1);
		int digital = 1;

		while (digital <=index)
		{
			if (index & digital)
				result->Multiply(temp);
			temp->Multiply(temp);
			digital=digital << 1;
		}
		return result;
	}
}

Matrix * Matrix::Power(int index)
{
	MatrixP temp = Power(this,index);
	if (temp != NULL)
	{
		CopyData(temp);
		delete[] temp;
		return this;
	}
	return NULL;
}

Matrix *Matrix::CreateTransposition()
{
	MatrixP m = new Matrix;
	int row, column;
	m->count_column = count_row;
	m->count_row = count_column;
	m->data = new double[count_column*count_row];
	for(row=0;row<count_row;row++)
		for (column=0; column < count_column; column++)
		{
			m->SetData(column, row, GetData(row, column));
		}
	return m;
}

Matrix * Matrix::CreateAugmentedMatrix(Vector *right)
{
	
	if (right!=NULL && (count_row != right->GetCountRow() || right->GetCountColumn() != 1))
		return NULL;
	MatrixP m = new Matrix;
	m->count_column = count_column+1;
	m->count_row = count_row;
	m->data = new double[m->count_column*m->count_row];
	int row, column;
	for (row = 0; row < count_row; row++)
	{
		for (column = 0; column < count_column; column++)
		{
			m->SetData(row, column, GetData(row, column));
		}
		if(right==NULL)
			m->SetData(row, column, 0);
		else
		    m->SetData(row, column, right->GetData(row, 0));
	}
	return m;
}

double Matrix::GetDeterminantExpansion()
{
	if (count_column != count_row)
		return 0.0;
	if (count_column == 1)
		return GetData(0, 0);
	MatrixP confactor;
	int i,sign=1;
	double sum = 0;

	for (i = 0; i < count_column; i++)
	{
		confactor = CreateCofactor(0, i);
		sum += sign*confactor->GetDeterminantExpansion()*GetData(0,i);
		sign *= -1;
		delete confactor;
	}
	return sum;
}

double Matrix::GetDeterminantDefinition()
{
	if (count_column != count_row)
		return 0.0;

	int *hash = new int[count_row], *list = new int[count_row];
	memset(hash, 0, sizeof(int)*count_row);
	int index = 0;
	double sum = 0;

	DeterminantDefinitionRecursion(list, hash, index, sum);

	delete hash, list;
	return sum;
}

double Matrix::GetDeterminantElementaryTransformation()
{
	if (count_column != count_row)
		return 0.0;
	MatrixP m = this->CreateCopy();
	int row,column;
	//transform
	for (column = 0; column < count_column-1; column++)
	{
		for (row = column; row < count_row; row++)
		{
			if (abs(m->GetData(row, column)) > EPS)
				break;
		}
		if (row == count_row)
		{
			delete m;
			return 0.0;
		}
		else
		{
			if (row != column)
				m->TransformElemRowSwap(row, column);
			for (row = column + 1; row < count_row; row++)
				m->TransformElemRowMultiplyPlus(column, -m->GetData(row, column) / m->GetData(column, column), row);
		}
	}
	//get result
	double result = 1;
	for (row = 0; row < m->count_column; row++)
		result *= m->GetData(row, row);

	delete m;
	return result;
		
}

Matrix * Matrix::CreateAdjoint()
{
	if (count_column != count_row)
		return NULL;
	MatrixP m = new Matrix,temp;
	m->count_column = count_column;
	m->count_row = count_row;
	m->data = new double[count_column*count_row];

	int row, column;
	for (row = 0; row < count_row; row++)
	{
		for (column = 0; column < count_column; column++)
		{
			temp = CreateCofactor(row, column);
			m->SetData(column, row, ((row+column)%2*-2+1)*temp->GetDeterminantElementaryTransformation());
			delete temp;
		}
	}
	return m;
}

Matrix * Matrix::CreateReverseFromAdjoint()
{
	if (count_row != count_column)
		return NULL;
	double determinant = GetDeterminantElementaryTransformation();
	if (abs(determinant) < EPS)
		return NULL;
	
	MatrixP m = CreateAdjoint()->Multiply(1.0 / determinant);
	return m;
}

Matrix * Matrix::CreateReverseFromElemTransform()
{
	if (count_column != count_row)
		return NULL;
	MatrixP right = CreateDiagonalAllSameNumber(count_column),origin=CreateCopy();
	int row, column;
	double temp;

	//左下边变成0,主对角线变成1
	for (column = 0; column < count_column ; column++)
	{
		for (row = column; row < count_row; row++)
		{
			if (abs(origin->GetData(row, column)) > EPS)
				break;
		}
		if (row == count_row)
		{
			delete origin;
			delete right;
			return NULL;
		}
		else
		{
			if (row != column)
			{
				origin->TransformElemRowSwap(row, column);
				right->TransformElemRowSwap(row, column);;
			}
			temp = 1.0 / origin->GetData(column, column);
			origin->TransformElemRowMultiply(column, temp);
			right->TransformElemRowMultiply(column, temp);
			for (row = column + 1; row < count_row; row++)
			{

				temp = -origin->GetData(row, column);
				origin->TransformElemRowMultiplyPlus(column,temp, row);
				right->TransformElemRowMultiplyPlus(column, temp, row);
			}
		}
	}
	//主对角线变成1
	/*for (row = 0; row < count_row; row++)
	{
		temp = 1.0/origin->GetData(row, row);
		origin->TransformElemRowMultiply(row, temp);
		right->TransformElemRowMultiply(row, temp);
	}*/
	//右下角变成0
	for (column = count_column - 1; column > 0; column--)
	{
		for (row = column - 1; row >= 0; row--)
		{
			temp = -origin->GetData(row, column);
			origin->TransformElemRowMultiplyPlus(column, temp, row);
			right->TransformElemRowMultiplyPlus(column, temp, row);
		}
	}
	delete origin;
	return right;
}

double Matrix::GetTrace()
{
	if (count_row != count_column)
		return 0;
	int i;
	double sum = 0;
	for (i = 0; i < count_column; i++)
		sum += GetData(i, i);
	return sum;
}

int Matrix::GetRank()
{
	int rank;
	MatrixP m= CreateCopy();
	m->TransformRowEchelon(rank);
	delete m;
	return rank;
}

void Matrix::Show(Matrix * p)
{
	int i, j;
	double temp;
	if (p->count_row*p->count_column == 0)
		cout << "矩阵为空" << endl;
	else
	{
		for (i = 0; i < p->count_row; i++)
		{
			putchar('(');
			for (j = 0; j < p->count_column; j++)
			{
				//if (j != 0)
				//	cout << '\t';
				temp=p->GetData(i,j);
				if (fabs(temp) < EPS)
					cout << 0 << '\t';
				else
					cout << setprecision(3)<< temp << '\t';
			}
			cout << ')' << endl;
		}
	}
	cout << endl;
}

void Matrix::Show()
{
	Show(this);
}

void Matrix::SolveEquation(Vector *v)
{
	MatrixP augment = CreateAugmentedMatrix(v);
	if(augment==NULL)
		cout << "方程错误" << endl;
	int rank, row, column, row2;
	augment->TransformRowEchelon(rank);
	
	int *not_free_varible = new int[count_column];
	int *first_1_position = new int[rank];
	memset(not_free_varible, 0, sizeof(int)*count_column);
	for(row=0;row<rank;row++)
		for (column = 0; column < augment->count_column; column++)
		{
			if (abs(augment->GetData(row, column) - 1) < EPS)
			{
				first_1_position[row] = column;
				not_free_varible[column] = true;
				column = augment->count_column;
			}
		}

	if (first_1_position[rank - 1] == augment->count_column-1)
	{
		cout << "方程无解" << endl << endl;
	}
	else
	{//最后的初等变换
		for (row = rank - 1; row >= 0; row--)
		{
			for (row2 = row - 1; row2 >= 0; row2--)
				augment->TransformElemRowMultiplyPlus(row, -augment->GetData(row2, first_1_position[row]), row2);
		}
		//开始输出结果
		int count_free_varible = 0;
		VectorP result;
		for (column = 0; column < count_column; column++)
		{
			if (!not_free_varible[column])
			{
				count_free_varible++;
				result = (VectorP)CreateAllSameNumber(count_column, 1, 0);
				for (row = 0; row < rank; row++)
					result->SetData(first_1_position[row], 0, -augment->GetData(row, column));
				result->SetData(column, 0, 1.0);
				if (count_free_varible != 1)
					cout << " + ";
				cout << 'k' << count_free_varible << " ";
				result->Show();
				delete result;
			}
		}
		if (v != NULL)
		{
			result = (VectorP)CreateAllSameNumber(count_column, 1, 0);
			for (row = 0; row < rank; row++)
				result->SetData(first_1_position[row], 0, augment->GetData(row, augment->count_column - 1));
			if (count_free_varible != 0)
				cout << " + ";
			result->Show();
			delete result;
			cout << endl << endl;
		}
		else
		{
			if (count_free_varible == 0)
			{
				result = (VectorP)CreateAllSameNumber(count_column, 1, 0);
				result->Show();
				delete result;
			}
		}
	}

	delete [] first_1_position, not_free_varible;
	delete augment;
}

Matrix::Matrix()
{
	count_row = 0;
	count_column = 0;
	data = NULL;
}


Matrix::~Matrix()
{	
	delete []data;//由于data是数组，必须使用data[]来释放
}

int Matrix::IsRowLegal(int row)
{
	return (0 <= row && row < count_row);
}

int Matrix::IsColumnLegal(int column)
{
	return (0 <= column && column < count_column);
}

int Matrix::IsRowAndColumnLegal(int row, int column)
{
	return IsRowLegal(row) && IsColumnLegal(column);
}

void Matrix::DeterminantDefinitionRecursion(int *list, int * hash, int & index, double &sum)
{
	int i;
	if (index == count_column)
	{
		double product = 1 - 2 * (ReverseNumber(list, index) % 2);
		for (i = 0; i < count_column; i++)
		{
			product *= GetData(i, list[i]);
		}
		sum += product;
	}
	else
	{
		for (i = 0; i < count_column; i++)
		{
			if (!hash[i])
			{
				hash[i] = true;
				list[index++] = i;
				DeterminantDefinitionRecursion(list,hash,index,sum);
				index--;
				hash[i] = false;
			}
		}
	}
}

long Matrix::ReverseNumber(int * list, int length)
{
	int i, j;
	long result = 0;
	for (i = 0; i < length; i++)
		for (j = i+1; j < length; j++)
		{
			if (list[i] > list[j])
				result++;
		}
	return result;
}


int Matrix::GetCountRow()
{
	return count_row;
}

int Matrix::GetCountColumn()
{
	return count_column;
}

double Matrix::GetData(int row, int column)
{
	if (IsRowAndColumnLegal(row, column))
	{
		return data[row*count_column + column];
	}
	return 0;
}

int Matrix::SetData(int row, int column,double data_to_store)
{
	if (IsRowAndColumnLegal(row, column))
	{
		data[row*count_column + column]= data_to_store;
		return 0;
	}
	return 1;
}
