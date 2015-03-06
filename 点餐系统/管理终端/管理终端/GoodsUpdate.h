#pragma once


// CGoodsUpdate 对话框

class CGoodsUpdate : public CDialogEx
{
	DECLARE_DYNAMIC(CGoodsUpdate)

public:
	CGoodsUpdate(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGoodsUpdate();

// 对话框数据
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
