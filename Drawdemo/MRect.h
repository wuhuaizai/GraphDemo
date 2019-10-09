#pragma once
#include <vector>
#include "Shape.h"
#include <algorithm>
using namespace std;
class MRect :public Shape
{
public:
	MRect();
	MRect(CPoint LT, CPoint RB,COLORREF color,int penWidth);
	MRect(MRect* pMRect);
	~MRect();
private:
	CPoint			m_LeftTop;
	CPoint			m_RightBottom;
	CPoint			m_LeftBottom;
	CPoint			m_RightTop;

	CPoint			temp_LeftTop;
	CPoint			temp_RightBottom;
	CPoint			temp_LeftBottom;
	CPoint			temp_RightTop;

	double			m_Left;
	double			m_Right;
	double			m_Top;
	double			m_Bottom;
public:
	void			Draw(CDC* pDC);
	void			Draw(CDC* pDC, COLORREF color);
	Shape*			Move(double stepx, double stepy);
	Shape*			MatrixMove(double stepx, double stepy);
	Shape*			Rotate(CPoint center,double flAngle);
	Shape*			MatrixRotate(CPoint center, double flAngle);
	Shape*			Magnify(CPoint center,double flScale);
	Shape*			MatrixMagnify(CPoint center, double flScale);
	Shape*			TopToBottom(CRect rect);
	Shape*			LeftToRight(CRect rect);
	CRect			GetBoundaryRect();
	CPoint			GetCenterPoint();
	MRect			GetCopy();
	int				GraphType();
	CPoint			getLeftTop();
	CPoint			getRightBottom();
	void			setLeftTop(CPoint LT);
	void			setRightBottom(CPoint RB);
	void			Draw_BresenhamLine(CPoint ptStart, CPoint ptEnd, CDC *pDC, int penWidth, COLORREF color);
	int				isInRect(CRect rect);
	double			Left();
	double			Right();
	double			Top();
	double			Bottom();
	void			Draw_Line(CPoint ptStart, CPoint ptEnd, CDC *pDC, int penWidth, COLORREF color);
	void			RefreshData();
};

