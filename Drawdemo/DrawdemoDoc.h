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

// DrawdemoDoc.h : CDrawdemoDoc ��Ľӿ�
//

#include<list>
#include "Shape.h"
#include <algorithm>
using namespace std;
#pragma once

class CDrawdemoView;
class CDrawdemoDoc : public CDocument
{
protected: // �������л�����
	CDrawdemoDoc();
	DECLARE_DYNCREATE(CDrawdemoDoc)

// ����
public:

// ����
public:
	COLORREF	globalColor;
	int			globalPenWidth;
	int			currentGraphType;//0�ߣ�1�ߣ�2���Σ�3Բ��4��Բ��5����Σ�*-1 �������⻭
	int			currentOperateType;//0���ƣ�1ƽ�ƣ�2��ת��3���ţ�4�Գƣ�5��ȡ��6 ˮƽ��ת��7 ��ֱ��ת��
// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CDrawdemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	list<Shape*>m_shapeList;//������״
public:
	void ComplexChangeAll(CRect rect, double movex, double movey, double rotate, double magnify);
	CRect GetSelectGraphBoundaryRect();//����ͼ�ε���߿�
	bool HasGraphSelected();//�Ƿ���ͼ��ѡ��
	int GetSelectNum();//ѡ�м���ͼ��
	void AddTail(Shape* shape);
	//void HighLightSelectedShape();
	void ChangeSelectedState(CRect rect);
	void DrawLastAdded(CDC* pDC);
	void DrawSelected(CDC* pDC);
	void RefreshSelected();
	void ClearSelectFlag();
	void MoveSelected(double stepx, double stepy);
	void RotateSeleted(CPoint center,double angle);
	void MagnifySelected(CPoint center,double scale);
	void LeftToRightSelected(CRect rect);
	void TopToBottomSelected(CRect rect);
public:

	afx_msg void OnLine();
	afx_msg void OnMove();
	afx_msg void OnRect();
	afx_msg void OnCircle();
	afx_msg void OnEllipse();
	afx_msg void OnPolygon();
	afx_msg void OnRotate();
	afx_msg void OnMagnify();
	afx_msg void OnSelect();
	afx_msg void OnLefttoright();
	afx_msg void OnToptobottom();
	afx_msg void OnLineweight1();
	afx_msg void OnLineweight2();
	afx_msg void OnLineweight3();
	afx_msg void OnLineweight5();
	afx_msg void OnLineweight7();
	afx_msg void OnColor();
	afx_msg void OnCurve();
	afx_msg void OnButtoncomp();
};
