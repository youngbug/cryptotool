// CCryptoAlgAes.cpp: 实现文件
//

#include "stdafx.h"
#include "cryptotool.h"
#include "CCryptoAlgAes.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "../Library/padding.h"
#include "../Library/dataconvert.h"
#include <mbedtls/aes.h>

extern CMainFrame* g_MainFrame; //全局指针

// CCryptoAlgAes 对话框

IMPLEMENT_DYNAMIC(CCryptoAlgAes, CDialogEx)

CCryptoAlgAes::CCryptoAlgAes(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_CRYPTOALG_AES, pParent)
	, m_Key(_T(""))
	, m_IV(_T(""))
	, m_Plain(_T(""))
	, m_Cipher(_T(""))
	, m_Len_Plain(0)
	, m_Len_Key(0)
	, m_Len_IV(0)
	, m_Len_Cipher(0)
{

}

CCryptoAlgAes::~CCryptoAlgAes()
{
}

void CCryptoAlgAes::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_KeyLength);
	DDX_Control(pDX, IDC_COMBO2, m_Mode);
	DDX_Control(pDX, IDC_COMBO3, m_Padding);
	DDX_Text(pDX, IDC_EDIT1, m_Key);
	DDX_Text(pDX, IDC_EDIT2, m_IV);
	DDX_Text(pDX, IDC_EDIT3, m_Plain);
	DDX_Text(pDX, IDC_EDIT4, m_Cipher);
	DDX_Text(pDX, IDC_EDIT7, m_Len_Plain);
	DDX_Text(pDX, IDC_EDIT5, m_Len_Key);
	DDX_Text(pDX, IDC_EDIT6, m_Len_IV);
	DDX_Text(pDX, IDC_EDIT8, m_Len_Cipher);
}


BEGIN_MESSAGE_MAP(CCryptoAlgAes, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT3, &CCryptoAlgAes::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT1, &CCryptoAlgAes::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CCryptoAlgAes::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT4, &CCryptoAlgAes::OnEnChangeEdit4)
	ON_BN_CLICKED(IDC_BUTTON3, &CCryptoAlgAes::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CCryptoAlgAes::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CCryptoAlgAes::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON1, &CCryptoAlgAes::OnBnClickedButton1)
END_MESSAGE_MAP()


// CCryptoAlgAes 消息处理程序


BOOL CCryptoAlgAes::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetBackgroundColor(RGB(255, 255, 255));//窗体背景色设置成白色
	//
	m_KeyLength.InsertString(0, "128 bits");
	m_KeyLength.InsertString(1, "192 bits");
	m_KeyLength.InsertString(2, "256 bits");
	m_KeyLength.SetCurSel(0);
	//
	m_Mode.InsertString(0, "ECB (Electronic Codebook Book)");
	m_Mode.InsertString(1, "CBC (Cipher Block Chaining)");
	m_Mode.InsertString(2, "CFB (Cipher Feed Back)");
	m_Mode.InsertString(3, "OFB (Output Feed Back)");
	m_Mode.InsertString(4, "CTR (Cunter)");
	m_Mode.InsertString(5, "XTS (XOR Encrypt XOR)");
	m_Mode.SetCurSel(0);
	//
	m_Padding.InsertString(0, "No Padding");
	m_Padding.InsertString(1, "ISO9797-1 Padding Method 1(Zero Padding)");
	m_Padding.InsertString(2, "ISO9797-1 Padding Method 2(ISO7816-4)");
	m_Padding.InsertString(3, "ISO9797-1 Padding Method 3");
	m_Padding.InsertString(4, "ISO9797-1 Padding Method 4");
	m_Padding.InsertString(5, "ISO1026");
	m_Padding.InsertString(6, "ANSI X9.23");
	m_Padding.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


BOOL CCryptoAlgAes::PreTranslateMessage(MSG* pMsg)
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


void CCryptoAlgAes::OnEnChangeEdit3()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (CheckHexString(m_Plain) == FALSE)
	{
		MessageBox("Edit box of Plain contains invalid char.");
		m_Plain.Format("");
	}
	m_Len_Plain = m_Plain.GetLength() / 2;

	UpdateData(FALSE);
}

