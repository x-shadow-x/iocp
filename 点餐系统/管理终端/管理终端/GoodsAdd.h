#pragma once


// CGoodsAdd 对话框

class CGoodsAdd : public CDialogEx
{
	DECLARE_DYNAMIC(CGoodsAdd)

public:
	CGoodsAdd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGoodsAdd();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
