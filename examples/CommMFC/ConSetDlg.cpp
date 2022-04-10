// ConSetDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CommMFC.h"
#include "ConSetDlg.h"
#include "afxdialogex.h"


// CConSetDlg 对话框

IMPLEMENT_DYNAMIC(CConSetDlg, CDialogEx)

CConSetDlg::CConSetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CConSetDlg::IDD, pParent)
	, strComPort(_T(""))
{

}

CConSetDlg::~CConSetDlg()
{
}

void CConSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CConSetDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CConSetDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CConSetDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CConSetDlg::OnBnClickedButton1)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CConSetDlg 消息处理程序


void CConSetDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void CConSetDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CConSetDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}


BOOL CConSetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//获取串口号

	CComboBox* pCComboBox=(CComboBox*)GetDlgItem(IDC_COMBO1);

	vector<SerialPortInfo> m_portsList = CSerialPortInfo::availablePortInfos();
	TCHAR m_regKeyValue[255];
	for (size_t i = 0; i < m_portsList.size(); i++)
	{
#ifdef UNICODE
		int iLength;
		const char * _char = m_portsList[i].portName.c_str();
		iLength = MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, NULL, 0);
		MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, m_regKeyValue, iLength);
#else
		strcpy_s(m_regKeyValue, 255, m_portsList[i].portName.c_str());
#endif
		
		pCComboBox->AddString(m_regKeyValue);
	}

	pCComboBox->SetCurSel(0);

	//300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 38400, 56000, 57600, 115200
	CComboBox* pCComboBox10=(CComboBox*)GetDlgItem(IDC_COMBO10);
	pCComboBox10->AddString(_T("300"));
	pCComboBox10->AddString(_T("600"));
	pCComboBox10->AddString(_T("1200"));
	pCComboBox10->AddString(_T("2400"));
	pCComboBox10->AddString(_T("4800"));
	pCComboBox10->AddString(_T("9600"));
	pCComboBox10->AddString(_T("14400"));
	pCComboBox10->AddString(_T("19200"));
	pCComboBox10->AddString(_T("38400"));
	pCComboBox10->AddString(_T("56000"));
	pCComboBox10->AddString(_T("57600"));
	pCComboBox10->AddString(_T("115200"));
	pCComboBox10->SetCurSel(5);

	//string ParityArray[] = { "None", "Odd", "Even", "Mark", "Space" };
	CComboBox* pCComboBox11=(CComboBox*)GetDlgItem(IDC_COMBO11);
	pCComboBox11->AddString(_T("None"));
	pCComboBox11->AddString(_T("Odd"));
	pCComboBox11->AddString(_T("Even"));
	pCComboBox11->AddString(_T("Mark"));
	pCComboBox11->AddString(_T("Space"));
	pCComboBox11->SetCurSel(0);

	//string DataBitsArray[] = { "5", "6", "7","8" };
	CComboBox* pCComboBox12=(CComboBox*)GetDlgItem(IDC_COMBO12);
	pCComboBox12->AddString(_T("5"));
	pCComboBox12->AddString(_T("6"));
	pCComboBox12->AddString(_T("7"));
	pCComboBox12->AddString(_T("8"));
	pCComboBox12->SetCurSel(3);

	//string StopArray[] = { "1", "1.5", "2"};
	CComboBox* pCComboBox13=(CComboBox*)GetDlgItem(IDC_COMBO13);
	pCComboBox13->AddString(_T("1"));
	pCComboBox13->AddString(_T("1.5"));
	pCComboBox13->AddString(_T("2"));
	pCComboBox13->SetCurSel(0);

	SetDlgItemText(IDC_EDIT10,_T("50"));

	if(PathFileExists(GetModuleDir() + _T("AppConfig.ini")))
	{
		ShowConfig();
	}
	pCComboBox11->EnableWindow(FALSE);
	pCComboBox12->EnableWindow(FALSE);
	pCComboBox13->EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CConSetDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//保存配置文件
	CString strComPort, strBaudRate, strParityBit, strDataBit, strStopBit, strReceiveTimeoutMS;
	GetDlgItemText(IDC_COMBO1, strComPort);
	GetDlgItemText(IDC_COMBO10, strBaudRate);
	GetDlgItemText(IDC_COMBO11, strParityBit);
	GetDlgItemText(IDC_COMBO12, strDataBit);
	GetDlgItemText(IDC_COMBO13, strStopBit);
	GetDlgItemText(IDC_EDIT10, strReceiveTimeoutMS);
	CString ConfigFileName = GetModuleDir() + _T("AppConfig.ini");
	WritePrivateProfileString(_T("SETTING CONFIG"), _T("ComPort"), strComPort, ConfigFileName);
	WritePrivateProfileString(_T("SETTING CONFIG"), _T("BaudRate"), strBaudRate, ConfigFileName);
	WritePrivateProfileString(_T("SETTING CONFIG"), _T("ParityBit"), strParityBit, ConfigFileName);
	WritePrivateProfileString(_T("SETTING CONFIG"), _T("DataBit"), strDataBit, ConfigFileName);
	WritePrivateProfileString(_T("SETTING CONFIG"), _T("StopBit"), strStopBit, ConfigFileName);
	WritePrivateProfileString(_T("SETTING CONFIG"), _T("ReceiveTimeoutMS"), strReceiveTimeoutMS, ConfigFileName);

	CDialogEx::OnClose();
}


