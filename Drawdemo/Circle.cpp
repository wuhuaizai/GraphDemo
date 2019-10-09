#include "stdafx.h"
#include "Circle.h"

Circle::Circle():Shape()
{
	isSelected = false;
}
Circle::Circle(Circle* pCircle) {
	color = pCircle->color;
	penWidth = pCircle->penWidth;
	fillColor = pCircle->fillColor;
	angle = pCircle->angle;
	scale = pCircle->scale;
	centerPoint = pCircle->GetCenterPoint();
	o = pCircle->o;
	radius = pCircle->radius;
}
Circle::Circle(CPoint center, double radius,COLORREF color,int penWidth) :Shape(){
	o = center;
	temp_o = center;
	this->radius = radius;
	temp_radius = radius;
	this->color = color;
	this->penWidth = penWidth;
	fillColor = RGB(255, 255, 255);
	angle = 0.0;
	scale = 1.0;
	isSelected = false;
}

Circle::~Circle()
{
}
void Circle::Draw(CDC* pDC) {
	/*bresenhamCircle(pDC, o, radius, penWidth, color);*/
	CPen m_pen;//首先定义一个对象
	CPen *oldPen;
	m_pen.CreatePen(PS_SOLID, this->penWidth, this->color);//创建一个画笔(这里是实线画笔)
	oldPen = pDC->SelectObject(&m_pen);//将画笔对象选入DC，替换oldPen

	/*temp_o.x = (o.x - MagnifyCenter.x)*scale + MagnifyCenter.x;
	temp_o.y = (o.y - MagnifyCenter.y)*scale + MagnifyCenter.y;*/

	/*temp_o.x = ((o.x - RotateCenter.x)*cos(angle) - (o.y - RotateCenter.y)*sin(angle)) + RotateCenter.x;
	temp_o.y = ((o.y - RotateCenter.y)*cos(angle) + (o.x - RotateCenter.x)*sin(angle)) + RotateCenter.y;*/
	//temp_radius = radius*scale;
	//_cprintf("now magnify %d %d\n", temp_o.x, temp_o.y);
	CRect rect = CRect(temp_o.x-temp_radius,temp_o.y-temp_radius,temp_o.x+temp_radius,temp_o.y+temp_radius);
	CPoint startAndEnd = CPoint(temp_o.x - temp_radius,temp_o.y);
	pDC->Arc(&rect, startAndEnd, startAndEnd);
	pDC->SelectObject(oldPen);
}
void Circle::Draw(CDC* pDC,COLORREF tempcolor) {
	/*bresenhamCircle(pDC, o, radius, penWidth, color);*/
	CPen m_pen;//首先定义一个对象
	CPen *oldPen;
	m_pen.CreatePen(PS_SOLID, this->penWidth, tempcolor);//创建一个画笔(这里是实线画笔)
	oldPen = pDC->SelectObject(&m_pen);//将画笔对象选入DC，替换oldPen

	/*temp_o.x = (o.x - MagnifyCenter.x)*scale + MagnifyCenter.x;
	temp_o.y = (o.y - MagnifyCenter.y)*scale + MagnifyCenter.y;

	temp_o.x = ((o.x - RotateCenter.x)*cos(angle) - (o.y - RotateCenter.y)*sin(angle)) + RotateCenter.x;
	temp_o.y = ((o.y - RotateCenter.y)*cos(angle) + (o.x - RotateCenter.x)*sin(angle)) + RotateCenter.y;
	temp_radius = radius*scale;
*/
	CRect rect = CRect(temp_o.x - temp_radius, temp_o.y - temp_radius, temp_o.x + temp_radius, temp_o.y + temp_radius);
	CPoint startAndEnd = CPoint(temp_o.x - temp_radius, temp_o.y);
	pDC->Arc(&rect, startAndEnd, startAndEnd);
	pDC->SelectObject(oldPen);
}
void Circle::bresenhamCircle(CDC* pDC, CPoint p, int r, int width, COLORREF color) {
	int x, y, d;
	d = 1.25 - r; x = 0; y = r;
	for (x = 0; x <= y; x++) {
		CirclePoint(pDC, p.x, p.y, x, y, width, color);
		if (d < 0)
			d += 2 * x + 3;
		else {
			d += 2 * (x - y) + 5;
			y--;
		}
	}
}
void Circle::CirclePoint(CDC* pDC, int x0, int y0, int x, int y, int width, COLORREF color) {
	CPen m_pen;//首先定义一个对象
	CPen *oldPen;
	m_pen.CreatePen(PS_SOLID, width, color);//创建一个画笔(这里是实线画笔)
	oldPen = pDC->SelectObject(&m_pen);//将画笔对象选入DC，替换oldPen
	
	if (x == 0 && y == radius) {
		pDC->MoveTo((x0 + x), (y0 + y));
		pDC->LineTo((x0 + x), (y0 + y));

		pDC->MoveTo((x0 + y), (y0 - x));
		pDC->LineTo((x0 + y), (y0 - x));

		pDC->MoveTo((x0 - y), (y0 - x));
		pDC->LineTo((x0 - y), (y0 - x));

		pDC->MoveTo((x0 - x), (y0 - y));
		pDC->LineTo((x0 - x), (y0 - y));
	}
	pDC->MoveTo((x0 + x), (y0 + y));
	pDC->LineTo((x0 + x), (y0 + y));

	pDC->MoveTo((x0 + y), (y0 + x));
	pDC->LineTo((x0 + y), (y0 + x));

	pDC->MoveTo((x0 + y), (y0 - x));
	pDC->LineTo((x0 + y), (y0 - x));

	pDC->MoveTo((x0 + x), (y0 - y));
	pDC->LineTo((x0 + x), (y0 - y));

	pDC->MoveTo((x0 - x), (y0 - y));
	pDC->LineTo((x0 - x), (y0 - y));

	pDC->MoveTo((x0 - y), (y0 - x));
	pDC->LineTo((x0 - y), (y0 - x));

	pDC->MoveTo((x0 - y), (y0 + x));
	pDC->LineTo((x0 - y), (y0 + x));

	pDC->MoveTo((x0 - x), (y0 + y));
	pDC->LineTo((x0 - x), (y0 + y));

	pDC->SelectObject(oldPen);
}
Shape* Circle::Move(double stepx, double stepy) {
	o.x += stepx;
	o.y += stepy;
	temp_o.x += stepx;
	temp_o.y += stepy;
	return this;
}
Shape* Circle::Rotate(CPoint center,double flAngle) {
	RotateCenter = center;
	flAngle = PI / 180.0*flAngle;
	angle += flAngle;
	temp_o.x = ((o.x - RotateCenter.x)*cos(angle) - (o.y - RotateCenter.y)*sin(angle)) + RotateCenter.x;
	temp_o.y = ((o.y - RotateCenter.y)*cos(angle) + (o.x - RotateCenter.x)*sin(angle)) + RotateCenter.y;
	return this;
}
Shape* Circle::Magnify(CPoint center,double flScale) {
	scale = flScale;
	MagnifyCenter = center;
	temp_o.x = (o.x - MagnifyCenter.x)*scale + MagnifyCenter.x;
	temp_o.y = (o.y - MagnifyCenter.y)*scale + MagnifyCenter.y;
	temp_radius = radius*scale;
	_cprintf("after magnify %d %d\n", temp_o.x, temp_o.y);

	_cprintf("\n\n\n");
	return this;
}
Shape* Circle::TopToBottom(CRect rect) {
	temp_o.y = rect.top+rect.bottom-temp_o.y;
	o.y =temp_o.y;
	return this;
}
Shape* Circle::LeftToRight(CRect rect) {
	temp_o.x = rect.left + rect.right - temp_o.x;
	o.x = temp_o.x;
	return this;
}
Shape Circle::GetCopy() {
	return Circle(this);
}
CRect Circle::GetBoundaryRect() {
	CRect rect(CPoint(o.x - radius, o.y - radius), CPoint(o.x + radius, o.y + radius));
	return rect;
}
CPoint Circle::GetCenterPoint() {
	return o;
}
CPoint Circle::getO() {
	return this->o;
}
double	Circle::getRadius() {
	return radius;
}
void Circle::setO(CPoint center) {
	o = center;
}
void Circle::setRadius(double radius) {
	this->radius = radius;
}
int Circle::isInRect(CRect rect) {
	//int result = 0;
	////if(fillColor==RGB(255,255,255))
	//if (PtDistance(rect.TopLeft(), temp_o) < temp_radius) result++;
	//if (PtDistance(rect.BottomRight(), temp_o) < temp_radius) result++;
	//if (PtDistance(CPoint(rect.right,rect.top), temp_o) < temp_radius) result++;
	//if (PtDistance(CPoint(rect.left,rect.bottom), temp_o) < temp_radius) result++;
	int nRltVal = 0;
	CPoint ptRectLT = rect.TopLeft();
	CPoint ptRectRB = rect.BottomRight();
	CPoint ptRectLB, ptRectRT;
	ptRectLB.x = rect.left;
	ptRectLB.y = rect.bottom;
	ptRectRT.x = rect.right;
	ptRectRT.y = rect.top;//矩形四点

	CPoint ptCircleCenter = temp_o;//圆心

															//求四条矩形边是否有和圆相交/在圆内	
	float flX[4][2], flY[4][2];
	flY[0][0] = rect.top;
	flY[1][0] = rect.bottom;
	flY[0][1] = rect.top;
	flY[1][1] = rect.bottom;
	if (rect.left>temp_o.x) {
		flX[0][0] = rect.left;
		flX[1][0] = rect.left;
		flX[0][1] = rect.right;
		flX[1][1] = rect.right;
	}
	else if (rect.right<temp_o.x) {
		flX[0][0] = rect.right;
		flX[1][0] = rect.right;
		flX[0][1] = rect.left;
		flX[1][1] = rect.left;
	}
	else {
		flX[0][0] = temp_o.x;
		flX[1][0] = temp_o.x;
		if (temp_o.x - rect.left > rect.right - temp_o.x) {
			flX[0][1] = rect.left;
			flX[1][1] = rect.left;
		}
		else {
			flX[0][1] = rect.right;
			flX[1][1] = rect.right;
		}
	}
	flX[2][0] = rect.left;
	flX[3][0] = rect.right;
	flX[2][1] = rect.left;
	flX[3][1] = rect.right;
	if (rect.top>temp_o.y) {
		flY[2][0] = rect.top;
		flY[3][0] = rect.top;
		flY[2][1] = rect.bottom;
		flY[3][1] = rect.bottom;
	}
	else if (rect.bottom<temp_o.y) {
		flY[2][0] = rect.bottom;
		flY[3][0] = rect.bottom;
		flY[2][1] = rect.top;
		flY[3][1] = rect.top;
	}
	else {
		flY[2][0] = temp_o.y;
		flY[3][0] = temp_o.y;
		if (temp_o.y - rect.top > rect.bottom - temp_o.y) {
			flX[2][1] = rect.top;
			flX[3][1] = rect.top;
		}
		else {
			flX[2][1] = rect.bottom;
			flX[3][1] = rect.bottom;
		}
	}
	int flag = 0;
	if (PtDistance(CPoint(flX[0][0], flY[0][0]), temp_o) <= temp_radius) {
		if (PtDistance(CPoint(flX[0][1], flY[0][1]), temp_o)>temp_radius) {
			nRltVal |= 1;//cut
		}
		else {
			nRltVal |= 2;
		}
	}
	else {
		flag++;
	}
	if (PtDistance(CPoint(flX[1][0], flY[1][0]), temp_o) <= temp_radius) {
		if (PtDistance(CPoint(flX[1][1], flY[1][1]), temp_o)>temp_radius) {
			nRltVal |= 1;//cut
		}
		else {
			nRltVal |= 2;
		}
	}
	else {
		flag++;
	}
	if (PtDistance(CPoint(flX[2][0], flY[2][0]), temp_o) <= temp_radius) {
		if (PtDistance(CPoint(flX[2][1], flY[2][1]), temp_o)>temp_radius) {
			nRltVal |= 1;//cut
		}
		else {
			nRltVal |= 2;
		}
	}
	else {
		flag++;
	}
	if (PtDistance(CPoint(flX[3][0], flY[3][0]), temp_o) <= temp_radius) {
		if (PtDistance(CPoint(flX[3][1], flY[3][1]), temp_o)>temp_radius) {
			nRltVal |= 1;//cut
		}
		else {
			nRltVal |= 2;
		}
	}
	else {
		flag++;
	}
	if (nRltVal == 3) {
		nRltVal = 1;
	}
	if (flag == 4 && rect.PtInRect(ptCircleCenter)) {
		nRltVal = 2;
	}
	return nRltVal;
	
}
void Circle::RefreshData() {
	o = temp_o;
	radius = temp_radius;
	scale = 1.0;
	angle = 0.0;
}
