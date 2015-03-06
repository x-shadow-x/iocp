// Goods.cpp : 实现文件
//

#include "stdafx.h"
#include "管理终端.h"
#include "Goods.h"
#include "afxdialogex.h"
#include "管理终端Dlg.h"
#include "GoodsAdd.h"
#include "GoodsUpdate.h"
#include <afxdb.h>
#include "TableAdd.h"
#include "TableUpdate.h"
#include "DishesAdd.h"
#include "DishesUpdate.h"
#include "DeptAdd.h"
#include "DeptUpdte.h"


// CGoods 对话框

IMPLEMENT_DYNAMIC(CGoods, CDialogEx)

CGoods::CGoods(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGoods::IDD, pParent)
{

}

CGoods::~CGoods()
{
}

void CGoods::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CGoods, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &CGoods::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CGoods::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CGoods::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CGoods::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CGoods::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CGoods::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CGoods::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CGoods::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON1, &CGoods::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CGoods::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON11, &CGoods::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CGoods::OnBnClickedButton12)
END_MESSAGE_MAP()


// CGoods 消息处理程序

int style=1;//表示当前选了什么表，为添加，删除，更新操作时打开哪个表格提供依据默认为1，打开员工表
BOOL CGoods::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(0,_T("员工号"),LVCFMT_LEFT,80);
	m_list.InsertColumn(1,_T("员工密码"),LVCFMT_LEFT,80);
	m_list.InsertColumn(2,_T("员工名"),LVCFMT_LEFT,80);
	m_list.InsertColumn(3,_T("性别"),LVCFMT_LEFT,80);
	m_list.InsertColumn(4,_T("部门编号"),LVCFMT_LEFT,80);
	m_list.InsertColumn(5,_T("工种"),LVCFMT_LEFT,80);

	CDatabase db;
    CRecordset rs(&db);
	db.OpenEx (_T("DSN=user_message;UID=sa;PWD=xxx"));
	rs.Open( 1,_T( "SELECT Employee_ID,Employee_Password,Employee_Name,Employee_Sex,Department_ID,Employee_Style FROM Employee"));
	CDBVariant varValue;
	short nFields = rs.GetODBCFieldCount( );
	int k=0;
	while( !rs.IsEOF( ) )
	{
		rs.GetFieldValue( short(0), varValue );
		CString str;
		str=*varValue.m_pstring ;
		str.TrimRight (" ");
		m_list.InsertItem(k,str,k);
		for( short index = 1; index < nFields; index++ )
		{
			rs.GetFieldValue( index, varValue );
			CString ss;
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


void CGoods::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	style=1;
	Update();
}


void CGoods::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	style=2;
	Update();
}


void CGoods::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	style=3;
	Update();
}


void CGoods::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	style=4;
	Update();
}


void CGoods::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	style=5;
	Update();
}


void CGoods::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	style=6;
	Update();
}


void CGoods::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	style=7;
	Update();
}


void CGoods::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	style=8;
	Update();
}


