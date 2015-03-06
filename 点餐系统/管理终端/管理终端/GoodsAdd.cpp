// GoodsAdd.cpp : 实现文件
//

#include "stdafx.h"
#include "管理终端.h"
#include "GoodsAdd.h"
#include "afxdialogex.h"
#include <afxdb.h>


// CGoodsAdd 对话框

IMPLEMENT_DYNAMIC(CGoodsAdd, CDialogEx)

CGoodsAdd::CGoodsAdd(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGoodsAdd::IDD, pParent)
{

}

CGoodsAdd::~CGoodsAdd()
{
}

void CGoodsAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGoodsAdd, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CGoodsAdd::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CGoodsAdd::OnBnClickedButton3)
END_MESSAGE_MAP()


// CGoodsAdd 消息处理程序


BOOL CGoodsAdd::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("男");
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("女");
	return TRUE;  // return TRUE unless you set the focus to a control
}


void CGoodsAdd::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString s1,s2,s3,s4,s5,s6;
	int index;
	GetDlgItemText(IDC_EDIT1,s1);//员工号
	GetDlgItemText(IDC_EDIT2,s2);//密码
	GetDlgItemText(IDC_EDIT3,s3);//姓名
	GetDlgItemText(IDC_EDIT4,s4);//部门
	GetDlgItemText(IDC_EDIT5,s5);//工种
	index=((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
	((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(index,s6);//性别
	CDatabase db;
    CRecordset rs(&db);
	db.OpenEx (_T("DSN=user_message;UID=sa;PWD=xxx"));
	rs.Open( 1,_T( "SELECT Employee_ID,Employee_Password,Employee_Name,Employee_Sex,Department_ID,Employee_Style FROM Employee"));
	CDBVariant varValue;
	CString sql="insert into Employee values('"+s1+"','"+s2+"','"+s3+"', '"+s6+"','"+s4+"','"+s5+"')";
	db.ExecuteSQL (sql);
	rs.Close();
	db.Close ();
	CDialog::OnOK();

}


void CGoodsAdd::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}
