// DeptUpdte.cpp : 实现文件
//

#include "stdafx.h"
#include "管理终端.h"
#include "DeptUpdte.h"
#include "afxdialogex.h"
#include <afxdb.h>


// CDeptUpdte 对话框

IMPLEMENT_DYNAMIC(CDeptUpdte, CDialogEx)

CDeptUpdte::CDeptUpdte(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDeptUpdte::IDD, pParent)
{

}

CDeptUpdte::~CDeptUpdte()
{
}

void CDeptUpdte::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDeptUpdte, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDeptUpdte::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDeptUpdte::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDeptUpdte 消息处理程序

extern CString s1;
extern CString s2;
BOOL CDeptUpdte::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetDlgItemText(IDC_STATIC1,s1);
	SetDlgItemText(IDC_EDIT1,s2);

	return TRUE;  // return TRUE unless you set the focus to a control

}
void CDeptUpdte::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str1,str2;
	GetDlgItemText(IDC_STATIC1,str1);
	GetDlgItemText(IDC_EDIT1,str2);

	CDatabase db;
	CRecordset rs(&db);
	db.OpenEx (_T("DSN=user_message;UID=sa;PWD=xxx"));
	rs.Open( 1,_T( "SELECT Department_ID ,Department_Name FROM Department"));
	CString sql1="delete from Department where Department_ID="+str1 ;
	db.ExecuteSQL (sql1);
	CString sql2="insert into Department values('"+str1+"','"+str2+"')";
	db.ExecuteSQL (sql2);
	rs.Close();
	db.Close ();
	CDialog::OnOK();
}

void CDeptUpdte::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}
