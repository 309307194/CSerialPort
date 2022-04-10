// ABC.cpp : 实现文件
//

#include "stdafx.h"
#include "CommMFC.h"
#include "ABC.h"
#include "afxdialogex.h"


// CABC 对话框

IMPLEMENT_DYNAMIC(CABC, CDialogEx)

CABC::CABC(CWnd* pParent /*=NULL*/)
	: CDialogEx(CABC::IDD, pParent)
{

}

CABC::~CABC()
{
}

void CABC::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CABC, CDialogEx)
	ON_COMMAND(ID_32771, &CABC::OnOpen)
	ON_BN_CLICKED(IDOK, &CABC::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CABC::OnBnClickedCancel)
END_MESSAGE_MAP()


// CABC 消息处理程序


void CABC::OnOpen()
{
	// TODO: 在此添加命令处理程序代码
}


void CABC::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void CABC::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
