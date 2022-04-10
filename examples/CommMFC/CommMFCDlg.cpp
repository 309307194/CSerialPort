// CommMFCDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CommMFC.h"
#include "CommMFCDlg.h"
#include "ConSetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define RECEIVE_TIMER_EVENT 1

int BaudRateArray[] = { 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 38400, 56000, 57600, 115200 };

string ParityArray[] = { "None", "Odd", "Even", "Mark", "Space" };

string DataBitsArray[] = { "5", "6", "7","8" };

string StopArray[] = { "1", "1.5", "2"};


static UINT BASED_CODE indicators[]=
{
    IDS_STRING102,
    IDS_STRING103
};
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CCommMFCDlg 对话框




CCommMFCDlg::CCommMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCommMFCDlg::IDD, pParent)
	, m_ReceiveTimeoutMS(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCommMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_COMBO_PORT_Nr, m_PortNr);
	//DDX_Control(pDX, IDC_COMBO_BAUDRATE, m_BaudRate);
	//DDX_Control(pDX, IDC_BUTTON_OPEN_CLOSE, m_OpenCloseCtrl);
	//DDX_Control(pDX, IDC_SendEdit, m_Send);
	//DDX_Control(pDX, IDC_ReceiveEdit, m_ReceiveCtrl);
	DDX_Control(pDX, IDC_STATIC_RECV_COUNT_VALUE, m_recvCountCtrl);
	DDX_Control(pDX, IDC_STATIC_SEND_COUNT_VALUE, m_sendCountCtrl);
	//DDX_Control(pDX, IDC_COMBO_PARITY, m_Parity);
	//DDX_Control(pDX, IDC_COMBO_STOP, m_Stop);
	//DDX_Control(pDX, IDC_COMBO_DATABITS, m_DataBits);
	DDX_Text(pDX, IDC_EDIT_RECEIVE_TIMEOUT_MS, m_ReceiveTimeoutMS);
	DDV_MinMaxUInt(pDX, m_ReceiveTimeoutMS, 0, 999999);
	//DDX_Control(pDX, IDC_EDIT_RECEIVE_TIMEOUT_MS, m_ReceiveTimeoutMSCtrl);
}

BEGIN_MESSAGE_MAP(CCommMFCDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN_CLOSE, &CCommMFCDlg::OnBnClickedButtonOpenClose)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CCommMFCDlg::OnBnClickedButtonSend)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CCommMFCDlg::OnBnClickedButtonClear)
	ON_WM_TIMER()
	ON_COMMAND(ID_32773, &CCommMFCDlg::OnHelpAbout)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CCommMFCDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CCommMFCDlg::OnBnClickedButtonSave)
	ON_COMMAND(ID_32771, &CCommMFCDlg::OnOpen)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_SEND2, &CCommMFCDlg::OnBnClickedButtonSend2)
	ON_EN_CHANGE(IDC_EDIT5, &CCommMFCDlg::OnEnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT6, &CCommMFCDlg::OnEnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT7, &CCommMFCDlg::OnEnChangeEdit7)
	ON_EN_CHANGE(IDC_EDIT8, &CCommMFCDlg::OnEnChangeEdit8)
	ON_EN_CHANGE(IDC_EDIT9, &CCommMFCDlg::OnEnChangeEdit9)
	ON_EN_CHANGE(IDC_EDIT10, &CCommMFCDlg::OnEnChangeEdit10)
	ON_EN_CHANGE(IDC_EDIT11, &CCommMFCDlg::OnEnChangeEdit11)
	ON_EN_CHANGE(IDC_EDIT12, &CCommMFCDlg::OnEnChangeEdit12)
	ON_EN_CHANGE(IDC_EDIT13, &CCommMFCDlg::OnEnChangeEdit13)
	ON_EN_CHANGE(IDC_EDIT14, &CCommMFCDlg::OnEnChangeEdit14)
	ON_EN_CHANGE(IDC_EDIT15, &CCommMFCDlg::OnEnChangeEdit15)
	ON_EN_CHANGE(IDC_EDIT16, &CCommMFCDlg::OnEnChangeEdit16)
	ON_EN_CHANGE(IDC_EDIT17, &CCommMFCDlg::OnEnChangeEdit17)
	ON_EN_CHANGE(IDC_EDIT18, &CCommMFCDlg::OnEnChangeEdit18)
	ON_EN_CHANGE(IDC_EDIT19, &CCommMFCDlg::OnEnChangeEdit19)
	ON_EN_CHANGE(IDC_EDIT20, &CCommMFCDlg::OnEnChangeEdit20)
	ON_EN_CHANGE(IDC_EDIT21, &CCommMFCDlg::OnEnChangeEdit21)
	ON_EN_CHANGE(IDC_EDIT22, &CCommMFCDlg::OnEnChangeEdit22)
	ON_EN_CHANGE(IDC_EDIT23, &CCommMFCDlg::OnEnChangeEdit23)
	ON_EN_CHANGE(IDC_EDIT24, &CCommMFCDlg::OnEnChangeEdit24)
	ON_EN_CHANGE(IDC_EDIT25, &CCommMFCDlg::OnEnChangeEdit25)
	ON_EN_CHANGE(IDC_EDIT30, &CCommMFCDlg::OnEnChangeEdit30)
	ON_EN_CHANGE(IDC_EDIT31, &CCommMFCDlg::OnEnChangeEdit31)
	//ON_BN_CLICKED(IDC_BUTTON2, &CCommMFCDlg::OnBnClickedButton2)
	//ON_BN_CLICKED(IDC_BUTTON3, &CCommMFCDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &CCommMFCDlg::OnBnClickedButton1)
	//ON_BN_CLICKED(IDC_BUTTON4, &CCommMFCDlg::OnBnClickedButton4)
	ON_COMMAND(ID_32772, &CCommMFCDlg::OnSave)
	ON_COMMAND(ID_32774, &CCommMFCDlg::OnExit)
	ON_COMMAND(ID_32775, &CCommMFCDlg::OnConSet)
END_MESSAGE_MAP()


// CCommMFCDlg 消息处理程序

BOOL CCommMFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	rx = 0;
	tx = 0;
	//m_recvCountCtrl.SetWindowText(CString("0"));
	//m_sendCountCtrl.SetWindowText(CString("0"));

	m_isTimerRunning = FALSE;
	// 默认接收超时时间(毫秒)
	//m_ReceiveTimeoutMSCtrl.SetWindowText(_T("50"));

	CString temp;
	//添加波特率到下拉列表
	//for (int i = 0; i < sizeof(BaudRateArray) / sizeof(int); i++)
	//{
	//	temp.Format(_T("%d"), BaudRateArray[i]);
	//	m_BaudRate.InsertString(i, temp);
	//}

	//temp.Format(_T("%d"), 9600);
	//m_BaudRate.SetCurSel(m_BaudRate.FindString(0, temp));

//	//校验位
//	for (int i = 0; i < sizeof(ParityArray) / sizeof(string); i++)
//	{
//#ifdef UNICODE
//		temp.Format(_T("%S"), ParityArray[i].c_str());
//#else
//		temp.Format(_T("%s"), ParityArray[i].c_str());
//#endif
//		m_Parity.InsertString(i, temp);
//	}
//	m_Parity.SetCurSel(0);
//
//	//数据位
//	for (int i = 0; i < sizeof(DataBitsArray) / sizeof(string); i++)
//	{
//#ifdef UNICODE
//		temp.Format(_T("%S"), DataBitsArray[i].c_str());
//#else
//		temp.Format(_T("%s"), DataBitsArray[i].c_str());
//#endif
//		m_DataBits.InsertString(i, temp);
//	}
//	m_DataBits.SetCurSel(3);

	//停止位
//	for (int i = 0; i < sizeof(StopArray) / sizeof(string); i++)
//	{
//#ifdef UNICODE
//		temp.Format(_T("%S"), StopArray[i].c_str());
//#else
//		temp.Format(_T("%s"), StopArray[i].c_str());
//#endif
//		m_Stop.InsertString(i, temp);
//	}
//	m_Stop.SetCurSel(0);

	//获取串口号
//	vector<SerialPortInfo> m_portsList = CSerialPortInfo::availablePortInfos();
//	TCHAR m_regKeyValue[255];
//	for (size_t i = 0; i < m_portsList.size(); i++)
//	{
//#ifdef UNICODE
//		int iLength;
//		const char * _char = m_portsList[i].portName.c_str();
//		iLength = MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, NULL, 0);
//		MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, m_regKeyValue, iLength);
//#else
//		strcpy_s(m_regKeyValue, 255, m_portsList[i].portName.c_str());
//#endif
//		m_PortNr.AddString(m_regKeyValue);
//	}
	//m_PortNr.SetCurSel(0);
	
	//OnBnClickedButtonOpenClose();

	//m_Send.SetWindowText(_T("https://blog.csdn.net/itas109"));

	m_SerialPort.readReady.connect(this, &CCommMFCDlg::OnReceive);

	//界面初始化
	UserInterfaceInit();

	//特殊字体初始化
	m_font.CreatePointFont(150,_T("宋体"));//代表15号宋体（华文行楷在WIN11显示不好看）

	//SetDlgItemText(IDC_SendEdit2, _T("0102C3B4A5D6FF"));

	//补充控件初始化
	m_bar.Create(this);//创建状态栏
	m_bar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT)); //设置状态栏数目
	CRect rect;
	GetClientRect(&rect);
	//设置各栏长度
	m_bar.SetPaneInfo(0, IDS_STRING102, SBPS_NORMAL, 300);
	m_bar.SetPaneInfo(0, IDS_STRING103, SBPS_STRETCH, rect.Width()-300);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, IDS_STRING103);	//指定状态栏位置
	//加载配置文件，自动连接
	if(PathFileExists(GetModuleDir() + _T("AppConfig.ini")))
	{
		//状态栏显示配置文件的连接状态
		ShowConfig();
	}
	else
	{
		//状态栏显示默认的连接状态,默认连接COM1
		OpenComPort(_T("COM1"), _T("9600"), _T("None"), _T("8"), _T("1"));
	}
	CString strSysCurrentTime;
	SYSTEMTIME stTime;
	GetLocalTime(&stTime);
	strSysCurrentTime.Format(
		_T("%04d/%02d/%02d %02d:%02d:%02d"), 
		stTime.wYear,
		stTime.wMonth,
		stTime.wDay,
		stTime.wHour, 
		stTime.wMinute, 
		stTime.wSecond);
	m_bar.SetPaneText(1,strSysCurrentTime);
	SetTimer(100, 1000, NULL);	//启动定时器刷新

	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCommMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCommMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCommMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCommMFCDlg::OnBnClickedButtonOpenClose()
{
	//GetDlgItem(IDC_SendEdit)->SetFocus();
	CString temp;
	m_OpenCloseCtrl.GetWindowText(temp);///获取按钮的文本
	UpdateData(true);
	if (temp == _T("关闭串口"))///表示点击后是"关闭串口"，也就是已经关闭了串口
	{
		m_SerialPort.close();
		m_OpenCloseCtrl.SetWindowText(_T("打开串口"));///设置按钮文字为"打开串口"
	}
	///打开串口操作
	else if (m_PortNr.GetCount() > 0)///当前列表的内容个数
	{
		string portName;
		int SelBaudRate;
		int SelParity;
		int SelDataBits;
		int SelStop;

		UpdateData(true);
		m_PortNr.GetWindowText(temp);///CString temp
#ifdef UNICODE
		portName = CW2A(temp.GetString());
#else
		portName = temp.GetBuffer();
#endif	

		m_BaudRate.GetWindowText(temp);
		SelBaudRate = _tstoi(temp);	

		SelParity = m_Parity.GetCurSel();

		m_DataBits.GetWindowText(temp);
		SelDataBits = _tstoi(temp);

		SelStop = m_Stop.GetCurSel();

		m_SerialPort.init(portName, SelBaudRate, itas109::Parity(SelParity), itas109::DataBits(SelDataBits), itas109::StopBits(SelStop));
		m_SerialPort.open();

		if (m_SerialPort.isOpened())
		{
			m_OpenCloseCtrl.SetWindowText(_T("关闭串口"));
		}
		else
		{
			AfxMessageBox(_T("串口已被占用！"));
		}
	}
	else
	{
		AfxMessageBox(_T("没有发现串口！"));
	}
}


void CCommMFCDlg::OnBnClickedButtonSend()
{
	GetDlgItem(IDC_SendEdit)->SetFocus();
	CString temp;
	UpdateData(true);
	m_OpenCloseCtrl.GetWindowText(temp);
	if (temp == "打开串口")///没有打开串口
	{
		AfxMessageBox(_T("请首先打开串口"));
		return;
	}

	m_Send.GetWindowText(temp);
	int len = 0;
	char* m_str = NULL;
#ifdef UNICODE
	// 兼容中文
	CStringA strA(temp);
	len = strA.GetLength();
	m_str = strA.GetBuffer();
#else
	len = temp.GetLength();
	m_str = temp.GetBuffer(0);
#endif
	
	m_SerialPort.writeData(m_str, len);

	tx += len;

	CString str2;
	str2.Format(_T("%d"), tx);
	m_sendCountCtrl.SetWindowText(str2);
}


void CCommMFCDlg::OnClose()
{
	m_SerialPort.close();
	CDialog::OnClose();
}

void CCommMFCDlg::OnReceive()
{
	if(m_isTimerRunning)
	{
		KillTimer(RECEIVE_TIMER_EVENT);
	}

	if(0 != m_ReceiveTimeoutMS)
	{
		SetTimer(RECEIVE_TIMER_EVENT, m_ReceiveTimeoutMS, NULL);
	}
	else
	{
		OnReceiveBusiness();
	}
}

