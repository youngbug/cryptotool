#pragma once


// CCryptoAlgDes 对话框

class CCryptoAlgDes : public CDialogEx
{
	DECLARE_DYNAMIC(CCryptoAlgDes)

public:
	CCryptoAlgDes(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CCryptoAlgDes();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_CRYPTOALG_DES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
