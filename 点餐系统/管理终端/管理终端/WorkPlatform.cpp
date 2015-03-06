// WorkPlatform.cpp : 实现文件
//

#include "stdafx.h"
#include "管理终端.h"
#include "WorkPlatform.h"
#include "afxdialogex.h"
#include "Chat.h"
#include "AllBill.h"
#include "管理终端Dlg.h"
#include <afxdb.h>

// CWorkPlatform 对话框

IMPLEMENT_DYNAMIC(CWorkPlatform, CDialogEx)

CWorkPlatform::CWorkPlatform(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWorkPlatform::IDD, pParent)
{

}

CWorkPlatform::~CWorkPlatform()
{
}

void CWorkPlatform::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST3, m_list);
	DDX_Control(pDX, IDC_LIST1, m_list1);
}


BEGIN_MESSAGE_MAP(CWorkPlatform, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_LIST3, &CWorkPlatform::OnClickList3)
	ON_MESSAGE(WM_RECVDATA,OnRecvData)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST3, &CWorkPlatform::OnDblclkList3)
	ON_BN_CLICKED(IDC_BUTTON1, &CWorkPlatform::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CWorkPlatform::OnBnClickedButton2)
END_MESSAGE_MAP()


// CWorkPlatform 消息处理程序

CString table_message[25];
BOOL CWorkPlatform::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CImageList * pImagelist;
	pImagelist=new CImageList();
	pImagelist->Create(32,32,ILC_COLOR32|ILC_MASK,10,0);
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP1);
	pImagelist->Add(&bmp,RGB(0,0,0));
	bmp.DeleteObject();

	bmp.LoadBitmap(IDB_BITMAP2);
	pImagelist->Add(&bmp,RGB(0,0,0));
	bmp.DeleteObject();

	bmp.LoadBitmap(IDB_BITMAP3);
	pImagelist->Add(&bmp,RGB(0,0,0));
	bmp.DeleteObject();

	CDatabase db1;
    CRecordset rs1(&db1);
	db1.OpenEx (_T("DSN=user_message;UID=sa;PWD=xxx"));
	rs1.Open( 1,_T( "SELECT count(distinct Table_ID) FROM Dinner_Table"));
	CDBVariant varValue1;
	short index1 = 0;
	rs1.GetFieldValue(index1, varValue1 );
	int num1=varValue1.m_iVal ;
	rs1.Close();
	db1.Close ();

	m_list.SetImageList(pImagelist,LVSIL_NORMAL);
	for(int i=0;i<num1;i++)
	{
		CString str;
		if(i+1<10)
		{
			str.Format("%d号桌",(i+1));
			str="0"+str;
		}
		else
			str.Format("%d号桌",(i+1));
		m_list.InsertItem(i,str,2);//m_list
	}
	m_tooltip.Create(this);
	InitSocket();
	//初始化消息列表
	m_list1.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_list1.InsertColumn(0,_T("餐桌号"),LVCFMT_LEFT,70);
	m_list1.InsertColumn(1,_T("催菜次数"),LVCFMT_LEFT,70);
	m_list1.InsertColumn(2,_T("账单号"),LVCFMT_LEFT,70);
	table_message[1]="1号桌，大厅中央，座位数：10";
	table_message[2]="2号桌，靠走道，座位数：8";
	table_message[3]="3号桌，靠窗，座位数：8";
	table_message[4]="4号桌，大厅中央，座位数：10";
	table_message[5]="5号桌，靠走道，座位数：8";
	table_message[6]="6号桌，靠窗，座位数:8";
	table_message[7]="7号桌，大厅中央，座位数：10";
	table_message[8]="8号桌，水池旁，座位数：8";
	table_message[9]="9号桌，秋千椅，座位数:4";
	table_message[10]="10号桌，水池旁，座位数:8";
	table_message[11]="11号桌，大厅中央，座位数10";
	table_message[12]="12号桌，秋千椅，座位数:4";
	table_message[13]="13号桌，水池旁，座位数:8";
	table_message[14]="14号桌，大厅中央，座位数:8";
	table_message[15]="15号桌，靠窗，座位数:8";
	table_message[16]="16号桌，大厅中央，座位数10";
	table_message[17]="17号桌，水池旁，座位数:8";
	table_message[18]="18号桌，秋千椅，座位数:4";
	table_message[19]="19号桌，秋千椅，座位数：4";
	table_message[20]="20号桌，靠窗，座位数：8";
	return TRUE;  // return TRUE unless you set the focus to a control
}


