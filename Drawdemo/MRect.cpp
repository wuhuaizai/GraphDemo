#include "stdafx.h"
#include "MRect.h"
#include "GlobalUtil.h"

MRect::MRect():Shape()
{
	isSelected = false;
}

MRect::MRect(CPoint LT,CPoint RB,COLORREF color,int penWidth):Shape() {
	m_LeftTop = CPoint(LT.x,LT.y);
	m_RightBottom = CPoint(RB.x,RB.y);
	m_LeftBottom = CPoint(LT.x,RB.y);
	m_RightTop = CPoint(RB.x,LT.y);
	temp_LeftTop = m_LeftTop;
	temp_RightBottom = m_RightBottom;
	temp_LeftBottom = m_LeftBottom;
	temp_RightTop = m_RightTop;
	this->color = color;
	this->penWidth = penWidth;
	fillColor = RGB(255, 255, 255);
	angle = 0.0;
	scale = 1.0;
	isSelected = false;
}
MRect::MRect(MRect *pMRect) {//not used
	color = pMRect->color;
	penWidth = pMRect->penWidth;
	fillColor = pMRect->fillColor;
	angle = pMRect->angle;
	scale = pMRect->scale;
	m_LeftTop = pMRect->getLeftTop();
	m_RightBottom = pMRect->getRightBottom(); 
	centerPoint = pMRect->GetCenterPoint();
}

