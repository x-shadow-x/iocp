#pragma once


// CTableAdd 对话框

class CTableAdd : public CDialogEx
{
	DECLARE_DYNAMIC(CTableAdd)

public:
	CTableAdd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTableAdd();

// 对话框数据
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
