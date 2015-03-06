// DishesAdd.cpp : 实现文件
//

#include "stdafx.h"
#include "管理终端.h"
#include "DishesAdd.h"
#include "afxdialogex.h"
#include <afxdb.h>


// CDishesAdd 对话框

IMPLEMENT_DYNAMIC(CDishesAdd, CDialogEx)

CDishesAdd::CDishesAdd(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDishesAdd::IDD, pParent)
{

}

CDishesAdd::~CDishesAdd()
{
}

void CDishesAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDishesAdd, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDishesAdd::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDishesAdd::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDishesAdd 消息处理程序


void CDishesAdd::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString s1,s2,s3,s4;
	GetDlgItemText(IDC_EDIT1,s1);//菜号
	GetDlgItemText(IDC_EDIT2,s2);//菜名
	GetDlgItemText(IDC_EDIT3,s3);//价格
	GetDlgItemText(IDC_EDIT4,s4);//类别
	CDatabase db;
    CRecordset rs(&db);
	db.OpenEx (_T("DSN=user_message;UID=sa;PWD=xxx"));
	rs.Open( 1,_T( "SELECT Dishes_ID,Dishes_Name,Dishes_Price,Dishes_Classification FROM Dishes_List"));
	CDBVariant varValue;
	CString sql="insert into Dishes_List values('"+s1+"','"+s2+"','"+s3+"', '"+s4+"')";
	db.ExecuteSQL (sql);
	rs.Close();
	db.Close ();
	CDialog::OnOK();
}


void CDishesAdd::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}
