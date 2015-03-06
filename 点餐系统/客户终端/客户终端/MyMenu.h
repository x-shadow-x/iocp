#pragma once
#include "afxcmn.h"


// CMyMenu 对话框

class CMyMenu : public CDialogEx
{
	DECLARE_DYNAMIC(CMyMenu)

public:
	CMyMenu(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyMenu();

// 对话框数据
	enum { IDD = IDD_MY_MENU };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	CListCtrl m_list;
	virtual BOOL OnInitDialog();
	CListCtrl m_list1;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
