#include "stdafx.h"
#include "Ellipse.h"
#include "conio.h"

MEllipse::MEllipse():Shape()
{
	isSelected = false;
}
MEllipse::MEllipse(MEllipse* MEllipse) {
	color = MEllipse->color;
	penWidth = MEllipse->penWidth;
	fillColor = MEllipse->fillColor;
	angle = MEllipse->angle;
	scale = MEllipse->scale;
	o = MEllipse->GetO();
	a = MEllipse->GetA();
	b = MEllipse->GetB();
	isSelected = false;
	centerPoint = MEllipse->GetO();
}
MEllipse::MEllipse(CPoint center, double a, double b,COLORREF color,int penWidth ):Shape(){
	o = center;
	temp_o = center;
	this->a = a;
	temp_a = a;
	temp_b = b;
	this->b = b;
	scale = 1.0;
	angle = 0.0;
	temp_angle = angle;
	anglePre = 0.0;
	isSelected = false;
	this->penWidth = penWidth;
	this->color = color;
}

MEllipse::~MEllipse()
{
}

void MEllipse::Draw(CDC* pDC) {
	//Bresenham_MEllipse(pDC, o, a, b, penWidth, color);
	CPen m_pen;//首先定义一个对象
	CPen *oldPen;
	m_pen.CreatePen(PS_SOLID, this->penWidth, this->color);//创建一个画笔(这里是实线画笔)
	oldPen = pDC->SelectObject(&m_pen);//将画笔对象选入DC，替换oldPen

	Bresenham_MEllipse(pDC, temp_o, temp_a, temp_b, this->penWidth, this->color);
	pDC->SelectObject(oldPen);
}
void MEllipse::Draw(CDC* pDC,COLORREF tempcolor) {
	//Bresenham_MEllipse(pDC, o, a, b, penWidth, color);
	CPen m_pen;//首先定义一个对象
	CPen *oldPen;
	m_pen.CreatePen(PS_SOLID, this->penWidth , tempcolor);//创建一个画笔(这里是实线画笔)
	oldPen = pDC->SelectObject(&m_pen);//将画笔对象选入DC，替换oldPen

	Bresenham_MEllipse(pDC, temp_o, temp_a, temp_b, this->penWidth, tempcolor);
	pDC->SelectObject(oldPen);
}
Shape* MEllipse::Move(double stepx, double stepy) {
	this->o.x += stepx;
	this->o.y += stepy;
	this->temp_o.x += stepx;
	this->temp_o.y += stepy;
	return this;
}
Shape* MEllipse::Rotate(CPoint center,double flAngle) {
	RotateCenter = center;
	flAngle = PI / 180.0*flAngle;
	//angle += flAngle;
	temp_angle += flAngle;//
	angle = anglePre + temp_angle;//
	/*temp_o.x = ((o.x - RotateCenter.x)*cos(angle) - (o.y - RotateCenter.y)*sin(angle)) + RotateCenter.x;
	temp_o.y = ((o.y - RotateCenter.y)*cos(angle) + (o.x - RotateCenter.x)*sin(angle)) + RotateCenter.y;*/
	temp_o.x = ((o.x - RotateCenter.x)*cos(temp_angle) - (o.y - RotateCenter.y)*sin(temp_angle)) + RotateCenter.x;
	temp_o.y = ((o.y - RotateCenter.y)*cos(temp_angle) + (o.x - RotateCenter.x)*sin(temp_angle)) + RotateCenter.y;
	return this;
}
Shape* MEllipse::Magnify(CPoint center,double flScale) {
	MagnifyCenter = center;
	scale = flScale;
	temp_a = scale*a;
	temp_b = scale*b;
	/*a *= scale;
	b *= scale;*/
	temp_o.x = (o.x - MagnifyCenter.x)*scale + MagnifyCenter.x;
	temp_o.y = (o.y - MagnifyCenter.y)*scale + MagnifyCenter.y;
	return this;
}
Shape* MEllipse::TopToBottom(CRect rect) {
	RefreshData();
	anglePre = angle;
	anglePre = -anglePre;
	angle = anglePre;

	temp_o.y = rect.bottom + rect.top - temp_o.y;
	o.y = rect.bottom + rect.top - o.y;
	return this;
}
Shape* MEllipse::LeftToRight(CRect rect) {
	RefreshData();
	anglePre = angle;
	anglePre = PI - anglePre;
	angle = anglePre;

	temp_o.x = rect.left + rect.right - temp_o.x;
	o.x = rect.left + rect.right - o.x;
	return this;
}
CRect MEllipse::GetBoundaryRect() {
	//CPoint left=CPoint(temp_o.x)
	//return CRect(CPoint(o.x-a,o.y-b), CPoint(o.x+a,o.y+b));
	CRect rect;
	float flX[4], flY[4];
	float _a = temp_a;
	float _b = temp_b;
	flX[0] = temp_o.x;
	flX[1] = temp_o.x;
	flX[2] = temp_o.x - _a;
	flX[3] = temp_o.x + _a;
	flY[0] = temp_o.y - _b;
	flY[1] = temp_o.y + _b;
	flY[2] = temp_o.y;
	flY[3] = temp_o.y;

	float fx, fy, cosA, sinA;
	cosA = cos(angle);
	sinA = sin(angle);
	fx = (flX[0] - temp_o.x)*cosA - (flY[0] - temp_o.y)*sinA + temp_o.x;
	fy = (flY[0] - temp_o.y)*cosA + (flX[0] - temp_o.x)*sinA + temp_o.y;
	flX[0] = fx;
	flY[0] = fy;
	fx = (flX[1] - temp_o.x)*cosA - (flY[1] - temp_o.y)*sinA + temp_o.x;
	fy = (flY[1] - temp_o.y)*cosA + (flX[1] - temp_o.x)*sinA + temp_o.y;
	flX[1] = fx;
	flY[1] = fy;
	fx = (flX[2] - temp_o.x)*cosA - (flY[2] - temp_o.y)*sinA + temp_o.x;
	fy = (flY[2] - temp_o.y)*cosA + (flX[2] - temp_o.x)*sinA + temp_o.y;
	flX[2] = fx;
	flY[2] = fy;
	fx = (flX[3] - temp_o.x)*cosA - (flY[3] - temp_o.y)*sinA + temp_o.x;
	fy = (flY[3] - temp_o.y)*cosA + (flX[3] - temp_o.x)*sinA + temp_o.y;
	flX[3] = fx;
	flY[3] = fy;

	/*rect.left = 1000 * min(min(flX[0], flX[1]), min(flX[2], flX[3]));
	rect.right = 1000 * max(max(flX[0], flX[1]), max(flX[2], flX[3]));
	rect.top = 1000 * min(min(flY[0], flY[1]), min(flY[2], flY[3]));
	rect.bottom = 1000 * max(max(flY[0], flY[1]), max(flY[2], flY[3]));*/
	rect.left =min(min(flX[0], flX[1]), min(flX[2], flX[3]));
	rect.right = max(max(flX[0], flX[1]), max(flX[2], flX[3]));
	rect.top = min(min(flY[0], flY[1]), min(flY[2], flY[3]));
	rect.bottom = max(max(flY[0], flY[1]), max(flY[2], flY[3]));
	return rect;
}
CPoint MEllipse::GetCenterPoint() {
	return o;
}
MEllipse MEllipse::GetCopy() {
	return MEllipse(this);
}
int	 MEllipse::GraphType() {
	return 4;
}
CPoint MEllipse::GetO() {
	return o;
}
double	MEllipse::GetA() {
	return a;
}
double	MEllipse::GetB() {
	return b;
}
void MEllipse::SetO(CPoint center) {
	o = center;
}			  
void MEllipse::SetA(double a) {
	this->a = a;
}			  
void MEllipse::SetB(double b) {
	this->b = b;
}
void MEllipse::Bresenham_MEllipse(CDC* pDC, CPoint p, int a, int b, int width, COLORREF color)
{
	int i;
	float x, y;
	double dx, dy, di, aa, bb, sinA, cosA;
	cosA = cos(angle);
	sinA = sin(angle);
	aa = temp_a*temp_a;
	bb = temp_b*temp_b;
	float flX[4], flY[4];
	x = 0;
	y = b;
	dx = 0;
	dy = 2 * aa*y;
	di = bb - aa*b + aa / 4;
	flX[0] = p.x + x*cosA - y*sinA;
	flX[1] = p.x + x*cosA + y*sinA;
	flX[2] = p.x - x*cosA - y*sinA;
	flX[3] = p.x - x*cosA + y*sinA;
	flY[0] = p.y + y*cosA + x*sinA;
	flY[1] = p.y - y*cosA + x*sinA;
	flY[2] = p.y + y*cosA - x*sinA;
	flY[3] = p.y - y*cosA - x*sinA;
	i = 0;
	while (dx<dy)
	{
		i++;
		if (i == 5)
		{
			pDC->MoveTo(flX[0], flY[0]);
			pDC->LineTo(p.x + x*cosA - y*sinA, p.y + y*cosA + x*sinA);
			pDC->MoveTo(flX[1], flY[1]);
			pDC->LineTo(p.x + x*cosA + y*sinA, p.y - y*cosA + x*sinA);
			pDC->MoveTo(flX[2], flY[2]);
			pDC->LineTo(p.x - x*cosA - y*sinA, p.y + y*cosA - x*sinA);
			pDC->MoveTo(flX[3], flY[3]);
			pDC->LineTo(p.x - x*cosA + y*sinA, p.y - y*cosA - x*sinA);
			flX[0] = p.x + x*cosA - y*sinA;
			flX[1] = p.x + x*cosA + y*sinA;
			flX[2] = p.x - x*cosA - y*sinA;
			flX[3] = p.x - x*cosA + y*sinA;
			flY[0] = p.y + y*cosA + x*sinA;
			flY[1] = p.y - y*cosA + x*sinA;
			flY[2] = p.y + y*cosA - x*sinA;
			flY[3] = p.y - y*cosA - x*sinA;
			i = 0;
		}
		x++;
		dx += 2 * bb;
		di += dx + bb;
		if (di >= 0)
		{
			dy -= 2 * aa;
			di -= dy;
			y--;
		}
	}
	pDC->MoveTo(flX[0], flY[0]);
	pDC->LineTo(p.x + x*cosA - y*sinA, p.y + y*cosA + x*sinA);
	pDC->MoveTo(flX[1], flY[1]);
	pDC->LineTo(p.x + x*cosA + y*sinA, p.y - y*cosA + x*sinA);
	pDC->MoveTo(flX[2], flY[2]);
	pDC->LineTo(p.x - x*cosA - y*sinA, p.y + y*cosA - x*sinA);
	pDC->MoveTo(flX[3], flY[3]);
	pDC->LineTo(p.x - x*cosA + y*sinA, p.y - y*cosA - x*sinA);

	di += int((3 * (aa - bb) - 2 * (dx - dy)) / 4 + 0.5);
	flX[0] = p.x + x*cosA - y*sinA;
	flX[1] = p.x + x*cosA + y*sinA;
	flX[2] = p.x - x*cosA - y*sinA;
	flX[3] = p.x - x*cosA + y*sinA;
	flY[0] = p.y + y*cosA + x*sinA;
	flY[1] = p.y - y*cosA + x*sinA;
	flY[2] = p.y + y*cosA - x*sinA;
	flY[3] = p.y - y*cosA - x*sinA;
	i = 0;
	while (y>0)
	{
		i++;
		if (i == 5)
		{
			pDC->MoveTo(flX[0], flY[0]);
			pDC->LineTo(p.x + x*cosA - y*sinA, p.y + y*cosA + x*sinA);
			pDC->MoveTo(flX[1], flY[1]);
			pDC->LineTo(p.x + x*cosA + y*sinA, p.y - y*cosA + x*sinA);
			pDC->MoveTo(flX[2], flY[2]);
			pDC->LineTo(p.x - x*cosA - y*sinA, p.y + y*cosA - x*sinA);
			pDC->MoveTo(flX[3], flY[3]);
			pDC->LineTo(p.x - x*cosA + y*sinA, p.y - y*cosA - x*sinA);
			flX[0] = p.x + x*cosA - y*sinA;
			flX[1] = p.x + x*cosA + y*sinA;
			flX[2] = p.x - x*cosA - y*sinA;
			flX[3] = p.x - x*cosA + y*sinA;
			flY[0] = p.y + y*cosA + x*sinA;
			flY[1] = p.y - y*cosA + x*sinA;
			flY[2] = p.y + y*cosA - x*sinA;
			flY[3] = p.y - y*cosA - x*sinA;
			i = 0;
		}
		y--;
		dy -= 2 * aa;
		di += aa - dy;
		if (di<0)
		{
			dx += 2 * bb;
			di += dx;
			x++;
		}
	}
	pDC->MoveTo(flX[0], flY[0]);
	pDC->LineTo(p.x + x*cosA - y*sinA, p.y + y*cosA + x*sinA);
	pDC->MoveTo(flX[1], flY[1]);
	pDC->LineTo(p.x + x*cosA + y*sinA, p.y - y*cosA + x*sinA);
	pDC->MoveTo(flX[2], flY[2]);
	pDC->LineTo(p.x - x*cosA - y*sinA, p.y + y*cosA - x*sinA);
	pDC->MoveTo(flX[3], flY[3]);
	pDC->LineTo(p.x - x*cosA + y*sinA, p.y - y*cosA - x*sinA);

}
void MEllipse::MEllipsePlot(CDC* pDC, int x0, int y0, int x, int y, int width, COLORREF color) {
	pDC->MoveTo(x*cos(angle) - y*sin(angle) + x0, y*cos(angle) + x*sin(angle) + y0);
	pDC->LineTo(x*cos(angle) - y*sin(angle) + x0, y*cos(angle) + x*sin(angle) + y0);
	//pDC->LineTo((x0 + x), (y0 + y));

	pDC->MoveTo(x*cos(angle) - y*sin(angle) + x0, -y*cos(angle) + x*sin(angle) + y0);
	pDC->LineTo(x*cos(angle) - y*sin(angle) + x0, -y*cos(angle) + x*sin(angle) + y0);
	//pDC->LineTo((x0 + x), (y0 - y));

	pDC->MoveTo(-x*cos(angle) - y*sin(angle) + x0, y*cos(angle) - x*sin(angle) + y0);
	pDC->LineTo(-x*cos(angle) - y*sin(angle) + x0, y*cos(angle) - x*sin(angle) + y0);
	//pDC->LineTo((x0 - x), (y0 + y));

	pDC->MoveTo(-x*cos(angle) + y*sin(angle) + x0, -y*cos(angle) - x*sin(angle) + y0);
	pDC->LineTo(-x*cos(angle) + y*sin(angle) + x0, -y*cos(angle) - x*sin(angle) + y0);
	//pDC->LineTo((x0 - x), (y0 - y));

	//pDC->SelectObject(oldPen);
}
int MEllipse::isInRect(CRect rect) {
	int nRltVal = 0;
	CPoint ptRectLT = rect.TopLeft();
	CPoint ptRectRB = rect.BottomRight();
	CPoint ptRectLB, ptRectRT;
	ptRectLB.x = rect.left;
	ptRectLB.y = rect.bottom;
	ptRectRT.x = rect.right;
	ptRectRT.y = rect.top;

	CPoint ptCircleCenter(temp_o.x, temp_o.y);
	int flag = 0;
	if (IsPointinRegion(ptRectLT)) {
		flag++;
	}
	if (IsPointinRegion(ptRectRB)) {
		flag++;
	}
	if (IsPointinRegion(ptRectLB)) {
		flag++;
	}
	if (IsPointinRegion(ptRectRT)) {
		flag++;
	}
	if (0<flag&&flag<4) {
		nRltVal = 1;
	}
	else if (flag == 0) {//判断矩形与长短直径的关系
		float flX[4], flY[4];
		float a = temp_a;
		float b = temp_b;
		flX[0] = temp_o.x;
		flX[1] = temp_o.x;
		flX[2] = temp_o.x - a;
		flX[3] = temp_o.x + a;
		flY[0] = temp_o.y - b;
		flY[1] = temp_o.y + b;
		flY[2] = temp_o.y;
		flY[3] = temp_o.y;

		float fx, fy,  cosA, sinA;
		cosA = cos(angle);
		sinA = sin(angle);
		fx = (flX[0] - temp_o.x)*cosA - (flY[0] - temp_o.y)*sinA + temp_o.x;
		fy = (flY[0] - temp_o.y)*cosA + (flX[0] - temp_o.x)*sinA + temp_o.y;
		flX[0] = fx;
		flY[0] = fy;
		fx = (flX[1] - temp_o.x)*cosA - (flY[1] - temp_o.y)*sinA + temp_o.x;
		fy = (flY[1] - temp_o.y)*cosA + (flX[1] - temp_o.x)*sinA + temp_o.y;
		flX[1] = fx;
		flY[1] = fy;
		fx = (flX[2] - temp_o.x)*cosA - (flY[2] - temp_o.y)*sinA + temp_o.x;
		fy = (flY[2] - temp_o.y)*cosA + (flX[2] - temp_o.x)*sinA + temp_o.y;
		flX[2] = fx;
		flY[2] = fy;
		fx = (flX[3] - temp_o.x)*cosA - (flY[3] - temp_o.y)*sinA + temp_o.x;
		fy = (flY[3] - temp_o.y)*cosA + (flX[3] - temp_o.x)*sinA + temp_o.y;
		flX[3] = fx;
		flY[3] = fy;

		flag = 0;
		flag |= GetLineStateToRect(flX[0], flY[0], flX[1], flY[1], rect);
		flag |= GetLineStateToRect(flX[2], flY[2], flX[3], flY[3], rect);
		if (flag == 1 || flag == 3) {
			nRltVal = 1;
		}
		else if (flag == 2) {
			nRltVal = 2;
		}
	}
	return nRltVal;
	return 0;
}
void MEllipse::RefreshData() {
	o = temp_o;
	a = temp_a;
	b = temp_b;
	anglePre = angle;//
	temp_angle = 0.0;
	scale = 1.0;
	//angle = 0.0;
}
int MEllipse::IsPointinRegion(CPoint point)
{
	angle = 0 - angle;
	float flx = (point.x - temp_o.x)*cos(angle) - (point.y - temp_o.y)*sin(angle) + temp_o.x;
	float fly = (point.y - temp_o.y)*cos(angle) + (point.x - temp_o.x)*sin(angle) + temp_o.y;
	int nRltVal = 0;
	float a = temp_a*temp_a;
	float b = temp_b*temp_b;

	float r2 = (flx - temp_o.x)*(flx - temp_o.x) / a + (fly - temp_o.y)*(fly - temp_o.y) / b;
	if (r2<1) {
		nRltVal = 1;
	}
	return nRltVal;
}