void CCommMFCDlg::OnReceiveBusiness()	//接收数据
{
	char * str = NULL;
	str = new char[1024];
	int iRet  = m_SerialPort.readAllData(str);	//从缓冲区接收数据存储到str数组

	if (iRet > 0)
	{
		str[iRet] = '\0';

		CString str1((char*)str);

		rx += str1.GetLength();

		//m_ReceiveCtrl.SetSel(-1, -1);
		//m_ReceiveCtrl.ReplaceSel(str1);

		//CString str2;
		//str2.Format(_T("%d"), rx);
		//m_recvCountCtrl.SetWindowText(str2);
	}

	if(str)
	{
		delete [] str;
		str = NULL;
	}
}


void CCommMFCDlg::OnBnClickedButtonClear()
{
	rx = 0;
	tx = 0;
	m_recvCountCtrl.SetWindowText(CString("0"));
	m_sendCountCtrl.SetWindowText(CString("0"));
}

void CCommMFCDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case RECEIVE_TIMER_EVENT:
		KillTimer(RECEIVE_TIMER_EVENT);
		OnReceiveBusiness();
		break;
	
	default:
		break;
	}

	if(nIDEvent == 100)	//显示时间
	{
		CString strSysCurrentTime;
		SYSTEMTIME stTime;
		GetLocalTime(&stTime);
		strSysCurrentTime.Format(
			_T("%04d/%02d/%02d %02d:%02d:%02d"), 
			stTime.wYear,
			stTime.wMonth,
			stTime.wDay,
			stTime.wHour, 
			stTime.wMinute, 
			stTime.wSecond);
		m_bar.SetPaneText(1,strSysCurrentTime);
	}

	__super::OnTimer(nIDEvent);
}


void CCommMFCDlg::OnHelpAbout()
{
	// TODO: 在此添加命令处理程序代码
	CAboutDlg dlg;
	dlg.DoModal();
}


void CCommMFCDlg::OnBnClickedButtonOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog  filedlg(
		TRUE, 
		NULL, 
		NULL, 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("pro文件(*.pro;)|*.pro;|所有文件( *.* )|*.*||")
	);
	filedlg.m_ofn.lpstrTitle = _T("打开文件");
	if (IDOK == filedlg.DoModal())
	{
		CString strFilePath = filedlg.GetPathName();
		SetDlgItemText(IDC_EDIT_OPEN, strFilePath);

		//按保存的设定加载
		ReadApplicationFile(strFilePath);

		//计算CRC16
		//测试：http://www.ip33.com/crc.html	CRC-16/MODBUS　　　　x16+x15+x2+1
		//参考：https://blog.csdn.net/kezunhb/article/details/81914771
		unsigned char fileArray[4096] = {0};
		CFile file;
		file.Open(strFilePath,CFile::modeRead);
		int len = (int)file.GetLength();	//这里可以确定的是文件长度不可能超过2^32次方
		file.Read(fileArray, len);
		unsigned short res = crc16table(fileArray, len);
		file.Close();

		CString str;
		str.Format(_T("%X"),res);
		SetDlgItemText(IDC_STATIC_CHECKSUM2,str);

		//貌似这种算法是对的
	}
	else
	{
		return;
	}
}


void CCommMFCDlg::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码

	CFileDialog  filedlg(
		FALSE,
		_T("pro"),
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("pro文件(*.pro)|*.pro;|所有文件(*.*)|*.*||")
	);
	filedlg.m_ofn.lpstrTitle = L"保存文件";
	if (IDOK == filedlg.DoModal())
	{
		CString strPath = filedlg.GetPathName();

		//if(!PathFileExists(strPath))	// if not exists the file, create the file; 
		//{
		//}

		//写应用配置文件
		if(WriteApplicationFile(strPath))
		{
			//MessageBox(_T("保存成功"),_T("提示:"));
		}
	}
}


void CCommMFCDlg::OnOpen()
{
	// TODO: 在此添加命令处理程序代码
	OnBnClickedButtonOpen();
}


bool CCommMFCDlg::UserInterfaceInit(void)
{
	//快速选列默认值
	CComboBox* pCComboBox=(CComboBox*)GetDlgItem(IDC_COMBO1);
	pCComboBox->AddString(_T("36V"));
	pCComboBox->AddString(_T("48V"));
	pCComboBox->AddString(_T("60V"));
	pCComboBox->AddString(_T("72V"));
	pCComboBox->AddString(_T("84V"));
	pCComboBox->AddString(_T("96V"));
	pCComboBox->SetCurSel(2);


	CComboBox* pCComboBox2=(CComboBox*)GetDlgItem(IDC_COMBO2);
	pCComboBox2->AddString(_T("36V"));
	pCComboBox2->AddString(_T("48V"));
	pCComboBox2->AddString(_T("60V"));
	pCComboBox2->AddString(_T("72V"));
	pCComboBox2->AddString(_T("84V"));
	pCComboBox2->AddString(_T("96V"));
	pCComboBox2->SetCurSel(3);

	CComboBox* pCComboBox3=(CComboBox*)GetDlgItem(IDC_COMBO3);
	pCComboBox3->AddString(_T("36V"));
	pCComboBox3->AddString(_T("48V"));
	pCComboBox3->AddString(_T("60V"));
	pCComboBox3->AddString(_T("72V"));
	pCComboBox3->AddString(_T("84V"));
	pCComboBox3->AddString(_T("96V"));
	pCComboBox3->SetCurSel(3);

	//欠电压列默认值
	SetDlgItemText(IDC_EDIT5,_T("52.5"));
	SetDlgItemText(IDC_EDIT6,_T("63"));
	SetDlgItemText(IDC_EDIT7,_T("63"));

	//满电电列默认值
	SetDlgItemText(IDC_EDIT8,_T("60"));
	SetDlgItemText(IDC_EDIT9,_T("72"));
	SetDlgItemText(IDC_EDIT10,_T("72"));

	//中点电列默认值
	SetDlgItemText(IDC_EDIT11,_T("30"));
	SetDlgItemText(IDC_EDIT12,_T("36"));
	SetDlgItemText(IDC_EDIT13,_T("36"));

	//中点速列默认值
	SetDlgItemText(IDC_EDIT14,_T("50"));
	SetDlgItemText(IDC_EDIT15,_T("50"));
	SetDlgItemText(IDC_EDIT16,_T("50"));

	//油电门列默认值
	SetDlgItemText(IDC_EDIT17,_T("54.5"));
	SetDlgItemText(IDC_EDIT18,_T("65"));
	SetDlgItemText(IDC_EDIT19,_T("65"));

	//功能配置默认值
	((CButton*)GetDlgItem(IDC_RADIO4))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_RADIO6))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_RADIO8))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_RADIO10))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_RADIO12))->SetCheck(TRUE);

	((CButton*)GetDlgItem(IDC_RADIO13))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_RADIO15))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_RADIO17))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_RADIO20))->SetCheck(TRUE);

	//其他设定默认值
	SetDlgItemText(IDC_EDIT20,_T("29"));
	SetDlgItemText(IDC_EDIT21,_T("25"));
	SetDlgItemText(IDC_EDIT22,_T("4"));
	SetDlgItemText(IDC_EDIT23,_T("1"));
	SetDlgItemText(IDC_EDIT24,_T("20"));
	SetDlgItemText(IDC_EDIT25,_T("2"));

	CComboBox* pCComboBox7=(CComboBox*)GetDlgItem(IDC_COMBO7);
	pCComboBox7->AddString(_T("单次"));
	pCComboBox7->AddString(_T("二次"));
	pCComboBox7->AddString(_T("三次"));
	pCComboBox7->AddString(_T("四次"));
	pCComboBox7->AddString(_T("五次"));
	pCComboBox7->AddString(_T("六次"));
	pCComboBox7->SetCurSel(0);

	CComboBox* pCComboBox8=(CComboBox*)GetDlgItem(IDC_COMBO8);
	pCComboBox8->AddString(_T("无P档"));
	pCComboBox8->AddString(_T("有P档"));
	pCComboBox8->SetCurSel(0);

	CComboBox* pCComboBox9=(CComboBox*)GetDlgItem(IDC_COMBO9);
	pCComboBox9->AddString(_T("不限速"));
	pCComboBox9->AddString(_T("限速"));
	pCComboBox9->SetCurSel(0);

	//左右大灯设定默认值
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(TRUE);

	//档位相关配置设定默认值
	((CButton*)GetDlgItem(IDC_RADIO21))->SetCheck(TRUE);

	CComboBox* pCComboBox4=(CComboBox*)GetDlgItem(IDC_COMBO4);
	pCComboBox4->AddString(_T("手动一档"));
	pCComboBox4->AddString(_T("手动二档"));
	pCComboBox4->AddString(_T("手动三档"));
	pCComboBox4->AddString(_T("手动四档"));
	pCComboBox4->AddString(_T("手动五档"));
	pCComboBox4->AddString(_T("手动六档"));
	pCComboBox4->SetCurSel(2);

	SetDlgItemText(IDC_EDIT30, _T("15"));
	SetDlgItemText(IDC_EDIT31, _T("30"));

	//三电压混合识别设定默认值
	((CButton*)GetDlgItem(IDC_RADIO23))->SetCheck(TRUE);


	return true;
}


HBRUSH CCommMFCDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = __super::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	 if (pWnd->GetDlgCtrlID() == IDC_STATIC_CHECKSUM)
     {
		 //pDC->SetBkColor(RGB(0,255,0));//背景色为绿色
         pDC->SetTextColor(RGB(0, 0, 250));//字体为蓝色
		 pDC->SelectObject(&m_font);//15号宋体

     }

	 if (pWnd->GetDlgCtrlID() == IDC_STATIC_CHECKSUM2)
     {
		 //pDC->SetBkColor(RGB(0,255,0));//背景色为绿色
         pDC->SetTextColor(RGB(250, 0, 250));//字体为红色
		 pDC->SelectObject(&m_font);//15号宋体

     }

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CCommMFCDlg::OnBnClickedButtonSend2()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_SendEdit2)->SetFocus();
	CString temp;
	//UpdateData(true);
	//m_OpenCloseCtrl.GetWindowText(temp);
	//if (temp == "打开串口")///没有打开串口
	//{
	//	AfxMessageBox(_T("请首先打开串口"));
	//	return;
	//}

	//m_Send.GetWindowText(temp);
	GetDlgItemText(IDC_SendEdit2,temp);
	int len = 0;
	char* m_str = NULL;
#ifdef UNICODE
	// 兼容中文
	CStringA strA(temp);
	len = strA.GetLength();
	m_str = strA.GetBuffer();
#else
	len = temp.GetLength();
	m_str = temp.GetBuffer(0);
#endif
	//直接发
	//m_SerialPort.writeData(m_str, len);

	//这里需要加一个算法，来将字符串转换为十六进制
	{
		for(int i = 0; i < len; i++)
		{
			if(m_str[i]>47&&m_str[i]<=58)
			{
				m_str[i]-=48;
			}
			if(m_str[i]>64&&m_str[i]<=71)
			{
				m_str[i]-=55;
			}
		}

		//m_SerialPort.writeData(m_str, len);	//按字符

		//计算每个字符转换后两两字符组合成0xFF格式存储到前面那个，后面的置0
		{
			for(int i = 0; i < len; i+=2)
			{
				m_str[i] = m_str[i] *16 + m_str[i+1];
				m_str[i+1] = 0;
				
			}
		}

		//m_SerialPort.writeData(m_str, len);	//按字符组合置零

		//快速移位删除所有字符数组中的0
		{
			for(int i = 0; i < len/2; i++)
			{
				m_str[i] = m_str[i*2];
				//m_str[len-1-i]=m_str[len-1-(i*2)];
			}
		}

	}

	m_SerialPort.writeData(m_str, len/2);
	strA.ReleaseBuffer();
	tx += len;

	CString str2;
	str2.Format(_T("%d"), tx);
	m_sendCountCtrl.SetWindowText(str2);
}


bool CCommMFCDlg::CStdioFileWriteEndString(LPCTSTR lpszFileName, CString ContextString)
{
	//创建文件 
		CStdioFile file;
		file.Open(lpszFileName, CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite);
		//写入文件
		file.SeekToEnd();
		CString str = _T("\n") + ContextString;

		// 处理UNICODE下【中文乱码】异常
        char * pOldLocale = _strdup(setlocale(LC_CTYPE, NULL));
        setlocale(LC_CTYPE, "chs");

		file.WriteString(str);

		// 处理完毕后,释放资源
		setlocale(LC_CTYPE, pOldLocale);
		free(pOldLocale);

		file.Close();//关闭输出文件

		return true;
}