BOOL CCryptoAlgAes::CheckHexString(CString strHexString)
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


void CCryptoAlgAes::OnEnChangeEdit1()
{

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (CheckHexString(m_Key) == FALSE)
	{
		MessageBox("Edit box of Key contains invalid char.");
		m_Key.Format("");
	}
	m_Len_Key = m_Key.GetLength() / 2;

	UpdateData(FALSE);
}


void CCryptoAlgAes::OnEnChangeEdit2()
{
	// TODO:  IV
	UpdateData(TRUE);
	if (CheckHexString(m_IV) == FALSE)
	{
		MessageBox("Edit box of IV contains invalid char.");
		m_IV.Format("");
	}
	m_Len_IV = m_IV.GetLength() / 2;

	UpdateData(FALSE);
}


void CCryptoAlgAes::OnEnChangeEdit4()
{
	// TODO:  Cipher
	UpdateData(TRUE);
	if (CheckHexString(m_Cipher) == FALSE)
	{
		MessageBox("Edit box of Cipher contains invalid char.");
		m_Cipher.Format("");
	}
	m_Len_Cipher = m_Cipher.GetLength() / 2;

	UpdateData(FALSE);
}


void CCryptoAlgAes::OnBnClickedButton3()
{
	// TODO: Add padding
	int len = 0;
	CString prefix = "0";
	unsigned char* buf = (unsigned char*)malloc(m_Len_Plain * 2 + 2);
	unsigned char* buf_padded = (unsigned char*)malloc(m_Len_Plain * 2 + 2 + 16 * 2);//最多padding 2个分组长度
	char* str_padded = (char*)malloc(m_Len_Plain * 2 + 4 + 16 * 2 * 2);//最多padding 2个分组长度
	memset(buf, 0, m_Len_Plain * 2 + 2);
	memset(buf_padded, 0, m_Len_Plain * 2 + 2 + 16);
	memset(str_padded, 0, m_Len_Plain * 2 + 4 + 16 * 2 * 2);
	UpdateData(TRUE);
	if (m_Plain.GetLength() != m_Len_Plain * 2)
	{
		m_Plain = prefix + m_Plain;
	}
	zy_string2hex(buf, m_Plain.GetBuffer(), m_Plain.GetLength());
	if (m_Padding.GetCurSel() == 0) //No padding
	{
		goto EXIT;
	}
	else if (m_Padding.GetCurSel() == 1) // iso9797_m1
	{
		zy_padding_iso9797_m1(PADDING_ADD, 16, buf, m_Plain.GetLength() / 2, buf_padded, &len);
	}
	else if (m_Padding.GetCurSel() == 2) // iso9797_m2
	{
		zy_padding_iso9797_m2(PADDING_ADD, 16, buf, m_Plain.GetLength() / 2, buf_padded, &len);
	}
	else if (m_Padding.GetCurSel() == 3) // iso9797_m3
	{
		zy_padding_iso9797_m3(PADDING_ADD, 16, buf, m_Plain.GetLength() / 2, buf_padded, &len);
	}
	else if (m_Padding.GetCurSel() == 4) // iso9797_m4
	{
		zy_padding_iso9797_m4(PADDING_ADD, 16, buf, m_Plain.GetLength() / 2, buf_padded, &len);
	}
	zy_hex2string(str_padded, buf_padded, len);
	m_Plain.Format("%s", str_padded);

EXIT:
	m_Len_Plain = m_Plain.GetLength() / 2;
	UpdateData(FALSE);
	free(buf);
	free(buf_padded);
	free(str_padded);
}


