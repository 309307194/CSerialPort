#pragma once


// CABC 对话框

class CABC : public CDialogEx
{
	DECLARE_DYNAMIC(CABC)

public:
	CABC(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CABC();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOpen();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
