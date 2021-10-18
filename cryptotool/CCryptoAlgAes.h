#pragma once


// CCryptoAlgAes 对话框

class CCryptoAlgAes : public CDialogEx
{
	DECLARE_DYNAMIC(CCryptoAlgAes)

public:
	CCryptoAlgAes(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CCryptoAlgAes();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_CRYPTOALG_AES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m_KeyLength;
	CComboBox m_Mode;
	CComboBox m_Padding;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnEnChangeEdit3();
	BOOL CheckHexString(CString strHexString);
	CString m_Key;
	CString m_IV;
	CString m_Plain;
	CString m_Cipher;
	int m_Len_Plain;
	int m_Len_Key;
	int m_Len_IV;
	int m_Len_Cipher;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
};
