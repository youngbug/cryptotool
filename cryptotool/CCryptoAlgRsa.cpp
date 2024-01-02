// CCryptoAlgRsa.cpp: 实现文件
//

#include "stdafx.h"
#include "cryptotool.h"
#include "afxdialogex.h"
#include "CCryptoAlgRsa.h"


// CCryptoAlgRsa 对话框

IMPLEMENT_DYNAMIC(CCryptoAlgRsa, CDialogEx)

CCryptoAlgRsa::CCryptoAlgRsa(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_CRYPTOALG_RSA, pParent)
	, m_Plain(_T(""))
	, m_Cipher(_T(""))
{

}

CCryptoAlgRsa::~CCryptoAlgRsa()
{
}

void CCryptoAlgRsa::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Plain);
	DDX_Text(pDX, IDC_EDIT9, m_Cipher);
}


BEGIN_MESSAGE_MAP(CCryptoAlgRsa, CDialogEx)
END_MESSAGE_MAP()


// CCryptoAlgRsa 消息处理程序


BOOL CCryptoAlgRsa::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetBackgroundColor(RGB(255, 255, 255));//窗体背景色设置成白色
	m_Plain.Format("test");
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


BOOL CCryptoAlgRsa::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	int x = 'a' - 'A';

	if (GetFocus() == GetDlgItem(IDC_EDIT1) ||
		GetFocus() == GetDlgItem(IDC_EDIT9) ||
		GetFocus() == GetDlgItem(IDC_EDIT2) ||
		GetFocus() == GetDlgItem(IDC_EDIT3) ||
		GetFocus() == GetDlgItem(IDC_EDIT4) ||
		GetFocus() == GetDlgItem(IDC_EDIT10) ||
		GetFocus() == GetDlgItem(IDC_EDIT11) ||
		GetFocus() == GetDlgItem(IDC_EDIT12) ||
		GetFocus() == GetDlgItem(IDC_EDIT13) ||
		GetFocus() == GetDlgItem(IDC_EDIT14))
	{
		if (pMsg->message == WM_CHAR)
		{
			if ((pMsg->wParam < 'a' || pMsg->wParam > 'f') &&
				(pMsg->wParam < 'A' || pMsg->wParam > 'F') &&
				(pMsg->wParam < '0' || pMsg->wParam > '9') &&
				(pMsg->wParam != VK_BACK) &&
				(pMsg->wParam != 0x16)
				)
			{
				return TRUE;//0~9 a-z A-Z之外的字符全都拦截
			}
			if (pMsg->wParam >= 'a' && pMsg->wParam <= 'f')
			{
				pMsg->wParam -= x; //小写字母转换成大写的
			}
		}
		else if (pMsg->message == WM_KEYDOWN)
		{
			if (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN)
			{
				return TRUE;
			}
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
