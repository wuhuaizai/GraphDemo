// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���  
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�  
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ������� 
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// DrawdemoView.h : CDrawdemoView ��Ľӿ�
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
protected: // �������л�����
	CDrawdemoView();
	DECLARE_DYNCREATE(CDrawdemoView)

// ����
public:
	CDrawdemoDoc* GetDocument() const;
// ����
public:
	double GetDistance(CPoint a,CPoint b);
	double GetAngleFromPoints(double x2, double y2, double x1, double y1, double x3, double y3);
	//double GetAngleFromPoints(CPoint ptStart,CPoint ptCenter,CPoint ptEnd);
// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CDrawdemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
private://���������
	bool decided;
	CPoint _MoveStart,_MoveEnd;
	CPoint PStart,PEnd;
	CPoint initCenter;
	//-------------------------------�߽���
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
	CPoint SelectedCenter;//��תʱ��doc��ʹ���ˣ�public���ȽϷ���
	void showCurveControllPoint(CDC *pDC, CPoint point, int penWidth);
};

#ifndef _DEBUG  // DrawdemoView.cpp �еĵ��԰汾
inline CDrawdemoDoc* CDrawdemoView::GetDocument() const
   { return reinterpret_cast<CDrawdemoDoc*>(m_pDocument); }
#endif