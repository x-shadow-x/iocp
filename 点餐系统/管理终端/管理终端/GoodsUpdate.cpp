// GoodsUpdate.cpp : 实现文件
//

#include "stdafx.h"
#include "管理终端.h"
#include "GoodsUpdate.h"
#include "afxdialogex.h"
#include <afxdb.h>


// CGoodsUpdate 对话框

IMPLEMENT_DYNAMIC(CGoodsUpdate, CDialogEx)

CGoodsUpdate::CGoodsUpdate(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGoodsUpdate::IDD, pParent)
{

}

CGoodsUpdate::~CGoodsUpdate()
{
}

void CGoodsUpdate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGoodsUpdate, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CGoodsUpdate::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CGoodsUpdate::OnBnClickedButton2)
END_MESSAGE_MAP()


// CGoodsUpdate 消息处理程序

extern CString s1;
extern CString s2;
extern CString s3;
extern CString s4;
extern CString s5;
extern CString s6;
BOOL CGoodsUpdate::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("男");
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("女");
	SetDlgItemText(IDC_EDIT1,s1);
	SetDlgItemText(IDC_EDIT2,s2);
	SetDlgItemText(IDC_EDIT3,s3);
	SetDlgItemText(IDC_EDIT4,s4);
	SetDlgItemText(IDC_EDIT5,s5);
	if(s6=="男")
		((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(0);
	else
		((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(1);
	return TRUE;  // return TRUE unless you set the focus to a control
}


void CGoodsUpdate::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str1,str2,str3,str4,str5,str6;
	GetDlgItemText(IDC_EDIT1,str1);
	GetDlgItemText(IDC_EDIT2,str2);
	GetDlgItemText(IDC_EDIT3,str3);
	GetDlgItemText(IDC_EDIT4,str4);
	GetDlgItemText(IDC_EDIT5,str5);
	int index=((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
	((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(index,str6);
	CDatabase db;
	CRecordset rs(&db);
	db.OpenEx (_T("DSN=user_message;UID=sa;PWD=xxx"));
	rs.Open( 1,_T( "SELECT Employee_ID,Employee_Password,Employee_Name,Employee_Sex,Department_ID,Employee_Style FROM Employee"));
	CString sql1="delete from Employee where Employee_ID="+str1 ;
	db.ExecuteSQL (sql1);
	CString sql2="insert into Employee values('"+str1+"','"+str2+"','"+str3+"', '"+str6+"','"+str4+"','"+str5+"')";
	db.ExecuteSQL (sql2);
	rs.Close();
	db.Close ();
	CDialog::OnOK();
}


void CGoodsUpdate::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}
