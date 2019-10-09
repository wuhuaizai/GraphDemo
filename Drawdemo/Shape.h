#pragma once
#include<vector>
#include "conio.h"
using namespace std;
#define PI 3.14159265358979323846
class Shape
{
public:
	Shape();
	Shape(Shape* pShape);
	~Shape();
protected:
	COLORREF		color;
	int				penWidth;
	COLORREF		fillColor;
	float			angle;
	float			scale;
	bool			isSelected;
	CPoint			centerPoint;
	CPoint			RotateCenter;
	CPoint			MagnifyCenter;
public:
	virtual	void	Draw(CDC* pDC) { _cprintf("error!!error!!error!!error!!error!!error!!error!!error!!error!!\n"); };
	virtual	void	Draw(CDC* pDC,COLORREF tempcolor) { _cprintf("error!!error!!error!!error!!error!!error!!error!!error!!error!!\n"); };
	virtual Shape*	Move(double stepx, double stepy) { return this; };
	virtual Shape*	Rotate(CPoint center,double flAngle) { return this; };
	virtual Shape*	Magnify(CPoint center,double flScale) { return this; };
	virtual Shape*	TopToBottom(CRect rect) { return this; };
	virtual Shape*	LeftToRight(CRect rect) { return this; };
	Shape			GetCopy();
	virtual CRect	GetBoundaryRect() { return CRect(0, 0, 0, 0); };
	virtual CPoint	GetCenterPoint() { return CPoint(0, 0); };
	virtual int		isInRect(CRect rect) { return 0; };
	virtual int		GraphType() {
		return 0;
	}
	bool			GetIsSelect() {
		return this->isSelected;
	}
	virtual void	RefreshData() { _cprintf("error!!error!!error!!error!!error!!error!!error!!error!!error!!\n"); };
	COLORREF		GetColor() {
		return color;
	}
	virtual void	SetColor(COLORREF color) {
		this->color = color;
	};
	virtual void	SetPenWidth(int penWidth) {
		this->penWidth = penWidth;
	};
	virtual void SetSelected(bool state) { this->isSelected = state; };
};

