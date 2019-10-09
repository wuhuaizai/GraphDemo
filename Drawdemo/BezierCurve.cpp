#include "stdafx.h"
#include "BezierCurve.h"


BezierCurve::BezierCurve()
{
	isSelected = false;
}

BezierCurve::BezierCurve(BezierCurve* curve) {
	this->m_Points = curve->getPoints();
	this->temp_Points = curve->getPoints();
	color = curve->color;
	penWidth = curve->penWidth;
	fillColor = curve->fillColor;
	angle = curve->angle;
	scale = curve->scale;
	isSelected = false;//注意这里默认不选中
	centerPoint = curve->GetCenterPoint();
}
BezierCurve::BezierCurve(vector<CPoint>curve, COLORREF color, int penWidth) {
	this->m_Points = curve;
	this->temp_Points = curve;
	this->color = color;
	this->penWidth = penWidth;
	fillColor = RGB(255, 255, 255);
	angle = 0.0;
	scale = 1.0;
	isSelected = false;
}

BezierCurve::~BezierCurve()
{

}

void BezierCurve::setPoints(vector<CPoint>&points) {
	this->temp_Points = points;
	this->m_Points = points;
}
vector<CPoint> BezierCurve::getPoints() {
	return this->m_Points;
}

void	BezierCurve::Draw(CDC* pDC) {
	CPen m_pen;//首先定义一个对象
	CPen *oldPen;
	m_pen.CreatePen(PS_SOLID, this->penWidth, this->color);//创建一个画笔(这里是实线画笔)
	oldPen = pDC->SelectObject(&m_pen);//将画笔对象选入DC，替换oldPen

	bezier(pDC);

	pDC->SelectObject(oldPen);
}

void	BezierCurve::Draw(CDC* pDC, COLORREF tempColor) {
	CPen m_pen;//首先定义一个对象
	CPen *oldPen;
	m_pen.CreatePen(PS_SOLID, this->penWidth, tempColor);//创建一个画笔(这里是实线画笔)
	oldPen = pDC->SelectObject(&m_pen);//将画笔对象选入DC，替换oldPen

	bezier(pDC);

	pDC->SelectObject(oldPen);
}
void BezierCurve::bezier(CDC *pDC)
{
	double *pflX, *pflY;
	double flTempx, flTempy, flU;//flu-------u参数	
	int i, n, j;

	n = temp_Points.size();
	if (n<2) return;

	pflX = new double[n];
	pflY = new double[n];

	flTempx = temp_Points[0].x;
	flTempy = temp_Points[0].y;

	for (i = 0; i<n; i++) {
		pflX[i] = temp_Points[i].x*1.0;
		pflY[i] = temp_Points[i].y*1.0;
	}

	for (flU = 0; flU <= 1; flU += 0.05 / n) {
		for (i = 1; i<n; i++) {
			for (j = 0; j<n - i; j++) {
				pflX[j] = (1 - flU)*pflX[j] + flU*pflX[j + 1];
				pflY[j] = (1 - flU)*pflY[j] + flU*pflY[j + 1];
			}
		}
		pDC->MoveTo(flTempx, flTempy);
		pDC->LineTo(pflX[0], pflY[0]);
		flTempx = pflX[0];
		flTempy = pflY[0];
	}
	delete[] pflX;
	delete[] pflY;
	for (int i = 0; i < n; i++) {
		pDC->MoveTo(temp_Points[i].x, temp_Points[i].y - 1 - penWidth);
		pDC->LineTo(temp_Points[i].x, temp_Points[i].y + 2 + penWidth);
		pDC->MoveTo(temp_Points[i].x - 1 - penWidth, temp_Points[i].y);
		pDC->LineTo(temp_Points[i].x + 2 + penWidth, temp_Points[i].y);
	}
	return;
}
Shape*	BezierCurve::Move(double stepx, double stepy) {
	int n = m_Points.size();
	for (int i = 0; i < n; i++) {
		m_Points[i].x += stepx;
		m_Points[i].y += stepy;
		temp_Points[i].x += stepx;
		temp_Points[i].y += stepy;
	}
	return this;
}
Shape*	BezierCurve::Rotate(CPoint center, double flAngle) {
	RotateCenter = center;
	flAngle = PI / 180.0*flAngle;
	angle += flAngle;
	int n = m_Points.size();
	for (int i = 0; i < n; i++) {
		temp_Points[i].x = ((m_Points[i].x - RotateCenter.x)*cos(angle) - (m_Points[i].y - RotateCenter.y)*sin(angle)) + RotateCenter.x;
		temp_Points[i].y = ((m_Points[i].y - RotateCenter.y)*cos(angle) + (m_Points[i].x - RotateCenter.x)*sin(angle)) + RotateCenter.y;
	}
	return this;
}
Shape*	BezierCurve::Magnify(CPoint center, double flScale) {
	MagnifyCenter = center;
	_cprintf("Magtemp %d %d\n",temp_Points[0].x, temp_Points[0].y);
	_cprintf("Mag %d %d\n", m_Points[0].x, m_Points[0].y);
	_cprintf("center %d %d\n", center.x, center.y);
	scale = flScale;
	int n = m_Points.size();
	for (int i = 0; i < n; i++) {
		temp_Points[i].x = (m_Points[i].x - MagnifyCenter.x)*scale + MagnifyCenter.x;
		temp_Points[i].y = (m_Points[i].y - MagnifyCenter.y)*scale + MagnifyCenter.y;
	}
	return this;
}
Shape*	BezierCurve::TopToBottom(CRect rect) {
	int n = m_Points.size();
	for (int i = 0; i < n; i++) {
		temp_Points[i].y = rect.top + rect.bottom - temp_Points[i].y;
		m_Points[i].y = temp_Points[i].y;
	}
	return this;
}
Shape*	BezierCurve::LeftToRight(CRect rect) {
	int n = m_Points.size();
	for (int i = 0; i < n; i++) {
		temp_Points[i].x = rect.left + rect.right - temp_Points[i].x;
		m_Points[i].x = temp_Points[i].x;
	}
	return this;
}
Shape	BezierCurve::GetCopy() {
	return BezierCurve(this);
}
CRect	BezierCurve::GetBoundaryRect() {
	int minx = m_Points[0].x;
	int miny = m_Points[0].y;
	int maxx = m_Points[0].x;
	int maxy = m_Points[0].y;
	int n = m_Points.size();
	for (int i = 0; i < n; i++) {
		minx = min(minx, m_Points[i].x);
		miny = min(miny, m_Points[i].y);
		maxx = max(maxx, m_Points[i].x);
		maxy = max(maxy, m_Points[i].y);
	}
	return CRect(minx, miny, maxx, maxy);
}

CPoint	BezierCurve::GetCenterPoint() {
	return GetBoundaryRect().CenterPoint();
}
int		BezierCurve::isInRect(CRect rect) {
	int nRltVal = 0, nTemp;
	int i = temp_Points.size();
	int j = 0;
	float fx1, fy1, fx2, fy2;
	while (++j < i) {
		fx1 = temp_Points[j - 1].x;
		fy1 = temp_Points[j - 1].y;
		fx2 = temp_Points[j].x;
		fy2 = temp_Points[j].y;

		nTemp = GetLineStateToRect(fx1, fy1, fx2, fy2, rect);

		nRltVal = nRltVal | nTemp;
	}
	if (nRltVal == 3) {
		nRltVal = 1;
	}
	return nRltVal;
}
void	BezierCurve::RefreshData() {
	m_Points = temp_Points;
	angle = 0.0;
	scale = 1.0;
}