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
};
