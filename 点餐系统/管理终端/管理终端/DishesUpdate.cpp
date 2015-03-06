// DishesUpdate.cpp : 实现文件
//

#include "stdafx.h"
#include "管理终端.h"
#include "DishesUpdate.h"
#include "afxdialogex.h"
#include <afxdb.h>


// CDishesUpdate 对话框

IMPLEMENT_DYNAMIC(CDishesUpdate, CDialogEx)

CDishesUpdate::CDishesUpdate(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDishesUpdate::IDD, pParent)
{

}

CDishesUpdate::~CDishesUpdate()
{
}

void CDishesUpdate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDishesUpdate, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDishesUpdate::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDishesUpdate::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDishesUpdate 消息处理程序

extern CString s1;
extern CString s2;
extern CString s3;
extern CString s4;
BOOL CDishesUpdate::OnInitDialog()
{
	int length=s3.GetLength();
	s3=s3.Mid(0,length-2);
	CDialogEx::OnInitDialog();
	SetDlgItemText(IDC_STATIC1,s1);
	SetDlgItemText(IDC_EDIT1,s2);
	SetDlgItemText(IDC_EDIT2,s3);
	SetDlgItemText(IDC_EDIT3,s4);

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CDishesUpdate::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str1,str2,str3,str4,str5,str6;
	GetDlgItemText(IDC_STATIC1,str1);
	GetDlgItemText(IDC_EDIT1,str2);
	GetDlgItemText(IDC_EDIT2,str3);
	GetDlgItemText(IDC_EDIT3,str4);
	CDatabase db;
	CRecordset rs(&db);
	db.OpenEx (_T("DSN=user_message;UID=sa;PWD=xxx"));
	rs.Open( 1,_T( "SELECT Dishes_ID,Dishes_Name,Dishes_Price,Dishes_Classification FROM Dishes_List"));
	CString sql1="delete from Dishes_List where Dishes_ID="+str1 ;
	db.ExecuteSQL (sql1);
	CString sql2="insert into Dishes_List values('"+str1+"','"+str2+"','"+str3+"', '"+str4+"')";
	db.ExecuteSQL (sql2);
	rs.Close();
	db.Close ();
	CDialog::OnOK();
}


void CDishesUpdate::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}
