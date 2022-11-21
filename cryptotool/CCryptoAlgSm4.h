#pragma once
#include "afxdialogex.h"


// CCryptoAlgSm4 对话框

class CCryptoAlgSm4 : public CDialogEx
{
	DECLARE_DYNAMIC(CCryptoAlgSm4)

public:
	CCryptoAlgSm4(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CCryptoAlgSm4();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_CRYPTOALG_SM4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_Mode;
	afx_msg void OnBnClickedButton4();
	virtual BOOL OnInitDialog();
	BOOL CheckHexString(CString strHexString);
	CString m_Key;
	CString m_Plain;
	CString m_IV;
	CString m_Cipher;
	int m_Len_Key;
	int m_Len_IV;
	int m_Len_Plain;
	int m_Len_Cipher;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnEnChangeEdit7();
	afx_msg void OnEnChangeEdit8();
};
