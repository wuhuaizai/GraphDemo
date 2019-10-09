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

// DrawdemoView.cpp : CDrawdemoView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Drawdemo.h"
#endif

#include "DrawdemoDoc.h"
#include "DrawdemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "conio.h"


#include "Line.h"
#include "MRect.h"
#include "Circle.h"
#include "Ellipse.h"
#include "MPolygon.h"
#include "CompDlg.h"
// CDrawdemoView

IMPLEMENT_DYNCREATE(CDrawdemoView, CView)

BEGIN_MESSAGE_MAP(CDrawdemoView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDrawdemoView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CDrawdemoView 构造/析构

CDrawdemoView::CDrawdemoView()
{
	// TODO: 在此处添加构造代码
	decided = true;
	::AllocConsole();
	FILE *fp;
	freopen_s(&fp, "CONOUT$", "w+t", stdout);
	_cprintf("!!!start printf!!!");
}

CDrawdemoView::~CDrawdemoView()
{
	FreeConsole();
}

BOOL CDrawdemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	return CView::PreCreateWindow(cs);
}

// CDrawdemoView 绘制

void CDrawdemoView::OnDraw(CDC* pDC)
{
	CDrawdemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此处为本机数据添加绘制代码
	pDC->SelectStockObject(NULL_BRUSH);

	list<Shape*>shapes = pDoc->m_shapeList;
	list<Shape*>::iterator it = shapes.begin();
	for (; it != shapes.end() ; it++) {
		/*_cprintf("type%d\n", (*it)->GraphType());*/
		if ((*it)->GetIsSelect()) {//选中临时画红色
			(*it)->Draw(pDC, RGB(255, 0, 0));
		}
		else
			(*it)->Draw(pDC);
		//画自己的颜色
	}
	CPen m_pen;//首先定义一个对象
	CPen *oldPen;
	m_pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));//画笔(这里是实线画笔)
	oldPen = pDC->SelectObject(&m_pen);//将画笔对象选入DC，替换oldPen
	
	CRect BigRect = GetDocument()->GetSelectGraphBoundaryRect();
	pDC->Rectangle(&BigRect);

	pDC->SelectObject(oldPen);

}


// CDrawdemoView 打印


void CDrawdemoView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CDrawdemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CDrawdemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CDrawdemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CDrawdemoView::OnRButtonUp(UINT  nFlags , CPoint point)
{
	CClientDC dc(this);

	
	decided = true;

	int globalWidth = GetDocument()->globalPenWidth;
	int color = GetDocument()->globalColor;
	if (GetDocument()->currentGraphType == 6) {
		curvePoints.push_back(point);
		GetDocument()->AddTail(new BezierCurve(curvePoints, color, globalWidth));
		GetDocument()->DrawLastAdded(&dc);
		curvePoints.clear();
		Invalidate(1);
	}
	//delete nowLine;
	//-------------------------------
	//ClientToScreen(&point);
	//OnContextMenu(this, point);
}

void CDrawdemoView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

void CDrawdemoView::ComplexChangeAll(double movex, double movey, double rotate, double magnify) {
	GetDocument()->ComplexChangeAll(SelectRect, movex, movey, rotate, magnify);
	Invalidate(1);
}
// CDrawdemoView 诊断

#ifdef _DEBUG
void CDrawdemoView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawdemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawdemoDoc* CDrawdemoView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawdemoDoc)));
	return (CDrawdemoDoc*)m_pDocument;
}
#endif //_DEBUG

///////////////////////////////////////////
void CDrawdemoView::bezier(CDC *pDC, vector<CPoint>&temp_Points)
{
	double *pflX, *pflY;
	double flTempx, flTempy, flU;//flu-------u参数	
	int i, n, j;

	n = temp_Points.size();
	if (n<2) return;

	pflX = new double[n];
	pflY = new double[n];

	flTempx = temp_Points[0].x;
	flTempy = temp_Points[0].y;

	for (i = 0; i<n; i++) {
		pflX[i] = temp_Points[i].x*1.0;
		pflY[i] = temp_Points[i].y*1.0;
	}

	for (flU = 0; flU <= 1; flU += 0.05/n) {
		for (i = 1; i<n; i++) {
			for (j = 0; j<n - i; j++) {
				pflX[j] = (1 - flU)*pflX[j] + flU*pflX[j + 1];
				pflY[j] = (1 - flU)*pflY[j] + flU*pflY[j + 1];
			}
		}
		pDC->MoveTo(flTempx, flTempy);
		pDC->LineTo(pflX[0], pflY[0]);
		flTempx = pflX[0];
		flTempy = pflY[0];
	}
	delete[] pflX;
	delete[] pflY;
	return;
}

