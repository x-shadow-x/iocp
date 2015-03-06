#pragma once


// CDeptAdd 对话框

class CDeptAdd : public CDialogEx
{
	DECLARE_DYNAMIC(CDeptAdd)

public:
	CDeptAdd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDeptAdd();

// 对话框数据
	enum { IDD = IDD_DIALOG9 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
