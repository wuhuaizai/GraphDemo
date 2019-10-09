#include "stdafx.h"
#include "Matrix.h"


CMatrix::CMatrix(int row, int column)
{
	this->row = row;
	this->column = column;
	vector<double>temp(row*column, 0.0);
	this->m = temp;
}

CMatrix::CMatrix(int row, int column, vector<double>temp) {
	this->row = row;
	this->column = column;
	this->m = temp;
}

CMatrix::CMatrix(CPoint& point) {
	this->row = 1;
	this->column = 3;
	this->m = { point.x*1.0,point.y*1.0,1.0 };
}

CMatrix::CMatrix(const CMatrix& b) {
	m = b.m;
	row = b.row;
	column = b.column;
}

CMatrix CMatrix::operator + (CMatrix b) const {
	if (row != b.row || column != b.column)
		throw runtime_error(string{ "row or column not match!" });
	int n = m.size();
	vector<double>res(n, 0.0);
	for (int i = 0; i<n; ++i)
		res[i] = m[i] + b.m[i];
	return CMatrix(row, column, res);
}

CMatrix CMatrix::operator * (CMatrix b) {
	if (column != b.row) {
		throw runtime_error(string{ "a.column not equal b.row!" });
	}
	CMatrix res = CMatrix(row, b.column);
	for (int i = 0; i<row; ++i)
		for (int j = 0; j<b.column; ++j)
			for (int k = 0; k<column; ++k)
				res.m[i*column + j] += m[i*column + k] * b.m[k*b.column + j];
	return res;
}

void CMatrix::show() {
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < column; ++j)
			_cprintf("%lf%c", m[i*column + j], " \n"[j == column - 1]);
	_cprintf("\n");
}

CMatrix::~CMatrix()
{

}