void CCryptoAlgAes::OnBnClickedButton2()
{
	// TODO: Remove padding
	int len = 0;
	CString prefix = "0";
	unsigned char* buf = (unsigned char*)malloc(m_Len_Plain * 2 + 2);
	unsigned char* buf_padded = (unsigned char*)malloc(m_Len_Plain * 2 + 2 + 16 * 2);//最多padding 2个分组长度
	char* str_padded = (char*)malloc(m_Len_Plain * 2 + 4 + 16 * 2 * 2);//最多padding 2个分组长度
	memset(buf, 0, m_Len_Plain * 2 + 2);
	memset(buf_padded, 0, m_Len_Plain * 2 + 2 + 16);
	memset(str_padded, 0, m_Len_Plain * 2 + 4 + 16 * 2 * 2);
	UpdateData(TRUE);
	if (m_Plain.GetLength() != m_Len_Plain * 2)
	{
		m_Plain = prefix + m_Plain;
	}
	zy_string2hex(buf, m_Plain.GetBuffer(), m_Plain.GetLength());
	if (m_Padding.GetCurSel() == 0) //No padding
	{
		goto EXIT;
	}
	else if (m_Padding.GetCurSel() == 1) // iso9797_m1
	{
		zy_padding_iso9797_m1(PADDING_REMOVE, 16, buf, m_Plain.GetLength() / 2, buf_padded, &len);
	}
	else if (m_Padding.GetCurSel() == 2) // iso9797_m2
	{
		zy_padding_iso9797_m2(PADDING_REMOVE, 16, buf, m_Plain.GetLength() / 2, buf_padded, &len);
	}
	else if (m_Padding.GetCurSel() == 3) // iso9797_m3
	{
		zy_padding_iso9797_m3(PADDING_REMOVE, 16, buf, m_Plain.GetLength() / 2, buf_padded, &len);
	}
	else if (m_Padding.GetCurSel() == 4) // iso9797_m4
	{
		zy_padding_iso9797_m4(PADDING_REMOVE, 16, buf, m_Plain.GetLength() / 2, buf_padded, &len);
	}
	zy_hex2string(str_padded, buf_padded, len);
	m_Plain.Format("%s", str_padded);
	OnEnChangeEdit4(); 

EXIT:
	m_Len_Plain = m_Plain.GetLength() / 2;
	UpdateData(FALSE);
	free(buf);
	free(buf_padded);
	free(str_padded);
}