bool CCommMFCDlg::WriteApplicationFile(CString strPath)
{
	CString str = _T("ApplicationFile");
	CStdioFile file;
	if(file.Open(strPath,CFile::modeCreate|CFile::modeRead|CFile::modeWrite))
	{
		file.WriteString(str);
		file.Close();
	}
	else
	{
		return false;
	}
	
	

	//快速选
	//GetDlgItemText(IDC_COMBO1, str);
	//CStdioFileWriteEndString(strPath, str);

	//GetDlgItemText(IDC_COMBO2, str);
	//CStdioFileWriteEndString(strPath, str);

	//GetDlgItemText(IDC_COMBO3, str);
	//CStdioFileWriteEndString(strPath, str);


	str.Format(_T("%d"),((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel());
	CStdioFileWriteEndString(strPath, str);

	str.Format(_T("%d"),((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCurSel());
	CStdioFileWriteEndString(strPath, str);

	str.Format(_T("%d"),((CComboBox*)GetDlgItem(IDC_COMBO3))->GetCurSel());
	CStdioFileWriteEndString(strPath, str);

	//欠电压
	GetDlgItemText(IDC_EDIT5, str);
	CStdioFileWriteEndString(strPath, str);

	GetDlgItemText(IDC_EDIT6, str);
	CStdioFileWriteEndString(strPath, str);

	GetDlgItemText(IDC_EDIT7, str);
	CStdioFileWriteEndString(strPath, str);

	//满电电
	GetDlgItemText(IDC_EDIT8, str);
	CStdioFileWriteEndString(strPath, str);

	GetDlgItemText(IDC_EDIT9, str);
	CStdioFileWriteEndString(strPath, str);

	GetDlgItemText(IDC_EDIT10, str);
	CStdioFileWriteEndString(strPath, str);

	//中点电
	GetDlgItemText(IDC_EDIT11, str);
	CStdioFileWriteEndString(strPath, str);

	GetDlgItemText(IDC_EDIT12, str);
	CStdioFileWriteEndString(strPath, str);

	GetDlgItemText(IDC_EDIT13, str);
	CStdioFileWriteEndString(strPath, str);

	//中点速
	GetDlgItemText(IDC_EDIT14, str);
	CStdioFileWriteEndString(strPath, str);

	GetDlgItemText(IDC_EDIT15, str);
	CStdioFileWriteEndString(strPath, str);

	GetDlgItemText(IDC_EDIT16, str);
	CStdioFileWriteEndString(strPath, str);

	//油门电
	GetDlgItemText(IDC_EDIT17, str);
	CStdioFileWriteEndString(strPath, str);

	GetDlgItemText(IDC_EDIT18, str);
	CStdioFileWriteEndString(strPath, str);

	GetDlgItemText(IDC_EDIT19, str);
	CStdioFileWriteEndString(strPath, str);

	//功能配置
	int nIDC_RADIO3 = ((CButton*)GetDlgItem(IDC_RADIO3))->GetCheck();
	str.Format(_T("%d"), nIDC_RADIO3);
	CStdioFileWriteEndString(strPath, str);

	int nIDC_RADIO4 = ((CButton*)GetDlgItem(IDC_RADIO4))->GetCheck();
	str.Format(_T("%d"), nIDC_RADIO4);
	CStdioFileWriteEndString(strPath, str);

	int nIDC_RADIO5 = ((CButton*)GetDlgItem(IDC_RADIO5))->GetCheck();
	str.Format(_T("%d"), nIDC_RADIO5);
	CStdioFileWriteEndString(strPath, str);

	int nIDC_RADIO6 = ((CButton*)GetDlgItem(IDC_RADIO6))->GetCheck();
	str.Format(_T("%d"), nIDC_RADIO6);
	CStdioFileWriteEndString(strPath, str);

	int nIDC_RADIO7 = ((CButton*)GetDlgItem(IDC_RADIO7))->GetCheck();
	str.Format(_T("%d"), nIDC_RADIO7);
	CStdioFileWriteEndString(strPath, str);

	int nIDC_RADIO8 = ((CButton*)GetDlgItem(IDC_RADIO8))->GetCheck();
	str.Format(_T("%d"), nIDC_RADIO8);
	CStdioFileWriteEndString(strPath, str);

	int nIDC_RADIO9 = ((CButton*)GetDlgItem(IDC_RADIO9))->GetCheck();
	str.Format(_T("%d"), nIDC_RADIO9);
	CStdioFileWriteEndString(strPath, str);

	int nIDC_RADIO10 = ((CButton*)GetDlgItem(IDC_RADIO10))->GetCheck();
	str.Format(_T("%d"), nIDC_RADIO10);
	CStdioFileWriteEndString(strPath, str);

	int nIDC_RADIO11 = ((CButton*)GetDlgItem(IDC_RADIO11))->GetCheck();
	str.Format(_T("%d"), nIDC_RADIO11);
	CStdioFileWriteEndString(strPath, str);

	int nIDC_RADIO12 = ((CButton*)GetDlgItem(IDC_RADIO12))->GetCheck();
	str.Format(_T("%d"), nIDC_RADIO12);
	CStdioFileWriteEndString(strPath, str);

	int nIDC_RADIO13 = ((CButton*)GetDlgItem(IDC_RADIO13))->GetCheck();
	str.Format(_T("%d"), nIDC_RADIO13);
	CStdioFileWriteEndString(strPath, str);

	int nIDC_RADIO14 = ((CButton*)GetDlgItem(IDC_RADIO14))->GetCheck();
	str.Format(_T("%d"), nIDC_RADIO14);
	CStdioFileWriteEndString(strPath, str);

	int nIDC_RADIO15 = ((CButton*)GetDlgItem(IDC_RADIO15))->GetCheck();
	str.Format(_T("%d"), nIDC_RADIO15);
	CStdioFileWriteEndString(strPath, str);

	int nIDC_RADIO16 = ((CButton*)GetDlgItem(IDC_RADIO16))->GetCheck();
	str.Format(_T("%d"), nIDC_RADIO16);
	CStdioFileWriteEndString(strPath, str);

	int nIDC_RADIO17 = ((CButton*)GetDlgItem(IDC_RADIO17))->GetCheck();
	str.Format(_T("%d"), nIDC_RADIO17);
	CStdioFileWriteEndString(strPath, str);

	int nIDC_RADIO18 = ((CButton*)GetDlgItem(IDC_RADIO18))->GetCheck();
	str.Format(_T("%d"), nIDC_RADIO18);
	CStdioFileWriteEndString(strPath, str);

	int nIDC_RADIO19 = ((CButton*)GetDlgItem(IDC_RADIO19))->GetCheck();
	str.Format(_T("%d"), nIDC_RADIO19);
	CStdioFileWriteEndString(strPath, str);

	int nIDC_RADIO20 = ((CButton*)GetDlgItem(IDC_RADIO20))->GetCheck();
	str.Format(_T("%d"), nIDC_RADIO20);
	CStdioFileWriteEndString(strPath, str);

	int nIDC_CHECK3 = ((CButton*)GetDlgItem(IDC_CHECK3))->GetCheck();
	str.Format(_T("%d"), nIDC_CHECK3);
	CStdioFileWriteEndString(strPath, str);

	int nIDC_CHECK4 = ((CButton*)GetDlgItem(IDC_CHECK4))->GetCheck();
	str.Format(_T("%d"), nIDC_CHECK4);
	CStdioFileWriteEndString(strPath, str);

	//其他设定
	GetDlgItemText(IDC_EDIT20, str);
	CStdioFileWriteEndString(strPath, str);

	GetDlgItemText(IDC_EDIT21, str);
	CStdioFileWriteEndString(strPath, str);

	GetDlgItemText(IDC_EDIT22, str);
	CStdioFileWriteEndString(strPath, str);

	GetDlgItemText(IDC_EDIT23, str);
	CStdioFileWriteEndString(strPath, str);

	GetDlgItemText(IDC_EDIT24, str);
	CStdioFileWriteEndString(strPath, str);

	GetDlgItemText(IDC_EDIT25, str);
	CStdioFileWriteEndString(strPath, str);

	//GetDlgItemText(IDC_COMBO7, str);
	//CStdioFileWriteEndString(strPath, str);

	//GetDlgItemText(IDC_COMBO8, str);
	//CStdioFileWriteEndString(strPath, str);

	//GetDlgItemText(IDC_COMBO9, str);
	//CStdioFileWriteEndString(strPath, str);

	str.Format(_T("%d"),((CComboBox*)GetDlgItem(IDC_COMBO7))->GetCurSel());
	CStdioFileWriteEndString(strPath, str);

	str.Format(_T("%d"),((CComboBox*)GetDlgItem(IDC_COMBO8))->GetCurSel());
	CStdioFileWriteEndString(strPath, str);

	str.Format(_T("%d"),((CComboBox*)GetDlgItem(IDC_COMBO9))->GetCurSel());
	CStdioFileWriteEndString(strPath, str);

	int nIDC_CHECK7 = ((CButton*)GetDlgItem(IDC_CHECK7))->GetCheck();
	str.Format(_T("%d"), nIDC_CHECK7);
	CStdioFileWriteEndString(strPath, str);

	int nIDC_CHECK8 = ((CButton*)GetDlgItem(IDC_CHECK8))->GetCheck();
	str.Format(_T("%d"), nIDC_CHECK8);
	CStdioFileWriteEndString(strPath, str);

	int nIDC_CHECK9 = ((CButton*)GetDlgItem(IDC_CHECK9))->GetCheck();
	str.Format(_T("%d"), nIDC_CHECK9);
	CStdioFileWriteEndString(strPath, str);

	int nIDC_CHECK10 = ((CButton*)GetDlgItem(IDC_CHECK10))->GetCheck();
	str.Format(_T("%d"), nIDC_CHECK10);
	CStdioFileWriteEndString(strPath, str);

	int nIDC_CHECK11 = ((CButton*)GetDlgItem(IDC_CHECK11))->GetCheck();
	str.Format(_T("%d"), nIDC_CHECK11);
	CStdioFileWriteEndString(strPath, str);

	int nIDC_CHECK12 = ((CButton*)GetDlgItem(IDC_CHECK12))->GetCheck();
	str.Format(_T("%d"), nIDC_CHECK12);
	CStdioFileWriteEndString(strPath, str);

	int nIDC_CHECK13 = ((CButton*)GetDlgItem(IDC_CHECK13))->GetCheck();
	str.Format(_T("%d"), nIDC_CHECK13);
	CStdioFileWriteEndString(strPath, str);

	//左右大灯配置
	int nIDC_RADIO1 = ((CButton*)GetDlgItem(IDC_RADIO1))->GetCheck();
	str.Format(_T("%d"), nIDC_RADIO1);
	CStdioFileWriteEndString(strPath, str);

	int nIDC_RADIO2 = ((CButton*)GetDlgItem(IDC_RADIO2))->GetCheck();
	str.Format(_T("%d"), nIDC_RADIO2);
	CStdioFileWriteEndString(strPath, str);

	int nIDC_CHECK1 = ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck();
	str.Format(_T("%d"), nIDC_CHECK1);
	CStdioFileWriteEndString(strPath, str);

	int nIDC_CHECK2 = ((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck();
	str.Format(_T("%d"), nIDC_CHECK2);
	CStdioFileWriteEndString(strPath, str);

	//档位相关配置
	int nIDC_RADIO21 = ((CButton*)GetDlgItem(IDC_RADIO21))->GetCheck();
	str.Format(_T("%d"), nIDC_RADIO21);
	CStdioFileWriteEndString(strPath, str);

	int nIDC_RADIO22 = ((CButton*)GetDlgItem(IDC_RADIO22))->GetCheck();
	str.Format(_T("%d"), nIDC_RADIO22);
	CStdioFileWriteEndString(strPath, str);

	int nIDC_CHECK5 = ((CButton*)GetDlgItem(IDC_CHECK5))->GetCheck();
	str.Format(_T("%d"), nIDC_CHECK5);
	CStdioFileWriteEndString(strPath, str);

	//GetDlgItemText(IDC_COMBO4, str);
	//CStdioFileWriteEndString(strPath, str);

	str.Format(_T("%d"),((CComboBox*)GetDlgItem(IDC_COMBO4))->GetCurSel());
	CStdioFileWriteEndString(strPath, str);

	GetDlgItemText(IDC_EDIT30, str);
	CStdioFileWriteEndString(strPath, str);

	GetDlgItemText(IDC_EDIT31, str);
	CStdioFileWriteEndString(strPath, str);

	//三电压混合识别
	int nIDC_CHECK6 = ((CButton*)GetDlgItem(IDC_CHECK6))->GetCheck();
	str.Format(_T("%d"), nIDC_CHECK6);
	CStdioFileWriteEndString(strPath, str);

	int nIDC_RADIO23 = ((CButton*)GetDlgItem(IDC_RADIO23))->GetCheck();
	str.Format(_T("%d"), nIDC_RADIO23);
	CStdioFileWriteEndString(strPath, str);

	int nIDC_RADIO24 = ((CButton*)GetDlgItem(IDC_RADIO24))->GetCheck();
	str.Format(_T("%d"), nIDC_RADIO24);
	CStdioFileWriteEndString(strPath, str);

	return true;
}


bool CCommMFCDlg::ReadApplicationFile(CString strPath)
{
	// 处理UNICODE下【中文乱码】异常
    char * pOldLocale = _strdup(setlocale(LC_CTYPE, NULL));
    setlocale(LC_CTYPE, "chs");

	CString str;
	CStdioFile file;
	file.Open(strPath,CFile::modeRead);
	file.ReadString(str);	//读第一行

	//快速选
	//file.ReadString(str);	//读第二行
	//SetDlgItemText(IDC_COMBO1, str);
	//file.ReadString(str);	//读第三行
	//SetDlgItemText(IDC_COMBO2, str);
	//file.ReadString(str);	//读第四行
	//SetDlgItemText(IDC_COMBO3, str);


	file.ReadString(str);	//读第二行
	((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(_ttoi(str));
	file.ReadString(str);	//读第三行
	((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(_ttoi(str));
	file.ReadString(str);	//读第四行
	((CComboBox*)GetDlgItem(IDC_COMBO3))->SetCurSel(_ttoi(str));

	//欠电压
	file.ReadString(str);	//读第5行
	SetDlgItemText(IDC_EDIT5, str);
	file.ReadString(str);	//读第6行
	SetDlgItemText(IDC_EDIT6, str);
	file.ReadString(str);	//读第7行
	SetDlgItemText(IDC_EDIT7, str);

	//满电电
	file.ReadString(str);	//读第8行
	SetDlgItemText(IDC_EDIT8, str);
	file.ReadString(str);	//读第9行
	SetDlgItemText(IDC_EDIT9, str);
	file.ReadString(str);	//读第10行
	SetDlgItemText(IDC_EDIT10, str);

	//中点电
	file.ReadString(str);	//11
	SetDlgItemText(IDC_EDIT11, str);	
	file.ReadString(str);	//12
	SetDlgItemText(IDC_EDIT12, str);
	file.ReadString(str);	//13
	SetDlgItemText(IDC_EDIT13, str);

	//中点速
	file.ReadString(str);
	SetDlgItemText(IDC_EDIT14, str);
	file.ReadString(str);
	SetDlgItemText(IDC_EDIT15, str);
	file.ReadString(str);
	SetDlgItemText(IDC_EDIT16, str);

	//油门电
	file.ReadString(str);
	SetDlgItemText(IDC_EDIT17, str);
	file.ReadString(str);
	SetDlgItemText(IDC_EDIT18, str);
	file.ReadString(str);
	SetDlgItemText(IDC_EDIT19, str);

	//功能配置
	file.ReadString(str);	//20
	((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(_ttoi(str));

	file.ReadString(str);
	((CButton*)GetDlgItem(IDC_RADIO4))->SetCheck(_ttoi(str));

	file.ReadString(str);
	((CButton*)GetDlgItem(IDC_RADIO5))->SetCheck(_ttoi(str));

	file.ReadString(str);
	((CButton*)GetDlgItem(IDC_RADIO6))->SetCheck(_ttoi(str));

	file.ReadString(str);
	((CButton*)GetDlgItem(IDC_RADIO7))->SetCheck(_ttoi(str));

	file.ReadString(str);
	((CButton*)GetDlgItem(IDC_RADIO8))->SetCheck(_ttoi(str));

	file.ReadString(str);
	((CButton*)GetDlgItem(IDC_RADIO9))->SetCheck(_ttoi(str));

	file.ReadString(str);
	((CButton*)GetDlgItem(IDC_RADIO10))->SetCheck(_ttoi(str));

	file.ReadString(str);
	((CButton*)GetDlgItem(IDC_RADIO11))->SetCheck(_ttoi(str));

	file.ReadString(str);
	((CButton*)GetDlgItem(IDC_RADIO12))->SetCheck(_ttoi(str));

	file.ReadString(str);
	((CButton*)GetDlgItem(IDC_RADIO13))->SetCheck(_ttoi(str));

	file.ReadString(str);
	((CButton*)GetDlgItem(IDC_RADIO14))->SetCheck(_ttoi(str));

	file.ReadString(str);
	((CButton*)GetDlgItem(IDC_RADIO15))->SetCheck(_ttoi(str));

	file.ReadString(str);
	((CButton*)GetDlgItem(IDC_RADIO16))->SetCheck(_ttoi(str));

	file.ReadString(str);
	((CButton*)GetDlgItem(IDC_RADIO17))->SetCheck(_ttoi(str));

	file.ReadString(str);
	((CButton*)GetDlgItem(IDC_RADIO18))->SetCheck(_ttoi(str));

	file.ReadString(str);
	((CButton*)GetDlgItem(IDC_RADIO19))->SetCheck(_ttoi(str));

	file.ReadString(str);
	((CButton*)GetDlgItem(IDC_RADIO20))->SetCheck(_ttoi(str));

	file.ReadString(str);
	((CButton*)GetDlgItem(IDC_CHECK3))->SetCheck(_ttoi(str));

	file.ReadString(str);
	((CButton*)GetDlgItem(IDC_CHECK4))->SetCheck(_ttoi(str));

	//其他设定
	file.ReadString(str);
	SetDlgItemText(IDC_EDIT20, str);

	file.ReadString(str);
	SetDlgItemText(IDC_EDIT21, str);

	file.ReadString(str);
	SetDlgItemText(IDC_EDIT22, str);

	file.ReadString(str);
	SetDlgItemText(IDC_EDIT23, str);

	file.ReadString(str);
	SetDlgItemText(IDC_EDIT24, str);

	file.ReadString(str);
	SetDlgItemText(IDC_EDIT25, str);

	//file.ReadString(str);
	//SetDlgItemText(IDC_COMBO7, str);

	//file.ReadString(str);
	//SetDlgItemText(IDC_COMBO8, str);

	//file.ReadString(str);
	//SetDlgItemText(IDC_COMBO9, str);

	file.ReadString(str);
	((CComboBox*)GetDlgItem(IDC_COMBO7))->SetCurSel(_ttoi(str));

	file.ReadString(str);
	((CComboBox*)GetDlgItem(IDC_COMBO8))->SetCurSel(_ttoi(str));

	file.ReadString(str);
	((CComboBox*)GetDlgItem(IDC_COMBO9))->SetCurSel(_ttoi(str));

	file.ReadString(str);
	((CButton*)GetDlgItem(IDC_CHECK7))->SetCheck(_ttoi(str));

	file.ReadString(str);
	((CButton*)GetDlgItem(IDC_CHECK8))->SetCheck(_ttoi(str));

	file.ReadString(str);
	((CButton*)GetDlgItem(IDC_CHECK9))->SetCheck(_ttoi(str));

	file.ReadString(str);
	((CButton*)GetDlgItem(IDC_CHECK10))->SetCheck(_ttoi(str));

	file.ReadString(str);
	((CButton*)GetDlgItem(IDC_CHECK11))->SetCheck(_ttoi(str));

	file.ReadString(str);
	((CButton*)GetDlgItem(IDC_CHECK12))->SetCheck(_ttoi(str));

	file.ReadString(str);
	((CButton*)GetDlgItem(IDC_CHECK13))->SetCheck(_ttoi(str));

	//左右大灯配置
	file.ReadString(str);
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(_ttoi(str));

	file.ReadString(str);
	((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(_ttoi(str));

	file.ReadString(str);
	((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(_ttoi(str));

	file.ReadString(str);
	((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(_ttoi(str));

	//档位相关配置
	file.ReadString(str);
	((CButton*)GetDlgItem(IDC_RADIO21))->SetCheck(_ttoi(str));

	file.ReadString(str);
	((CButton*)GetDlgItem(IDC_RADIO22))->SetCheck(_ttoi(str));

	file.ReadString(str);
	((CButton*)GetDlgItem(IDC_CHECK5))->SetCheck(_ttoi(str));

	//file.ReadString(str);
	//SetDlgItemText(IDC_COMBO4, str);

	file.ReadString(str);	//读第二行
	((CComboBox*)GetDlgItem(IDC_COMBO4))->SetCurSel(_ttoi(str));

	file.ReadString(str);
	SetDlgItemText(IDC_EDIT30, str);

	file.ReadString(str);
	SetDlgItemText(IDC_EDIT31, str);

	//三电压混合识别
	file.ReadString(str);
	((CButton*)GetDlgItem(IDC_CHECK6))->SetCheck(_ttoi(str));

	file.ReadString(str);
	((CButton*)GetDlgItem(IDC_RADIO23))->SetCheck(_ttoi(str));

	file.ReadString(str);
	((CButton*)GetDlgItem(IDC_RADIO24))->SetCheck(_ttoi(str));

	file.Close();

	// 处理完毕后,释放资源
	setlocale(LC_CTYPE, pOldLocale);
	free(pOldLocale);

	return true;
}

//这个算法实现有问题
unsigned int CCommMFCDlg::CalculateCRC32(LPCTSTR lpszFileName)
{
	#define INIT 0xffffffff;
	#define XOROT 0xffffffff;

	unsigned crc32_table[256] =
	{
		0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA,
		0x076DC419, 0x706AF48F, 0xE963A535, 0x9E6495A3,
		0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988,
		0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91,
		0x1DB71064, 0x6AB020F2, 0xF3B97148, 0x84BE41DE,
		0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7,
		0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC,
		0x14015C4F, 0x63066CD9, 0xFA0F3D63, 0x8D080DF5,
		0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172,
		0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B,
		0x35B5A8FA, 0x42B2986C, 0xDBBBC9D6, 0xACBCF940,
		0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59,
		0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116,
		0x21B4F4B5, 0x56B3C423, 0xCFBA9599, 0xB8BDA50F,
		0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924,
		0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D,

		0x76DC4190, 0x01DB7106, 0x98D220BC, 0xEFD5102A,
		0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433,
		0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818,
		0x7F6A0DBB, 0x086D3D2D, 0x91646C97, 0xE6635C01,
		0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E,
		0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457,
		0x65B0D9C6, 0x12B7E950, 0x8BBEB8EA, 0xFCB9887C,
		0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65,
		0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2,
		0x4ADFA541, 0x3DD895D7, 0xA4D1C46D, 0xD3D6F4FB,
		0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0,
		0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9,
		0x5005713C, 0x270241AA, 0xBE0B1010, 0xC90C2086,
		0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F,
		0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4,
		0x59B33D17, 0x2EB40D81, 0xB7BD5C3B, 0xC0BA6CAD,

		0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A,
		0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73DC1683,
		0xE3630B12, 0x94643B84, 0x0D6D6A3E, 0x7A6A5AA8,
		0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1,
		0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE,
		0xF762575D, 0x806567CB, 0x196C3671, 0x6E6B06E7,
		0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC,
		0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5,
		0xD6D6A3E8, 0xA1D1937E, 0x38D8C2C4, 0x4FDFF252,
		0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B,
		0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6, 0x41047A60,
		0xDF60EFC3, 0xA867DF55, 0x316E8EEF, 0x4669BE79,
		0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236,
		0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F,
		0xC5BA3BBE, 0xB2BD0B28, 0x2BB45A92, 0x5CB36A04,
		0xC2D7FFA7, 0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D,

		0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A,
		0x9C0906A9, 0xEB0E363F, 0x72076785, 0x05005713,
		0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38,
		0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21,
		0x86D3D2D4, 0xF1D4E242, 0x68DDB3F8, 0x1FDA836E,
		0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777,
		0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C,
		0x8F659EFF, 0xF862AE69, 0x616BFFD3, 0x166CCF45,
		0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2,
		0xA7672661, 0xD06016F7, 0x4969474D, 0x3E6E77DB,
		0xAED16A4A, 0xD9D65ADC, 0x40DF0B66, 0x37D83BF0,
		0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9,
		0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6,
		0xBAD03605, 0xCDD70693, 0x54DE5729, 0x23D967BF,
		0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94,
		0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D,
	};

	unsigned int* pCrc32_table = (unsigned int*)malloc(sizeof(unsigned int)*256);
	memcpy_s(pCrc32_table, 256, crc32_table, 256);

	unsigned uCRCValue = 0;
	unsigned char* pData;

	//CFile file(lpszFileName, CFile::modeRead | CFile::shareDenyNone);
	///If sharing is enabled, sharing conflicts can easily occur here
	//CFile file(lpszFileName, CFile::modeRead);
	CFile file;
	if (file.Open(lpszFileName, CFile::modeRead))
	{
		LARGE_INTEGER nFileLength = { 0 };
		nFileLength.QuadPart = file.GetLength();
		void* pStart = malloc(nFileLength.LowPart);
		memset(pStart, 0, nFileLength.LowPart);
		file.Read(pStart, nFileLength.LowPart);
		unsigned uSize = nFileLength.LowPart;

		/* init the start value */
		uCRCValue = INIT;
		pData = (unsigned char*)pStart;

		/* calculate CRC */
		while (uSize--)
		{
			uCRCValue = pCrc32_table[(uCRCValue ^ *pData++) & 0xFF] ^ (uCRCValue >> 8);
		}

		free(pStart);
		free(pCrc32_table);
		/* XOR the output value */

		return uCRCValue ^ XOROT;
	}
	else
	{
		return 0;
	}
}


typedef signed char qint8;         /* 8 bit signed */
typedef unsigned char quint8;      /* 8 bit unsigned */
typedef short qint16;              /* 16 bit signed */
typedef unsigned short quint16;    /* 16 bit unsigned */
typedef int qint32;                /* 32 bit signed */
typedef unsigned int quint32;      /* 32 bit unsigned */


/*!
 * \brief calculate_crc16   通用的16位CRC校验算法
 * \param CRC_INIT          CRC16算法的初始值
 * \param CRC_POLY          特征多项式
 * \param CRC_RESULT_XOR    结果异或值
 * \param input_invert      输入值是否反转
 * \param ouput_invert      输出值是否反转
 * \param inputData         输入数据的起始地址
 * \param inputDataLen      输入数据的长度
 * \return                  16位CRC校验结果
 */

//这个算法实现有问题
unsigned short CCommMFCDlg::calculate_crc16(unsigned short CRC_INIT, unsigned short CRC_POLY, unsigned short CRC_RESULT_XOR, bool input_invert, bool ouput_invert, const char* inputData, int inputDataLen)
{
	quint8 data_item = 0;

    //--商
    quint32 ans = 0;


    while (inputDataLen--)
    {
        data_item = *(inputData++);

        //输入值反转 (最高位变最低位，最低位变最高位, 1100 0100 反转 0010 0011)
        if (input_invert)
        {
            //printf("输入值反转前  data_item = %02x \n", data_item);
            quint8 temp_char = data_item;
            data_item = 0;
            for (int i = 0; i < 8; ++i)
            {
                if (temp_char & 0x01)
                    data_item |= 0x01 << (7 - i);
                temp_char >>= 1;
            }
            //printf("输入值反转后 data_item = %02x \n", data_item);
        }

        //---多项式除法----------------------
        //---模2除法结果与异或相同
        //---模2除法可以用在CRC冗余校验上

        //多项式除法的余数R(x)=CRC，存储在CRC_INIT,作为下一次计算的被除数
        //data_item扩展成16位，异或初始值,
        CRC_INIT ^= (data_item << 8);

        //--当前输入字节的每一位执行模2除法
        for (int i = 0; i < 8; i++)
        {
            //--从最高的16位开始模2除法
            if (CRC_INIT & 0x8000) {//--第一位是1,商是1,执行摸2相减
                CRC_INIT = (CRC_INIT << 1) ^ CRC_POLY;
                ans += 1;
            }
            else {//--第一位是0,商是0,继续移位,不执行摸2相减
                CRC_INIT = CRC_INIT << 1;
                ans += 0;
            }
            ans = ans << 1;
        }
        ans <<= 1;
    }
    //printf("商 ans = %02x \n", ans);
    //printf("余数 CRC_INIT = %02x \n", CRC_INIT);

    //输出值(16位)反转 (最高位变最低位，最低位变最高位, 1010 0010 0011 1001 反转 1001 1100 0100 0101 )
    if (ouput_invert)
    {
        //printf("输出值反转前  CRC_INIT = %02x \n", CRC_INIT);
        quint16 temp_short = CRC_INIT;
        CRC_INIT = 0;
        for (int i = 0; i < 16; ++i)
        {
            if (temp_short & 0x01)
                CRC_INIT |= 0x01 << (15 - i);
            temp_short >>= 1;
        }
        //printf("输出值反转后  CRC_INIT = %02x \n", CRC_INIT);
    }
    //printf("结果异或  CRC_INIT^CRC_RESULT_XOR = %02x \n", CRC_INIT ^ CRC_RESULT_XOR);
    return (CRC_INIT ^ CRC_RESULT_XOR);
}


unsigned short CCommMFCDlg::crc16table(unsigned char* ptr, unsigned short len)
{
	typedef unsigned char uint8_t;
	typedef unsigned short uint16_t;
	typedef unsigned long uint32_t;
	typedef int int32_t;

	/* Table of CRC values for high�Corder byte */
	const uint8_t crctablehi[] = {
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
		0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
		0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
		0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
		0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
		0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
		0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
		0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
		0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
		0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
		0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
		0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
		0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
		0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
		0x40
	};
	/* Table of CRC values for low�Corder byte */
	const uint8_t crctablelo[] = {
		0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,
		0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
		0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD,
		0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
		0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
		0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
		0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE,
		0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
		0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2,
		0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
		0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB,
		0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
		0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91,
		0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
		0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88,
		0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
		0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,
		0x40
	};


	uint8_t crchi = 0xff;
	uint8_t crclo = 0xff;
	uint16_t index;
	while (len--)
	{
		index = crclo ^ *ptr++;
		crclo = crchi ^ crctablehi[index];
		crchi = crctablelo[index];
	}
	return (crchi << 8 | crclo);
}


bool CCommMFCDlg::SpanIncluding(CString str)
{
	if(str.SpanIncluding(_T("0123456789.")) == str)
	{
		return true;
	}
	return false;
}


void CCommMFCDlg::OnEnChangeEdit5()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 __super::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	//范围安全检查
	CString str;
	GetDlgItemText(IDC_EDIT5, str);
	if(!SpanIncluding(str) || str.Replace(_T("."), _T(".")) > 1)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT5, _T(""));
	}

	int nPostion = str.ReverseFind('.');
	if(nPostion == -1)
	{
		if(str.GetLength() >5)
		{
			MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
			SetDlgItemText(IDC_EDIT5, _T(""));
		}
	}
	
	if(str.GetLength() - str.ReverseFind('.') - 1 > 6)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT5, _T(""));
	}

}


BOOL CCommMFCDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_RETURN:
			return TRUE;
		case VK_ESCAPE:
			return TRUE;
		}
	}

	return __super::PreTranslateMessage(pMsg);
}


void CCommMFCDlg::OnEnChangeEdit6()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 __super::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	//范围安全检查
	CString str;
	GetDlgItemText(IDC_EDIT6, str);
	if(!SpanIncluding(str) || str.Replace(_T("."), _T(".")) > 1)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT6, _T(""));
	}

	int nPostion = str.ReverseFind('.');
	if(nPostion == -1)
	{
		if(str.GetLength() >5)
		{
			MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
			SetDlgItemText(IDC_EDIT6, _T(""));
		}
	}
	
	if(str.GetLength() - str.ReverseFind('.') - 1 > 6)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT6, _T(""));
	}
}


void CCommMFCDlg::OnEnChangeEdit7()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 __super::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	//范围安全检查
	CString str;
	GetDlgItemText(IDC_EDIT7, str);
	if(!SpanIncluding(str) || str.Replace(_T("."), _T(".")) > 1)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT7, _T(""));
	}

	int nPostion = str.ReverseFind('.');
	if(nPostion == -1)
	{
		if(str.GetLength() >5)
		{
			MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
			SetDlgItemText(IDC_EDIT7, _T(""));
		}
	}
	
	if(str.GetLength() - str.ReverseFind('.') - 1 > 6)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT7, _T(""));
	}
}


