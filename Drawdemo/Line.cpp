#include "stdafx.h"
#include "Line.h"
#include "conio.h"
#include "GlobalUtil.h"

CLine::CLine()
{
	isSelected = false;
}
CLine::CLine(CPoint s, CPoint e,COLORREF color,int penWidth) {
	m_Start = s;
	m_End = e;
	temp_Start = s;
	temp_End = e;
	this->color = color;
	this->penWidth = penWidth;
	fillColor = RGB(255, 255, 255);
	angle = 0.0;
	scale = 1.0;
	isSelected = false;
	centerPoint = CPoint((m_Start.x + m_End.x) / 2.0, (m_Start.y + m_End.y) / 2.0);
}
CLine::CLine(CLine* pLine) {
	m_Start = pLine->getStartPoint();
	m_End = pLine->getEndPoint();
	color = pLine->color;
	penWidth = pLine->penWidth;
	fillColor = pLine->fillColor;
	angle = pLine->angle;
	scale = pLine->scale;
	isSelected = false;//注意这里默认不选中
	centerPoint = pLine->GetCenterPoint();
}
CLine::~CLine()
{
}
//统一绘制函数
void CLine::Draw(CDC* pDC) {
	
	/*temp_Start.x = (m_Start.x - MagnifyCenter.x)*scale + MagnifyCenter.x;
	temp_Start.y = (m_Start.y - MagnifyCenter.y)*scale + MagnifyCenter.y;
	temp_End.x = (m_End.x - MagnifyCenter.x)*scale + MagnifyCenter.x;
	temp_End.y = (m_End.y - MagnifyCenter.y)*scale + MagnifyCenter.y;
*/
	/*temp_Start.x = ((m_Start.x - RotateCenter.x)*cos(angle) - (m_Start.y - RotateCenter.y)*sin(angle)) + RotateCenter.x;
	temp_Start.y = ((m_Start.y - RotateCenter.y)*cos(angle) + (m_Start.x - RotateCenter.x)*sin(angle)) + RotateCenter.y;
	temp_End.x = ((m_End.x - RotateCenter.x)*cos(angle) - (m_End.y - RotateCenter.y)*sin(angle)) + RotateCenter.x;
	temp_End.y = ((m_End.y - RotateCenter.y)*cos(angle) + (m_End.x - RotateCenter.x)*sin(angle)) + RotateCenter.y;*/
	/*if (temp_Start.x == m_Start.x) {
		_cprintf("xiangdeng\n");
	}*/
	Draw_Line(temp_Start, temp_End, pDC, this->penWidth, this->color);
}
void CLine::Draw(CDC* pDC,COLORREF tempColor) {

	temp_Start.x = (m_Start.x - MagnifyCenter.x)*scale + MagnifyCenter.x;
	temp_Start.y = (m_Start.y - MagnifyCenter.y)*scale + MagnifyCenter.y;
	temp_End.x = (m_End.x - MagnifyCenter.x)*scale + MagnifyCenter.x;
	temp_End.y = (m_End.y - MagnifyCenter.y)*scale + MagnifyCenter.y;

	temp_Start.x = ((m_Start.x - RotateCenter.x)*cos(angle) - (m_Start.y - RotateCenter.y)*sin(angle)) + RotateCenter.x;
	temp_Start.y = ((m_Start.y - RotateCenter.y)*cos(angle) + (m_Start.x - RotateCenter.x)*sin(angle)) + RotateCenter.y;
	temp_End.x = ((m_End.x - RotateCenter.x)*cos(angle) - (m_End.y - RotateCenter.y)*sin(angle)) + RotateCenter.x;
	temp_End.y = ((m_End.y - RotateCenter.y)*cos(angle) + (m_End.x - RotateCenter.x)*sin(angle)) + RotateCenter.y;

	Draw_Line(temp_Start, temp_End, pDC, this->penWidth, tempColor);
}
Shape*	CLine::Move(double stepx, double stepy) {
	temp_Start.x += stepx;
	temp_Start.y += stepy;
	temp_End.x += stepx;
	temp_End.y += stepy;
	m_Start.x += stepx;
	m_Start.y += stepy;
	m_End.x += stepx;
	m_End.y += stepy;
	
	return this;
}
Shape*	CLine::MatrixMove(double stepx, double stepy) {
	CMatrix movedTempStart = MovePointByMatrix(temp_Start, stepx, stepy);
	temp_Start.x = movedTempStart.m[0];
	temp_Start.y = movedTempStart.m[1];

	CMatrix movedTempEnd = MovePointByMatrix(temp_End, stepx, stepy);
	temp_End.x = movedTempEnd.m[0];
	temp_End.y = movedTempEnd.m[1];

	m_Start = temp_Start;
	m_End = temp_End;
	return this;
}
Shape*	CLine::Rotate(CPoint center, double flAngle) {
	RotateCenter = center;
	flAngle = PI / 180.0*flAngle;
	angle +=flAngle;
	temp_Start.x = ((m_Start.x - RotateCenter.x)*cos(angle) - (m_Start.y - RotateCenter.y)*sin(angle)) + RotateCenter.x;
	temp_Start.y = ((m_Start.y - RotateCenter.y)*cos(angle) + (m_Start.x - RotateCenter.x)*sin(angle)) + RotateCenter.y;
	temp_End.x = ((m_End.x - RotateCenter.x)*cos(angle) - (m_End.y - RotateCenter.y)*sin(angle)) + RotateCenter.x;
	temp_End.y = ((m_End.y - RotateCenter.y)*cos(angle) + (m_End.x - RotateCenter.x)*sin(angle)) + RotateCenter.y;
	return this;
	
	/*m_Start.x = ((m_Start.x - centerPoint.x)*cos(flAngle) - (m_Start.y - centerPoint.y)*sin(flAngle)) + centerPoint.x;
	m_Start.y = ((m_Start.y - centerPoint.y)*cos(flAngle) + (m_Start.x - centerPoint.x)*sin(flAngle)) + centerPoint.y;
	m_End.x = ((m_End.x - centerPoint.x)*cos(flAngle) - (m_End.y - centerPoint.y)*sin(flAngle)) + centerPoint.x;
	m_End.y = ((m_End.y - centerPoint.y)*cos(flAngle) + (m_End.x - centerPoint.x)*sin(flAngle)) + centerPoint.y;*/
	/*m_Start.x = ((m_Start.x*100000 - centerPoint.x * 100000)*cos(flAngle) - (m_Start.y * 100000 - centerPoint.y * 100000)*sin(flAngle))/100000 + centerPoint.x;
	m_Start.y = ((m_Start.y * 100000 - centerPoint.y * 100000)*cos(flAngle) + (m_Start.x * 100000 - centerPoint.x * 100000)*sin(flAngle)) / 100000 + centerPoint.y;
	m_End.x = ((m_End.x * 100000 - centerPoint.x * 100000)*cos(flAngle) - (m_End.y * 100000 - centerPoint.y * 100000)*sin(flAngle)) / 100000 + centerPoint.x;
	m_End.y = ((m_End.y * 100000 - centerPoint.y * 100000)*cos(flAngle) + (m_End.x * 100000 - centerPoint.x * 100000)*sin(flAngle)) / 100000 + centerPoint.y;*/
	
}
Shape* CLine::MatrixRotate(CPoint center, double flAngle) {
	RotateCenter = center;
	flAngle = PI / 180.0*flAngle;
	angle += flAngle;
	
	CMatrix afterTempStart = RotatePointByMatrix(m_Start, center, angle);
	temp_Start.x = afterTempStart.m[0];
	temp_Start.y = afterTempStart.m[1];

	CMatrix afterTempEnd = RotatePointByMatrix(m_End, center, angle);
	temp_End.x = afterTempEnd.m[0];
	temp_End.y = afterTempEnd.m[1];
	return this;
}
Shape*	CLine::Magnify(CPoint center,double flScale) {
	
	MagnifyCenter = center;
	scale = flScale;
	//_cprintf("CLine Magnify:%lf\n",scale);
	temp_Start.x = (m_Start.x - MagnifyCenter.x)*scale + MagnifyCenter.x;
	temp_Start.y = (m_Start.y - MagnifyCenter.y)*scale + MagnifyCenter.y;
	temp_End.x = (m_End.x - MagnifyCenter.x)*scale + MagnifyCenter.x;
	temp_End.y = (m_End.y - MagnifyCenter.y)*scale + MagnifyCenter.y;

	/*m_Start.x = (m_Start.x - centerPoint.x)*flScale + centerPoint.x;
	m_Start.y = (m_Start.y - centerPoint.y)*flScale + centerPoint.y;
	m_End.x = (m_End.x - centerPoint.x)*flScale + centerPoint.x;
	m_End.y = (m_End.y - centerPoint.y)*flScale + centerPoint.y;*/
	return this;
}
Shape*	CLine::MatrixMagnify(CPoint center, double flScale) {
	MagnifyCenter = center;
	scale = flScale;

	CMatrix afterTempStart = MagnifyPointByMatrix(m_Start, center, scale);
	temp_Start.x = afterTempStart.m[0];
	temp_Start.y = afterTempStart.m[1];

	CMatrix afterTempEnd = MagnifyPointByMatrix(m_End, center, scale);
	temp_End.x = afterTempEnd.m[0];
	temp_End.y = afterTempEnd.m[1];
	return this;
}
Shape*	CLine::TopToBottom( CRect rect) {
	temp_Start.y = rect.top+rect.bottom-temp_Start.y;
	temp_End.y = rect.top + rect.bottom - temp_End.y;

	m_Start.y = temp_Start.y;
	m_End.y = temp_End.y;
	return this;
}
Shape*	CLine::LeftToRight( CRect rect) {
	temp_Start.x = rect.left + rect.right - temp_Start.x;
	temp_End.x = rect.left + rect.right - temp_End.x;

	m_Start.x = temp_Start.x;
	m_End.x = temp_End.x;
	return this;
}
Shape	CLine::GetCopy() {
	return CLine(this);
}
CRect	CLine::GetBoundaryRect() {
	CPoint lt = CPoint(min(m_Start.x, m_End.x), min(m_Start.y, m_End.y));
	CPoint rb = CPoint(max(m_Start.x, m_End.x), max(m_Start.y, m_End.y));
	return CRect(lt,rb);
}
CPoint	CLine::GetCenterPoint() {
	return CPoint((m_Start.x + m_End.x) /2.0, (m_Start.y + m_End.y) /2.0);
}
//Bresenham画线
void CLine::Draw_BresenhamLine(CPoint ptStart, CPoint ptEnd, CDC *pDC, int penWidth, COLORREF color) {
	CPen m_pen;//首先定义一个对象
	CPen *oldPen;
	m_pen.CreatePen(PS_SOLID, penWidth, color);//创建一个画笔(这里是实线画笔)
	oldPen = pDC->SelectObject(&m_pen);//将画笔对象选入DC，替换oldPen
	
	int dx = ptEnd.x - ptStart.x;
	int dy = ptEnd.y - ptStart.y;
	int ux = ((dx > 0) << 1) - 1;
	int uy = ((dy > 0) << 1) - 1;
	int x = ptStart.x, y = ptStart.y, eps;

	eps = 0; dx = abs(dx); dy = abs(dy);
	if (dx > dy) {
		for (x = ptStart.x; x != ptEnd.x; x += ux) {
			pDC->MoveTo(x, y);
			pDC->LineTo(x, y);
			//points.push_back(CPoint(x, y));//加入组成点
			eps += dy;
			if ((eps << 1) >= dx) {
				y += uy; eps -= dx;
			}
		}
	}
	else {
		for (y = ptStart.y; y != ptEnd.y; y += uy) {
			pDC->MoveTo(x, y);
			pDC->LineTo(x, y);
			//points.push_back(CPoint(x, y));//加入组成点
			eps += dx;
			if ((eps << 1) >= dy) {
				x += ux; eps -= dy;
			}
		}
	}
	pDC->SelectObject(oldPen);
	return;
}
void CLine::Draw_Line(CPoint ptStart, CPoint ptEnd, CDC *pDC, int penWidth, COLORREF color) {
	CPen m_pen;//首先定义一个对象
	CPen *oldPen;
	m_pen.CreatePen(PS_SOLID, penWidth, color);//创建一个画笔(这里是实线画笔)
	oldPen = pDC->SelectObject(&m_pen);//将画笔对象选入DC，替换oldPen
	pDC->MoveTo(ptStart);
	pDC->LineTo(ptEnd);
	pDC->SelectObject(oldPen);
	return;

}
CPoint CLine::getStartPoint() {
	return m_Start;
}
CPoint CLine::getEndPoint() {
	return m_End;
}
void CLine::setStart(CPoint start) {
	m_Start = start;
}
void CLine::setEnd(CPoint end) {
	m_End = end;
}
int CLine::isInRect(CRect rect) {
	if (IsPtInRect(temp_Start, rect) || IsPtInRect(temp_End, rect)) {
		return 1;
	}
	_cprintf("start::%d :%d end:%d %d\n", temp_Start.x, temp_Start.y, temp_End.x, temp_End.y);
	CPoint LT = CPoint(rect.left,rect.top);
	CPoint RT = CPoint(rect.right, rect.top);
	CPoint RB = CPoint(rect.right, rect.bottom);
	CPoint LB = CPoint(rect.left, rect.bottom);
	if (SegmentIntersection(temp_Start, temp_End, LT, RT)) return true;
	if (SegmentIntersection(temp_Start, temp_End, RT, RB)) return true;
	if (SegmentIntersection(temp_Start, temp_End, RB, LB)) return true;
	if (SegmentIntersection(temp_Start, temp_End, LB, LT)) return true;
	return 0;
}
void CLine::RefreshData() {
	m_Start = temp_Start;
	m_End = temp_End;
	angle = 0.0;
	scale = 1.0;
}
void CLine::SetSelected(bool state) {
	//_cprintf("%d\n",state);
	this->isSelected = state;
}
bool CLine::GetIsSelect() {
	//_cprintf("GetIsSelect\n");
	return this->isSelected;
}