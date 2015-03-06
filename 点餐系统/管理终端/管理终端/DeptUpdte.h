#pragma once


// CDeptUpdte 对话框

class CDeptUpdte : public CDialogEx
{
	DECLARE_DYNAMIC(CDeptUpdte)

public:
	CDeptUpdte(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDeptUpdte();

// 对话框数据
	enum { IDD = IDD_DIALOG10 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton2();
};
