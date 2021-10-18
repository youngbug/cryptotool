// CCryptoAlgAes.cpp: 实现文件
//

#include "stdafx.h"
#include "cryptotool.h"
#include "CCryptoAlgAes.h"
#include "afxdialogex.h"
#include "../Library/padding.h"
#include "../Library/dataconvert.h"


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
	else if (m_Padding.GetCurSel() == 3) // 
	{
		goto EXIT;
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
	else if (m_Padding.GetCurSel() == 3) // 
	{
		goto EXIT;
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
