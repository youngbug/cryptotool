// CCryptoAlgSm4.cpp: 实现文件
//

#include "stdafx.h"
#include "cryptotool.h"
#include "afxdialogex.h"
#include "CCryptoAlgSm4.h"


// CCryptoAlgSm4 对话框

IMPLEMENT_DYNAMIC(CCryptoAlgSm4, CDialogEx)

CCryptoAlgSm4::CCryptoAlgSm4(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_CRYPTOALG_SM4, pParent)
{

}

CCryptoAlgSm4::~CCryptoAlgSm4()
{
}

void CCryptoAlgSm4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCryptoAlgSm4, CDialogEx)
END_MESSAGE_MAP()


// CCryptoAlgSm4 消息处理程序
