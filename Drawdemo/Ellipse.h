#pragma once
#include "Shape.h"
#include "GlobalUtil.h"
class MEllipse:public Shape
{
public:
	MEllipse();
	MEllipse(MEllipse*MEllipse);
	MEllipse(CPoint center,double a,double b,COLORREF color,int penWidth);
	~MEllipse();
private:
	CPoint			o;//��Բ����
	double			a;//�����һ��
	double			b;//�����һ��
	CPoint			temp_o;
	double			temp_a;
	double			temp_b;
	double			temp_angle;
	double			anglePre;
public:
	void			Draw(CDC* pDC);
	void			Draw(CDC* pDC, COLORREF color);
	Shape*			Move(double stepx, double stepy);
	Shape*			Rotate(CPoint center,double flAngle);
	Shape*			Magnify(CPoint center,double flScale);
	Shape*			TopToBottom(CRect rect);
	Shape*			LeftToRight(CRect rect);
	CRect			GetBoundaryRect();
	CPoint			GetCenterPoint();
	MEllipse		GetCopy();
	int				GraphType();
	CPoint			GetO();
	double			GetA();
	double			GetB();
	void			SetO(CPoint center);
	void			SetA(double a);
	void			SetB(double b);
	int				isInRect(CRect rect);
	//����Բ����
	void			Bresenham_MEllipse(CDC* pDC, CPoint p, int a, int b, int width, COLORREF color);
	void			MEllipsePlot(CDC* pDC, int x0, int y0, int x, int y, int width, COLORREF color);
	void			RefreshData();
	int				IsPointinRegion(CPoint point);

};