void CDrawdemoView::showCurveControllPoint(CDC *pDC,CPoint point,int penWidth) {
	pDC->MoveTo(point.x, point.y - 1 - penWidth);
	pDC->LineTo(point.x, point.y + 2 + penWidth);
	pDC->MoveTo(point.x - 1 - penWidth, point.y);
	pDC->LineTo(point.x + 2 + penWidth, point.y);
}
///////////////////////////////////////////

//
double CDrawdemoView::GetDistance(CPoint a,CPoint b) {
	int delx = a.x - b.x;
	int dely = a.y - b.y;
	return sqrt((delx*delx)+(dely*dely));
}
// CDrawdemoView 消息处理程序
//
double CDrawdemoView::GetAngleFromPoints(double x2, double y2, double x1, double y1, double x3, double y3)
{
	double xm = x2;
	double ym = y2;
	CPoint oldPoint = CPoint(x1, y1);
	CPoint point = CPoint(x3, y3);

	double a = sqrt((xm - point.x)*(xm - point.x) + (ym - point.y)*(ym - point.y)),
		b = sqrt((oldPoint.x - point.x)*(oldPoint.x - point.x) + (oldPoint.y - point.y)*(oldPoint.y - point.y)),
		c = sqrt((xm - oldPoint.x)*(xm - oldPoint.x) + (ym - oldPoint.y)*(ym - oldPoint.y));
	double angle = (acos((a*a + c*c - b*b) / (2 * a*c)) / PI * 180.0);
	double angle_judge = (oldPoint.x - xm)*(point.y - ym) - (point.x - xm)*(oldPoint.y - ym); //>0顺时针，<0逆时针
	angle = (angle_judge >= 0.0 ? angle : -angle);
	return angle;
}
//

void CDrawdemoView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	decided = false;
	int operate = GetDocument()->currentOperateType;
	int globalWidth = GetDocument()->globalPenWidth;
	int color = GetDocument()->globalColor;
	//debug
	_cprintf("GraphyType:%d  operate:%d\n", GetDocument()->currentGraphType, operate);
	//debug
	//
	CPen m_pen;//首先定义一个对象
	CPen *oldPen;
	m_pen.CreatePen(PS_SOLID, globalWidth, color);//创建一个画笔(这里是实线画笔)
	oldPen = dc.SelectObject(&m_pen);//将画笔对象选入DC，替换oldPen
	//
	switch (GetDocument()->currentGraphType)
	{
		case 1: {
			PStart = point; PEnd = point;
			break;
		}
		case 2: {
			PStart = PEnd = point;
			break;
		}
		case 3: {
			PStart = PEnd = point;
			break;
		}
		case 4: {

			PStart = PEnd = point;
			break;
		}
		case 5: {
			
			points.push_back(point);
			if(points.size()>=2) {
				dc.MoveTo(points[points.size() - 2]);
				dc.LineTo(point);
				if (GetDistance(point, points[0]) < 18.0) {
					dc.MoveTo(point);
					dc.LineTo(points[0]);
					//points.pop_back();
					/*if (nowLine) { delete nowLine; nowLine = nullptr; }
					nowLine = new MPolygon(points,color, globalWidth);*/
					GetDocument()->AddTail(new MPolygon(points, color, globalWidth));
					GetDocument()->DrawLastAdded(&dc);
					points.clear();
					decided = true;
				}
			}
			else {
				PStart = PEnd=point;
				dc.MoveTo(point);
				dc.LineTo(point);
			}
			_cprintf("pointNum %d\n", points.size());
			break;
		}
		case 6: {
			int old_rop = dc.SetROP2(R2_NOT);
			curvePoints.push_back(PEnd);
			bezier(&dc, curvePoints);
			curvePoints.pop_back();
			dc.SetROP2(old_rop);

			//_cprintf("curve::::::add curve Point");
			/*int old_rop = dc.SetROP2(R2_XORPEN);
			bezier(&dc, curvePoints);*/

			curvePoints.push_back(point);
			showCurveControllPoint(&dc, point, globalWidth);
			PStart = PEnd = point;
			vector<CPoint>temp = curvePoints; temp.push_back(PEnd);
			bezier(&dc, temp);
			
			
			break;
		}
	default:
		break;
	}
	//----------------------------------------
	switch (operate)
	{
		//平移
		case 1: {
			SetCursor(LoadCursor(NULL, IDC_SIZEALL));
			_MoveStart = _MoveEnd = point;
			break;
		}
		case 2: {
			//SetCursor(LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_CROTATE), IMAGE_BITMAP,32,32,LR_COPYFROMRESOURCE));
			//SetCursor(LoadCursorFromFile(_T("res\cursor1.cur")));
			_MoveStart = _MoveEnd = point;
			break;
		}
		case 3:
		case 4:
		case 5:
		case 6:
			_MoveStart = _MoveEnd = point;
			break;
		default:
			break;
	}
	
	CView::OnLButtonDown(nFlags, point);
}


