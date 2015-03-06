#pragma once
#include "afxcmn.h"


// CServiceVip 对话框

class CServiceVip : public CDialogEx
{
	DECLARE_DYNAMIC(CServiceVip)

public:
	CServiceVip(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CServiceVip();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton4();
	CListCtrl m_list;
	virtual BOOL OnInitDialog();
};
