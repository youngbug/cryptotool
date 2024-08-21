#pragma once
#include "afxdialogex.h"


// CCryptoAlgRsa 对话框

class CCryptoAlgRsa : public CDialogEx
{
	DECLARE_DYNAMIC(CCryptoAlgRsa)

public:
	CCryptoAlgRsa(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CCryptoAlgRsa();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_CRYPTOALG_RSA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_Plain;
	CString m_Cipher;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
