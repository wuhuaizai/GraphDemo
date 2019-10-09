#include "stdafx.h"
#include "Shape.h"


Shape::Shape()
{
	color = RGB(0, 0, 0);
	penWidth = 2;
	fillColor = RGB(255, 255, 255);
	angle = 0.0;
	scale = 1.0;
	isSelected = false;
	centerPoint = CPoint(0, 0);
	RotateCenter = centerPoint;
	MagnifyCenter = centerPoint;
}

Shape::Shape(Shape* pShape) {
	color = pShape->color;
	penWidth = pShape->penWidth;
	fillColor = pShape->fillColor;
	angle = pShape->angle;
	scale = pShape->scale;
	isSelected = false;
	//copy centerpoint?
}

Shape::~Shape()
{
}

Shape Shape::GetCopy() {
	Shape shape = Shape(this);
	return shape;
}