void CDrawdemoView::OnMouseMove(UINT nFlags, CPoint point)
{
	//_cprintf("decided %d", decided);
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);
	dc.SetROP2(R2_NOT);
	COLORREF color = GetDocument()->globalColor;
	int penWidth = GetDocument()->globalPenWidth;
	int operate = GetDocument()->currentOperateType;
	dc.SelectStockObject(NULL_BRUSH);
	dc.SetBkMode(TRANSPARENT);
	//未放下的颜色
	CPen m_pen;//首先定义一个对象
	CPen *oldPen;
	m_pen.CreatePen(PS_SOLID, penWidth, RGB(0,255,0));//创建一个画笔(这里是实线画笔)
	oldPen = dc.SelectObject(&m_pen);//将画笔对象选入DC，替换oldPen
	//未放下的颜色
	if (!decided) {
		switch (GetDocument()->currentGraphType)
		{
		case 1: {
			int old_rop = dc.SetROP2(R2_XORPEN);
			dc.MoveTo(PStart);
			dc.LineTo(PEnd);
			PEnd = point;
			dc.MoveTo(PStart);
			dc.LineTo(PEnd);
			dc.SetROP2(old_rop);
			break;
		}
		case 2: {
			int old_rop = dc.SetROP2(R2_XORPEN);
			CRect rect = CRect(PStart, PEnd);
			rect.NormalizeRect();
			dc.MoveTo(rect.TopLeft());
			dc.LineTo(CPoint(rect.right, rect.top));
			dc.LineTo(rect.BottomRight());
			dc.LineTo(CPoint(rect.left, rect.bottom));
			dc.LineTo(rect.TopLeft());
			//dc.Rectangle(&rect);

			PEnd = point;

			rect = CRect(PStart, PEnd);
			rect.NormalizeRect();
			dc.MoveTo(rect.TopLeft());
			dc.LineTo(CPoint(rect.right, rect.top));
			dc.LineTo(rect.BottomRight());
			dc.LineTo(CPoint(rect.left, rect.bottom));
			dc.LineTo(rect.TopLeft());
			//dc.Rectangle(&rect);
			dc.SetROP2(old_rop);
			//_cprintf("point %d %d\n", PEnd.x, PEnd.y); _cprintf("rect %d %d\n", rect.BottomRight().x, rect.BottomRight().y);
			break;
		}
		case 3: {
			int old_rop = dc.SetROP2(R2_XORPEN);

			double tempR = GetDistance(PStart, PEnd);
			CRect rect = CRect(PStart.x - tempR, PStart.y - tempR, PStart.x + tempR, PStart.y + tempR);
			CPoint StartAndEnd = CPoint(PStart.x - tempR, PStart.y);
			dc.Arc(&rect, StartAndEnd, StartAndEnd);

			PEnd = point;

			tempR = GetDistance(PStart, PEnd);
			rect = CRect(PStart.x - tempR, PStart.y - tempR, PStart.x + tempR, PStart.y + tempR);
			StartAndEnd = CPoint(PStart.x - tempR, PStart.y);
			dc.Arc(&rect, StartAndEnd, StartAndEnd);

			dc.SetROP2(old_rop);
			break;
		}
		case 4: {
			int old_rop = dc.SetROP2(R2_XORPEN);
			CRect rect = CRect(PStart.x - abs(PStart.x - PEnd.x), PStart.y - abs(PStart.y - PEnd.y), PStart.x + abs(PStart.x - PEnd.x), PStart.y + abs(PStart.y - PEnd.y));
			//rect.NormalizeRect();
			CPoint startAndEnd = CPoint(PStart.x - abs(PStart.x - PEnd.x), PStart.y);
			dc.Arc(&rect, startAndEnd, startAndEnd);
			PEnd = point;
			rect = CRect(PStart.x - abs(PStart.x - PEnd.x), PStart.y - abs(PStart.y - PEnd.y), PStart.x + abs(PStart.x - PEnd.x), PStart.y + abs(PStart.y - PEnd.y));
			//rect.NormalizeRect();
			startAndEnd = CPoint(PStart.x - abs(PStart.x - PEnd.x), PStart.y);
			dc.Arc(&rect, startAndEnd, startAndEnd);

			dc.SetROP2(old_rop);
			break;
		}
		case 5: {
			int old_rop = dc.SetROP2(R2_XORPEN);
			int n = points.size();
			dc.MoveTo(points[n - 1]);
			dc.LineTo(PEnd);
			PEnd = point;
			dc.MoveTo(points[n - 1]);
			dc.LineTo(PEnd);
			dc.SetROP2(old_rop);
			break;
		}
		case 6: {
			
			curvePoints.push_back(PEnd);
			bezier(&dc, curvePoints);
			curvePoints.pop_back();

			PEnd = point;

			curvePoints.push_back(point);
			bezier(&dc, curvePoints);
			curvePoints.pop_back();
			break;
		}
		default:
			break;
		}
		dc.SelectObject(oldPen);
		//-----------------------------------------
		switch (operate)
		{
		case 1: {
			if (GetDocument()->HasGraphSelected()) {
				SetCursor(LoadCursor(NULL, IDC_SIZEALL));//设置鼠标图标
				GetDocument()->DrawSelected(&dc);
				GetDocument()->MoveSelected(point.x-_MoveStart.x, point.y - _MoveStart.y);
		
				_MoveStart = point;

				GetDocument()->DrawSelected(&dc);
			}
			break;
		}
		case 2: {
			if (GetDocument()->HasGraphSelected()) {
				GetDocument()->DrawSelected(&dc);
				//CPoint center = GetDocument()->GetSelectGraphBoundaryRect().CenterPoint();
				double angle = GetAngleFromPoints(SelectedCenter.x, SelectedCenter.y, _MoveStart.x, _MoveStart.y, point.x, point.y);
				GetDocument()->RotateSeleted(SelectedCenter,angle);
				_MoveStart = point;
				GetDocument()->DrawSelected(&dc);
			}
			break;
		}
		case 3: {
			if (GetDocument()->HasGraphSelected()) {
				GetDocument()->DrawSelected(&dc);
				double dB = abs(SelectedCenter.x- _MoveStart.x);
				double dA = dB;
				if (_MoveStart.x != _MoveEnd.x||_MoveStart.y != _MoveEnd.y)
					dA = abs(_MoveEnd.x - SelectedCenter.x);
				double dmagnify = dA / dB;
				GetDocument()->MagnifySelected(SelectedCenter, dmagnify);
				_MoveEnd = point;
				GetDocument()->DrawSelected(&dc);
			}
			break;
		}
		case 5: {
			//选择框，只在移动时绘制，最后不加入list，重绘时就不会画出来了
			CRect rect = CRect(_MoveStart, _MoveEnd);
			rect.NormalizeRect();
			dc.Rectangle(&rect);
			_MoveEnd = point;
			rect = CRect(_MoveStart, _MoveEnd);
			rect.NormalizeRect();
			dc.Rectangle(&rect);
			break;
		}
		default:
			break;
		}	
	}
	dc.SelectObject(oldPen);
	CView::OnMouseMove(nFlags, point);
}