void CCommMFCDlg::OnEnChangeEdit8()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 __super::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	//范围安全检查
	CString str;
	GetDlgItemText(IDC_EDIT8, str);
	if(!SpanIncluding(str) || str.Replace(_T("."), _T(".")) > 1)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT8, _T(""));
	}

	int nPostion = str.ReverseFind('.');
	if(nPostion == -1)
	{
		if(str.GetLength() >5)
		{
			MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
			SetDlgItemText(IDC_EDIT8, _T(""));
		}
	}
	
	if(str.GetLength() - str.ReverseFind('.') - 1 > 6)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT8, _T(""));
	}
}


void CCommMFCDlg::OnEnChangeEdit9()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 __super::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	//范围安全检查
	CString str;
	GetDlgItemText(IDC_EDIT9, str);
	if(!SpanIncluding(str) || str.Replace(_T("."), _T(".")) > 1)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT9, _T(""));
	}

	int nPostion = str.ReverseFind('.');
	if(nPostion == -1)
	{
		if(str.GetLength() >5)
		{
			MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
			SetDlgItemText(IDC_EDIT9, _T(""));
		}
	}
	
	if(str.GetLength() - str.ReverseFind('.') - 1 > 6)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT9, _T(""));
	}
}


void CCommMFCDlg::OnEnChangeEdit10()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 __super::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	//范围安全检查
	CString str;
	GetDlgItemText(IDC_EDIT10, str);
	if(!SpanIncluding(str) || str.Replace(_T("."), _T(".")) > 1)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT10, _T(""));
	}

	int nPostion = str.ReverseFind('.');
	if(nPostion == -1)
	{
		if(str.GetLength() >5)
		{
			MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
			SetDlgItemText(IDC_EDIT10, _T(""));
		}
	}
	
	if(str.GetLength() - str.ReverseFind('.') - 1 > 6)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT10, _T(""));
	}
}


