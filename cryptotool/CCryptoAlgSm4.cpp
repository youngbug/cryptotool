// CCryptoAlgSm4.cpp: 实现文件
//

#include "stdafx.h"
#include "cryptotool.h"
#include "afxdialogex.h"
#include "CCryptoAlgSm4.h"
#include "MainFrm.h"
#include "../Library/dataconvert.h"
#include <sm4.h>

extern CMainFrame* g_MainFrame; //全局指针

// CCryptoAlgSm4 对话框

IMPLEMENT_DYNAMIC(CCryptoAlgSm4, CDialogEx)

CCryptoAlgSm4::CCryptoAlgSm4(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_CRYPTOALG_SM4, pParent)
	, m_Key(_T(""))
	, m_Plain(_T(""))
	, m_IV(_T(""))
	, m_Cipher(_T(""))
	, m_Len_Key(0)
	, m_Len_IV(0)
	, m_Len_Plain(0)
	, m_Len_Cipher(0)
{

}

CCryptoAlgSm4::~CCryptoAlgSm4()
{
}

void CCryptoAlgSm4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO2, m_Mode);

	DDX_Text(pDX, IDC_EDIT1, m_Key);
	DDX_Text(pDX, IDC_EDIT3, m_Plain);
	DDX_Text(pDX, IDC_EDIT2, m_IV);
	DDX_Text(pDX, IDC_EDIT4, m_Cipher);
	DDX_Text(pDX, IDC_EDIT5, m_Len_Key);
	DDX_Text(pDX, IDC_EDIT6, m_Len_IV);
	DDX_Text(pDX, IDC_EDIT7, m_Len_Plain);
	DDX_Text(pDX, IDC_EDIT8, m_Len_Cipher);
}


BEGIN_MESSAGE_MAP(CCryptoAlgSm4, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON4, &CCryptoAlgSm4::OnBnClickedButton4)
	ON_EN_CHANGE(IDC_EDIT1, &CCryptoAlgSm4::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CCryptoAlgSm4::OnEnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT3, &CCryptoAlgSm4::OnEnChangeEdit7)
	ON_EN_CHANGE(IDC_EDIT4, &CCryptoAlgSm4::OnEnChangeEdit8)
	ON_BN_CLICKED(IDC_BUTTON1, &CCryptoAlgSm4::OnBnClickedButton1)
END_MESSAGE_MAP()


// CCryptoAlgSm4 消息处理程序


void CCryptoAlgSm4::OnBnClickedButton4()
{
	// 
	unsigned char key[16] = { 0 };
	unsigned char iv[16] = { 0 };
	unsigned char* input = NULL;
	unsigned char* output = NULL;
	char* cipher = NULL;
	sm4_context ctx;
	int ret = 0;
	UpdateData(TRUE);
	
	if (m_Len_Key != 16)
	{
		g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"SM4 key length is incorrect.");
		goto EXIT;
	}

	if (m_Len_IV != 16)
	{
		g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"IV length is incorrect.");
		goto EXIT;
	}

	if (m_Len_Plain % 16 != 0)
	{
		g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"Plaintext length is incorrect.");
		goto EXIT;
	}

	zy_string2hex(key, m_Key.GetBuffer(), m_Key.GetLength());
	zy_string2hex(iv, m_IV.GetBuffer(), m_IV.GetLength());
	input = (unsigned char*)malloc(m_Len_Plain);
	output = (unsigned char*)malloc(m_Len_Plain);
	cipher = (char*)malloc(m_Len_Plain * 2 + 1);
	memset(cipher, 0, m_Len_Plain * 2 + 1);
	zy_string2hex(input, m_Plain.GetBuffer(), m_Plain.GetLength());
	
	sm4_setkey_enc(&ctx, key);
	if (m_Mode.GetCurSel() == 0)
	{
		sm4_crypt_ecb(&ctx, SM4_ENCRYPT, m_Len_Plain, input, output);
	}
	else
	{
		sm4_crypt_cbc(&ctx, SM4_ENCRYPT, m_Len_Plain, iv, input, output);
	}
	zy_hex2string(cipher, output, m_Len_Plain);
	m_Cipher.Format("%s", cipher);
	m_Len_Cipher = m_Cipher.GetLength() / 2;
EXIT:
	UpdateData(FALSE);
	free(input);
	free(output);
	free(cipher);
}