MRect::~MRect()
{

}
void MRect::Draw_BresenhamLine(CPoint ptStart, CPoint ptEnd, CDC *pDC, int penWidth, COLORREF color) {
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

void MRect::Draw(CDC* pDC) {
	//CPen m_pen;//首先定义一个对象
	//CPen *oldPen;
	//m_pen.CreatePen(PS_SOLID, penWidth, color);//创建一个画笔(这里是实线画笔)
	//oldPen = pDC->SelectObject(&m_pen);//将画笔对象选入DC，替换oldPen

	Draw_Line(temp_LeftTop, temp_RightTop, pDC, this->penWidth, this->color);
	Draw_Line(temp_RightTop, temp_RightBottom, pDC, this->penWidth, this->color);
	Draw_Line(temp_RightBottom, temp_LeftBottom, pDC, this->penWidth, this->color);
	Draw_Line(temp_LeftBottom, temp_LeftTop, pDC, this->penWidth, this->color);
	//pDC->SelectObject(oldPen);
}
void MRect::Draw(CDC* pDC, COLORREF tempcolor) {
	temp_LeftTop.x = ((m_LeftTop.x - RotateCenter.x)*cos(angle) - (m_LeftTop.y - RotateCenter.y)*sin(angle)) + RotateCenter.x;
	temp_LeftTop.y = ((m_LeftTop.y - RotateCenter.y)*cos(angle) + (m_LeftTop.x - RotateCenter.x)*sin(angle)) + RotateCenter.y;
	temp_RightBottom.x = ((m_RightBottom.x - RotateCenter.x)*cos(angle) - (m_RightBottom.y - RotateCenter.y)*sin(angle)) + RotateCenter.x;
	temp_RightBottom.y = ((m_RightBottom.y - RotateCenter.y)*cos(angle) + (m_RightBottom.x - RotateCenter.x)*sin(angle)) + RotateCenter.y;
	temp_RightTop.x = ((m_RightTop.x - RotateCenter.x)*cos(angle) - (m_RightTop.y - RotateCenter.y)*sin(angle)) + RotateCenter.x;
	temp_RightTop.y = ((m_RightTop.y - RotateCenter.y)*cos(angle) + (m_RightTop.x - RotateCenter.x)*sin(angle)) + RotateCenter.y;
	temp_LeftBottom.x = ((m_LeftBottom.x - RotateCenter.x)*cos(angle) - (m_LeftBottom.y - RotateCenter.y)*sin(angle)) + RotateCenter.x;
	temp_LeftBottom.y = ((m_LeftBottom.y - RotateCenter.y)*cos(angle) + (m_LeftBottom.x - RotateCenter.x)*sin(angle)) + RotateCenter.y;

	temp_LeftTop.x = (m_LeftTop.x - MagnifyCenter.x)*scale + MagnifyCenter.x;
	temp_LeftTop.y = (m_LeftTop.y - MagnifyCenter.y)*scale + MagnifyCenter.y;
	temp_RightBottom.x = (m_RightBottom.x - MagnifyCenter.x)*scale + MagnifyCenter.x;
	temp_RightBottom.y = (m_RightBottom.y - MagnifyCenter.y)*scale + MagnifyCenter.y;
	temp_RightTop.x = (m_RightTop.x - MagnifyCenter.x)*scale + MagnifyCenter.x;
	temp_RightTop.y = (m_RightTop.y - MagnifyCenter.y)*scale + MagnifyCenter.y;
	temp_LeftBottom.x = (m_LeftBottom.x - MagnifyCenter.x)*scale + MagnifyCenter.x;
	temp_LeftBottom.y = (m_LeftBottom.y - MagnifyCenter.y)*scale + MagnifyCenter.y;

	Draw_Line(temp_LeftTop, temp_RightTop, pDC, this->penWidth, tempcolor);
	Draw_Line(temp_RightTop, temp_RightBottom, pDC, this->penWidth, tempcolor);
	Draw_Line(temp_RightBottom, temp_LeftBottom, pDC, this->penWidth, tempcolor);
	Draw_Line(temp_LeftBottom, temp_LeftTop, pDC, this->penWidth, tempcolor);
}
Shape* MRect::Move(double stepx, double stepy) {
	temp_LeftTop.x += stepx;
	temp_RightBottom.x += stepx;
	temp_LeftTop.y += stepy;
	temp_RightBottom.y += stepy;
	temp_RightTop.x += stepx;
	temp_RightTop.y += stepy;
	temp_LeftBottom.x += stepx;
	temp_LeftBottom.y += stepy;

	m_LeftTop.x += stepx;
	m_RightBottom.x += stepx;
	m_LeftTop.y += stepy;
	m_RightBottom.y += stepy;
	m_RightTop.x += stepx;
	m_RightTop.y += stepy;
	m_LeftBottom.x += stepx;
	m_LeftBottom.y += stepy;
	return this;
}
Shape* MRect::MatrixMove(double stepx, double stepy) {
	CMatrix movedTempLT = MovePointByMatrix(temp_LeftTop, stepx, stepy);
	temp_LeftTop.x = movedTempLT.m[0];
	temp_LeftTop.y = movedTempLT.m[1];

	CMatrix movedTempRB = MovePointByMatrix(temp_RightBottom, stepx, stepy);
	temp_RightBottom.x = movedTempRB.m[0];
	temp_RightBottom.y = movedTempRB.m[1];

	CMatrix movedTempRT = MovePointByMatrix(temp_RightTop, stepx, stepy);
	temp_RightTop.x = movedTempRT.m[0];
	temp_RightTop.y = movedTempRT.m[1];

	CMatrix movedTempLB = MovePointByMatrix(temp_LeftBottom, stepx, stepy);
	temp_LeftBottom.x = movedTempLB.m[0];
	temp_LeftBottom.y = movedTempLB.m[1];

	m_LeftTop = temp_LeftTop;
	m_RightBottom = temp_RightBottom;
	m_RightTop = temp_RightTop;
	m_LeftBottom = temp_LeftBottom;
	return this;
}
Shape* MRect::Rotate(CPoint center,double flAngle) {
	flAngle = PI / 180.0*flAngle;
	RotateCenter = center;
	angle += flAngle;
	//_cprintf("MRect Rotate %lf\n",angle);
	temp_LeftTop.x = ((m_LeftTop.x - RotateCenter.x)*cos(angle) - (m_LeftTop.y - RotateCenter.y)*sin(angle)) + RotateCenter.x;
	temp_LeftTop.y = ((m_LeftTop.y - RotateCenter.y)*cos(angle) + (m_LeftTop.x - RotateCenter.x)*sin(angle)) + RotateCenter.y;
	temp_RightBottom.x = ((m_RightBottom.x - RotateCenter.x)*cos(angle) - (m_RightBottom.y - RotateCenter.y)*sin(angle)) + RotateCenter.x;
	temp_RightBottom.y = ((m_RightBottom.y - RotateCenter.y)*cos(angle) + (m_RightBottom.x - RotateCenter.x)*sin(angle)) + RotateCenter.y;
	temp_RightTop.x = ((m_RightTop.x - RotateCenter.x)*cos(angle) - (m_RightTop.y - RotateCenter.y)*sin(angle)) + RotateCenter.x;
	temp_RightTop.y = ((m_RightTop.y - RotateCenter.y)*cos(angle) + (m_RightTop.x - RotateCenter.x)*sin(angle)) + RotateCenter.y;
	temp_LeftBottom.x = ((m_LeftBottom.x - RotateCenter.x)*cos(angle) - (m_LeftBottom.y - RotateCenter.y)*sin(angle)) + RotateCenter.x;
	temp_LeftBottom.y = ((m_LeftBottom.y - RotateCenter.y)*cos(angle) + (m_LeftBottom.x - RotateCenter.x)*sin(angle)) + RotateCenter.y;
	
	return this;
}
Shape* MRect::MatrixRotate(CPoint center, double flAngle) {
	flAngle = PI / 180.0*flAngle;
	RotateCenter = center;
	angle += flAngle;

	CMatrix movedTempLT = RotatePointByMatrix(temp_LeftTop, center, angle);
	temp_LeftTop.x = movedTempLT.m[0];
	temp_LeftTop.y = movedTempLT.m[1];

	CMatrix movedTempRB = RotatePointByMatrix(temp_RightBottom, center, angle);
	temp_RightBottom.x = movedTempRB.m[0];
	temp_RightBottom.y = movedTempRB.m[1];

	CMatrix movedTempRT = RotatePointByMatrix(temp_RightTop, center, angle);
	temp_RightTop.x = movedTempRT.m[0];
	temp_RightTop.y = movedTempRT.m[1];

	CMatrix movedTempLB = RotatePointByMatrix(temp_LeftBottom, center, angle);
	temp_LeftBottom.x = movedTempLB.m[0];
	temp_LeftBottom.y = movedTempLB.m[1];
	return this;
}
Shape* MRect::Magnify(CPoint center,double flScale) {
	scale = flScale;
	MagnifyCenter = center;

	temp_LeftTop.x = (m_LeftTop.x - MagnifyCenter.x)*scale + MagnifyCenter.x;
	temp_LeftTop.y = (m_LeftTop.y - MagnifyCenter.y)*scale + MagnifyCenter.y;
	temp_RightBottom.x = (m_RightBottom.x - MagnifyCenter.x)*scale + MagnifyCenter.x;
	temp_RightBottom.y = (m_RightBottom.y - MagnifyCenter.y)*scale + MagnifyCenter.y;
	temp_RightTop.x = (m_RightTop.x - MagnifyCenter.x)*scale + MagnifyCenter.x;
	temp_RightTop.y = (m_RightTop.y - MagnifyCenter.y)*scale + MagnifyCenter.y;
	temp_LeftBottom.x = (m_LeftBottom.x - MagnifyCenter.x)*scale + MagnifyCenter.x;
	temp_LeftBottom.y = (m_LeftBottom.y - MagnifyCenter.y)*scale + MagnifyCenter.y;
	return this;
}
Shape* MRect::MatrixMagnify(CPoint center, double flScale) {
	scale = flScale;
	MagnifyCenter = center;

	CMatrix movedTempLT = MagnifyPointByMatrix(temp_LeftTop, center, scale);
	temp_LeftTop.x = movedTempLT.m[0];
	temp_LeftTop.y = movedTempLT.m[1];

	CMatrix movedTempRB = MagnifyPointByMatrix(temp_RightBottom, center, scale);
	temp_RightBottom.x = movedTempRB.m[0];
	temp_RightBottom.y = movedTempRB.m[1];

	CMatrix movedTempRT = MagnifyPointByMatrix(temp_RightTop, center, scale);
	temp_RightTop.x = movedTempRT.m[0];
	temp_RightTop.y = movedTempRT.m[1];

	CMatrix movedTempLB = MagnifyPointByMatrix(temp_LeftBottom, center, scale);
	temp_LeftBottom.x = movedTempLB.m[0];
	temp_LeftBottom.y = movedTempLB.m[1];
	return this;
}
Shape* MRect::TopToBottom(CRect rect) {
	temp_LeftTop.y = rect.top + rect.bottom - temp_LeftTop.y;
	temp_RightBottom.y = rect.top + rect.bottom - temp_RightBottom.y;
	temp_RightTop.y = rect.top + rect.bottom - temp_RightTop.y;
	temp_LeftBottom.y = rect.top + rect.bottom - temp_LeftBottom.y;

	m_LeftTop.y = temp_LeftTop.y;
	m_RightBottom.y = temp_RightBottom.y;
	m_RightTop.y = temp_RightTop.y;
	m_LeftBottom.y = temp_LeftBottom.y;
	/*_cprintf("after lefttop %d %d\n", temp_LeftTop.x, temp_LeftTop.y);
	_cprintf("after rightTop %d %d\n", temp_RightTop.x, temp_RightTop.y);
	_cprintf("after rightBottom %d %d\n", tem
}p_RightBottom.x, temp_RightBottom.y);
	_cprintf("after leftBottom %d %d\n", temp_LeftBottom.x, temp_LeftBottom.y);*/

	/*_cprintf("\n\n\n");*/
	return this;
}
Shape* MRect::LeftToRight(CRect rect) {
	temp_LeftTop.x = rect.left + rect.right - temp_LeftTop.x;
	temp_RightBottom.x = rect.left + rect.right - temp_RightBottom.x;
	temp_RightTop.x = rect.left + rect.right - temp_RightTop.x;
	temp_LeftBottom.x = rect.left + rect.right - temp_LeftBottom.x;

	m_LeftTop.x = temp_LeftTop.x;
	m_RightBottom.x = temp_RightBottom.x;
	m_RightTop.x = temp_RightTop.x;
	m_LeftBottom.x = temp_LeftBottom.x;
	return this;
}
CRect MRect::GetBoundaryRect() {
	double minx = m_LeftTop.x;
	double maxx = m_LeftTop.x;
	double miny = m_LeftTop.y;
	double maxy = m_LeftTop.y;
	minx = min(minx, m_LeftBottom.x);
	minx = min(minx, m_RightBottom.x);
	minx = min(minx, m_RightTop.x);
	maxx = max(maxx, m_LeftBottom.x);
	maxx = max(maxx, m_RightBottom.x);
	maxx = max(maxx, m_RightTop.x);

	miny = min(miny, m_LeftBottom.y);
	miny = min(miny, m_RightBottom.y);
	miny = min(miny, m_RightTop.y);
	maxy = max(maxy, m_LeftBottom.y);
	maxy = max(maxy, m_RightBottom.y);
	maxy = max(maxy, m_RightTop.y);
	//_cprintf("MRect GetBoundaryRect\n");
	return CRect(minx,miny,maxx,maxy);
}
CPoint MRect::GetCenterPoint() {
	return CPoint((m_LeftTop.x+m_RightBottom.x)>>1,(m_LeftTop.y+m_RightBottom.y)>>1);
}
MRect MRect::GetCopy() {
	return MRect(this);
}
int MRect::GraphType() {
	return 2;
}
CPoint MRect::getLeftTop() {
	return m_LeftTop;
}
CPoint MRect::getRightBottom() {
	return m_RightBottom;
}
void MRect::setLeftTop(CPoint LT) {
	this->m_LeftTop = LT;
}
void MRect::setRightBottom(CPoint RB) {
	this->m_RightBottom = RB;
}
int MRect::isInRect(CRect rect) {
	if (IsPtInRect(m_LeftTop, rect)) return true;
	if (IsPtInRect(m_RightBottom, rect)) return true;
	if (IsPtInRect(m_LeftBottom, rect)) return true;
	if (IsPtInRect(m_RightTop, rect)) return true;

	if (SegmentIntersection(temp_LeftTop, temp_RightTop, rect.TopLeft(), rect.BottomRight())) return true;
	if (SegmentIntersection(temp_RightTop, temp_RightBottom, rect.TopLeft(), rect.BottomRight())) return true;
	if (SegmentIntersection(temp_RightBottom, temp_LeftBottom, rect.TopLeft(), rect.BottomRight())) return true;
	if (SegmentIntersection(temp_LeftBottom, temp_LeftTop, rect.TopLeft(), rect.BottomRight())) return true;

	CPoint RT = CPoint(rect.right, rect.top);
	CPoint LB = CPoint(rect.left, rect.bottom);
	if (SegmentIntersection(temp_RightBottom, temp_LeftBottom, RT, LB)) return true;
	if (SegmentIntersection(temp_LeftBottom, temp_LeftTop, RT, LB)) return true;
	if (SegmentIntersection(temp_RightBottom, temp_LeftBottom, RT, LB)) return true;
	if (SegmentIntersection(temp_LeftBottom, temp_LeftTop, RT, LB)) return true;

	return false;
}
double MRect::Left() {
	return m_Left;
}
double MRect::Right() {
	return m_Right;
}
double MRect::Top() {
	return m_Top;
}
double MRect::Bottom() {
	return m_Bottom;
}
void MRect::Draw_Line(CPoint ptStart, CPoint ptEnd, CDC *pDC, int penWidth, COLORREF color) {
	CPen m_pen;//首先定义一个对象
	CPen *oldPen;
	m_pen.CreatePen(PS_SOLID, penWidth, color);//创建一个画笔(这里是实线画笔)
	oldPen = pDC->SelectObject(&m_pen);//将画笔对象选入DC，替换oldPen
	pDC->MoveTo(ptStart);
	pDC->LineTo(ptEnd);
	pDC->SelectObject(oldPen);
	return;

}
void MRect::RefreshData() {
	m_LeftTop = temp_LeftTop;
	m_RightBottom = temp_RightBottom;
	m_LeftBottom = temp_LeftBottom;
	m_RightTop = temp_RightTop;
	scale = 1.0;
	angle = 0.0;
	//_cprintf("MRect RefreshData\n");
}
