#pragma once


// CompDlg �Ի���
#include "conio.h"
class CDrawdemoView;
class CompDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CompDlg)

public:
	CompDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CompDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COMP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
