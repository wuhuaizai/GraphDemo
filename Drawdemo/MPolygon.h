#pragma once
#include<vector>
#include "Shape.h"
#include<algorithm>
#include "conio.h"
using namespace std;
class MPolygon:public Shape
{
public:
	MPolygon();
	MPolygon(vector<CPoint> vertices,COLORREF color,int penWidth);
	MPolygon(MPolygon *pMPolygon);
	~MPolygon();
private:
	vector<CPoint>vertices;
	vector<CPoint>temp_vertices;
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
	MPolygon		GetCopy();
	int				GraphType();
	vector<CPoint>	GetVertices();
	void			SetVertices(vector<CPoint>& vertices);
	void			Draw_BresenhamLine(CPoint ptStart, CPoint ptEnd, CDC *pDC, int penWidth, COLORREF color);
	int				isInRect(CRect rect);
	void			RefreshData();
};

