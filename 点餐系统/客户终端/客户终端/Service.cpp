// Service.cpp : 实现文件
//

#include "stdafx.h"
#include "客户终端.h"
#include "Service.h"
#include "afxdialogex.h"
#include "Chat.h"
#include "DinnerMenu.h"
#include "ServiceVip.h"


// CService 对话框

IMPLEMENT_DYNAMIC(CService, CDialogEx)

CService::CService(CWnd* pParent /*=NULL*/)
	: CDialogEx(CService::IDD, pParent)
{

}

CService::~CService()
{
}

void CService::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CService, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON4, &CService::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CService::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON6, &CService::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON1, &CService::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CService::OnBnClickedButton2)
END_MESSAGE_MAP()


// CService 消息处理程序


void CService::OnBnClickedButton4()
{
	CChat dlg;
	dlg.DoModal();
}


void CService::OnBnClickedButton3()
{
	static int num=1;//记录催菜次数
	CString str="";
	//如果是第一次催菜，则要先连接服务器
	sockClient = socket(AF_INET, SOCK_STREAM, 0);  
	if(sockClient == INVALID_SOCKET) {     
		MessageBox("套接字创建失败！");
		WSACleanup();   
		return;   
	} 
	SOCKADDR_IN addrTo;
	addrTo.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
	//addrTo.sin_addr.S_un.S_addr=inet_addr("192.168.137.5");
	addrTo.sin_family=AF_INET;
	addrTo.sin_port=htons(6000);
	if(SOCKET_ERROR == connect(sockClient, (SOCKADDR*)&addrTo, sizeof(SOCKADDR))){  
		MessageBox("连接服务器失败！");
		return;  
	}
	send(sockClient,"51",3,0);
	Sleep(500);
	str.Format("%d", num);
	str="51"+str;
	int len=str.GetLength();
	send(sockClient,str,len,0);
	num++;
}


void CService::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	//send(sockClient,"01$",4,0);
	CDialog::OnOK();
}


void CService::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CDinnerMenu dlg;
	dlg.DoModal();
}


void CService::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CServiceVip dlg;
	if(IDOK==dlg.DoModal())
	{
		SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);  
		if(sockClient == INVALID_SOCKET) {     
			MessageBox("套接字创建失败！");
			WSACleanup();   
			return;   
		} 
		SOCKADDR_IN addrTo;
		addrTo.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
		addrTo.sin_family=AF_INET;
		addrTo.sin_port=htons(6000);
		if(SOCKET_ERROR == connect(sockClient, (SOCKADDR*)&addrTo, sizeof(SOCKADDR))){  
			MessageBox("连接服务器失败！");
			return;  
		}
		send(sockClient,"01$",4,0);
	}
}
