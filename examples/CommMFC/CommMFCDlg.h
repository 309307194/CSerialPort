// CommMFCDlg.h : 头文件
//

#pragma once

//About CSerialPort start
#include "CSerialPort/SerialPort.h"
#include "CSerialPort/SerialPortInfo.h"
#include "afxwin.h"
#include "afxext.h"
using namespace itas109;
//About CSerialPort end


// CCommMFCDlg 对话框
class CCommMFCDlg : public CDialog, public has_slots<>//About CSerialPort 
{
// 构造
public:
	CCommMFCDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_COMMMFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	void OnReceive();//About CSerialPort
	void OnReceiveBusiness(); // receive business


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()

public:
	CComboBox m_PortNr;
	CComboBox m_BaudRate;
	CComboBox m_Parity;
	CComboBox m_Stop;
	CComboBox m_DataBits;
	CButton m_OpenCloseCtrl;
	CEdit m_Send;
	CEdit m_ReceiveCtrl;
	CStatic m_recvCountCtrl;
	CStatic m_sendCountCtrl;
	CEdit m_ReceiveTimeoutMSCtrl;
	UINT m_ReceiveTimeoutMS;

	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonOpenClose();
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedButtonClear();

private:
	CSerialPort m_SerialPort;//About CSerialPort 

	int rx; 
	int tx;

	BOOL m_isTimerRunning;	
public:
	afx_msg void OnHelpAbout();
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnOpen();
	bool UserInterfaceInit(void);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CFont m_font;
	afx_msg void OnBnClickedButtonSend2();
	bool CStdioFileWriteEndString(LPCTSTR lpszFileName, CString ContextString);
	bool WriteApplicationFile(CString strPath);
	bool ReadApplicationFile(CString strPath);
	unsigned int CalculateCRC32(LPCTSTR lpszFileName);
	unsigned short calculate_crc16(unsigned short CRC_INIT, unsigned short CRC_POLY, unsigned short CRC_RESULT_XOR, bool input_invert, bool ouput_invert, const char* inputData, int inputDataLen);
	unsigned short crc16table(unsigned char* ptr, unsigned short len);
	bool SpanIncluding(CString str);
	afx_msg void OnEnChangeEdit5();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnEnChangeEdit7();
	afx_msg void OnEnChangeEdit8();
	afx_msg void OnEnChangeEdit9();
	afx_msg void OnEnChangeEdit10();
	afx_msg void OnEnChangeEdit11();
	afx_msg void OnEnChangeEdit12();
	afx_msg void OnEnChangeEdit13();
	afx_msg void OnEnChangeEdit14();
	afx_msg void OnEnChangeEdit15();
	afx_msg void OnEnChangeEdit16();
	afx_msg void OnEnChangeEdit17();
	afx_msg void OnEnChangeEdit18();
	afx_msg void OnEnChangeEdit19();
	afx_msg void OnEnChangeEdit20();
	afx_msg void OnEnChangeEdit21();
	afx_msg void OnEnChangeEdit22();
	afx_msg void OnEnChangeEdit23();
	afx_msg void OnEnChangeEdit24();
	afx_msg void OnEnChangeEdit25();
	afx_msg void OnEnChangeEdit30();
	afx_msg void OnEnChangeEdit31();
	bool GetData2Hex(void);
	afx_msg void OnBnClickedButton2();
	bool GetEditFloat2Binary32(int nID, unsigned char* pbyte);
	bool AddStr2EditCtr(CString str);
	bool AddDebugStr2EditCtr(CString str);
	int AddRadioStr2EditCtr(int nRadioCtrGroup1, int nRadioCtrGroup0);
	bool GetUi2Hex(void);
	bool AddStr2EditCtr(CString str, int nCtrID);
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnSave();
	afx_msg void OnExit();
	afx_msg void OnConSet();
	CStatusBar m_bar;
	CString GetModuleDir(void);
	bool ShowConfig(void);
	bool OpenComPort(CString strComPort, CString strBaudRate, CString strParityBit, CString strDataBit, CString strStopBit);
	string W2AString(const wchar_t* str);
	bool SendUi2Com();
};
