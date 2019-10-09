// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。  
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。  
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问 
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// DrawdemoView.h : CDrawdemoView 类的接口
//
#pragma once
#include<math.h>
#include<algorithm>
#include<vector>
#include <list>
#include"Shape.h"
#include "BezierCurve.h"
class CompDlg;
class CDrawdemoDoc;
class CDrawdemoView : public CView
{
protected: // 仅从序列化创建
	CDrawdemoView();
	DECLARE_DYNCREATE(CDrawdemoView)

// 特性
public:
	CDrawdemoDoc* GetDocument() const;
// 操作
public:
	double GetDistance(CPoint a,CPoint b);
	double GetAngleFromPoints(double x2, double y2, double x1, double y1, double x3, double y3);
	//double GetAngleFromPoints(CPoint ptStart,CPoint ptCenter,CPoint ptEnd);
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CDrawdemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
private://保存旧数据
	bool decided;
	CPoint _MoveStart,_MoveEnd;
	CPoint PStart,PEnd;
	CPoint initCenter;
	//-------------------------------线结束
	CRect tempRect; CPoint tempStart;
	//-------------------------------rec over
	//double tempR;
	//-------------------------------circle over
	CPoint EllipseCenter,EllipseEnd;
	//-------------------------------Ellipse over
	std::vector<CPoint> points;
	//-------------------------------polygon over
	std::vector<CPoint> curvePoints;
	//-------------------------------curve over
	CRect SelectRect;
public:
	void ComplexChangeAll(double movex, double movey, double rotate, double magnify);
	void bezier(CDC *pDC, vector<CPoint>&temp_Points);
	CPoint SelectedCenter;//翻转时在doc类使用了，public化比较方便
	void showCurveControllPoint(CDC *pDC, CPoint point, int penWidth);
};

#ifndef _DEBUG  // DrawdemoView.cpp 中的调试版本
inline CDrawdemoDoc* CDrawdemoView::GetDocument() const
   { return reinterpret_cast<CDrawdemoDoc*>(m_pDocument); }
#endif