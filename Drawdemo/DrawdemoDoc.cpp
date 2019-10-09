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

// DrawdemoDoc.cpp : CDrawdemoDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Drawdemo.h"
#endif
#include "DrawdemoDoc.h"
#include "MainFrm.h"
#include <propkey.h>
#include "conio.h"
#include "CompDlg.h"
#include "DrawdemoView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
////////////////////

// CDrawdemoDoc

IMPLEMENT_DYNCREATE(CDrawdemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CDrawdemoDoc, CDocument)
	ON_COMMAND(ID_Line, &CDrawdemoDoc::OnLine)
	ON_COMMAND(ID_MOVE, &CDrawdemoDoc::OnMove)
	ON_COMMAND(ID_RECT, &CDrawdemoDoc::OnRect)
	ON_COMMAND(ID_CIRCLE, &CDrawdemoDoc::OnCircle)
	ON_COMMAND(ID_ELLIPSE, &CDrawdemoDoc::OnEllipse)
	ON_COMMAND(ID_POLYGON, &CDrawdemoDoc::OnPolygon)
	ON_COMMAND(ID_ROTATE, &CDrawdemoDoc::OnRotate)
	ON_COMMAND(ID_MAGNIFY, &CDrawdemoDoc::OnMagnify)
	ON_COMMAND(ID_SELECT, &CDrawdemoDoc::OnSelect)
	ON_COMMAND(ID_LEFTTORIGHT, &CDrawdemoDoc::OnLefttoright)
	ON_COMMAND(ID_TOPTOBOTTOM, &CDrawdemoDoc::OnToptobottom)
	ON_COMMAND(ID_LINEWEIGHT1, &CDrawdemoDoc::OnLineweight1)
	ON_COMMAND(ID_LINEWEIGHT2, &CDrawdemoDoc::OnLineweight2)
	ON_COMMAND(ID_LINEWEIGHT3, &CDrawdemoDoc::OnLineweight3)
	ON_COMMAND(ID_LINEWEIGHT5, &CDrawdemoDoc::OnLineweight5)
	ON_COMMAND(ID_LINEWEIGHT7, &CDrawdemoDoc::OnLineweight7)
	ON_COMMAND(ID_COLOR, &CDrawdemoDoc::OnColor)
	ON_COMMAND(ID_CURVE, &CDrawdemoDoc::OnCurve)
	ON_COMMAND(ID_BUTTONCOMP, &CDrawdemoDoc::OnButtoncomp)
END_MESSAGE_MAP()


// CDrawdemoDoc 构造/析构

CDrawdemoDoc::CDrawdemoDoc()
{
	// TODO: 在此添加一次性构造代码
	//globalColor = RGB(0, 0, 0);
	globalColor = RGB(0, 0, 0);
	globalPenWidth = 1;
	currentGraphType = 1;
	currentOperateType = 0;
}

CDrawdemoDoc::~CDrawdemoDoc()
{
	list<Shape*>::iterator it = m_shapeList.begin();
	for (; it != m_shapeList.end(); it++) {
		delete (*it);
	}
}

BOOL CDrawdemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CDrawdemoDoc 序列化

void CDrawdemoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CDrawdemoDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CDrawdemoDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CDrawdemoDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CDrawdemoDoc 诊断

#ifdef _DEBUG
void CDrawdemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDrawdemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


CRect CDrawdemoDoc::GetSelectGraphBoundaryRect() {
	CRect rectRltVal(0, 0, 0, 0);
	CRect rectTemp;
	int nflag = 0;
	int left = 10000;
	int right = 0;
	int bottom = 0;
	int top = 10000;
	if (HasGraphSelected()) {
		list<Shape*>::iterator it = m_shapeList.begin();
		for (; it != m_shapeList.end(); it++) {
			if ((*it)->GetIsSelect()) {
				CRect rect = (*it)->GetBoundaryRect();
				left = min(left,rect.left);
				top = min(top, rect.top);
				right = max(right, rect.right);
				bottom = max(bottom, rect.bottom);
			}
		}
	}
	return CRect(left, top, right, bottom);
}
int CDrawdemoDoc::GetSelectNum() {
	int num=0;
	list<Shape*>::iterator it = m_shapeList.begin();
	for (; it != m_shapeList.end(); it++) {
		num += (*it)->GetIsSelect();
	}
	return num;
}
bool CDrawdemoDoc::HasGraphSelected() {
	int num = 0;
	list<Shape*>::iterator it = m_shapeList.begin();
	for (; it != m_shapeList.end(); it++) {
		if ((*it)->GetIsSelect()) {
			return true;
		}
	}
	return false;
}