void CWorkPlatform::OnClickList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	*pResult = 0;
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos=m_list.GetFirstSelectedItemPosition();
	if(pos==NULL)
	{
		//MessageBox("用户双击位置错误");
	}
	else
	{
		CString str;
		int nItem=m_list.GetNextSelectedItem(pos);
		int index=nItem;
		str=m_list.GetItemText(nItem,0);
		int index_of_table_message=_ttoi(str);
	//	m_tt.Create(this);
		m_tooltip.AddTool(GetDlgItem(IDC_LIST3), table_message[index_of_table_message]);
		m_tooltip.SetMaxTipWidth(123);
		m_tooltip.Activate(TRUE);
	}
	*pResult = 0;
}


BOOL CWorkPlatform::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	ASSERT(pMsg != NULL);
	if (pMsg->message == WM_MOUSEMOVE || pMsg->message == WM_LBUTTONDOWN || pMsg->message == WM_LBUTTONUP)
		m_tooltip.RelayEvent(pMsg);
	return CDialogEx::PreTranslateMessage(pMsg);
}


bool CWorkPlatform::InitSocket(void)
{
	sockClient = socket(AF_INET, SOCK_STREAM, 0);  
     if(sockClient == INVALID_SOCKET) {     
		 MessageBox("套接字创建失败！");
        WSACleanup();   
        return false;   
      } 
	SOCKADDR_IN addrTo;
	addrTo.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
	addrTo.sin_family=AF_INET;
	addrTo.sin_port=htons(6000);
	if(SOCKET_ERROR == connect(sockClient, (SOCKADDR*)&addrTo, sizeof(SOCKADDR))){  
		MessageBox("连接服务器失败！");
		return false;  
	}
	send(sockClient,"00",3,0);
	RECVPARAM *pRecvParam=new RECVPARAM;
	pRecvParam->hwnd=this->m_hWnd;
	pRecvParam->socket=sockClient;
	HANDLE receiveThread = CreateThread(NULL, 0, ReceiveMessageThread,(LPVOID)pRecvParam, 0, NULL);
    CloseHandle(receiveThread);
	return TRUE;
}

DWORD WINAPI CWorkPlatform::ReceiveMessageThread(LPVOID IpParameter)  
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
bool isconnect[100];//用以判断管理终端中图标对应下的饭桌是否已经连接，若没有连接则在双击消息响应函数中
                   //不能打开与对应客户端的聊天窗口