BOOL CCryptoAlgSm4::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetBackgroundColor(RGB(255, 255, 255));//窗体背景色设置成白色
	//
	m_Mode.InsertString(0, "ECB (Electronic Codebook Book)");
	m_Mode.InsertString(1, "CBC (Cipher Block Chaining)");
	m_Mode.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


BOOL CCryptoAlgSm4::CheckHexString(CString strHexString)
{
	CString strResult;
	if (strHexString.GetLength() == 0)
	{
		return TRUE;
	}
	strResult = strHexString.SpanIncluding(_T("0123456789abcdefABCDEF"));
	if (strResult != strHexString)
	{
		return FALSE;
	}
	return TRUE;
}

void CCryptoAlgSm4::OnEnChangeEdit1()
{
	UpdateData(TRUE);
	if (CheckHexString(m_Key) == FALSE)
	{
		MessageBox("Edit box of Key contains invalid char.");
		m_Key.Format("");
	}
	m_Len_Key = m_Key.GetLength() / 2;

	UpdateData(FALSE);
}


void CCryptoAlgSm4::OnEnChangeEdit6()
{
	UpdateData(TRUE);
	if (CheckHexString(m_IV) == FALSE)
	{
		MessageBox("Edit box of IV contains invalid char.");
		m_IV.Format("");
	}
	m_Len_IV = m_IV.GetLength() / 2;

	UpdateData(FALSE);
}


void CCryptoAlgSm4::OnEnChangeEdit7()
{
	UpdateData(TRUE);
	if (CheckHexString(m_Plain) == FALSE)
	{
		MessageBox("Edit box of plaintext contains invalid char.");
		m_Plain.Format("");
	}
	m_Len_Plain = m_Plain.GetLength() / 2;

	UpdateData(FALSE);
}


void CCryptoAlgSm4::OnEnChangeEdit8()
{
	UpdateData(TRUE);
	if (CheckHexString(m_Cipher) == FALSE)
	{
		MessageBox("Edit box of ciphertext contains invalid char.");
		m_Cipher.Format("");
	}
	m_Len_Cipher = m_Cipher.GetLength() / 2;

	UpdateData(FALSE);
}


BOOL CCryptoAlgSm4::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	int x = 'a' - 'A';

	if (GetFocus() == GetDlgItem(IDC_EDIT1) ||
		GetFocus() == GetDlgItem(IDC_EDIT2) ||
		GetFocus() == GetDlgItem(IDC_EDIT3) ||
		GetFocus() == GetDlgItem(IDC_EDIT4))
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


void CCryptoAlgSm4::OnBnClickedButton1()
{
	// SM4 Decrypt
	unsigned char key[16] = { 0 };
	unsigned char iv[16] = { 0 };
	unsigned char* input = NULL;
	unsigned char* output = NULL;
	char* plain = NULL;
	sm4_context ctx;
	int ret = 0;
	UpdateData(TRUE);

	if (m_Len_Key % 16 != 0)
	{
		g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"SM4 key length is incorrect.");
		goto EXIT;
	}

	if (m_Len_IV != 16)
	{
		g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"IV length is incorrect.");
		goto EXIT;
	}

	if (m_Len_Cipher % 16 != 0)
	{
		g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"Ciphertext length is incorrect.");
		goto EXIT;
	}

	zy_string2hex(key, m_Key.GetBuffer(), m_Key.GetLength());
	zy_string2hex(iv, m_IV.GetBuffer(), m_IV.GetLength());
	input = (unsigned char*)malloc(m_Len_Cipher);
	output = (unsigned char*)malloc(m_Len_Cipher);
	plain = (char*)malloc(m_Len_Cipher * 2 + 1);
	memset(plain, 0, m_Len_Cipher * 2 + 1);
	zy_string2hex(input, m_Cipher.GetBuffer(), m_Cipher.GetLength());

	sm4_setkey_dec(&ctx, key);
	if (m_Mode.GetCurSel() == 0)
	{
		sm4_crypt_ecb(&ctx, SM4_DECRYPT, m_Len_Cipher, input, output);
	}
	else
	{
		sm4_crypt_cbc(&ctx, SM4_DECRYPT, m_Len_Cipher, iv, input, output);
	}
	zy_hex2string(plain, output, m_Len_Cipher);
	m_Plain.Format("%s", plain);
	m_Len_Plain = m_Plain.GetLength() / 2;
EXIT:
	UpdateData(FALSE);
	free(input);
	free(output);
	free(plain);
}
