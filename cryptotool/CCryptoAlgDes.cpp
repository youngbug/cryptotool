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


BOOL CCryptoAlgDes::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetBackgroundColor(RGB(255, 255, 255));//窗体背景色设置成白色

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
