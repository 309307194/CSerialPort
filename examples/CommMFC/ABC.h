#pragma once


// CABC �Ի���

class CABC : public CDialogEx
{
	DECLARE_DYNAMIC(CABC)

public:
	CABC(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CABC();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOpen();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
