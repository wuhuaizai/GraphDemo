// CompDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Drawdemo.h"
#include "CompDlg.h"
#include "afxdialogex.h"
#include "DrawdemoView.h"
#include "MainFrm.h"

// CompDlg 对话框

IMPLEMENT_DYNAMIC(CompDlg, CDialogEx)

CompDlg::CompDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_COMP, pParent)
{

}

CompDlg::~CompDlg()
{
}

void CompDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CompDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CompDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CompDlg 消息处理程序


void CompDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	int x, y;
	x = y = 0.0;
	x = GetDlgItemInt(IDC_MOVEX);
	y = GetDlgItemInt(IDC_MOVEY);
	int rotate = GetDlgItemInt(IDC_ROTATEA);
	CString magnifyp;
	GetDlgItem(IDC_MAGNIFYP)->GetWindowText(magnifyp);
	double m = atof(magnifyp)/100;
	_cprintf("CompDlg::Entered::%d %d %d %lf\n", x, y,rotate,m);
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CDrawdemoView* pViw = (CDrawdemoView*)pFrame->GetActiveView();
	pViw->ComplexChangeAll(x, y, rotate, m);
	CDialogEx::OnOK();
}
