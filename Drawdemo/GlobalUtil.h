#pragma once
#include <math.h>
#include "Matrix.h"
const double eps = 1e-10;
int dcmp(double x);
CPoint operator-(CPoint A, CPoint B);
double Dot(CPoint A, CPoint B);
double Cross(CPoint A, CPoint B);
bool InSegment(CPoint P, CPoint A, CPoint B);
bool SegmentIntersection(CPoint a1, CPoint a2, CPoint b1, CPoint b2);
bool IsPtInRect(CPoint p, CRect rect);
double PtDistance(CPoint a, CPoint b);
int GetPointStateToRect(double x, double y, CRect rectRes);
int GetLineStateToRect(double flStartx, double flStarty, double flEndx, double flEndy, CRect rect);
CMatrix MovePointByMatrix(CPoint p, double stepx, double stepy);
CMatrix RotatePointByMatrix(CPoint p, CPoint center, double angle);
CMatrix MagnifyPointByMatrix(CPoint p, CPoint center, double scale);