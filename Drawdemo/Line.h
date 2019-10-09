#pragma once
#include <vector>
#include<algorithm>
#include"Shape.h"
#include "conio.h"
using namespace std;
#define PI 3.14159265358979323846
class CLine:public Shape
{
public:
	CLine();
	CLine(CLine* pLine);
	CLine(CPoint s, CPoint e,COLORREF color,int penWidth);
	~CLine();
private:
	CPoint			m_Start;
	CPoint			m_End;
	CPoint			temp_Start;
	CPoint			temp_End;
public:
public:
	void	Draw(CDC* pDC);
	void	Draw(CDC* pDC, COLORREF tempColor);
	Shape*	Move(double stepx, double stepy);
	Shape*	MatrixMove(double stepx, double stepy);
	Shape*	Rotate( CPoint center,double flAngle);
	Shape*	MatrixRotate(CPoint center, double flAngle);
	Shape*	Magnify(CPoint center, double flScale);
	Shape*	MatrixMagnify(CPoint center, double flScale);
	Shape*	TopToBottom( CRect rect);
	Shape*	LeftToRight( CRect rect);
	Shape	GetCopy();
	CRect	GetBoundaryRect();
	CPoint	GetCenterPoint();
	int		GraphType() { return 1; }
	void Draw_BresenhamLine(CPoint ptStart, CPoint ptEnd, CDC *pDC, int penWidth, COLORREF color);
	void Draw_Line(CPoint ptStart, CPoint ptEnd, CDC *pDC, int penWidth, COLORREF color);
	int		isInRect(CRect rect);
	CPoint getStartPoint();
	CPoint getEndPoint();
	void setStart(CPoint start);
	void setEnd(CPoint end);
	void RefreshData();
	bool GetIsSelect();
	void SetSelected(bool state);
};

