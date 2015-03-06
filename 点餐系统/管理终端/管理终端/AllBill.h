#pragma once
#include "afxcmn.h"


// CAllBill 对话框

class CAllBill : public CDialogEx
{
	DECLARE_DYNAMIC(CAllBill)

public:
	CAllBill(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAllBill();

// 对话框数据
	enum { IDD = IDD_ALL_BILL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	void Update(CString bill_of_find);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
