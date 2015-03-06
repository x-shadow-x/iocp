// TableUpdate.cpp : 实现文件
//

#include "stdafx.h"
#include "管理终端.h"
#include "TableUpdate.h"
#include "afxdialogex.h"
#include <afxdb.h>


// CTableUpdate 对话框

IMPLEMENT_DYNAMIC(CTableUpdate, CDialogEx)

CTableUpdate::CTableUpdate(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTableUpdate::IDD, pParent)
{

}

CTableUpdate::~CTableUpdate()
{
}

void CTableUpdate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTableUpdate, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CTableUpdate::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTableUpdate::OnBnClickedButton2)
END_MESSAGE_MAP()


// CTableUpdate 消息处理程序

extern CString s1;
extern CString s2;
extern CString s3;
extern CString s4;
BOOL CTableUpdate::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetDlgItemText(IDC_STATIC1,s1);
	SetDlgItemText(IDC_EDIT1,s2);
	SetDlgItemText(IDC_EDIT2,s3);
	SetDlgItemText(IDC_EDIT6,s4);

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CTableUpdate::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str1,str2,str3,str4,str5,str6;
	GetDlgItemText(IDC_STATIC1,str1);
	GetDlgItemText(IDC_EDIT1,str2);
	GetDlgItemText(IDC_EDIT2,str3);
	GetDlgItemText(IDC_EDIT6,str4);
	CDatabase db;
	CRecordset rs(&db);
	db.OpenEx (_T("DSN=user_message;UID=sa;PWD=xxx"));
	rs.Open( 1,_T( "SELECT Table_ID,Seat_Num,Table_Position,Table_Situation FROM Dinner_Table"));
	CString sql1="delete from Dinner_Table where Table_ID="+str1 ;
	db.ExecuteSQL (sql1);
	CString sql2="insert into Dinner_Table values('"+str1+"','"+str2+"','"+str3+"', '"+str4+"')";
	db.ExecuteSQL (sql2);
	rs.Close();
	db.Close ();
	CDialog::OnOK();

}


void CTableUpdate::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}
