#pragma once
#include "afxcmn.h"


// CPurchase 对话框

class CPurchase : public CDialogEx
{
	DECLARE_DYNAMIC(CPurchase)

public:
	CPurchase(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPurchase();

// 对话框数据
	enum { IDD = IDD_PURCHASE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	void Update1(CString str);
	void Update2(CString str);
	void Update3(CString str);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
