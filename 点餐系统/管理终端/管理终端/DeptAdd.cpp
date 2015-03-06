// DeptAdd.cpp : 实现文件
//

#include "stdafx.h"
#include "管理终端.h"
#include "DeptAdd.h"
#include "afxdialogex.h"
#include <afxdb.h>


// CDeptAdd 对话框

IMPLEMENT_DYNAMIC(CDeptAdd, CDialogEx)

CDeptAdd::CDeptAdd(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDeptAdd::IDD, pParent)
{

}

CDeptAdd::~CDeptAdd()
{
}

void CDeptAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDeptAdd, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDeptAdd::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDeptAdd 消息处理程序


void CDeptAdd::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString s1,s2;
	GetDlgItemText(IDC_EDIT1,s1);
	GetDlgItemText(IDC_EDIT2,s2);
	CDatabase db;
    CRecordset rs(&db);
	db.OpenEx (_T("DSN=user_message;UID=sa;PWD=xxx"));
	rs.Open( 1,_T( "SELECT Department_ID,Department_Name FROM Department"));
	CDBVariant varValue;
	CString sql="insert into Department values('"+s1+"','"+s2+"')";
	db.ExecuteSQL (sql);
	rs.Close();
	db.Close ();
	CDialog::OnOK();
}
