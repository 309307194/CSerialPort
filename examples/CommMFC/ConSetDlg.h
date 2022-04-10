#pragma once

#include "CSerialPort/SerialPort.h"
#include "CSerialPort/SerialPortInfo.h"
#include "afxwin.h"
#include "afxext.h"
using namespace itas109;
// CConSetDlg 对话框

class CConSetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CConSetDlg)

public:
	CConSetDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CConSetDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();
	CString strComPort;
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	CString GetModuleDir(void);
	bool ShowConfig(void);
};
