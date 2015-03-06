// Chat.cpp : 实现文件
//

#include "stdafx.h"
#include "管理终端.h"
#include "Chat.h"
#include "afxdialogex.h"
#include <afxdb.h>


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
	DDX_Control(pDX, IDC_LIST1, m_list1);
}


BEGIN_MESSAGE_MAP(CChat, CDialogEx)
	ON_MESSAGE(WM_RECVDATA,OnRecvData)
	ON_BN_CLICKED(IDC_BUTTON2, &CChat::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CChat::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CChat::OnBnClickedButton3)
END_MESSAGE_MAP()


// CChat 消息处理程序
static bool isfirst;//聊天对话框打开时在txt文档中读取记录,因为其结尾加了换行符,为避免对话框在第一次接收数据时
                    //重复添加换行符,故设此变量来判断
extern CString tableindex;
extern CString bill_id;
extern bool is_subit[25];
BOOL CChat::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//=============================================================================================
	//==============================读取文本文档中的聊天记录=======================================
	isfirst=true;//刚开始打开对话框是为true
	FILE *pFile;
	long curpos,length;
	char *ch;
	fopen_s(&pFile,tableindex+".txt","rb");
	curpos=ftell(pFile);
	fseek(pFile,0L,SEEK_END);
	length=ftell(pFile);
	fseek(pFile,curpos,SEEK_SET);
	ch=new char[length+1];
	fread(ch,1,length,pFile);
	ch[length]=0;
	fclose(pFile);
	SetDlgItemText(IDC_RECV,ch);
	delete [] ch;
	//=============================================================================================
	//=================================创建用以通信的套接字========================================
	sockClient = socket(AF_INET, SOCK_STREAM, 0);  
	if(sockClient == INVALID_SOCKET) {     
		MessageBox("套接字创建失败！");
		WSACleanup();   
		return false;   
	} 
	SOCKADDR_IN addrTo;
	addrTo.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
	//addrTo.sin_addr.S_un.S_addr=inet_addr("192.168.137.5");
	addrTo.sin_family=AF_INET;
	addrTo.sin_port=htons(6000);
	if(SOCKET_ERROR == connect(sockClient, (SOCKADDR*)&addrTo, sizeof(SOCKADDR))){  
		MessageBox("连接服务器失败！");
		return false;  
	}
	int tableindex2=_ttoi(tableindex);
	tableindex2=tableindex2+75;
	CString tableindex3;
	tableindex3.Format("%d", tableindex2);
	
	send(sockClient,tableindex3,3,0);//告知服务器此管理端聊天窗口的套接字序号
	//创建接收数据线程
	RECVPARAM1 *pRecvParam=new RECVPARAM1;
	pRecvParam->hwnd=this->m_hWnd;
	pRecvParam->socket=sockClient;
	HANDLE receiveThread = CreateThread(NULL, 0, ReceiveMessageThread,(LPVOID)pRecvParam, 0, NULL);
    CloseHandle(receiveThread);
	GetDlgItem(IDC_STATIC)->SetWindowTextA(tableindex);
	GetDlgItem(IDC_STATIC1)->SetWindowTextA(bill_id);

	//===========================================================================================
	//=================================初始化客户菜单表==========================================
	m_list1.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_list1.InsertColumn(0,_T("账单号"),LVCFMT_LEFT,80);
	m_list1.InsertColumn(1,_T("菜号"),LVCFMT_LEFT,80);
	m_list1.InsertColumn(2,_T("菜名"),LVCFMT_LEFT,100);
	m_list1.InsertColumn(3,_T("数量"),LVCFMT_LEFT,80);
	m_list1.InsertColumn(4,_T("价格"),LVCFMT_LEFT,80);

	//===========================================================================================
	//=================================显示对应客户账单==========================================
	CString is_subit_index;
	GetDlgItemText(IDC_STATIC,is_subit_index);
	int subit_index=_ttoi(is_subit_index);
	if(is_subit[subit_index]==true)//说明客户已经按下确认点餐按钮，此时可以显示其账单
		update();
	//===========================================================================================
	return TRUE;  // return TRUE unless you set the focus to a control
}