void CCryptoAlgAes::OnBnClickedButton4()
{
	//AES Encrypt
	int ret;
	int keybits = 128;
	size_t iv_off = 0;
	unsigned char ucKey[32] = { 0 };
	unsigned char iv[16] = { 0 };
	unsigned char stream_block[16] = { 0 };
	char* pcCipher = NULL;
	unsigned char* pucInput = NULL;
	unsigned char* pucOutput = NULL;
	mbedtls_aes_context ctx;
	mbedtls_aes_xts_context xts_ctx;
	mbedtls_aes_init(&ctx);
	mbedtls_aes_xts_init(&xts_ctx);
	UpdateData(TRUE);
	
	if (m_KeyLength.GetCurSel() == 0) //128bit
	{
		if (m_Len_Key != 16)
		{
			g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"AES key length is incorrect.");
			goto EXIT;
		}
		if (m_Len_IV != 16)
		{
			g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"Initialization vector length is incorrect.");
			goto EXIT;
		}
		keybits = 128;
	}
	else if (m_KeyLength.GetCurSel() == 1) //192bit
	{
		if (m_Len_Key != 24)
		{
			g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"AES key length is incorrect.");
			goto EXIT;
		}
		if (m_Len_IV != 16)
		{
			g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"Initialization vector length is incorrect.");
			goto EXIT;
		}
		keybits = 192;
	}
	else if (m_KeyLength.GetCurSel() == 2) //256bit
	{
		if (m_Len_Key != 32)
		{
			g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"AES key length is incorrect.");
			goto EXIT;
		}
		if (m_Len_IV != 16)
		{
			g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"Initialization vector length is incorrect.");
			goto EXIT;
		}
		keybits = 256;
	}

	zy_string2hex(ucKey, m_Key.GetBuffer(), m_Key.GetLength());
	ret = mbedtls_aes_setkey_enc(&ctx, ucKey, keybits);
	if (ret != 0)
	{
		g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"Set AES key failed.");
		goto EXIT;
	}

	pucInput = (unsigned char*)malloc(m_Len_Plain);
	pucOutput = (unsigned char*)malloc(m_Len_Plain);
	pcCipher = (char*)malloc(m_Len_Plain * 2 + 1);
	memset(pucInput, 0, m_Len_Plain);
	memset(pucOutput, 0, m_Len_Plain);
	memset(pcCipher, 0, m_Len_Plain * 2 + 1);

	if (m_Mode.GetCurSel() == 0) //ECB
	{
		if (m_Len_Plain != 16)
		{
			g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"Plaintext length must be 16.");
			goto EXIT;
		}
		zy_string2hex(pucInput, m_Plain.GetBuffer(), m_Plain.GetLength());
		ret = mbedtls_aes_crypt_ecb(&ctx, MBEDTLS_AES_ENCRYPT, pucInput, pucOutput);
	}
	else if (m_Mode.GetCurSel() == 1) //CBC
	{
		if (m_Len_Plain % 16 != 0)
		{
			g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"Plaintext length must be multiple of the block size(16 bytes).You can push 'Add Padding' button or manual add padding.");
			goto EXIT;
		}
		if (m_Len_IV != 16)
		{
			g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"Initialization vector length must be 16 bytes.");
			goto EXIT;
		}
		
		zy_string2hex(pucInput, m_Plain.GetBuffer(), m_Plain.GetLength());
		zy_string2hex(iv, m_IV.GetBuffer(), m_IV.GetLength());
		ret = mbedtls_aes_crypt_cbc(&ctx, MBEDTLS_AES_ENCRYPT, m_Len_Plain, iv, pucInput, pucOutput);
	}
	else if (m_Mode.GetCurSel() == 2) //CFB
	{
		if (m_Len_IV != 16)
		{
			g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"Initialization vector length must be 16 bytes.");
			goto EXIT;
		}
		zy_string2hex(pucInput, m_Plain.GetBuffer(), m_Plain.GetLength());
		zy_string2hex(iv, m_IV.GetBuffer(), m_IV.GetLength());
		ret = mbedtls_aes_crypt_cfb128(&ctx, MBEDTLS_AES_ENCRYPT, m_Len_Plain, &iv_off, iv, pucInput, pucOutput);
	}
	else if (m_Mode.GetCurSel() == 3) //OFB
	{
		if (m_Len_IV != 16)
		{
			g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"Initialization vector length must be 16 bytes.");
			goto EXIT;
		}
		zy_string2hex(pucInput, m_Plain.GetBuffer(), m_Plain.GetLength());
		zy_string2hex(iv, m_IV.GetBuffer(), m_IV.GetLength());
		ret = mbedtls_aes_crypt_ofb(&ctx, m_Len_Plain, &iv_off, iv, pucInput, pucOutput);
	}
	else if (m_Mode.GetCurSel() == 4) //CTR
	{
		if (m_Len_IV != 16)
		{
			g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"Nonce counter(IV) length must be 16 bytes.");
			goto EXIT;
		}
		zy_string2hex(pucInput, m_Plain.GetBuffer(), m_Plain.GetLength());
		zy_string2hex(iv, m_IV.GetBuffer(), m_IV.GetLength());
		//这里用iv保存nonce,iv_off=0
		ret = mbedtls_aes_crypt_ctr(&ctx, m_Len_Plain, &iv_off, iv, stream_block, pucInput, pucOutput);
	}
	else if (m_Mode.GetCurSel() == 5) //XTS
	{
		if (m_Len_IV != 16)
		{
			g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"Address of data unit(IV) length must be 16 bytes.");
			goto EXIT;
		}
		//这里用iv保存
		ret = mbedtls_aes_xts_setkey_enc(&xts_ctx, ucKey, keybits);
		if (ret != 0)
		{
			g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"Set AES XEX key failed.");
			goto EXIT;
		}
		zy_string2hex(pucInput, m_Plain.GetBuffer(), m_Plain.GetLength());
		zy_string2hex(iv, m_IV.GetBuffer(), m_IV.GetLength());
		ret = mbedtls_aes_crypt_xts(&xts_ctx, MBEDTLS_AES_ENCRYPT, m_Len_Plain, iv, pucInput, pucOutput);
	}

	if (ret != 0)
	{
		g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"AES encrypt failed.");
		goto EXIT;
	}
	zy_hex2string(pcCipher, pucOutput, m_Len_Plain);
	m_Cipher.Format("%s", pcCipher);
	m_Len_Cipher = m_Cipher.GetLength() / 2;

