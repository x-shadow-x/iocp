
// 管理终端Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "管理终端.h"
#include "管理终端Dlg.h"
#include "afxdialogex.h"
#include "WorkPlatform.h"
#include "Purchase.h"
#include "Goods.h"
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


// C管理终端Dlg 对话框



C管理终端Dlg::C管理终端Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C管理终端Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C管理终端Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(C管理终端Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &C管理终端Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &C管理终端Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// C管理终端Dlg 消息处理程序

BOOL C管理终端Dlg::OnInitDialog()
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

void C管理终端Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C管理终端Dlg::OnPaint()
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
HCURSOR C管理终端Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C管理终端Dlg::OnBnClickedButton1()
{
	CString str1=_T("");//账号
	CString str2=_T("");//密码
	GetDlgItemText(IDC_EDIT1,str1);
	if(str1=="")
	{
		MessageBox("请输入工号！");
		return;
	}
	GetDlgItemText(IDC_EDIT2,str2);
	CDatabase db;
	db.OpenEx (_T("DSN=user_message;UID=sa;PWD=xxx"));//这里你改成你的sa密码吧,注册窗口那里也有和数据库相连的语句,也改一下
	CRecordset rs(&db);
	rs.Open( 1,_T( "SELECT Employee_ID,Employee_Password,Department_ID FROM Employee"));

	CDBVariant varValue;
	short nFields = rs.GetODBCFieldCount( );
	while( !rs.IsEOF( ) )
	{
		rs.GetFieldValue( short(0), varValue );
		CString s1;
		CString s2;
		s1=*varValue.m_pstring ;
		s1.TrimRight (" ");
		if(s1==str1){
			rs.GetFieldValue( short(1), varValue );
			s2=*varValue.m_pstring ;
			s2.TrimRight (" ");
			if(s2==str2){
				CString s22;
				rs.GetFieldValue( short(2), varValue );
				s22=*varValue.m_pstring ;
				s22.TrimRight (" ");
				if(s22=="001"){
					CGoods dlg;
					CDialog::OnOK();
					dlg.DoModal();
				}
				if(s22=="002"){
					CWorkPlatform dlg;
					CDialog::OnOK();
					dlg.DoModal();
				}
				if(s22=="003"){
					CPurchase dlg;
					CDialog::OnOK();
					dlg.DoModal();
				}
			}
			else
				MessageBox("工号或密码错误！");
		}
		rs.MoveNext();
	}
	rs.Close();
	db.Close();
}


void C管理终端Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedButton1();
}
