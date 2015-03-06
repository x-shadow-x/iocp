#pragma once


// CDishesAdd 对话框

class CDishesAdd : public CDialogEx
{
	DECLARE_DYNAMIC(CDishesAdd)

public:
	CDishesAdd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDishesAdd();

// 对话框数据
	enum { IDD = IDD_DIALOG7 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
