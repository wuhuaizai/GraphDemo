#pragma once
#include"Shape.h"
#include "GlobalUtil.h"
class Circle:public Shape
{
public:
	Circle();
	Circle(Circle* pCircle);
	Circle(CPoint center, double radius,COLORREF color,int penWidth);
	~Circle();
private:
	CPoint			o;
	CPoint			temp_o;
	double			radius;
	double			temp_radius;
public:
	void			Draw(CDC* pDC);
	void			Draw(CDC* pDC, COLORREF color);
	Shape*			Move(double stepx, double stepy);
	Shape*			Rotate(CPoint center,double flAngle);
	Shape*			Magnify(CPoint center,double flScale);
	Shape*			TopToBottom(CRect rect);
	Shape*			LeftToRight(CRect rect);
	Shape			GetCopy();
	CRect			GetBoundaryRect();
	CPoint			GetCenterPoint();
	int				GraphType() { return 3;}
	CPoint			getO();
	double			getRadius();
	void			setO(CPoint center);
	void			setRadius(double radius);
	void			bresenhamCircle(CDC* pDC, CPoint p, int r, int width, COLORREF color);
	void			CirclePoint(CDC* pDC, int x0, int y0, int x, int y, int width, COLORREF color);
	int				isInRect(CRect rect);
	void			RefreshData();
};