void CCommMFCDlg::OnEnChangeEdit11()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 __super::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	//范围安全检查
	CString str;
	GetDlgItemText(IDC_EDIT11, str);
	if(!SpanIncluding(str) || str.Replace(_T("."), _T(".")) > 1)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT11, _T(""));
	}

	int nPostion = str.ReverseFind('.');
	if(nPostion == -1)
	{
		if(str.GetLength() >5)
		{
			MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
			SetDlgItemText(IDC_EDIT11, _T(""));
		}
	}
	
	if(str.GetLength() - str.ReverseFind('.') - 1 > 6)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT11, _T(""));
	}
}


void CCommMFCDlg::OnEnChangeEdit12()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 __super::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	//范围安全检查
	CString str;
	GetDlgItemText(IDC_EDIT12, str);
	if(!SpanIncluding(str) || str.Replace(_T("."), _T(".")) > 1)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT12, _T(""));
	}

	int nPostion = str.ReverseFind('.');
	if(nPostion == -1)
	{
		if(str.GetLength() >5)
		{
			MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
			SetDlgItemText(IDC_EDIT12, _T(""));
		}
	}
	
	if(str.GetLength() - str.ReverseFind('.') - 1 > 6)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT12, _T(""));
	}
}


void CCommMFCDlg::OnEnChangeEdit13()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 __super::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	//范围安全检查
	CString str;
	GetDlgItemText(IDC_EDIT13, str);
	if(!SpanIncluding(str) || str.Replace(_T("."), _T(".")) > 1)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT13, _T(""));
	}

	int nPostion = str.ReverseFind('.');
	if(nPostion == -1)
	{
		if(str.GetLength() >5)
		{
			MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
			SetDlgItemText(IDC_EDIT13, _T(""));
		}
	}
	
	if(str.GetLength() - str.ReverseFind('.') - 1 > 6)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT13, _T(""));
	}
}


void CCommMFCDlg::OnEnChangeEdit14()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 __super::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	//范围安全检查
	CString str;
	GetDlgItemText(IDC_EDIT14, str);
	if(!SpanIncluding(str) || str.Replace(_T("."), _T(".")) > 1)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT14, _T(""));
	}

	int nPostion = str.ReverseFind('.');
	if(nPostion == -1)
	{
		if(str.GetLength() >5)
		{
			MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
			SetDlgItemText(IDC_EDIT14, _T(""));
		}
	}
	
	if(str.GetLength() - str.ReverseFind('.') - 1 > 6)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT14, _T(""));
	}
}


void CCommMFCDlg::OnEnChangeEdit15()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 __super::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	//范围安全检查
	CString str;
	GetDlgItemText(IDC_EDIT15, str);
	if(!SpanIncluding(str) || str.Replace(_T("."), _T(".")) > 1)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT15, _T(""));
	}

	int nPostion = str.ReverseFind('.');
	if(nPostion == -1)
	{
		if(str.GetLength() >5)
		{
			MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
			SetDlgItemText(IDC_EDIT15, _T(""));
		}
	}
	
	if(str.GetLength() - str.ReverseFind('.') - 1 > 6)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT15, _T(""));
	}
}


void CCommMFCDlg::OnEnChangeEdit16()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 __super::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	//范围安全检查
	CString str;
	GetDlgItemText(IDC_EDIT16, str);
	if(!SpanIncluding(str) || str.Replace(_T("."), _T(".")) > 1)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT16, _T(""));
	}

	int nPostion = str.ReverseFind('.');
	if(nPostion == -1)
	{
		if(str.GetLength() >5)
		{
			MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
			SetDlgItemText(IDC_EDIT16, _T(""));
		}
	}
	
	if(str.GetLength() - str.ReverseFind('.') - 1 > 6)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT16, _T(""));
	}
}


void CCommMFCDlg::OnEnChangeEdit17()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 __super::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	//范围安全检查
	CString str;
	GetDlgItemText(IDC_EDIT17, str);
	if(!SpanIncluding(str) || str.Replace(_T("."), _T(".")) > 1)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT17, _T(""));
	}

	int nPostion = str.ReverseFind('.');
	if(nPostion == -1)
	{
		if(str.GetLength() >5)
		{
			MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
			SetDlgItemText(IDC_EDIT17, _T(""));
		}
	}
	
	if(str.GetLength() - str.ReverseFind('.') - 1 > 6)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT17, _T(""));
	}
}


void CCommMFCDlg::OnEnChangeEdit18()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 __super::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	//范围安全检查
	CString str;
	GetDlgItemText(IDC_EDIT18, str);
	if(!SpanIncluding(str) || str.Replace(_T("."), _T(".")) > 1)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT18, _T(""));
	}

	int nPostion = str.ReverseFind('.');
	if(nPostion == -1)
	{
		if(str.GetLength() >5)
		{
			MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
			SetDlgItemText(IDC_EDIT18, _T(""));
		}
	}
	
	if(str.GetLength() - str.ReverseFind('.') - 1 > 6)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT18, _T(""));
	}
}


void CCommMFCDlg::OnEnChangeEdit19()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 __super::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	//范围安全检查
	CString str;
	GetDlgItemText(IDC_EDIT19, str);
	if(!SpanIncluding(str) || str.Replace(_T("."), _T(".")) > 1)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT19, _T(""));
	}

	int nPostion = str.ReverseFind('.');
	if(nPostion == -1)
	{
		if(str.GetLength() >5)
		{
			MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
			SetDlgItemText(IDC_EDIT19, _T(""));
		}
	}
	
	if(str.GetLength() - str.ReverseFind('.') - 1 > 6)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT19, _T(""));
	}
}


void CCommMFCDlg::OnEnChangeEdit20()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 __super::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	//范围安全检查
	CString str;
	GetDlgItemText(IDC_EDIT20, str);
	if(!SpanIncluding(str) || str.Replace(_T("."), _T(".")) > 1)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT20, _T(""));
	}

	int nPostion = str.ReverseFind('.');
	if(nPostion == -1)
	{
		if(str.GetLength() >5)
		{
			MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
			SetDlgItemText(IDC_EDIT20, _T(""));
		}
	}
	
	if(str.GetLength() - str.ReverseFind('.') - 1 > 6)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT20, _T(""));
	}
}


void CCommMFCDlg::OnEnChangeEdit21()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 __super::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	//范围安全检查
	CString str;
	GetDlgItemText(IDC_EDIT21, str);
	if(!SpanIncluding(str) || str.Replace(_T("."), _T(".")) > 1)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT21, _T(""));
	}

	int nPostion = str.ReverseFind('.');
	if(nPostion == -1)
	{
		if(str.GetLength() >5)
		{
			MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
			SetDlgItemText(IDC_EDIT21, _T(""));
		}
	}
	
	if(str.GetLength() - str.ReverseFind('.') - 1 > 6)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT21, _T(""));
	}
}