EXIT:
	UpdateData(FALSE);
	mbedtls_aes_free(&ctx);
	mbedtls_aes_xts_free(&xts_ctx);
	free(pucInput);
	free(pucOutput);
	free(pcCipher);
}


void CCryptoAlgAes::OnBnClickedButton1()
{
	// AES Decrypt
	int ret;
	int keybits = 128;
	size_t iv_off = 0;
	unsigned char ucKey[32] = { 0 };
	unsigned char iv[16] = { 0 };
	unsigned char stream_block[16] = { 0 };
	char* pcPlain = NULL;
	unsigned char* pucInput = NULL;
	unsigned char* pucOutput = NULL;
	mbedtls_aes_context ctx;
	mbedtls_aes_xts_context xts_ctx;
	mbedtls_aes_init(&ctx);
	mbedtls_aes_xts_init(&xts_ctx);
	UpdateData(TRUE);
	if (m_KeyLength.GetCurSel() == 0) //128bit
	{
		if (m_Len_Key != 16)
		{
			g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"AES key length is incorrect.");
			goto EXIT;
		}
		if (m_Len_IV != 16)
		{
			g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"Initialization vector length is incorrect.");
			goto EXIT;
		}
		keybits = 128;
	}
	else if (m_KeyLength.GetCurSel() == 1) //192bit
	{
		if (m_Len_Key != 24)
		{
			g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"AES key length is incorrect.");
			goto EXIT;
		}
		if (m_Len_IV != 16)
		{
			g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"Initialization vector length is incorrect.");
			goto EXIT;
		}
		keybits = 192;
	}
	else if (m_KeyLength.GetCurSel() == 2) //256bit
	{
		if (m_Len_Key != 32)
		{
			g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"AES key length is incorrect.");
			goto EXIT;
		}
		if (m_Len_IV != 16)
		{
			g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"Initialization vector length is incorrect.");
			goto EXIT;
		}
		keybits = 256;
	}

	zy_string2hex(ucKey, m_Key.GetBuffer(), m_Key.GetLength());
	ret = mbedtls_aes_setkey_dec(&ctx, ucKey, keybits);
	if (ret != 0)
	{
		g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"Set AES key failed.");
		goto EXIT;
	}

	pucInput = (unsigned char*)malloc(m_Len_Cipher);
	pucOutput = (unsigned char*)malloc(m_Len_Cipher);
	pcPlain = (char*)malloc(m_Len_Cipher * 2 + 1);
	memset(pucInput, 0, m_Len_Cipher);
	memset(pucOutput, 0, m_Len_Cipher);
	memset(pcPlain, 0, m_Len_Cipher * 2 + 1);

	if (ret != 0)
	{
		g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"Set AES key failed.");
		goto EXIT;
	}

	if (m_Mode.GetCurSel() == 0) //ECB
	{
		if (m_Len_Cipher != 16)
		{
			g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"Ciphertext length must be 16.");
			goto EXIT;
		}
		zy_string2hex(pucInput, m_Cipher.GetBuffer(), m_Cipher.GetLength());
		ret = mbedtls_aes_crypt_ecb(&ctx, MBEDTLS_AES_DECRYPT, pucInput, pucOutput);
	}
	else if (m_Mode.GetCurSel() == 1) //CBC
	{
		if (m_Len_Cipher % 16 != 0)
		{
			g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"Ciphertext length must be multiple of the block size(16 bytes).You can push 'Add Padding' button or manual add padding.");
			goto EXIT;
		}
		if (m_Len_IV != 16)
		{
			g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"Initialization vector length must be 16 bytes.");
			goto EXIT;
		}

		zy_string2hex(pucInput, m_Cipher.GetBuffer(), m_Cipher.GetLength());
		zy_string2hex(iv, m_IV.GetBuffer(), m_IV.GetLength());
		ret = mbedtls_aes_crypt_cbc(&ctx, MBEDTLS_AES_DECRYPT, m_Len_Cipher, iv, pucInput, pucOutput);
	}
	else if (m_Mode.GetCurSel() == 2) //CFB
	{
		if (m_Len_IV != 16)
		{
			g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"Initialization vector length must be 16 bytes.");
			goto EXIT;
		}
		zy_string2hex(pucInput, m_Cipher.GetBuffer(), m_Cipher.GetLength());
		zy_string2hex(iv, m_IV.GetBuffer(), m_IV.GetLength());
		ret = mbedtls_aes_crypt_cfb128(&ctx, MBEDTLS_AES_DECRYPT, m_Len_Cipher, &iv_off, iv, pucInput, pucOutput);
	}
	else if (m_Mode.GetCurSel() == 3) //OFB
	{
		if (m_Len_IV != 16)
		{
			g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"Initialization vector length must be 16 bytes.");
			goto EXIT;
		}
		ret = mbedtls_aes_setkey_enc(&ctx, ucKey, keybits);
		if (ret != 0)
		{
			g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"Set AES key failed.");
			goto EXIT;
		}
		zy_string2hex(pucInput, m_Cipher.GetBuffer(), m_Cipher.GetLength());
		zy_string2hex(iv, m_IV.GetBuffer(), m_IV.GetLength());
		ret = mbedtls_aes_crypt_ofb(&ctx, m_Len_Cipher, &iv_off, iv, pucInput, pucOutput);
	}
	else if (m_Mode.GetCurSel() == 4) //CTR
	{
		if (m_Len_IV != 16)
		{
			g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"Nonce counter(IV) length must be 16 bytes.");
			goto EXIT;
		}
		zy_string2hex(pucInput, m_Cipher.GetBuffer(), m_Cipher.GetLength());
		zy_string2hex(iv, m_IV.GetBuffer(), m_IV.GetLength());
		//这里用iv保存nonce,iv_off=0
		ret = mbedtls_aes_crypt_ctr(&ctx, m_Len_Cipher, &iv_off, iv, stream_block, pucInput, pucOutput);
	}
	else if (m_Mode.GetCurSel() == 5) //XTS
	{
		if (m_Len_IV != 16)
		{
			g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"Address of data unit(IV) length must be 16 bytes.");
			goto EXIT;
		}
		//这里用iv保存
		ret = mbedtls_aes_xts_setkey_dec(&xts_ctx, ucKey, keybits);
		if (ret != 0)
		{
			g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"Set AES XEX key failed.");
			goto EXIT;
		}
		zy_string2hex(pucInput, m_Cipher.GetBuffer(), m_Cipher.GetLength());
		zy_string2hex(iv, m_IV.GetBuffer(), m_IV.GetLength());
		ret = mbedtls_aes_crypt_xts(&xts_ctx, MBEDTLS_AES_ENCRYPT, m_Len_Cipher, iv, pucInput, pucOutput);
	}

	if (ret != 0)
	{
		g_MainFrame->PostMessageA(WM_SHOWLOG_MESSAGE, 1, (LPARAM)"AES decrypt failed.");
		goto EXIT;
	}
	zy_hex2string(pcPlain, pucOutput, m_Len_Cipher);
	m_Plain.Format("%s", pcPlain);
	m_Len_Plain = m_Plain.GetLength() / 2;
EXIT:
	UpdateData(FALSE);
	mbedtls_aes_free(&ctx);
	mbedtls_aes_xts_free(&xts_ctx);
	free(pucInput);
	free(pucOutput);
	free(pcPlain);

}
