#pragma once
#include<vector>
#include "conio.h"
using namespace std;

class CMatrix
{
public:
	vector<double>m;
	int row;
	int column;
public:
	CMatrix(int row, int column);
	CMatrix(CPoint& point);
	CMatrix(int row, int column, vector<double>temp);
	CMatrix(const CMatrix& b);
	CMatrix operator + (CMatrix b) const;
	CMatrix operator * (CMatrix b);
	void show();
	~CMatrix();

};

