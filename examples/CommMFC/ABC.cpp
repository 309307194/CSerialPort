// ABC.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CommMFC.h"
#include "ABC.h"
#include "afxdialogex.h"


// CABC �Ի���

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


// CABC ��Ϣ�������


void CABC::OnOpen()
{
	// TODO: �ڴ���������������
}


void CABC::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}


void CABC::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
