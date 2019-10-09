#include "stdafx.h"
#include "MPolygon.h"
#include "GlobalUtil.h"

MPolygon::MPolygon():Shape(){
	isSelected = false;
}
MPolygon::MPolygon(vector<CPoint> vertices,COLORREF color,int penWidth):Shape() {
	this->vertices = vertices;
	temp_vertices = vertices;
	this->color = color;
	this->penWidth = penWidth;
	fillColor = RGB(255, 255, 255);
	angle = 0.0;
	scale = 1.0;
	isSelected = false;
}
MPolygon::MPolygon(MPolygon *pMPolygon) {
	color = pMPolygon->color;
	penWidth = pMPolygon->penWidth;
	fillColor = pMPolygon->fillColor;
	angle = pMPolygon->angle;
	scale = pMPolygon->scale;
	centerPoint = pMPolygon->GetCenterPoint();
	vertices = pMPolygon->vertices;
}

MPolygon::~MPolygon()
{
}
void MPolygon::Draw(CDC* pDC) {
	CPen m_pen;//首先定义一个对象
	CPen *oldPen;
	m_pen.CreatePen(PS_SOLID, this->penWidth, this->color);//创建一个画笔(这里是实线画笔)
	oldPen = pDC->SelectObject(&m_pen);//将画笔对象选入DC，替换oldPen
	int n = vertices.size();
	//处理临时的点
	/*for (int i = 0; i < n; i++) {
		temp_vertices[i].x= ((vertices[i].x - centerPoint.x)*cos(angle) - (vertices[i].y - centerPoint.y)*sin(angle)) + centerPoint.x;
		temp_vertices[i].y = ((vertices[i].y - centerPoint.y)*cos(angle) + (vertices[i].x - centerPoint.x)*sin(angle)) + centerPoint.y;
	}*/
	//
	pDC->MoveTo(temp_vertices[0]);
	
	for (int i = 1; i <=n; i++) {
		int e = i % n;
		pDC->LineTo(temp_vertices[e]);
	}
	for (int i = 0; i < n; i++) {
		pDC->MoveTo(temp_vertices[i]);
		pDC->LineTo(temp_vertices[i]);
	}
	pDC->SelectObject(oldPen);
}
void MPolygon::Draw(CDC* pDC,COLORREF tempcolor) {
	CPen m_pen;//首先定义一个对象
	CPen *oldPen;
	m_pen.CreatePen(PS_SOLID, this->penWidth, tempcolor);//创建一个画笔(这里是实线画笔)
	oldPen = pDC->SelectObject(&m_pen);//将画笔对象选入DC，替换oldPen
	int n = vertices.size();
	//处理临时的点
	/*for (int i = 0; i < n; i++) {
	temp_vertices[i].x= ((vertices[i].x - centerPoint.x)*cos(angle) - (vertices[i].y - centerPoint.y)*sin(angle)) + centerPoint.x;
	temp_vertices[i].y = ((vertices[i].y - centerPoint.y)*cos(angle) + (vertices[i].x - centerPoint.x)*sin(angle)) + centerPoint.y;
	}*/
	//
	pDC->MoveTo(temp_vertices[0]);

	for (int i = 1; i <= n; i++) {
		int e = i % n;
		pDC->LineTo(temp_vertices[e]);
	}
	for (int i = 0; i < n; i++) {
		pDC->MoveTo(temp_vertices[i]);
		pDC->LineTo(temp_vertices[i]);
	}
	pDC->SelectObject(oldPen);
}
Shape* MPolygon::Move(double stepx, double stepy) {
	int n = vertices.size();
	for (int i = 0; i < n; i++) {
		vertices[i].x += stepx;
		vertices[i].y += stepy;
		temp_vertices[i].x += stepx;
		temp_vertices[i].y += stepy;
	}
	return this;
}
Shape* MPolygon::Rotate(CPoint center,double flAngle) {
	RotateCenter = center;
	flAngle = PI / 180.0*flAngle;
	angle += flAngle;
	
	int n = vertices.size();
	for (int i = 0; i < n; i++) {
		temp_vertices[i].x = ((vertices[i].x - RotateCenter.x)*cos(angle) - (vertices[i].y - RotateCenter.y)*sin(angle)) + RotateCenter.x;
		temp_vertices[i].y = ((vertices[i].y - RotateCenter.y)*cos(angle) + (vertices[i].x - RotateCenter.x)*sin(angle)) + RotateCenter.y;
	}
	return this;
}
Shape* MPolygon::Magnify(CPoint center,double flScale) {
	MagnifyCenter = center;
	scale = flScale;
	int n = vertices.size();
	for (int i = 0; i < n; i++) {
		temp_vertices[i].x = (vertices[i].x - MagnifyCenter.x)*scale + MagnifyCenter.x;
		temp_vertices[i].y = (vertices[i].y - MagnifyCenter.y)*scale + MagnifyCenter.y;
	}
	return this;
}
Shape* MPolygon::TopToBottom(CRect rect) {
	int n = vertices.size();
	for (int i = 0; i < n; i++) {
		temp_vertices[i].y =rect.top+rect.bottom -temp_vertices[i].y;
	}
	vertices = temp_vertices;
	return this;
}
Shape* MPolygon::LeftToRight(CRect rect) {
	int n = vertices.size();
	for (int i = 0; i < n; i++) {
		temp_vertices[i].x = rect.left + rect.right - temp_vertices[i].x;
	}
	vertices = temp_vertices;
	return this;
}
CRect MPolygon::GetBoundaryRect() {
	int minx = vertices[0].x;
	int miny = vertices[0].y;
	int maxx = vertices[0].x;
	int maxy = vertices[0].y;
	int n = vertices.size();
	for (int i = 0; i < n; i++) {
		minx = min(minx, vertices[i].x);
		miny = min(miny, vertices[i].y);
		maxx = max(maxx, vertices[i].x);
		maxy = max(maxy, vertices[i].y);
	}
	return CRect(minx,miny,maxx,maxy);
}
CPoint MPolygon::GetCenterPoint() {
	return GetBoundaryRect().CenterPoint();
}
MPolygon MPolygon::GetCopy() {
	return MPolygon(this);
}
int MPolygon::GraphType() {
	return 5;
}
vector<CPoint> MPolygon::GetVertices() {
	return vertices;
}
void MPolygon::SetVertices(vector<CPoint>& vertices) {
	this->vertices = vertices;
}
void MPolygon::Draw_BresenhamLine(CPoint ptStart, CPoint ptEnd, CDC *pDC, int penWidth, COLORREF color) {
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
int MPolygon::isInRect(CRect rect) {
	int n = vertices.size();
	CPoint RT = CPoint(rect.right, rect.top);
	CPoint LB = CPoint(rect.left, rect.bottom);
	for (int i = 0; i < n; i++) {
		int e = (i+1) % n;
		if(IsPtInRect(temp_vertices[i],rect))return true;
		if(IsPtInRect(temp_vertices[e],rect))return true;
		if (SegmentIntersection(temp_vertices[i], temp_vertices[e], rect.TopLeft(), rect.BottomRight()))return true;
		if (SegmentIntersection(temp_vertices[i], temp_vertices[e], RT, LB))return true;
	}
	return 0;
}
void MPolygon::RefreshData() {
	vertices = temp_vertices;
	scale = 1.0;
	angle = 0.0;
}