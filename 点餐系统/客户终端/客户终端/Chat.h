#pragma once


// CChat 对话框
#define WM_RECVDATA		WM_USER+1
class CChat : public CDialogEx
{
	DECLARE_DYNAMIC(CChat)

public:
	CChat(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChat();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg LRESULT OnRecvData(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	SOCKET sockClient;
public:
	bool InitSocket(void);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	static DWORD WINAPI ReceiveMessageThread(LPVOID IpParameter);
	afx_msg void OnBnClickedButton2();
};
struct RECVPARAM
{
	SOCKET socket;
	HWND hwnd;
};