CString CConSetDlg::GetModuleDir(void)	//获取当前程序目录
{
	CString  strPathName;
	GetModuleFileName(NULL, strPathName.GetBuffer(MAX_PATH), MAX_PATH);
	strPathName.ReleaseBuffer(MAX_PATH);
	int nPos = strPathName.ReverseFind(_T('\\'));
	strPathName = strPathName.Left(nPos + 1);
	return strPathName;
}


bool CConSetDlg::ShowConfig(void)
{
	CString ConfigFileName = GetModuleDir() + _T("AppConfig.ini");

	CString strComPort, strBaudRate, strParityBit, strDataBit, strStopBit, strReceiveTimeoutMS;
	GetPrivateProfileString(
		_T("SETTING CONFIG"),
		_T("ComPort"),
		_T(""),
		strComPort.GetBuffer(MAX_PATH),
		MAX_PATH,
		ConfigFileName
	);
	strComPort.ReleaseBuffer();

	GetPrivateProfileString(
		_T("SETTING CONFIG"),
		_T("BaudRate"),
		_T(""),
		strBaudRate.GetBuffer(MAX_PATH),
		MAX_PATH,
		ConfigFileName
	);
	strBaudRate.ReleaseBuffer();

	GetPrivateProfileString(
		_T("SETTING CONFIG"),
		_T("ParityBit"),
		_T(""),
		strParityBit.GetBuffer(MAX_PATH),
		MAX_PATH,
		ConfigFileName
	);
	strParityBit.ReleaseBuffer();

	GetPrivateProfileString(
		_T("SETTING CONFIG"),
		_T("DataBit"),
		_T(""),
		strDataBit.GetBuffer(MAX_PATH),
		MAX_PATH,
		ConfigFileName
	);
	strDataBit.ReleaseBuffer();

	GetPrivateProfileString(
		_T("SETTING CONFIG"),
		_T("StopBit"),
		_T(""),
		strStopBit.GetBuffer(MAX_PATH),
		MAX_PATH,
		ConfigFileName
	);
	strStopBit.ReleaseBuffer();

	GetPrivateProfileString(
		_T("SETTING CONFIG"),
		_T("ReceiveTimeoutMS"),
		_T(""),
		strReceiveTimeoutMS.GetBuffer(MAX_PATH),
		MAX_PATH,
		ConfigFileName
	);
	strReceiveTimeoutMS.ReleaseBuffer();

	SetDlgItemText(IDC_COMBO1, strComPort);
	SetDlgItemText(IDC_COMBO10, strBaudRate);
	SetDlgItemText(IDC_COMBO11, strParityBit);
	SetDlgItemText(IDC_COMBO12, strDataBit);
	SetDlgItemText(IDC_COMBO13, strStopBit);
	SetDlgItemText(IDC_EDIT10, strReceiveTimeoutMS);

	return true;
}
