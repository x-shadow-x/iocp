// AllBill.cpp : 实现文件
//

#include "stdafx.h"
#include "管理终端.h"
#include "AllBill.h"
#include "afxdialogex.h"
#include <afxdb.h>

// CAllBill 对话框

IMPLEMENT_DYNAMIC(CAllBill, CDialogEx)

CAllBill::CAllBill(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAllBill::IDD, pParent)
{

}

CAllBill::~CAllBill()
{
}

void CAllBill::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CAllBill, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CAllBill::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAllBill::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CAllBill::OnBnClickedButton3)
END_MESSAGE_MAP()


// CAllBill 消息处理程序


BOOL CAllBill::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(0,_T("账单号"),LVCFMT_LEFT,80);
	m_list.InsertColumn(1,_T("菜号"),LVCFMT_LEFT,80);
	m_list.InsertColumn(2,_T("菜名"),LVCFMT_LEFT,100);
	m_list.InsertColumn(3,_T("数量"),LVCFMT_LEFT,80);
	m_list.InsertColumn(4,_T("价格"),LVCFMT_LEFT,80);

	CDatabase db;
    CRecordset rs(&db);
	db.OpenEx (_T("DSN=user_message;UID=sa;PWD=xxx"));
	rs.Open( 1,_T( "SELECT Bill_ID,Dishes_ID,Dishes_Name,Quantity,Price FROM Bill"));
	CDBVariant varValue;
	short nFields = rs.GetODBCFieldCount( );
	int k=0;
	short index1=0;
	while( !rs.IsEOF( ) )
	{
		rs.GetFieldValue( index1, varValue );
		CString str;
		str=*varValue.m_pstring ;
		str.TrimRight (" ");
		m_list.InsertItem(k,str,k);
		for( short index = 1; index < nFields; index++ )
		{
			rs.GetFieldValue( index, varValue );
			CString ss;
			if(index==3)
			{
				int temp=varValue.m_iVal ;
				ss.Format("%d",temp);
				ss=ss+"份";
			}
			else if(index==4)
			{
				int temp=varValue.m_iVal ;
				ss.Format("%d",temp);
				ss=ss+"元";
			}
			else
				ss=*varValue.m_pstring ;
			ss.TrimRight (" ");
			m_list.SetItemText(k,index,ss);

		}
		rs.MoveNext( );
		k++;
	}
	rs.Close();
	db.Close ();

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CAllBill::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString billid_of_find;
	GetDlgItemText(IDC_EDIT1,billid_of_find);
	if(billid_of_find=="")
		MessageBox("请输入要查找的账单ID号!");
	else
		Update(billid_of_find);
}


void CAllBill::Update(CString bill_of_find)
{
	m_list.DeleteAllItems();
	CDatabase db;
    CRecordset rs(&db);
	db.OpenEx (_T("DSN=user_message;UID=sa;PWD=xxx"));
	rs.Open( 1,_T( "SELECT Bill_ID,Dishes_ID,Dishes_Name,Quantity,Price FROM Bill"));	
	CDBVariant varValue;
	short nFields = rs.GetODBCFieldCount( );
	int k=0;
	short index1=0;
	while( !rs.IsEOF( ) )
	{
		rs.GetFieldValue( index1, varValue );
		CString str;
		str=*varValue.m_pstring ;
		str.TrimRight (" ");
		if(str!=bill_of_find)
		{
			rs.MoveNext( );
			continue;
		}
		m_list.InsertItem(k,str,k);
		for( short index = 1; index < nFields; index++ )
		{
			rs.GetFieldValue( index, varValue );
			CString ss;
			if(index==3)
			{
				int temp=varValue.m_iVal ;
				ss.Format("%d",temp);
				ss=ss+"份";
			}
			else if(index==4)
			{
				int temp=varValue.m_iVal ;
				ss.Format("%d",temp);
				ss=ss+"元";
			}
			else
				ss=*varValue.m_pstring ;
			ss.TrimRight (" ");
			m_list.SetItemText(k,index,ss);

		}
		rs.MoveNext( );
		k++;
	}
	rs.Close();
	db.Close ();
}


void CAllBill::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}


void CAllBill::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedButton1();
}