void CCommMFCDlg::OnEnChangeEdit22()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 __super::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	//范围安全检查
	CString str;
	GetDlgItemText(IDC_EDIT22, str);
	if(!SpanIncluding(str) || str.Replace(_T("."), _T(".")) > 1)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT22, _T(""));
	}

	int nPostion = str.ReverseFind('.');
	if(nPostion == -1)
	{
		if(str.GetLength() >5)
		{
			MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
			SetDlgItemText(IDC_EDIT22, _T(""));
		}
	}
	
	if(str.GetLength() - str.ReverseFind('.') - 1 > 6)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT22, _T(""));
	}
}


void CCommMFCDlg::OnEnChangeEdit23()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 __super::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	//范围安全检查
	CString str;
	GetDlgItemText(IDC_EDIT23, str);
	if(!SpanIncluding(str) || str.Replace(_T("."), _T(".")) > 1)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT23, _T(""));
	}

	int nPostion = str.ReverseFind('.');
	if(nPostion == -1)
	{
		if(str.GetLength() >5)
		{
			MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
			SetDlgItemText(IDC_EDIT23, _T(""));
		}
	}
	
	if(str.GetLength() - str.ReverseFind('.') - 1 > 6)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT23, _T(""));
	}
}


void CCommMFCDlg::OnEnChangeEdit24()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 __super::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	//范围安全检查
	CString str;
	GetDlgItemText(IDC_EDIT24, str);
	if(!SpanIncluding(str) || str.Replace(_T("."), _T(".")) > 1)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT24, _T(""));
	}

	int nPostion = str.ReverseFind('.');
	if(nPostion == -1)
	{
		if(str.GetLength() >5)
		{
			MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
			SetDlgItemText(IDC_EDIT24, _T(""));
		}
	}
	
	if(str.GetLength() - str.ReverseFind('.') - 1 > 6)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT24, _T(""));
	}
}


void CCommMFCDlg::OnEnChangeEdit25()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 __super::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	//范围安全检查
	CString str;
	GetDlgItemText(IDC_EDIT25, str);
	if(!SpanIncluding(str) || str.Replace(_T("."), _T(".")) > 1)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT25, _T(""));
	}

	int nPostion = str.ReverseFind('.');
	if(nPostion == -1)
	{
		if(str.GetLength() >5)
		{
			MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
			SetDlgItemText(IDC_EDIT25, _T(""));
		}
	}
	
	if(str.GetLength() - str.ReverseFind('.') - 1 > 6)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT25, _T(""));
	}
}


void CCommMFCDlg::OnEnChangeEdit30()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 __super::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	//范围安全检查
	CString str;
	GetDlgItemText(IDC_EDIT30, str);
	if(!SpanIncluding(str) || str.Replace(_T("."), _T(".")) > 1)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT30, _T(""));
	}

	int nPostion = str.ReverseFind('.');
	if(nPostion == -1)
	{
		if(str.GetLength() >5)
		{
			MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
			SetDlgItemText(IDC_EDIT30, _T(""));
		}
	}
	
	if(str.GetLength() - str.ReverseFind('.') - 1 > 6)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT30, _T(""));
	}
}


void CCommMFCDlg::OnEnChangeEdit31()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 __super::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	//范围安全检查
	CString str;
	GetDlgItemText(IDC_EDIT31, str);
	if(!SpanIncluding(str) || str.Replace(_T("."), _T(".")) > 1)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT31, _T(""));
	}

	int nPostion = str.ReverseFind('.');
	if(nPostion == -1)
	{
		if(str.GetLength() >5)
		{
			MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
			SetDlgItemText(IDC_EDIT31, _T(""));
		}
	}
	
	if(str.GetLength() - str.ReverseFind('.') - 1 > 6)
	{
		MessageBox(_T("输入了错误的值,请重新输入！"), _T("提示："),MB_ICONERROR);
		SetDlgItemText(IDC_EDIT31, _T(""));
	}
}