DWORD WINAPI CChat::ReceiveMessageThread(LPVOID IpParameter)  
{ 
	static int rcv=0;
	SOCKET socket=((RECVPARAM1*)IpParameter)->socket;
	HWND hwnd=((RECVPARAM1*)IpParameter)->hwnd;
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
	CString strTemp;
	CString temp;
	int length_of_str=str.GetLength();
	FILE *pFile1;
	temp=str.Mid(0,2);
	int index=_ttoi(temp);
	int index1=index;
	if(index>=26&&index<=50)//表示这则信息是由客户发来的
		index=index-25;//还原到餐桌的原来序号以便找到对应的记录文档进行写入
	str=str.Mid(2,length_of_str);
	if(index<10)
	{
		temp.Format("%d", index);
		temp="0"+temp;
	}
	else
		temp.Format("%d", index);
	if(index1>=26&&index1<=50)//说明这则消息是由客户发来的,设置对应的称谓
		str=temp+":"+str;
	if(index>=1&&index1<=25)//说明这则消息是由管理端发回给自己的,设置对应的称谓
		str="管理端:"+str;
	str+="\r\n";
	fopen_s(&pFile1,temp+".txt","a+");
	fwrite(str,1,strlen(str),pFile1);
	fclose(pFile1);

	GetDlgItemText(IDC_RECV,strTemp);
	str=strTemp+str;
	SetDlgItemText(IDC_RECV,str);
	return true;
}



void CChat::PostNcDestroy()
{
	// TODO: 在此添加专用代码和/或调用基类
	delete this;
	CDialogEx::PostNcDestroy();
}


void CChat::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString tableindexnow;
	
	GetDlgItem(IDC_STATIC)->GetWindowTextA(tableindexnow);
	int inttableindex=_ttoi(tableindexnow);
	inttableindex=inttableindex+75;
	tableindexnow.Format("%d", inttableindex);
	send(sockClient, tableindexnow+"#", 4, 0);//关闭聊天窗口的标示改成#
	CDialog::OnOK();
}


void CChat::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString tableindexnow;
	GetDlgItem(IDC_STATIC)->GetWindowTextA(tableindexnow);
	int len;//保存CString中字符的数目
	WSABUF wsabuf;
	CString getstr;
	//CString strTemp2;//获取名字
	GetDlgItemText(IDC_SEND,getstr);
	getstr=tableindexnow+getstr;
	//getstr=tableindex+getstr;//------------------------------------------
	//getstr=strTemp2+"\r\n"+getstr;
	len=getstr.GetLength();
	wsabuf.buf=(CHAR*)getstr.GetBuffer(len);
	wsabuf.len=len+1;
	send(sockClient, getstr, 200, 0);
	SetDlgItemText(IDC_SEND,TEXT(""));
}


void CChat::update(void)
{
	CDatabase db;
    CRecordset rs(&db);
	CString Bill_ID;
	GetDlgItem(IDC_STATIC1)->GetWindowTextA(Bill_ID);
	db.OpenEx (_T("DSN=user_message;UID=sa;PWD=xxx"));
	rs.Open( 1,_T( "SELECT Bill_ID,Dishes_ID,Dishes_Name,Quantity,Price FROM Bill"));
	CDBVariant varValue;
	short nFields = rs.GetODBCFieldCount( );
	int k=0;
	short index1=0;
	while( !rs.IsEOF( ) )
	{
		rs.GetFieldValue( index1, varValue );
		CString s;
		s=*varValue.m_pstring ;
		s.TrimRight (" ");
		if(s!=Bill_ID)
		{
			rs.MoveNext( );
			continue;
		}
		m_list1.InsertItem(k,s,k);
		for( short index = 1; index < nFields; index++ )
		{
			rs.GetFieldValue( index, varValue );
			CString s;
			if(index==3)
			{
				int age=varValue.m_iVal ;
				s.Format("%d",age);
				s=s+"份";
			}
			else if(index==4)
			{
				int age=varValue.m_iVal ;
				s.Format("%d",age);
				s=s+"元";
			}
			else
				s=*varValue.m_pstring ;
			s.TrimRight (" ");
			m_list1.SetItemText(k,index,s);
		}
		rs.MoveNext( );
		k++;
	}
	rs.Close();
	db.Close ();
}


void CChat::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedButton1();
}