CString bill_id;//账单id，用以显示账单信息是对数据进行过滤
bool is_subit[25];//用以判断对应的餐桌的客人是否已经按下确认点餐
LRESULT CWorkPlatform::OnRecvData(WPARAM wParam,LPARAM lParam)
{
	
	FILE *pFile1;
	CString str=(char*)lParam;
	if(str.GetLength()==9&&str.Mid(0,2)!="00"&&str[8]=='@')//若长度为9,且最后一个字符为@,则是餐桌的连接消息，中间六位为账单id
	{
		CString str_index=str.Mid(0,2);
		int index=_ttoi(str_index);
		if(index<=25)//对方初次登陆的套接字，设置对应的图标为已经连接
		{
			m_list.DeleteItem(index-1);
			m_list.InsertItem(index-1,str_index+"号桌",0);
			isconnect[index]=true;//客户端已经连接，此时可以打开对应的对话框了
			fopen_s(&pFile1,str_index+".txt","a+");//创建文件
			fclose(pFile1);

			int i=m_list1.GetItemCount();
			int length_of_str=str.GetLength();
			bill_id=str.Mid(2,length_of_str-3);
		    m_list1.InsertItem(i,str_index);     //添加新Item到i所在位置,虽然记录个数是i个,但最后一行所在位置为i-1
		    m_list1.SetItemText(i, 1, "0");  //催菜次数
		    m_list1.SetItemText(i, 2, bill_id); //账单id

			return true;
		}
		return true;
	}
	if(str.GetLength()==2)
	{
		int index=_ttoi(str);
		if(index>=26&&index<=50)return true;
	}
	if(str.GetLength()==3)
	{
		CString strindex=str.Mid(0,2);
		int index=_ttoi(strindex);
		if(index<=25&&str[2]=='*')//小于等于25且索引值后跟着事先设定的确认点餐时发送的标示符*,说明是确认点餐
		{
			is_subit[index]=true;
			return true;
		}
		if(index<=25&&str[2]=='$')//小于等于25且索引值后跟着事先设定的确认付款时发送的标示符$,说明是确认付款
		{
			m_list.DeleteItem(index-1);
			m_list.InsertItem(index-1,strindex+"号桌",1);//设置对应的图标以提示管理端顾客希望结账了
			return true;
		}
		if(index<=25&&str[2]=='l')//小于等于25且索引值后跟着事先设定的关闭窗口时发送的标示符l,说明是餐桌退台
		{
			is_subit[index]=false;//客户离台，对应用以判断其是否已经按下确认点餐的按钮的bool数组值复位

			m_list.DeleteItem(index-1);
			m_list.InsertItem(index-1,strindex+"号桌",2);
			isconnect[index]=false;//客户端已经退出，此时不能打开对应的对话框
			DeleteFile(strindex+".txt");
			int i=m_list1.GetItemCount();
			CString tempindex=str.Mid(0,2);
			CString strtemp;
			for(int j=0;j<i;j++)
			{
				strtemp=m_list1.GetItemText(j,0);
				if(strtemp==tempindex)
				{
					m_list1.DeleteItem(j);//客户已离台,删除对应的消息
					break;
				}
			}
			return true;
		}
	}
	CString index2=str.Mid(0,2);;//用以判断是用以何种需求的套接字
	int index3=_ttoi(index2);
	if(index3>=51&&index3<=75)//说明这次信息是是催菜信息
	{
		index3=index3-50;
		CString tempindex;
		if(index3<10)
		{
			tempindex.Format("%d", index3);
			tempindex="0"+tempindex;
		}
		else
			tempindex.Format("%d", index3);
		if(str.GetLength()>=3)//若小于3则说明是催菜套接字第一次发过来用以建立连接的,这次通信不包含催菜次数
		{
			int length_of_str=str.GetLength();
			CString str2=str.Mid(2,length_of_str);
			/*if(str2=="1")
			{
				int i=m_list1.GetItemCount();
				m_list1.InsertItem(i,tempindex);     //添加新Item到i所在位置,虽然记录个数是i个,但最后一行所在位置为i-1
				m_list1.SetItemText(i, 1, str2);
			}
			else
			{*/
				int i=m_list1.GetItemCount();
				CString strtemp;
				for(int j=0;j<i;j++)
				{
					strtemp=m_list1.GetItemText(j,0);
					if(strtemp==tempindex)
					{
						CString str3=m_list1.GetItemText(j,2);
						m_list1.DeleteItem(j);
						m_list1.InsertItem(j,tempindex);
						m_list1.SetItemText(j, 1, str2);
						m_list1.SetItemText(j, 2, str3);
						break;
					}
				}
			//}
		}
	}
	//////////以上为为刚连接上的客户创建保存聊天记录的文档,以及根据客户的连接退出状态设置对应的图标
	//////////以下为在管理端还没有打开聊天窗口时由此父窗口将聊天记录保存到记录文档
	CString temp;//以下设置设置写入文档的称谓,因在此父窗口,故管理端聊天窗口没有打开,所以这里收到的消息一定是客户发来的
	temp=str.Mid(0,2);
	int index=_ttoi(temp);
	index=index-25;
	if(index<10)
	{
		temp.Format("%d", index);
		temp="0"+temp;
	}
	else
		temp.Format("%d", index);

	int length_of_str=str.GetLength();
	str=str.Mid(2,length_of_str);
	str=temp+":"+str;
	str=str+"\r\n";
	fopen_s(&pFile1,temp+".txt","a+");
	fwrite(str,1,strlen(str),pFile1);
	fclose(pFile1);
	return true;
}

CString tableindex;
void CWorkPlatform::OnDblclkList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	*pResult = 0;
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos=m_list.GetFirstSelectedItemPosition();
	if(pos==NULL)
	{
		//MessageBox("用户双击位置错误");
	}
	else
	{
		CString str;
		int nItem=m_list.GetNextSelectedItem(pos);
		int index=nItem;
		str=m_list.GetItemText(nItem,0);
		tableindex=str.Mid(0,2);
		int i=m_list1.GetItemCount();
		CString strtemp;
		for(int j=0;j<i;j++)
		{
			strtemp=m_list1.GetItemText(j,0);
			if(strtemp==tableindex)
			{
				bill_id=m_list1.GetItemText(j,2);//此时bill保存了此时使用此台桌的顾客所对应的订单号
				break;
			}
		}
	}
	int index=_ttoi(tableindex);
	if(isconnect[index]==true)
	{
		CChat *dlg=new CChat;
		dlg->Create(IDD_DIALOG2,this);
		dlg->ShowWindow(SW_SHOW);
	}
	*pResult = 0;
}


void CWorkPlatform::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CAllBill dlg;
	dlg.DoModal();
}


void CWorkPlatform::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	C管理终端Dlg dlg;
	CDialog::OnOK();
	dlg.DoModal();
}
