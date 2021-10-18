// CCryptoAlgDes.cpp: 实现文件
//

#include "StdAfx.h"
#include "cryptotool.h"
#include "CCryptoAlgDes.h"
#include "afxdialogex.h"


// CCryptoAlgDes 对话框

IMPLEMENT_DYNAMIC(CCryptoAlgDes, CDialogEx)

CCryptoAlgDes::CCryptoAlgDes(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_CRYPTOALG_DES, pParent)
{

}

CCryptoAlgDes::~CCryptoAlgDes()
{
}

void CCryptoAlgDes::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCryptoAlgDes, CDialogEx)
END_MESSAGE_MAP()


// CCryptoAlgDes 消息处理程序
