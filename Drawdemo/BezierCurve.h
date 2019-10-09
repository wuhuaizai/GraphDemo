#pragma once
#include "Shape.h"
#include "GlobalUtil.h"
class BezierCurve:public Shape
{
public:
	BezierCurve();
	~BezierCurve();
	BezierCurve(BezierCurve * curve);
	BezierCurve(vector<CPoint>pCurves ,COLORREF color, int penWidth);
private:
	vector<CPoint>		m_Points;
	vector<CPoint>		temp_Points;
public:
	void	Draw(CDC* pDC);
	void	Draw(CDC* pDC, COLORREF tempColor);

	Shape*	Move(double stepx, double stepy);
	Shape*	Rotate(CPoint center, double flAngle);
	Shape*	Magnify(CPoint center, double flScale);
	Shape*	TopToBottom(CRect rect);
	Shape*	LeftToRight(CRect rect);
	Shape	GetCopy();
	CRect	GetBoundaryRect();
	CPoint	GetCenterPoint();
	int		GraphType() { return 1; }
	void	RefreshData();
	int		isInRect(CRect rect);
	void	setPoints(vector<CPoint>&points);
	vector<CPoint> getPoints();
	void	bezier(CDC *pDC);
};

