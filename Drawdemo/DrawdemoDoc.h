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

// DrawdemoDoc.h : CDrawdemoDoc 类的接口
//

#include<list>
#include "Shape.h"
#include <algorithm>
using namespace std;
#pragma once

class CDrawdemoView;
class CDrawdemoDoc : public CDocument
{
protected: // 仅从序列化创建
	CDrawdemoDoc();
	DECLARE_DYNCREATE(CDrawdemoDoc)

// 特性
public:

// 操作
public:
	COLORREF	globalColor;
	int			globalPenWidth;
	int			currentGraphType;//0线；1线；2矩形；3圆；4椭圆；5多边形；*-1 画笔随意画
	int			currentOperateType;//0绘制；1平移；2旋转；3缩放；4对称；5截取；6 水平翻转；7 垂直翻转；
// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CDrawdemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	list<Shape*>m_shapeList;//所有形状
public:
	void ComplexChangeAll(CRect rect, double movex, double movey, double rotate, double magnify);
	CRect GetSelectGraphBoundaryRect();//所有图形的外边框
	bool HasGraphSelected();//是否有图形选中
	int GetSelectNum();//选中几个图形
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
