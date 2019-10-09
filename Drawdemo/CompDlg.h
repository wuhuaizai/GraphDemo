#pragma once


// CompDlg 对话框
#include "conio.h"
class CDrawdemoView;
class CompDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CompDlg)

public:
	CompDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CompDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COMP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
