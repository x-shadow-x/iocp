
// 客户终端Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "客户终端.h"
#include "客户终端Dlg.h"
#include "afxdialogex.h"
#include "Service.h"
#include "ServiceVip.h"
#include <afxdb.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// C客户终端Dlg 对话框



C客户终端Dlg::C客户终端Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C客户终端Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C客户终端Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(C客户终端Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &C客户终端Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &C客户终端Dlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// C客户终端Dlg 消息处理程序

BOOL C客户终端Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C客户终端Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C客户终端Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR C客户终端Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


SOCKET sockClient;
CString bill_id;
CString client_id;
void C客户终端Dlg::OnBnClickedButton1()
{
	/*CDatabase db;
    CRecordset rs(&db);
	db.OpenEx (_T("DSN=user_message;UID=sa;PWD=xxx"));
	rs.Open( 1,_T( "SELECT count(distinct Bill_ID) FROM Bill"));
	//rs.Open( 1,_T( "Bill_ID FROM Bill"));
	CDBVariant varValue;
	short index = 0;
	rs.GetFieldValue(index, varValue );
	int num=1+varValue.m_iVal ;
	CString num_str;
	num_str.Format("%d",num);
	num_str="00000"+num_str;
	int length_of_num_str=num_str.GetLength();
	num_str=num_str.Mid(length_of_num_str-6,length_of_num_str);
	rs.Close();
	db.Close ();*/
	CDatabase db1;
    CRecordset rs1(&db1);
	db1.OpenEx (_T("DSN=user_message;UID=sa;PWD=xxx"));
	rs1.Open( 1,_T( "SELECT count(distinct Client_ID) FROM Client"));
	CDBVariant varValue1;
	short index1 = 0;
	rs1.GetFieldValue(index1, varValue1 );
	int num1=1+varValue1.m_iVal ;
	CString num_client;
	num_client.Format("%d",num1);
	num_client="00000"+num_client;
	int length_of_num_client = num_client.GetLength();
	num_client=num_client.Mid(length_of_num_client-6,length_of_num_client);
	rs1.Close();
	db1.Close ();
	client_id=num_client;
	//此时num_client里保存的是这个顾客的id
	sockClient = socket(AF_INET, SOCK_STREAM, 0);  
	if(sockClient == INVALID_SOCKET) {     
		MessageBox("套接字创建失败！");
		WSACleanup();   
		return;   
	} 
	SOCKADDR_IN addrTo;
	addrTo.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
	//addrTo.sin_addr.S_un.S_addr=inet_addr("192.168.23.4");
	addrTo.sin_family=AF_INET;
	addrTo.sin_port=htons(6000);
	if(SOCKET_ERROR == connect(sockClient, (SOCKADDR*)&addrTo, sizeof(SOCKADDR))){  
		MessageBox("连接服务器失败！");
		return;  
	}
	send(sockClient,"01"+num_client+"@",10,0);//num_str此顾客的账单ID
	bill_id=num_client;

	

	CString Table_ID="001";
	CString Client_Message="";
	CDatabase db2;
    CRecordset rs2(&db2);
	db2.OpenEx (_T("DSN=user_message;UID=sa;PWD=xxx"));
	rs2.Open( 1,_T( "SELECT Client_ID,Table_ID,Client_Message  FROM Client"));
	CString sql="insert into Client values('"+num_client+"','"+Table_ID+"','"+Client_Message+"')";
	db2.ExecuteSQL(sql);
	rs2.Close();
	db2.Close ();
	CService dlg;
	CDialog::OnOK();
	if(IDOK==dlg.DoModal())
	{
		send(sockClient,"01l",4,0);
		CDialog::OnOK();
	}
}


void C客户终端Dlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	send(sockClient,"01l",4,0);
	CDialog::OnOK();
}