void CDrawdemoDoc::AddTail(Shape *shape) {
	m_shapeList.push_back(shape);
}
void CDrawdemoDoc::ChangeSelectedState(CRect rect) {
	list<Shape*>::iterator it = m_shapeList.begin();
	for (; it != m_shapeList.end(); it++) {
		int state = (*it)->isInRect(rect);
		if(state>0)
			(*it)->SetSelected(true);
		else
			(*it)->SetSelected(false);
		/*_cprintf("%d\n", (*it)->GetIsSelect());*/
	}
}
void CDrawdemoDoc::ClearSelectFlag() {
	list<Shape*>::iterator it = m_shapeList.begin();
	for (; it != m_shapeList.end(); it++) {
		if ((*it)->GetIsSelect())
			(*it)->SetSelected(false);
	}
	POSITION   pos = GetFirstViewPosition(); GetNextView(pos)->Invalidate(1);
}
void CDrawdemoDoc::DrawSelected(CDC* pDC) {
	list<Shape*>::iterator it = m_shapeList.begin();
	for (; it != m_shapeList.end(); it++) {
		if ((*it)->GetIsSelect())
			(*it)->Draw(pDC);
	}
}
void CDrawdemoDoc::DrawLastAdded(CDC* pDC) {
	list<Shape*>::iterator it = m_shapeList.end();
	it--;
	(*it)->Draw(pDC);
}
void CDrawdemoDoc::MoveSelected(double stepx, double stepy) {
	list<Shape*>::iterator it = m_shapeList.begin();
	for (; it != m_shapeList.end(); it++) {
		if((*it)->GetIsSelect())
			(*it)->Move(stepx, stepy);
	}
}
void CDrawdemoDoc::RotateSeleted(CPoint center,double angle) {
	list<Shape*>::iterator it = m_shapeList.begin();
	for (; it != m_shapeList.end(); it++) {
		if ((*it)->GetIsSelect())
			(*it)->Rotate(center, angle);
	}
}
void CDrawdemoDoc::MagnifySelected(CPoint center,double scale) {
	list<Shape*>::iterator it = m_shapeList.begin();
	for (; it != m_shapeList.end(); it++) {
		if ((*it)->GetIsSelect())
			(*it)->Magnify(center, scale);
	}
}
void CDrawdemoDoc::RefreshSelected() {
	list<Shape*>::iterator it = m_shapeList.begin();
	for (; it != m_shapeList.end(); it++) {
		if ((*it)->GetIsSelect()) {
			(*it)->RefreshData();
			_cprintf("call RefreshSelected\n");
		}
			
	}
}
void CDrawdemoDoc::LeftToRightSelected(CRect rect) {
	list<Shape*>::iterator it = m_shapeList.begin();
	for (; it != m_shapeList.end(); it++) {
		if ((*it)->GetIsSelect())
			(*it)->LeftToRight(rect);
	}
}
void CDrawdemoDoc::TopToBottomSelected(CRect rect) {
	list<Shape*>::iterator it = m_shapeList.begin();
	for (; it != m_shapeList.end(); it++) {
		if ((*it)->GetIsSelect())
			(*it)->TopToBottom(rect);
	}
}
void CDrawdemoDoc::ComplexChangeAll(CRect rect,double movex,double movey,double rotate,double magnify) {
	list<Shape*>::iterator it = m_shapeList.begin();
	for (; it != m_shapeList.end(); it++) {
		if ((*it)->GetIsSelect()) {
			(*it)->Move(movex, movey);
			CPoint before = rect.CenterPoint();
			CPoint after = CPoint(before.x + movex, before.y + movey);
			(*it)->Rotate(after, rotate);
			(*it)->RefreshData();
			(*it)->Magnify(after, magnify);
		}
	}
	RefreshSelected();
	ClearSelectFlag();
}
//void CDrawdemoDoc::HighLightSelectedShape() {
//	list<Shape*>::iterator it = m_shapeList.begin();
//	for (; it != m_shapeList.end(); it++) {
//		if ((*it)->GetIsSelect()) {
//			(*it)->SetColor(RGB(255, 0, 0));
//		}
//	}
//	CDrawdemoView* pView = (CDrawdemoView*)((CMainFrame*)AfxGetApp()->GetMainWnd())->GetActiveView();
//	pView->Invalidate(1);
//}
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// CDrawdemoDoc 命令