void CGoods::Update(void)
{
	m_list.DeleteAllItems();
	int n=m_list.GetHeaderCtrl()->GetItemCount();
	for (int i=0;i<n;i++)
	{
		m_list.DeleteColumn(0);
	}
	CDatabase db;
	CRecordset rs(&db);
	db.OpenEx (_T("DSN=user_message;UID=sa;PWD=xxx"));
	if(style==1){
		rs.Open( 1,_T( "SELECT Employee_ID,Employee_Password,Employee_Name,Employee_Sex,Department_ID,Employee_Style FROM Employee"));
		m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
		m_list.InsertColumn(0,_T("员工号"),LVCFMT_LEFT,80);
		m_list.InsertColumn(1,_T("员工密码"),LVCFMT_LEFT,80);
		m_list.InsertColumn(2,_T("员工名"),LVCFMT_LEFT,80);
		m_list.InsertColumn(3,_T("性别"),LVCFMT_LEFT,80);
		m_list.InsertColumn(4,_T("部门编号"),LVCFMT_LEFT,80);
		m_list.InsertColumn(5,_T("工种"),LVCFMT_LEFT,80);
	}
	else if(style==2){
		rs.Open( 1,_T( "SELECT Table_ID,Seat_Num,Table_Position,Table_Situation FROM Dinner_Table"));
		m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
		m_list.InsertColumn(0,_T("餐桌号"),LVCFMT_LEFT,80);
		m_list.InsertColumn(1,_T("座位数"),LVCFMT_LEFT,80);
		m_list.InsertColumn(2,_T("位置"),LVCFMT_LEFT,80);
		m_list.InsertColumn(3,_T("使用情况"),LVCFMT_LEFT,80);
	}
	else if(style==3){
		rs.Open( 1,_T( "SELECT Client_ID,Table_ID,Client_Message FROM Client"));
		m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
		m_list.InsertColumn(0,_T("顾客号"),LVCFMT_LEFT,80);
		m_list.InsertColumn(1,_T("餐桌号"),LVCFMT_LEFT,80);
		m_list.InsertColumn(2,_T("顾客信息"),LVCFMT_LEFT,80);
	}
	else if(style==4){
		rs.Open( 1,_T( "SELECT Dishes_ID,Dishes_Name,Dishes_Price,Dishes_Classification FROM Dishes_List"));
		m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
		m_list.InsertColumn(0,_T("菜号"),LVCFMT_LEFT,80);
		m_list.InsertColumn(1,_T("菜名"),LVCFMT_LEFT,80);
		m_list.InsertColumn(2,_T("价格"),LVCFMT_LEFT,80);
		m_list.InsertColumn(3,_T("菜类"),LVCFMT_LEFT,80);
	}
	else if(style==5){
		rs.Open( 1,_T( "SELECT Bill_ID,Client_ID,Dishes_ID,Dishes_Name,Quantity,Price FROM Bill"));
		m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
		m_list.InsertColumn(0,_T("账单号"),LVCFMT_LEFT,80);
		m_list.InsertColumn(1,_T("顾客号"),LVCFMT_LEFT,80);
		m_list.InsertColumn(2,_T("菜号"),LVCFMT_LEFT,80);
		m_list.InsertColumn(3,_T("菜名"),LVCFMT_LEFT,80);
		m_list.InsertColumn(4,_T("数量"),LVCFMT_LEFT,80);
		m_list.InsertColumn(5,_T("价格"),LVCFMT_LEFT,80);
	}
	else if(style==6){
		rs.Open( 1,_T( "SELECT Department_ID,Department_Name FROM Department"));
		m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
		m_list.InsertColumn(0,_T("部门号"),LVCFMT_LEFT,80);
		m_list.InsertColumn(1,_T("部门名"),LVCFMT_LEFT,80);
	}
	else if(style==7){
		rs.Open( 1,_T( "SELECT Goods_ID,Employee_ID,Goods_Name,Goods_Quantity,Purchase_Date FROM Purchase"));
		m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
		m_list.InsertColumn(0,_T("商品号"),LVCFMT_LEFT,80);
		m_list.InsertColumn(1,_T("员工号"),LVCFMT_LEFT,80);
		m_list.InsertColumn(2,_T("商品名"),LVCFMT_LEFT,80);
		m_list.InsertColumn(3,_T("进货数量"),LVCFMT_LEFT,80);
		m_list.InsertColumn(4,_T("进货时间"),LVCFMT_LEFT,80);
	}
	else if(style==8){
		rs.Open( 1,_T( "SELECT Goods_ID,Goods_Name,Goods_Price FROM Goods"));
		m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
		m_list.InsertColumn(0,_T("商品号"),LVCFMT_LEFT,80);
		m_list.InsertColumn(1,_T("商品名"),LVCFMT_LEFT,80);
		m_list.InsertColumn(2,_T("价格"),LVCFMT_LEFT,80);
		
	}
	if(style==1||style==3||style==6){
		CDBVariant varValue;
		short nFields = rs.GetODBCFieldCount( );
		int k=0;
		while( !rs.IsEOF( ) )
		{
			rs.GetFieldValue( short(0), varValue );
			CString str;
			str=*varValue.m_pstring ;
			str.TrimRight (" ");
			m_list.InsertItem(k,str,k);
			for( short index = 1; index < nFields; index++ )
			{
				rs.GetFieldValue( index, varValue );
				CString ss;
				ss=*varValue.m_pstring ;
				ss.TrimRight (" ");
				m_list.SetItemText(k,index,ss);

			}
			rs.MoveNext( );
			k++;
		}
	}
	else if(style==2){
		CDBVariant varValue;
		short nFields = rs.GetODBCFieldCount( );
		int k=0;
		while( !rs.IsEOF( ) )
		{
			rs.GetFieldValue( short(0), varValue );
			CString str;
			str=*varValue.m_pstring ;
			str.TrimRight (" ");
			m_list.InsertItem(k,str,k);
			for( short index = 1; index < nFields; index++ )
			{
				rs.GetFieldValue( index, varValue );
				CString ss;
				if(index==1)
				{
					int temp=varValue.m_iVal ;
					ss.Format("%d",temp);
				}
				else
					ss=*varValue.m_pstring ;
				ss.TrimRight (" ");
				m_list.SetItemText(k,index,ss);

			}
			rs.MoveNext( );
			k++;
		}
	}
	else if(style==4){
		CDBVariant varValue;
		short nFields = rs.GetODBCFieldCount( );
		int k=0;
		while( !rs.IsEOF( ) )
		{
			rs.GetFieldValue( short(0), varValue );
			CString str;
			str=*varValue.m_pstring ;
			str.TrimRight (" ");
			m_list.InsertItem(k,str,k);
			for( short index = 1; index < nFields; index++ )
			{
				rs.GetFieldValue( index, varValue );
				CString ss;
				if(index==2)
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
	}
	else if(style==5){
		CDBVariant varValue;
		short nFields = rs.GetODBCFieldCount( );
		int k=0;
		while( !rs.IsEOF( ) )
		{
			rs.GetFieldValue( short(0), varValue );
			CString str;
			str=*varValue.m_pstring ;
			str.TrimRight (" ");
			m_list.InsertItem(k,str,k);
			for( short index = 1; index < nFields; index++ )
			{
				rs.GetFieldValue( index, varValue );
				CString ss;
				if(index==4)
				{
					int temp=varValue.m_iVal ;
					ss.Format("%d",temp);
					ss=ss+"份";
				}
				else if(index==5)
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
	}
	else if(style==7){
		CDBVariant varValue;
		short nFields = rs.GetODBCFieldCount( );
		int k=0;
		while( !rs.IsEOF( ) )
		{
			rs.GetFieldValue( short(0), varValue );
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
				}
				else
					ss=*varValue.m_pstring ;
				ss.TrimRight (" ");
				m_list.SetItemText(k,index,ss);

			}
			rs.MoveNext( );
			k++;
		}
	}
	else if(style==8){
		CDBVariant varValue;
		short nFields = rs.GetODBCFieldCount( );
		int k=0;
		while( !rs.IsEOF( ) )
		{
			rs.GetFieldValue( short(0), varValue );
			CString str;
			str=*varValue.m_pstring ;
			str.TrimRight (" ");
			m_list.InsertItem(k,str,k);
			for( short index = 1; index < nFields; index++ )
			{
				rs.GetFieldValue( index, varValue );
				CString ss;
				if(index==2)
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
	}
	rs.Close();
	db.Close ();
}

void CGoods::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	C管理终端Dlg dlg;
	CDialog::OnOK();
	dlg.DoModal();
}


void CGoods::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	if(style==3||style==5||style==7||style==8)
	{
		MessageBox("此表格不允擅自添加!");
		return;
	}
	else if(style==1)
	{
		CGoodsAdd dlg;
		if(IDOK==dlg.DoModal())
		{
			Update();
		}
		return;
	}
	else if(style==2)
	{
		CTableAdd dlg;
		if(IDOK==dlg.DoModal())
		{
			Update();
		}
		return;
	}
	else if(style==4)
	{
		CDishesAdd dlg;
		if(IDOK==dlg.DoModal())
		{
			Update();
		}
		return;
	}
	else if(style==6)
	{
		CDeptAdd dlg;
		if(IDOK==dlg.DoModal())
		{
			Update();
		}
		return;
	}
}


void CGoods::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	if(style==3||style==5||style==7||style==8)
	{
		MessageBox("此表格不允许擅自删除!");
		return;
	}
	CDatabase db;
    CRecordset rs(&db);
	int num=-1;
	num=m_list.GetSelectionMark();
	CString s=m_list.GetItemText(num,0);//i是行，j是列。m_list是个list control 对象
	if(num>=0)
	{
		if(MessageBox(_T("真的要删除档案吗？"),_T("提示"),MB_YESNO|MB_ICONWARNING)==IDYES)
		{
			CString s=m_list.GetItemText(num,0);
			CString sql;
			db.OpenEx (_T("DSN=user_message;UID=sa;PWD=xxx"));
			if(style==1)
			{
				rs.Open( 1,_T( "SELECT Employee_ID,Employee_Password,Employee_Name,Employee_Sex,Department_ID,Employee_Style FROM Employee"));
				sql="delete from Employee where Employee_ID="+s ;
			}
			else if(style==2)
			{
				rs.Open( 1,_T( "SELECT Table_ID,Seat_Num,Table_Position,Table_Situation FROM Dinner_Table"));
				sql="delete from Dinner_Table where Table_ID="+s ;
			}
			else if(style==4)
			{
				rs.Open( 1,_T( "SELECT Dishes_ID,Dishes_Name,Dishes_Price,Dishes_Classification FROM Dishes_List"));
				sql="delete from Dishes_List where Dishes_ID="+s ;
			}
			else if(style==6)
			{
				rs.Open( 1,_T( "SELECT Department_ID,Department_Name FROM Department"));
				sql="delete from Department where Department_ID="+s ;
			}
			db.ExecuteSQL (sql);
			rs.Close();
	        db.Close ();
			Update();
		}
	}
	else
		MessageBox(_T("请选择要删除的档案！"),_T("提示"),MB_OK|MB_ICONWARNING);
	m_list.SetSelectionMark(-1);
}

CString s1;//i是行，j是列。m_list是个list control 对象
CString s2;
CString s3;
CString s4;
CString s5;
CString s6;
void CGoods::OnBnClickedButton12()
{
	// TODO: 在此添加控件通知处理程序代码
	if(style==3||style==5||style==7||style==8)
	{
		MessageBox("此表格不允许擅自修改!");
		return;
	}
	int num=-1;
	num=m_list.GetSelectionMark();
	if(style==1)
	{
		if(num>=0)
		{
			s1=m_list.GetItemText(num,0);//员工号
			s2=m_list.GetItemText(num,1);//密码
			s3=m_list.GetItemText(num,2);//姓名
			s4=m_list.GetItemText(num,4);//部门号
			s5=m_list.GetItemText(num,5);//工种
			s6=m_list.GetItemText(num,3);//性别
			CGoodsUpdate dlg;
			if(IDOK==dlg.DoModal())
			{
				Update();
			}

		}
		else
			MessageBox(_T("请选择要修改的档案！"),_T("提示"),MB_OK|MB_ICONWARNING);
		m_list.SetSelectionMark(-1);
	}
	else if(style==2)
	{
		if(num>=0)
		{
			s1=m_list.GetItemText(num,0);
			s2=m_list.GetItemText(num,1);
			s3=m_list.GetItemText(num,2);
			s4=m_list.GetItemText(num,3);
			CTableUpdate dlg;
			if(IDOK==dlg.DoModal())
			{
				Update();
			}

		}
		else
			MessageBox(_T("请选择要修改的档案！"),_T("提示"),MB_OK|MB_ICONWARNING);
		m_list.SetSelectionMark(-1);
	}
	else if(style==4)
	{
		if(num>=0)
		{
			s1=m_list.GetItemText(num,0);
			s2=m_list.GetItemText(num,1);
			s3=m_list.GetItemText(num,2);
			s4=m_list.GetItemText(num,3);
			CDishesUpdate dlg;
			if(IDOK==dlg.DoModal())
			{
				Update();
			}

		}
		else
			MessageBox(_T("请选择要修改的档案！"),_T("提示"),MB_OK|MB_ICONWARNING);
		m_list.SetSelectionMark(-1);
	}
	else if(style==6)
	{
		if(num>=0)
		{
			s1=m_list.GetItemText(num,0);
			s2=m_list.GetItemText(num,1);
			CDeptUpdte dlg;
			if(IDOK==dlg.DoModal())
			{
				Update();
			}

		}
		else
			MessageBox(_T("请选择要修改的档案！"),_T("提示"),MB_OK|MB_ICONWARNING);
		m_list.SetSelectionMark(-1);
	}
}