bool CCommMFCDlg::GetData2Hex(void)
{
	//电压配置
	//快速选
	CString str;																																				AddDebugStr2EditCtr(_T("快速选"));
	str.Format(_T("0x%02X"),((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel());															AddStr2EditCtr(str);
	str.Format(_T("0x%02X"),((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCurSel());															AddStr2EditCtr(str);
	str.Format(_T("0x%02X"),((CComboBox*)GetDlgItem(IDC_COMBO3))->GetCurSel());															AddStr2EditCtr(str);

	//欠压电
	unsigned char pbyte[4] = {0};																																AddDebugStr2EditCtr(_T("欠压电"));
	GetEditFloat2Binary32(IDC_EDIT5, pbyte);	str.Format(_T("0x%02X 0x%02X 0x%02X 0x%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);	AddStr2EditCtr(str);
	GetEditFloat2Binary32(IDC_EDIT6, pbyte);	str.Format(_T("0x%02X 0x%02X 0x%02X 0x%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);	AddStr2EditCtr(str);
	GetEditFloat2Binary32(IDC_EDIT7, pbyte);	str.Format(_T("0x%02X 0x%02X 0x%02X 0x%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);	AddStr2EditCtr(str);	AddDebugStr2EditCtr(_T("满电电"));
	GetEditFloat2Binary32(IDC_EDIT8, pbyte);	str.Format(_T("0x%02X 0x%02X 0x%02X 0x%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);	AddStr2EditCtr(str);
	GetEditFloat2Binary32(IDC_EDIT9, pbyte);	str.Format(_T("0x%02X 0x%02X 0x%02X 0x%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);	AddStr2EditCtr(str);
	GetEditFloat2Binary32(IDC_EDIT10, pbyte);	str.Format(_T("0x%02X 0x%02X 0x%02X 0x%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);	AddStr2EditCtr(str);	AddDebugStr2EditCtr(_T("中点电"));
	GetEditFloat2Binary32(IDC_EDIT11, pbyte);	str.Format(_T("0x%02X 0x%02X 0x%02X 0x%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);	AddStr2EditCtr(str);
	GetEditFloat2Binary32(IDC_EDIT12, pbyte);	str.Format(_T("0x%02X 0x%02X 0x%02X 0x%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);	AddStr2EditCtr(str);
	GetEditFloat2Binary32(IDC_EDIT13, pbyte);	str.Format(_T("0x%02X 0x%02X 0x%02X 0x%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);	AddStr2EditCtr(str);	AddDebugStr2EditCtr(_T("中点速"));
	GetEditFloat2Binary32(IDC_EDIT14, pbyte);	str.Format(_T("0x%02X 0x%02X 0x%02X 0x%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);	AddStr2EditCtr(str);
	GetEditFloat2Binary32(IDC_EDIT15, pbyte);	str.Format(_T("0x%02X 0x%02X 0x%02X 0x%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);	AddStr2EditCtr(str);
	GetEditFloat2Binary32(IDC_EDIT16, pbyte);	str.Format(_T("0x%02X 0x%02X 0x%02X 0x%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);	AddStr2EditCtr(str);	AddDebugStr2EditCtr(_T("油门电"));
	GetEditFloat2Binary32(IDC_EDIT17, pbyte);	str.Format(_T("0x%02X 0x%02X 0x%02X 0x%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);	AddStr2EditCtr(str);
	GetEditFloat2Binary32(IDC_EDIT18, pbyte);	str.Format(_T("0x%02X 0x%02X 0x%02X 0x%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);	AddStr2EditCtr(str);
	GetEditFloat2Binary32(IDC_EDIT19, pbyte);	str.Format(_T("0x%02X 0x%02X 0x%02X 0x%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);	AddStr2EditCtr(str);

	//功能配置
																																								AddDebugStr2EditCtr(_T("LOGO标"));
	str.Format(_T("0x%02X"), AddRadioStr2EditCtr(IDC_RADIO3, IDC_RADIO4));																AddStr2EditCtr(str);	AddDebugStr2EditCtr(_T("数字电压"));
	str.Format(_T("0x%02X"), AddRadioStr2EditCtr(IDC_RADIO5, IDC_RADIO6));																AddStr2EditCtr(str);	AddDebugStr2EditCtr(_T("电量百分"));
	str.Format(_T("0x%02X"), AddRadioStr2EditCtr(IDC_RADIO7, IDC_RADIO8));																AddStr2EditCtr(str);	AddDebugStr2EditCtr(_T("温度"));
	str.Format(_T("0x%02X"), AddRadioStr2EditCtr(IDC_RADIO9, IDC_RADIO10));																AddStr2EditCtr(str);	AddDebugStr2EditCtr(_T("欠压超前"));
	str.Format(_T("0x%02X"), AddRadioStr2EditCtr(IDC_RADIO11, IDC_RADIO12));															AddStr2EditCtr(str);	AddDebugStr2EditCtr(_T("速度调节"));
	str.Format(_T("0x%02X"), AddRadioStr2EditCtr(IDC_RADIO13, IDC_RADIO14));															AddStr2EditCtr(str);	AddDebugStr2EditCtr(_T("相线速度"));
	str.Format(_T("0x%02X"), AddRadioStr2EditCtr(IDC_RADIO15, IDC_RADIO16));															AddStr2EditCtr(str);	AddDebugStr2EditCtr(_T("一线"));
	str.Format(_T("0x%02X"), AddRadioStr2EditCtr(IDC_RADIO17, IDC_RADIO18));															AddStr2EditCtr(str);	AddDebugStr2EditCtr(_T("电量延时"));
	str.Format(_T("0x%02X"), AddRadioStr2EditCtr(IDC_RADIO19, IDC_RADIO20));															AddStr2EditCtr(str);	AddDebugStr2EditCtr(_T("仅剩一格电"));
	str.Format(_T("0x%02X"), ((CButton*)GetDlgItem(IDC_CHECK3))->GetCheck());															AddStr2EditCtr(str);	AddDebugStr2EditCtr(_T("一线通无速度"));
	str.Format(_T("0x%02X"), ((CButton*)GetDlgItem(IDC_CHECK4))->GetCheck());															AddStr2EditCtr(str);

	//其他设定
																																								AddDebugStr2EditCtr(_T("一线通速"));
	GetEditFloat2Binary32(IDC_EDIT20, pbyte);	str.Format(_T("0x%02X 0x%02X 0x%02X 0x%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);	AddStr2EditCtr(str);	AddDebugStr2EditCtr(_T("最大速度"));
	GetEditFloat2Binary32(IDC_EDIT21, pbyte);	str.Format(_T("0x%02X 0x%02X 0x%02X 0x%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);	AddStr2EditCtr(str);	AddDebugStr2EditCtr(_T("延迟时间"));
	GetEditFloat2Binary32(IDC_EDIT22, pbyte);	str.Format(_T("0x%02X 0x%02X 0x%02X 0x%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);	AddStr2EditCtr(str);	AddDebugStr2EditCtr(_T("里程倍"));
	GetEditFloat2Binary32(IDC_EDIT23, pbyte);	str.Format(_T("0x%02X 0x%02X 0x%02X 0x%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);	AddStr2EditCtr(str);	AddDebugStr2EditCtr(_T("限速速度"));
	GetEditFloat2Binary32(IDC_EDIT24, pbyte);	str.Format(_T("0x%02X 0x%02X 0x%02X 0x%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);	AddStr2EditCtr(str);	AddDebugStr2EditCtr(_T("一一一>"));
	GetEditFloat2Binary32(IDC_EDIT25, pbyte);	str.Format(_T("0x%02X 0x%02X 0x%02X 0x%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);	AddStr2EditCtr(str);	AddDebugStr2EditCtr(_T("小计里程"));
	str.Format(_T("0x%02X"),((CComboBox*)GetDlgItem(IDC_COMBO7))->GetCurSel());															AddStr2EditCtr(str);	AddDebugStr2EditCtr(_T("P档位置"));
	str.Format(_T("0x%02X"),((CComboBox*)GetDlgItem(IDC_COMBO7))->GetCurSel());															AddStr2EditCtr(str);	AddDebugStr2EditCtr(_T("P限速方式"));
	str.Format(_T("0x%02X"),((CComboBox*)GetDlgItem(IDC_COMBO7))->GetCurSel());															AddStr2EditCtr(str);	AddDebugStr2EditCtr(_T("左右大灯上拉"));
	str.Format(_T("0x%02X"), ((CButton*)GetDlgItem(IDC_CHECK7))->GetCheck());															AddStr2EditCtr(str);	AddDebugStr2EditCtr(_T("档位上位"));
	str.Format(_T("0x%02X"), ((CButton*)GetDlgItem(IDC_CHECK8))->GetCheck());															AddStr2EditCtr(str);	AddDebugStr2EditCtr(_T("一线通上拉"));
	str.Format(_T("0x%02X"), ((CButton*)GetDlgItem(IDC_CHECK9))->GetCheck());															AddStr2EditCtr(str);	AddDebugStr2EditCtr(_T("配置时修调"));
	str.Format(_T("0x%02X"), ((CButton*)GetDlgItem(IDC_CHECK10))->GetCheck());															AddStr2EditCtr(str);	AddDebugStr2EditCtr(_T("相速优先"));
	str.Format(_T("0x%02X"), ((CButton*)GetDlgItem(IDC_CHECK11))->GetCheck());															AddStr2EditCtr(str);	AddDebugStr2EditCtr(_T("速度递增"));
	str.Format(_T("0x%02X"), ((CButton*)GetDlgItem(IDC_CHECK12))->GetCheck());															AddStr2EditCtr(str);	AddDebugStr2EditCtr(_T("自动配置"));
	str.Format(_T("0x%02X"), ((CButton*)GetDlgItem(IDC_CHECK13))->GetCheck());															AddStr2EditCtr(str);

	//左右大灯配置
																																								AddDebugStr2EditCtr(_T("左右大灯正负控"));
	str.Format(_T("0x%02X"), AddRadioStr2EditCtr(IDC_RADIO1, IDC_RADIO2));																AddStr2EditCtr(str);	AddDebugStr2EditCtr(_T("开启清累计"));
	str.Format(_T("0x%02X"), ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck());															AddStr2EditCtr(str);	AddDebugStr2EditCtr(_T("转向灯同步闪烁"));
	str.Format(_T("0x%02X"), ((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck());															AddStr2EditCtr(str);

	//档位相关配置
																																								AddDebugStr2EditCtr(_T("档位相关正负控"));
	str.Format(_T("0x%02X"), AddRadioStr2EditCtr(IDC_RADIO21, IDC_RADIO22));															AddStr2EditCtr(str);	AddDebugStr2EditCtr(_T("开启超三速"));
	str.Format(_T("0x%02X"), ((CButton*)GetDlgItem(IDC_CHECK5))->GetCheck());															AddStr2EditCtr(str);	AddDebugStr2EditCtr(_T("档位模"));
	str.Format(_T("0x%02X"),((CComboBox*)GetDlgItem(IDC_COMBO4))->GetCurSel());															AddStr2EditCtr(str);	AddDebugStr2EditCtr(_T("自动二档位"));
	GetEditFloat2Binary32(IDC_EDIT30, pbyte);	str.Format(_T("0x%02X 0x%02X 0x%02X 0x%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);	AddStr2EditCtr(str);	AddDebugStr2EditCtr(_T("自动三档位"));
	GetEditFloat2Binary32(IDC_EDIT31, pbyte);	str.Format(_T("0x%02X 0x%02X 0x%02X 0x%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);	AddStr2EditCtr(str);

	//三电压混合识别
																																								AddDebugStr2EditCtr(_T("开启三电压混合识别"));
	str.Format(_T("0x%02X"), ((CButton*)GetDlgItem(IDC_CHECK6))->GetCheck());															AddStr2EditCtr(str);	AddDebugStr2EditCtr(_T("三电压默认"));
	str.Format(_T("0x%02X"), AddRadioStr2EditCtr(IDC_RADIO23, IDC_RADIO24));															AddStr2EditCtr(str);
	return true;
}


void CCommMFCDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

#if 1	//调试信息开关
	#ifndef _DebugInfo
	#define _DebugInfo
	#endif
#endif

	//((CEdit*)GetDlgItem(IDC_EDIT2))->SetWindowText(_T(""));	//清空编辑框内容
	GetData2Hex();

	OnBnClickedButton3();
}

/**
*	测试：https://lostphp.com/hexconvert/
*	参考：http://www.niuguwen.cn/blog/13926.html
*/
bool CCommMFCDlg::GetEditFloat2Binary32(int nID, unsigned char* pbyte)
{
	CString str;
	GetDlgItemText(nID, str);
	float fInput = (float)_ttof(str);
	unsigned char* p = (unsigned char*)&fInput;
	*(pbyte + 0) = *(p + 0);
	*(pbyte + 1) = *(p + 1);
	*(pbyte + 2) = *(p + 2);
	*(pbyte + 3) = *(p + 3);

	return true;
}


bool CCommMFCDlg::AddStr2EditCtr(CString str)
{
	//CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT2);
	//int nLength = pEdit->GetWindowTextLength();
	//pEdit->SetSel(nLength, nLength);	//选定文件的末尾
	//if(nLength > 0)	//第一次填内容不要间隔，不然对不齐
	//{
	//	CString strData = _T(" ") + str;
	//	pEdit->ReplaceSel(strData);
	//}
	//else
	//{
	//	CString strData = str;	
	//	pEdit->ReplaceSel(strData);
	//}
	
	return true;
}


bool CCommMFCDlg::AddDebugStr2EditCtr(CString str)
{
//#ifdef _DebugInfo
//
//	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT2);
//	int nLength = pEdit->GetWindowTextLength();
//	pEdit->SetSel(nLength, nLength);	//选定文件的末尾
//	if(nLength > 0)	//第一次填内容不要间隔，不然对不齐
//	{
//		CString strData = _T("\r\n") + str + _T(":\r\n");
//		pEdit->ReplaceSel(strData);
//	}
//	else
//	{
//		CString strData = str + _T(":\r\n");	
//		pEdit->ReplaceSel(strData);
//	}
//
//#endif
	return true;
}


int CCommMFCDlg::AddRadioStr2EditCtr(int nRadioCtrGroup1, int nRadioCtrGroup0)
{
	if(((CButton*)GetDlgItem(nRadioCtrGroup1))->GetCheck())	//如果选择是返回1
	{
		return 0x01;
	}
	if(((CButton*)GetDlgItem(nRadioCtrGroup0))->GetCheck())//如果选择不是返回0
	{
		return 0x00;
	}

	return 0xff;	//错误返回ff
}


bool CCommMFCDlg::GetUi2Hex(void)
{
	//电压配置
	//快速选
	CString str;																																			
	str.Format(_T("%02X"),((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel());													AddStr2EditCtr(str, IDC_SendEdit2);
	str.Format(_T("%02X"),((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCurSel());													AddStr2EditCtr(str, IDC_SendEdit2);
	str.Format(_T("%02X"),((CComboBox*)GetDlgItem(IDC_COMBO3))->GetCurSel());													AddStr2EditCtr(str, IDC_SendEdit2);

	//欠压电
	unsigned char pbyte[4] = {0};																															
	GetEditFloat2Binary32(IDC_EDIT5, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		AddStr2EditCtr(str, IDC_SendEdit2);
	GetEditFloat2Binary32(IDC_EDIT6, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		AddStr2EditCtr(str, IDC_SendEdit2);
	GetEditFloat2Binary32(IDC_EDIT7, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		AddStr2EditCtr(str, IDC_SendEdit2);
	GetEditFloat2Binary32(IDC_EDIT8, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		AddStr2EditCtr(str, IDC_SendEdit2);
	GetEditFloat2Binary32(IDC_EDIT9, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		AddStr2EditCtr(str, IDC_SendEdit2);
	GetEditFloat2Binary32(IDC_EDIT10, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		AddStr2EditCtr(str, IDC_SendEdit2);
	GetEditFloat2Binary32(IDC_EDIT11, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		AddStr2EditCtr(str, IDC_SendEdit2);
	GetEditFloat2Binary32(IDC_EDIT12, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		AddStr2EditCtr(str, IDC_SendEdit2);
	GetEditFloat2Binary32(IDC_EDIT13, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		AddStr2EditCtr(str, IDC_SendEdit2);
	GetEditFloat2Binary32(IDC_EDIT14, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		AddStr2EditCtr(str, IDC_SendEdit2);
	GetEditFloat2Binary32(IDC_EDIT15, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		AddStr2EditCtr(str, IDC_SendEdit2);
	GetEditFloat2Binary32(IDC_EDIT16, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		AddStr2EditCtr(str, IDC_SendEdit2);
	GetEditFloat2Binary32(IDC_EDIT17, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		AddStr2EditCtr(str, IDC_SendEdit2);
	GetEditFloat2Binary32(IDC_EDIT18, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		AddStr2EditCtr(str, IDC_SendEdit2);
	GetEditFloat2Binary32(IDC_EDIT19, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		AddStr2EditCtr(str, IDC_SendEdit2);

	//功能配置
																																							
	str.Format(_T("%02X"), AddRadioStr2EditCtr(IDC_RADIO3, IDC_RADIO4));														AddStr2EditCtr(str, IDC_SendEdit2);															
	str.Format(_T("%02X"), AddRadioStr2EditCtr(IDC_RADIO5, IDC_RADIO6));														AddStr2EditCtr(str, IDC_SendEdit2);															
	str.Format(_T("%02X"), AddRadioStr2EditCtr(IDC_RADIO7, IDC_RADIO8));														AddStr2EditCtr(str, IDC_SendEdit2);															
	str.Format(_T("%02X"), AddRadioStr2EditCtr(IDC_RADIO9, IDC_RADIO10));														AddStr2EditCtr(str, IDC_SendEdit2);															
	str.Format(_T("%02X"), AddRadioStr2EditCtr(IDC_RADIO11, IDC_RADIO12));														AddStr2EditCtr(str, IDC_SendEdit2);														
	str.Format(_T("%02X"), AddRadioStr2EditCtr(IDC_RADIO13, IDC_RADIO14));														AddStr2EditCtr(str, IDC_SendEdit2);														
	str.Format(_T("%02X"), AddRadioStr2EditCtr(IDC_RADIO15, IDC_RADIO16));														AddStr2EditCtr(str, IDC_SendEdit2);														
	str.Format(_T("%02X"), AddRadioStr2EditCtr(IDC_RADIO17, IDC_RADIO18));														AddStr2EditCtr(str, IDC_SendEdit2);														
	str.Format(_T("%02X"), AddRadioStr2EditCtr(IDC_RADIO19, IDC_RADIO20));														AddStr2EditCtr(str, IDC_SendEdit2);														
	str.Format(_T("%02X"), ((CButton*)GetDlgItem(IDC_CHECK3))->GetCheck());														AddStr2EditCtr(str, IDC_SendEdit2);														
	str.Format(_T("%02X"), ((CButton*)GetDlgItem(IDC_CHECK4))->GetCheck());														AddStr2EditCtr(str, IDC_SendEdit2);

	//其他设定
																																							
	GetEditFloat2Binary32(IDC_EDIT20, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		AddStr2EditCtr(str, IDC_SendEdit2);
	GetEditFloat2Binary32(IDC_EDIT21, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		AddStr2EditCtr(str, IDC_SendEdit2);
	GetEditFloat2Binary32(IDC_EDIT22, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		AddStr2EditCtr(str, IDC_SendEdit2);
	GetEditFloat2Binary32(IDC_EDIT23, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		AddStr2EditCtr(str, IDC_SendEdit2);
	GetEditFloat2Binary32(IDC_EDIT24, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		AddStr2EditCtr(str, IDC_SendEdit2);
	GetEditFloat2Binary32(IDC_EDIT25, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		AddStr2EditCtr(str, IDC_SendEdit2);
	str.Format(_T("%02X"),((CComboBox*)GetDlgItem(IDC_COMBO7))->GetCurSel());													AddStr2EditCtr(str, IDC_SendEdit2);														
	str.Format(_T("%02X"),((CComboBox*)GetDlgItem(IDC_COMBO7))->GetCurSel());													AddStr2EditCtr(str, IDC_SendEdit2);														
	str.Format(_T("%02X"),((CComboBox*)GetDlgItem(IDC_COMBO7))->GetCurSel());													AddStr2EditCtr(str, IDC_SendEdit2);														
	str.Format(_T("%02X"), ((CButton*)GetDlgItem(IDC_CHECK7))->GetCheck());														AddStr2EditCtr(str, IDC_SendEdit2);														
	str.Format(_T("%02X"), ((CButton*)GetDlgItem(IDC_CHECK8))->GetCheck());														AddStr2EditCtr(str, IDC_SendEdit2);														
	str.Format(_T("%02X"), ((CButton*)GetDlgItem(IDC_CHECK9))->GetCheck());														AddStr2EditCtr(str, IDC_SendEdit2);														
	str.Format(_T("%02X"), ((CButton*)GetDlgItem(IDC_CHECK10))->GetCheck());													AddStr2EditCtr(str, IDC_SendEdit2);														
	str.Format(_T("%02X"), ((CButton*)GetDlgItem(IDC_CHECK11))->GetCheck());													AddStr2EditCtr(str, IDC_SendEdit2);														
	str.Format(_T("%02X"), ((CButton*)GetDlgItem(IDC_CHECK12))->GetCheck());													AddStr2EditCtr(str, IDC_SendEdit2);														
	str.Format(_T("%02X"), ((CButton*)GetDlgItem(IDC_CHECK13))->GetCheck());													AddStr2EditCtr(str, IDC_SendEdit2);

	//左右大灯配置
																																							
	str.Format(_T("%02X"), AddRadioStr2EditCtr(IDC_RADIO1, IDC_RADIO2));														AddStr2EditCtr(str, IDC_SendEdit2);															
	str.Format(_T("%02X"), ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck());														AddStr2EditCtr(str, IDC_SendEdit2);														
	str.Format(_T("%02X"), ((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck());														AddStr2EditCtr(str, IDC_SendEdit2);

	//档位相关配置
																																							
	str.Format(_T("%02X"), AddRadioStr2EditCtr(IDC_RADIO21, IDC_RADIO22));														AddStr2EditCtr(str, IDC_SendEdit2);														
	str.Format(_T("%02X"), ((CButton*)GetDlgItem(IDC_CHECK5))->GetCheck());														AddStr2EditCtr(str, IDC_SendEdit2);														
	str.Format(_T("%02X"),((CComboBox*)GetDlgItem(IDC_COMBO4))->GetCurSel());													AddStr2EditCtr(str, IDC_SendEdit2);														
	GetEditFloat2Binary32(IDC_EDIT30, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		AddStr2EditCtr(str, IDC_SendEdit2);
	GetEditFloat2Binary32(IDC_EDIT31, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		AddStr2EditCtr(str, IDC_SendEdit2);

	//三电压混合识别
																																							
	str.Format(_T("%02X"), ((CButton*)GetDlgItem(IDC_CHECK6))->GetCheck());														AddStr2EditCtr(str, IDC_SendEdit2);														
	str.Format(_T("%02X"), AddRadioStr2EditCtr(IDC_RADIO23, IDC_RADIO24));														AddStr2EditCtr(str, IDC_SendEdit2);
	return true;
}


bool CCommMFCDlg::AddStr2EditCtr(CString str, int nCtrID)
{
	CEdit* pEdit = (CEdit*)GetDlgItem(nCtrID);
	int nLength = pEdit->GetWindowTextLength();
	pEdit->SetSel(nLength, nLength);	//选定文件的末尾

	CString strData = str;	
	pEdit->ReplaceSel(strData);
	
	return true;
}


void CCommMFCDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码

	((CEdit*)GetDlgItem(IDC_SendEdit2))->SetWindowText(_T(""));	//清空编辑框内容
	GetUi2Hex();
}


void CCommMFCDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	SendUi2Com();
}


void CCommMFCDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	GetDlgItemText(IDC_SendEdit2,str);

	unsigned char fileArray[1024] = {0};

	int len = 0;
	char* m_str = NULL;

	CStringA strA(str);		//这里频繁使用可能会造成内存泄漏，待优化
	len = strA.GetLength();
	m_str = strA.GetBuffer();

	//这里需要加一个算法，来将字符串转换为十六进制
	{
		for(int i = 0; i < len; i++)
		{
			if(m_str[i]>47&&m_str[i]<=58)
			{
				m_str[i]-=48;
			}
			if(m_str[i]>64&&m_str[i]<=71)
			{
				m_str[i]-=55;
			}
		}

		//计算每个字符转换后两两字符组合成0xFF格式存储到前面那个，后面的置0
		{
			for(int i = 0; i < len; i+=2)
			{
				m_str[i] = m_str[i] *16 + m_str[i+1];
				m_str[i+1] = 0;
				
			}
		}

		//快速移位删除所有字符数组中的0
		{
			for(int i = 0; i < len/2; i++)
			{
				m_str[i] = m_str[i*2];
				//m_str[len-1-i]=m_str[len-1-(i*2)];
				fileArray[i] = m_str[i];
			}
		}

	}

	unsigned short res = crc16table((unsigned char*)fileArray, len/2);

	CString strCrc;
	strCrc.Format(_T("%X"),res);

	strA.ReleaseBuffer();

	AddStr2EditCtr(strCrc, IDC_SendEdit2);

}


void CCommMFCDlg::OnSave()
{
	// TODO: 在此添加命令处理程序代码
	OnBnClickedButtonSave();
}


void CCommMFCDlg::OnExit()
{
	// TODO: 在此添加命令处理程序代码
	OnClose();
	exit(0);
}


void CCommMFCDlg::OnConSet()
{
	// TODO: 在此添加命令处理程序代码
	CConSetDlg dlg;
	dlg.DoModal();
	if (m_SerialPort.isOpened())
	{
		m_SerialPort.close();
	}
	
	//重新加载更新的Appconfig.ini
	ShowConfig();
}


CString CCommMFCDlg::GetModuleDir(void)
{
	CString  strPathName;
	GetModuleFileName(NULL, strPathName.GetBuffer(MAX_PATH), MAX_PATH);
	strPathName.ReleaseBuffer(MAX_PATH);
	int nPos = strPathName.ReverseFind(_T('\\'));
	strPathName = strPathName.Left(nPos + 1);
	return strPathName;
}


bool CCommMFCDlg::ShowConfig(void)
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

	CString str = _T("串口号:") + strComPort + _T(" 波特率:") + strBaudRate + _T(" 校验位:") + strParityBit + 
		_T(" 数据位:") + strDataBit + _T(" 停止位:") + strStopBit;

	m_bar.SetPaneText(0,str);

	OpenComPort(strComPort, strBaudRate, strParityBit, strDataBit, strStopBit);
	return true;
}


bool CCommMFCDlg::OpenComPort(CString strComPort, CString strBaudRate, CString strParityBit, CString strDataBit, CString strStopBit)
{
	string portName = W2AString(strComPort);
	int SelBaudRate = _ttoi(strBaudRate);

	int SelParity = 0;
	int SelDataBits = 8;
	int SelStop = 0;

	m_SerialPort.init(portName, SelBaudRate, itas109::Parity(SelParity), itas109::DataBits(SelDataBits), itas109::StopBits(SelStop));
	m_SerialPort.open();
	
	if (m_SerialPort.isOpened())
	{
		CString str = _T("串口号:") + strComPort + _T(" 波特率:") + strBaudRate + _T(" 校验位:") + strParityBit + 
		_T(" 数据位:") + strDataBit + _T(" 停止位:") + strStopBit + _T(" 连接状态:") + _T("已连接");
		
		m_bar.SetPaneText(0,str);
	}
	else
	{
		CString str = _T("串口号:") + strComPort + _T(" 波特率:") + strBaudRate + _T(" 校验位:") + strParityBit + 
		_T(" 数据位:") + strDataBit + _T(" 停止位:") + strStopBit + _T(" 连接状态:") + _T("未连接");
		
		m_bar.SetPaneText(0,str);
	}

	return true;

}


string CCommMFCDlg::W2AString(const wchar_t* str)
{
	string returnstring = "";
	int num = WideCharToMultiByte(
		CP_ACP,		//转换的格式ASCII
		0,			//默认转换方式
		str,		//输入字节
		-1,			//字符串大小，-1就是\0计算
		0,			//输出地址
		0,			//输出空间大小
		0,			//失败默认替换
		false
	);

	if (num <= 0)
		return returnstring;

	char* data = new char[num + 1];        //\0
	data[0] = 0;
	num = WideCharToMultiByte(
		CP_ACP,		//转换的格式ASCII
		0,			//默认转换方式
		str,		//输入字节
		-1,			//字符串大小，-1就是\0计算
		data,       //输出地址
		num,        //输出空间大小
		0,			//失败默认替换
		false
	);
	if (num > 0)
		returnstring = data;

	delete[]data;
	return returnstring;
}


bool CCommMFCDlg::SendUi2Com()	//124个字节
{
	//电压配置
	//快速选
	CString str = _T(""), strTotal = _T("");																																			
	str.Format(_T("%02X"),((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel());													strTotal += str;
	str.Format(_T("%02X"),((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCurSel());													strTotal += str;
	str.Format(_T("%02X"),((CComboBox*)GetDlgItem(IDC_COMBO3))->GetCurSel());													strTotal += str;

	//欠压电
	unsigned char pbyte[4] = {0};																															
	GetEditFloat2Binary32(IDC_EDIT5, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		strTotal += str;
	GetEditFloat2Binary32(IDC_EDIT6, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		strTotal += str;
	GetEditFloat2Binary32(IDC_EDIT7, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		strTotal += str;
	GetEditFloat2Binary32(IDC_EDIT8, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		strTotal += str;
	GetEditFloat2Binary32(IDC_EDIT9, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		strTotal += str;
	GetEditFloat2Binary32(IDC_EDIT10, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		strTotal += str;
	GetEditFloat2Binary32(IDC_EDIT11, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		strTotal += str;
	GetEditFloat2Binary32(IDC_EDIT12, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		strTotal += str;
	GetEditFloat2Binary32(IDC_EDIT13, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		strTotal += str;
	GetEditFloat2Binary32(IDC_EDIT14, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		strTotal += str;
	GetEditFloat2Binary32(IDC_EDIT15, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		strTotal += str;
	GetEditFloat2Binary32(IDC_EDIT16, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		strTotal += str;
	GetEditFloat2Binary32(IDC_EDIT17, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		strTotal += str;
	GetEditFloat2Binary32(IDC_EDIT18, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		strTotal += str;
	GetEditFloat2Binary32(IDC_EDIT19, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		strTotal += str;

	//功能配置
																																							
	str.Format(_T("%02X"), AddRadioStr2EditCtr(IDC_RADIO3, IDC_RADIO4));														strTotal += str;															
	str.Format(_T("%02X"), AddRadioStr2EditCtr(IDC_RADIO5, IDC_RADIO6));														strTotal += str;															
	str.Format(_T("%02X"), AddRadioStr2EditCtr(IDC_RADIO7, IDC_RADIO8));														strTotal += str;															
	str.Format(_T("%02X"), AddRadioStr2EditCtr(IDC_RADIO9, IDC_RADIO10));														strTotal += str;															
	str.Format(_T("%02X"), AddRadioStr2EditCtr(IDC_RADIO11, IDC_RADIO12));														strTotal += str;														
	str.Format(_T("%02X"), AddRadioStr2EditCtr(IDC_RADIO13, IDC_RADIO14));														strTotal += str;														
	str.Format(_T("%02X"), AddRadioStr2EditCtr(IDC_RADIO15, IDC_RADIO16));														strTotal += str;														
	str.Format(_T("%02X"), AddRadioStr2EditCtr(IDC_RADIO17, IDC_RADIO18));														strTotal += str;														
	str.Format(_T("%02X"), AddRadioStr2EditCtr(IDC_RADIO19, IDC_RADIO20));														strTotal += str;														
	str.Format(_T("%02X"), ((CButton*)GetDlgItem(IDC_CHECK3))->GetCheck());														strTotal += str;														
	str.Format(_T("%02X"), ((CButton*)GetDlgItem(IDC_CHECK4))->GetCheck());														strTotal += str;

	//其他设定
																																							
	GetEditFloat2Binary32(IDC_EDIT20, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		strTotal += str;
	GetEditFloat2Binary32(IDC_EDIT21, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		strTotal += str;
	GetEditFloat2Binary32(IDC_EDIT22, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		strTotal += str;
	GetEditFloat2Binary32(IDC_EDIT23, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		strTotal += str;
	GetEditFloat2Binary32(IDC_EDIT24, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		strTotal += str;
	GetEditFloat2Binary32(IDC_EDIT25, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		strTotal += str;
	str.Format(_T("%02X"),((CComboBox*)GetDlgItem(IDC_COMBO7))->GetCurSel());													strTotal += str;														
	str.Format(_T("%02X"),((CComboBox*)GetDlgItem(IDC_COMBO7))->GetCurSel());													strTotal += str;														
	str.Format(_T("%02X"),((CComboBox*)GetDlgItem(IDC_COMBO7))->GetCurSel());													strTotal += str;														
	str.Format(_T("%02X"), ((CButton*)GetDlgItem(IDC_CHECK7))->GetCheck());														strTotal += str;														
	str.Format(_T("%02X"), ((CButton*)GetDlgItem(IDC_CHECK8))->GetCheck());														strTotal += str;														
	str.Format(_T("%02X"), ((CButton*)GetDlgItem(IDC_CHECK9))->GetCheck());														strTotal += str;														
	str.Format(_T("%02X"), ((CButton*)GetDlgItem(IDC_CHECK10))->GetCheck());													strTotal += str;														
	str.Format(_T("%02X"), ((CButton*)GetDlgItem(IDC_CHECK11))->GetCheck());													strTotal += str;														
	str.Format(_T("%02X"), ((CButton*)GetDlgItem(IDC_CHECK12))->GetCheck());													strTotal += str;														
	str.Format(_T("%02X"), ((CButton*)GetDlgItem(IDC_CHECK13))->GetCheck());													strTotal += str;

	//左右大灯配置
																																							
	str.Format(_T("%02X"), AddRadioStr2EditCtr(IDC_RADIO1, IDC_RADIO2));														strTotal += str;															
	str.Format(_T("%02X"), ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck());														strTotal += str;														
	str.Format(_T("%02X"), ((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck());														strTotal += str;

	//档位相关配置
																																							
	str.Format(_T("%02X"), AddRadioStr2EditCtr(IDC_RADIO21, IDC_RADIO22));														strTotal += str;														
	str.Format(_T("%02X"), ((CButton*)GetDlgItem(IDC_CHECK5))->GetCheck());														strTotal += str;														
	str.Format(_T("%02X"),((CComboBox*)GetDlgItem(IDC_COMBO4))->GetCurSel());													strTotal += str;														
	GetEditFloat2Binary32(IDC_EDIT30, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		strTotal += str;
	GetEditFloat2Binary32(IDC_EDIT31, pbyte);	str.Format(_T("%02X%02X%02X%02X"), pbyte[3], pbyte[2], pbyte[1], pbyte[0]);		strTotal += str;

	//三电压混合识别
																																							
	str.Format(_T("%02X"), ((CButton*)GetDlgItem(IDC_CHECK6))->GetCheck());														strTotal += str;														
	str.Format(_T("%02X"), AddRadioStr2EditCtr(IDC_RADIO23, IDC_RADIO24));														strTotal += str;


	int len = 0;
	char* m_str = NULL;


	CStringA strA(strTotal);
	len = strA.GetLength();
	m_str = strA.GetBuffer();

	//unsigned char fileArray[1024] = {0};
	//这里需要加一个算法，来将字符串转换为十六进制
	for(int i = 0; i < len; i++)
	{
		if(m_str[i]>47&&m_str[i]<=58)	//字符0~9转二进制
		{
			m_str[i]-=48;
		}
		if(m_str[i]>64&&m_str[i]<=71)	////字符A~F转二进制
		{
			m_str[i]-=55;
		}
	}

	//计算每个字符转换后两两字符组合成0xFF格式存储到前面那个，后面的置0
	for(int i = 0; i < len; i+=2)
	{
		m_str[i] = m_str[i] *16 + m_str[i+1];
		m_str[i+1] = 0;
		
	}

	//快速移位排序
	for(int i = 0; i < len/2; i++)
	{
		m_str[i] = m_str[i*2];
		//fileArray[i] = m_str[i];
	}
	
	unsigned short res = crc16table((unsigned char*)m_str, len/2);	//计算AddCRC16/MODBUS值用于接收端验证

	unsigned char* pc = (unsigned char*)&res;	//将计算的计算AddCRC16/MODBUS值添加到结尾准备发送
	m_str[len/2] = *(pc+1);
	m_str[len/2+1] = *(pc+0);

	m_SerialPort.writeData(m_str, len/2+2);	//增加两个添加的值发送
	strA.ReleaseBuffer();
	return true;
}