void CDrawdemoDoc::OnLine()
{
	ClearSelectFlag();
	currentGraphType = 1;
	currentOperateType = 0;
	// TODO: 在此添加命令处理程序代码
}


void CDrawdemoDoc::OnMove()
{
	//SetCursor(LoadCursor(NULL, IDC_SIZEALL));//move
	currentGraphType = 0;
	currentOperateType = 1;
	// TODO: 在此添加命令处理程序代码
}


void CDrawdemoDoc::OnRect()
{
	ClearSelectFlag();
	currentGraphType = 2;
	currentOperateType = 0;
	// TODO: 在此添加命令处理程序代码
}


void CDrawdemoDoc::OnCircle()
{
	ClearSelectFlag();
	currentGraphType = 3;
	currentOperateType = 0;
	// TODO: 在此添加命令处理程序代码
}


void CDrawdemoDoc::OnEllipse()
{
	ClearSelectFlag();
	currentGraphType = 4;
	currentOperateType = 0;
	// TODO: 在此添加命令处理程序代码
}


void CDrawdemoDoc::OnPolygon()
{
	ClearSelectFlag();
	currentGraphType = 5;
	currentOperateType = 0;
	// TODO: 在此添加命令处理程序代码
}


void CDrawdemoDoc::OnRotate()
{
	currentGraphType = 0;
	currentOperateType = 2;
	// TODO: 在此添加命令处理程序代码
}


void CDrawdemoDoc::OnMagnify()
{
	currentGraphType = 0;
	currentOperateType = 3;
	// TODO: 在此添加命令处理程序代码
}


void CDrawdemoDoc::OnSelect()
{
	ClearSelectFlag();
	currentGraphType = 0;
	currentOperateType = 5;
	// TODO: 在此添加命令处理程序代码
}


void CDrawdemoDoc::OnLefttoright()
{
	POSITION   pos = GetFirstViewPosition();
	currentGraphType = 0;
	currentOperateType = 6;
	LeftToRightSelected(GetSelectGraphBoundaryRect());
	ClearSelectFlag();
	 GetNextView(pos)->Invalidate(1);
	// TODO: 在此添加命令处理程序代码
}


void CDrawdemoDoc::OnToptobottom()
{
	POSITION   pos = GetFirstViewPosition();
	currentGraphType = 0;
	currentOperateType = 7;
	TopToBottomSelected(GetSelectGraphBoundaryRect());
	ClearSelectFlag();
	GetNextView(pos)->Invalidate(1);
	// TODO: 在此添加命令处理程序代码
}


void CDrawdemoDoc::OnLineweight1()
{
	ClearSelectFlag();
	currentOperateType = 0;
	globalPenWidth = 1;
	// TODO: 在此添加命令处理程序代码
}


void CDrawdemoDoc::OnLineweight2()
{
	ClearSelectFlag();
	currentOperateType = 0;
	globalPenWidth = 2;
	// TODO: 在此添加命令处理程序代码
}


void CDrawdemoDoc::OnLineweight3()
{
	ClearSelectFlag();
	currentOperateType = 0;
	globalPenWidth = 3;
	// TODO: 在此添加命令处理程序代码
}


void CDrawdemoDoc::OnLineweight5()
{
	ClearSelectFlag();
	currentOperateType = 0;
	globalPenWidth =5;
	// TODO: 在此添加命令处理程序代码
}


void CDrawdemoDoc::OnLineweight7()
{
	ClearSelectFlag();
	currentOperateType = 0;
	globalPenWidth = 7;
	// TODO: 在此添加命令处理程序代码
}


void CDrawdemoDoc::OnColor()
{
	ClearSelectFlag();
	currentOperateType = 0;


	CMFCRibbonBar* pRibbon = ((CMainFrame*)AfxGetMainWnd()->GetTopLevelFrame())->GetRibbonBar();
	ASSERT_VALID(pRibbon);
	CMFCRibbonColorButton* pFontColorBtn = DYNAMIC_DOWNCAST(CMFCRibbonColorButton, pRibbon->FindByID(ID_COLOR));
	globalColor = pFontColorBtn->GetColor();
	// TODO: 在此添加命令处理程序代码
}


void CDrawdemoDoc::OnCurve()
{
	ClearSelectFlag();
	currentGraphType = 6;
	currentOperateType = 0;
	// TODO: 在此添加命令处理程序代码
}


void CDrawdemoDoc::OnButtoncomp()
{
	// TODO: 在此添加命令处理程序代码
	currentGraphType = 0;
	currentOperateType = 0;
	CompDlg compdlg;
	compdlg.DoModal();
}
