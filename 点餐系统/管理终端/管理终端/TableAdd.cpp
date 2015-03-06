// TableAdd.cpp : 实现文件
//

#include "stdafx.h"
#include "管理终端.h"
#include "TableAdd.h"
#include "afxdialogex.h"
#include <afxdb.h>


// CTableAdd 对话框

IMPLEMENT_DYNAMIC(CTableAdd, CDialogEx)

CTableAdd::CTableAdd(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTableAdd::IDD, pParent)
{

}

CTableAdd::~CTableAdd()
{
}

void CTableAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTableAdd, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CTableAdd::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTableAdd::OnBnClickedButton2)
END_MESSAGE_MAP()


// CTableAdd 消息处理程序


void CTableAdd::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString s1,s2,s3,s4;
	GetDlgItemText(IDC_EDIT1,s1);//餐桌号
	GetDlgItemText(IDC_EDIT2,s2);//座位数
	GetDlgItemText(IDC_EDIT3,s3);//餐桌信息
	GetDlgItemText(IDC_EDIT4,s4);//使用情况
	CDatabase db;
    CRecordset rs(&db);
	db.OpenEx (_T("DSN=user_message;UID=sa;PWD=xxx"));
	rs.Open( 1,_T( "SELECT Table_ID,Seat_Num,Table_Position,Table_Situation FROM Dinner_Table"));
	CDBVariant varValue;
	CString sql="insert into Dinner_Table values('"+s1+"','"+s2+"','"+s3+"', '"+s4+"')";
	db.ExecuteSQL (sql);
	rs.Close();
	db.Close ();
	CDialog::OnOK();
}


void CTableAdd::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}
