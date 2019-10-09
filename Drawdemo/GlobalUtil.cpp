#include "stdafx.h"
#include "GlobalUtil.h"

int dcmp(double x)
{
	if (fabs(x)<eps) return 0;
	return x<0 ? -1 : 1;
}
CPoint operator-(CPoint A, CPoint B)
{
	return CPoint(A.x - B.x, A.y - B.y);
}
double Dot(CPoint A, CPoint B)
{
	return A.x*B.x + A.y*B.y;
}
double Cross(CPoint A, CPoint B)
{
	return A.x*B.y - A.y*B.x;
}
bool InSegment(CPoint P, CPoint A, CPoint B)
{
	return dcmp(Cross(A - P, B - P)) == 0 && dcmp(Dot(A - P, B - P)) <= 0;
}
bool SegmentIntersection(CPoint a1, CPoint a2, CPoint b1, CPoint b2)
{
	double c1 = Cross(a2 - a1, b1 - a1), c2 = Cross(a2 - a1, b2 - a1);
	double c3 = Cross(b2 - b1, a1 - b1), c4 = Cross(b2 - b1, a2 - b1);
	if (dcmp(c1)*dcmp(c2)<0 && dcmp(c3)*dcmp(c4)<0) return true;
	if (dcmp(c1) == 0 && InSegment(b1, a1, a2)) return true;
	if (dcmp(c2) == 0 && InSegment(b2, a1, a2)) return true;
	if (dcmp(c3) == 0 && InSegment(a1, b1, b2)) return true;
	if (dcmp(c4) == 0 && InSegment(a2, b1, b2)) return true;
	return false;
}
bool IsPtInRect(CPoint p, CRect rect) {
	if (p.x <= rect.right && p.x >= rect.left && p.y <= rect.bottom && p.y >= rect.top) {
		return true;
	}
	return false;
}
double PtDistance(CPoint a, CPoint b) {
	int delx = a.x - b.x;
	int dely = a.y - b.y;
	return sqrt((delx*delx) + (dely*dely));
}
int GetPointStateToRect(double x, double y, CRect rectRes)
{
	int val = 0;
	if (x<rectRes.left) val = 1;
	else if (x>rectRes.right) val = 2;
	if (y<rectRes.top) val = val + 4;
	else if (y>rectRes.bottom) val = val + 8;
	return val;
}
int GetLineStateToRect(double flStartx, double flStarty, double flEndx, double flEndy, CRect rect)
{
	int nRtVal = 0;
	int nPtStartState, nPtEndState;

	nPtStartState = GetPointStateToRect(flStartx, flStarty, rect);
	nPtEndState = GetPointStateToRect(flEndx, flEndy, rect);
	if (nPtStartState == 0 && nPtEndState == 0) {//in
		nRtVal = 2;
	}
	else if (nPtStartState == 0 || nPtEndState == 0) {//cut
		nRtVal = 1;
	}
	else if ((nPtStartState & nPtEndState) != 0) {	//out 
		nRtVal = 0;
	}
	else {
		//中点对分法
		int nTemp;
		float Startx, Starty, Endx, Endy, Tempx, Tempy;
		Startx = flStartx;
		Starty = flStarty;
		Endx = flEndx;
		Endy = flEndy;
		Tempx = (flStartx + flEndx) / 2;
		Tempy = (flStarty + flEndy) / 2;

		nTemp = GetPointStateToRect(Tempx, Tempy, rect);
		while (1) {
			if (nTemp == 0) {
				nRtVal = 1;
				break;
			}
			if (nTemp&nPtStartState) {
				Startx = Tempx;
				Starty = Tempy;
				nPtStartState = nTemp;
				Tempx = (Startx + Endx) / 2;
				Tempy = (Starty + Endy) / 2;
				nTemp = GetPointStateToRect(Tempx, Tempy, rect);
			}
			if (nTemp&nPtEndState) {
				Endx = Tempx;
				Endy = Tempy;
				nPtEndState = nTemp;
				Tempx = (Startx + Endx) / 2;
				Tempy = (Starty + Endy) / 2;
				nTemp = GetPointStateToRect(Tempx, Tempy, rect);
			}
			if (fabs(Startx - Endx)<1 && fabs(Starty - Endy)<1) {
				nRtVal = 0;
				break;
			}
		}//while(1)
	}//else
	return nRtVal;
}
CMatrix MovePointByMatrix(CPoint p, double stepx, double stepy) {
	CMatrix m1_3 = CMatrix(p);
	CMatrix change = CMatrix(3, 3);
	change.m[0] = 1.0; change.m[4] = 1.0; change.m[8] = 1.0;
	change.m[6] = stepx; change.m[7] = stepy;
	m1_3.show();
	change.show();
	CMatrix res = m1_3*change;
	
	return res;
}
//angle为弧度
CMatrix RotatePointByMatrix(CPoint p, CPoint center,double angle) {
	CMatrix m1_3 = CMatrix(p);
	CMatrix change = CMatrix(3, 3);
	change.m = { cos(angle),sin(angle),0,-sin(angle),cos(angle),0.0,0.0,0.0,1.0 };
	CMatrix move1 = CMatrix(3, 3);
	move1.m[0] = 1.0; move1.m[4] = 1.0; move1.m[8] = 1.0;
	move1.m[6] = center.x*-1.0; move1.m[7] = center.y*-1.0;

	CMatrix move2 = CMatrix(3, 3);
	move2.m[0] = 1.0; move2.m[4] = 1.0; move2.m[8] = 1.0;
	move2.m[6] = center.x*1.0; move2.m[7] = center.y*1.0;
	
	move1.show();
	//CMatrix temp = m1_3*move1;
	
	return m1_3*move1*change*move2;
	//return m1_3*move1*change;
}
CMatrix MagnifyPointByMatrix(CPoint p, CPoint center, double scale) {
	CMatrix m1_3 = CMatrix(p);
	CMatrix change = CMatrix(3, 3);
	change.m[0] = scale; change.m[4] = scale; change.m[8] = 1.0;
	CMatrix move = CMatrix(3, 3);
	move.m[0] = 1.0; move.m[4] = 1.0; move.m[8] = 1.0;
	move.m[6] = center.x*(1.0-scale); change.m[7] = center.y*(1.0-scale);
	return m1_3*change*move;
}