// Chat.cpp : 实现文件
//

#include "stdafx.h"
#include "客户终端.h"
#include "Chat.h"
#include "afxdialogex.h"


// CChat 对话框

IMPLEMENT_DYNAMIC(CChat, CDialogEx)

CChat::CChat(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChat::IDD, pParent)
{

}

CChat::~CChat()
{
}

void CChat::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CChat, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CChat::OnBnClickedButton1)
	ON_MESSAGE(WM_RECVDATA,OnRecvData)
	ON_BN_CLICKED(IDC_BUTTON2, &CChat::OnBnClickedButton2)
END_MESSAGE_MAP()


// CChat 消息处理程序


bool CChat::InitSocket(void)
{
	sockClient = socket(AF_INET, SOCK_STREAM, 0);  
     if(sockClient == INVALID_SOCKET) {     
		 MessageBox("套接字创建失败！");
        WSACleanup();   
        return false;   
      } 
	SOCKADDR_IN addrTo;
	addrTo.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
	//addrTo.sin_addr.S_un.S_addr=inet_addr("192.168.23.4");
	addrTo.sin_family=AF_INET;
	addrTo.sin_port=htons(6000);
	if(SOCKET_ERROR == connect(sockClient, (SOCKADDR*)&addrTo, sizeof(SOCKADDR))){  
		MessageBox("连接服务器失败！");
		return false;  
	}
	send(sockClient,"26",3,0);//发送套接字编号使服务器创建对应套接字
	RECVPARAM *pRecvParam=new RECVPARAM;
	pRecvParam->hwnd=this->m_hWnd;
	pRecvParam->socket=sockClient;
	HANDLE receiveThread = CreateThread(NULL, 0, ReceiveMessageThread,(LPVOID)pRecvParam, 0, NULL);
    CloseHandle(receiveThread);
	return TRUE;
}

DWORD WINAPI CChat::ReceiveMessageThread(LPVOID IpParameter)  
{ 
	static int rcv=0;
	SOCKET socket=((RECVPARAM*)IpParameter)->socket;
	HWND hwnd=((RECVPARAM*)IpParameter)->hwnd;
	delete IpParameter;
	char recvBuf[1200]; 
	while(1){     
		recv(socket, recvBuf, 1024, 0);
		::PostMessage(hwnd,WM_RECVDATA,0,(LPARAM)recvBuf);
	} 
	return 0;
}
LRESULT CChat::OnRecvData(WPARAM wParam,LPARAM lParam)
{
	CString str=(char*)lParam;
	CString str1=str.Mid(0,2);
	CString temp;//用以临时记录客户端端套接字序号以便还原成对应的餐桌号
	int index=_ttoi(str1);
	CString strTemp;
	int length_of_str=str.GetLength();
	str=str.Mid(2,length_of_str);
	if(index>=1&&index<=25)//由管理端发来的信息
	{
		str="管理端:"+str;
	}
	if(index>=26&&index<=50)//由客户端发回给自己的
	{
		index=index-25;
		if(index<10)
		{
			temp.Format("%d", index);
			temp="0"+temp;
		}
		else
			temp.Format("%d", index);
		str=temp+":"+str;
	}
	str+="\r\n";
	GetDlgItemText(IDC_EDIT_RECV,strTemp);
	
	str=strTemp+str;
	SetDlgItemText(IDC_EDIT_RECV,str);
	return true;
}





BOOL CChat::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	InitSocket();
	return TRUE;  // return TRUE unless you set the focus to a control
}





void CChat::OnBnClickedButton1()
{
	int len;//保存CString中字符的数目
	WSABUF wsabuf;
	CString getstr;
	//CString strTemp2;//获取名字
	GetDlgItemText(IDC_EDIT_SEND,getstr);
	getstr="26"+getstr;
	//getstr=strTemp2+"\r\n"+getstr;
	len=getstr.GetLength();
	wsabuf.buf=(CHAR*)getstr.GetBuffer(len);
	wsabuf.len=len+1;
	send(sockClient, getstr, 200, 0);
	SetDlgItemText(IDC_EDIT_SEND,TEXT(""));
}


void CChat::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedButton1();
}
