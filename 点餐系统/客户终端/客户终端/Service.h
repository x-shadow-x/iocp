#pragma once


// CService 对话框

class CService : public CDialogEx
{
	DECLARE_DYNAMIC(CService)

public:
	CService(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CService();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton6();
	SOCKET sockClient;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