void CDrawdemoView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);
	
	COLORREF color = GetDocument()->globalColor;
	int penWidth = GetDocument()->globalPenWidth;
	int operate = GetDocument()->currentOperateType;
	//
	if (GetDocument()->currentGraphType != 5) {
		decided = true;
	}
	CPen m_pen;//首先定义一个对象
	CPen *oldPen;
	m_pen.CreatePen(PS_SOLID, penWidth, color);//创建一个画笔(这里是实线画笔)
	oldPen = dc.SelectObject(&m_pen);//将画笔对象选入DC，替换oldPen
									 //
	switch (GetDocument()->currentGraphType)
	{
	case 1: {
		//if (nowLine) { delete nowLine; nowLine = nullptr; }
		//nowLine = new CLine(PStart, PEnd, color, penWidth);
		GetDocument()->AddTail(new CLine(PStart, PEnd, color, penWidth));
		GetDocument()->DrawLastAdded(&dc);
		break;
	}
	case 2: {
		//if (nowLine) { delete nowLine; nowLine = nullptr; }
		//nowLine = new MRect(PStart, PEnd,color,penWidth);
		CRect rect = CRect(PStart, PEnd);
		rect.NormalizeRect();
		GetDocument()->AddTail(new MRect(rect.TopLeft(), rect.BottomRight(), color, penWidth));
		GetDocument()->DrawLastAdded(&dc);
		break;
	}
	case 3: {
		//if (nowLine) { delete nowLine; nowLine = nullptr; }
		//nowLine = new Circle(PStart, GetDistance(PStart,PEnd),color,penWidth);
		GetDocument()->AddTail(new Circle(PStart, GetDistance(PStart, PEnd), color, penWidth));
		GetDocument()->DrawLastAdded(&dc);
		break;
	}
	case 4: {
		//if (nowLine) { delete nowLine; nowLine = nullptr; }
		//nowLine = new MEllipse(PStart, abs(PStart.x-PEnd.x), abs(PStart.y-PEnd.y),color,penWidth);
		GetDocument()->AddTail(new MEllipse(PStart, abs(PStart.x - PEnd.x), abs(PStart.y - PEnd.y), color, penWidth));
		/*CRect rect = CRect(PStart.x - abs(PStart.x - PEnd.x), PStart.y - abs(PStart.y - PEnd.y), PStart.x + abs(PStart.x - PEnd.x), PStart.y + abs(PStart.y - PEnd.y));
		rect.NormalizeRect();
		CPoint startAndEnd = CPoint(PStart.x - abs(PStart.x - PEnd.x), PStart.y);
		dc.Arc(&rect, startAndEnd, startAndEnd);*/
		GetDocument()->DrawLastAdded(&dc);
		Invalidate(1);
		break;
	}
	case 5: {
		/*int n = points.size();
		if (n<2) {
			points.push_back(point);
			break;
		}
		else {
			dc.MoveTo(points[n - 1]);
			dc.LineTo(points[n - 2]);
			if (points.size() > 0) {
				decided = false;
			}
			break;
		}*/
		break;
	}
	case 6: {
		decided = false;
		
		_cprintf("curvePoint %d\n\n", curvePoints.size());
		break;
	}
	default:
		break;
	}
	//dc.SelectObject(oldPen);
	//-------------------------------------
	//m_pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));//创建一个画笔(这里是实线画笔)
	//oldPen = dc.SelectObject(&m_pen);//将画笔对象选入DC，替换oldPen
	switch (operate)
	{
	case 1:
		GetDocument()->ClearSelectFlag();
		break;
	case 2: {
		_cprintf("now SelectedCenter:x:%d y:%d\n", SelectedCenter.x, SelectedCenter.y);
		GetDocument()->RefreshSelected();
		GetDocument()->ClearSelectFlag();
		break;
	}
	case 3: {
		GetDocument()->RefreshSelected();
		GetDocument()->ClearSelectFlag();
		break;
	}
	case 4:
		//nowLine->Draw(&dc, color, penWidth);
		break;
	case 5: {
		CRect rect = CRect(_MoveStart, _MoveEnd); rect.NormalizeRect();
		//_cprintf("rect width:%d height%d\n", rect.Width(),rect.Height());
		SelectRect = rect;
		//_cprintf("selected retangle:left:%d top:%d right:%d bottom%d\n", SelectRect.left, SelectRect.top, SelectRect.right, SelectRect.bottom);
		GetDocument()->ChangeSelectedState(SelectRect);
		SelectedCenter = GetDocument()->GetSelectGraphBoundaryRect().CenterPoint();
		Invalidate(1);
		/*CRect BigRect = GetDocument()->GetSelectGraphBoundaryRect();
		dc.Rectangle(&BigRect);*/
		break;
	}
	default:
		break;
	}
	_cprintf("click At:x:%d y:%d\n", point.x, point.y);
	//?????????????????????
	dc.SelectObject(oldPen);
	CView::OnLButtonUp(nFlags, point);
}
