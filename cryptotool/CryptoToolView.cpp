// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://msdn.microsoft.com/officeui.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

#include "stdafx.h"
#include "CryptoTool.h"

#include "CryptoToolDoc.h"
#include "CryptoToolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const CString strInfo =
_T("This sample illustrates how to create the various Ribbon elements.\r\n")
_T("\"Source Code\" window contains source code for the current ribbon category (tab).\r\n")
_T("Please select a specific tab on the bottom to see the panel source code.\r\n")
_T("You may copy this code into the clipboard, print it or save it in an external file.");

/////////////////////////////////////////////////////////////////////////////
// CRibbonGadgetsView

IMPLEMENT_DYNCREATE(CCryptoToolView, CView)

BEGIN_MESSAGE_MAP(CCryptoToolView, CView)
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_CONTEXTMENU()
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRibbonGadgetsView construction/destruction

CCryptoToolView::CCryptoToolView()
{

}

CCryptoToolView::~CCryptoToolView()
{
}

BOOL CCryptoToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style |= WS_HSCROLL | WS_VSCROLL;

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CRibbonGadgetsView printing

void CCryptoToolView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CCryptoToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}


void CCryptoToolView::OnDestroy()
{
	CView::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CRibbonGadgetsView diagnostics

#ifdef _DEBUG
void CCryptoToolView::AssertValid() const
{
	CView::AssertValid();
}

void CCryptoToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCryptoToolDoc* CCryptoToolView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCryptoToolDoc)));
	return (CCryptoToolDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRibbonGadgetsView message handlers

int CCryptoToolView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	//���CDialog�ߴ�


	InitPage();
	SwitchPage(PAGE_CRYPTO_ALG_AES);
	return 0;
}

HMENU CCryptoToolView::GetContextMenu(WORD, LPOLEOBJECT, CHARRANGE*)
{
	return NULL;
}

void CCryptoToolView::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	theApp.ShowPopupMenu(IDR_EDIT_MENU, point, this);
}

void CCryptoToolView::UpdateScrollInfo(int nWidthNeed, int nLengthNeed)
{
	ASSERT(nWidthNeed > 0);
	ASSERT(nLengthNeed > 0);
	int nCxVscroll = ::GetSystemMetrics(SM_CXVSCROLL);
	int nCyHscroll = ::GetSystemMetrics(SM_CYHSCROLL);

	//��ǰ�ͻ����������������ĳߴ�
	CRect rcClient;
	GetClientRect(rcClient);

	//�����ǰ�д�ֱ/ˮƽ������ �ͻ������/�߶ȼ��ϴ�ֱ/ˮƽ������
	if ((GetStyle() & WS_VSCROLL) == WS_VSCROLL) rcClient.right += nCxVscroll;
	if ((GetStyle() & WS_HSCROLL) == WS_HSCROLL) rcClient.bottom += nCyHscroll;

	//�Ƿ���Ҫ��Ӵ�ֱ������
	BOOL bVscrollAdd = nLengthNeed > rcClient.Height();

	if (bVscrollAdd)
	{
		rcClient.right -= nCxVscroll; //�ͻ�����ȼ�ȥ��ֱ������
	}
	//�Ƿ���Ҫ���ˮƽ������
	BOOL bHscrollAdd = nWidthNeed > rcClient.Width();

	if (bHscrollAdd)
	{
		rcClient.bottom -= nCyHscroll;//�ͻ����߶ȼ�ȥˮƽ������
	}
	//����ˮƽ���������ټ������ǲ�����Ҫ��ֱ������
	if (bHscrollAdd && !bVscrollAdd)
	{
		bVscrollAdd = nLengthNeed > rcClient.Height();
		if (bVscrollAdd)
		{
			rcClient.right -= nCxVscroll;
		}
	}
	//���´�ֱ���������ٿ����ǲ�����Ҫˮƽ������
	if (!bHscrollAdd && bVscrollAdd)
	{
		bHscrollAdd = nWidthNeed > rcClient.Width();
		if (bHscrollAdd)
		{
			rcClient.bottom -= nCyHscroll;
		}
	}

	SCROLLINFO scinfo = { 0 };
	scinfo.cbSize = sizeof(SCROLLINFO);
	scinfo.fMask = SIF_RANGE | SIF_PAGE;
	//���´�ֱ������
	scinfo.nMax = max(0, nLengthNeed - rcClient.Height());
	scinfo.nPage = scinfo.nMax * rcClient.Height() / nLengthNeed;
	SetScrollInfo(SB_VERT, &scinfo);
	//����ˮƽ������
	scinfo.nMax = max(0, nWidthNeed - rcClient.Width());
	scinfo.nPage = scinfo.nMax * rcClient.Width() / nWidthNeed;
	SetScrollInfo(SB_HORZ, &scinfo);
}

void CCryptoToolView::InitPage()
{
	m_DlgCryptoAlgAes.Create(IDD_DLG_CRYPTOALG_AES, this);
	m_DlgCryptoAlgAes.CenterWindow();
	m_DlgCryptoAlgAes.ShowWindow(SW_HIDE);
	//
	m_DlgCryptoAlgDes.Create(IDD_DLG_CRYPTOALG_DES, this);
	m_DlgCryptoAlgDes.CenterWindow();
	m_DlgCryptoAlgDes.ShowWindow(SW_HIDE);
	//
	//��ʼ��֮��ǰѡ��ҳ����Aes
	m_pCurrentPage = &m_DlgCryptoAlgAes;
}

void CCryptoToolView::SwitchPage(int nPageId)
{
	m_pCurrentPage->ShowWindow(SW_HIDE);
	switch (nPageId)
	{
	case PAGE_CRYPTO_ALG_AES:
		m_pCurrentPage = &m_DlgCryptoAlgAes;
		break;
	case PAGE_CRYPTO_ALG_DES:
		m_pCurrentPage = &m_DlgCryptoAlgDes;
		break;
	default:
		break;
	}
	m_pCurrentPage->ShowWindow(SW_SHOW);
	m_pCurrentPage->GetClientRect(&rt);
	UpdateScrollInfo(rt.Width(), rt.Height());
}

void CCryptoToolView::OnDraw(CDC* pDC)
{

	UpdateScrollInfo(rt.Width(), rt.Height());//�����ػ�ʱ��ˢ�¹�����
	/*
	const int iOffset = 20;

	CFont* pFontOld = (CFont*)pDC->SelectStockObject(DEFAULT_GUI_FONT);
	ASSERT(pFontOld != NULL);

	CRect rectClient;
	GetClientRect(&rectClient);

	CRect rectText = rectClient;
	rectText.DeflateRect(iOffset, iOffset);
	pDC->DrawText(strInfo, rectText, DT_CALCRECT | DT_WORDBREAK);

	rectText.OffsetRect((rectClient.Width() - rectText.Width() - 2 * iOffset) / 2,
		(rectClient.Height() - rectText.Height() - 2 * iOffset) / 2);

	CRect rectFrame = rectText;
	rectFrame.InflateRect(iOffset, iOffset);

	pDC->FillSolidRect(rectFrame, ::GetSysColor(COLOR_INFOBK));

	rectFrame.DeflateRect(1, 1);
	pDC->Draw3dRect(rectFrame, ::GetSysColor(COLOR_3DSHADOW),
		::GetSysColor(COLOR_3DLIGHT));

	rectFrame.DeflateRect(2, 2);
	pDC->Draw3dRect(rectFrame, ::GetSysColor(COLOR_3DSHADOW),
		::GetSysColor(COLOR_3DLIGHT));

	pDC->SetTextColor(::GetSysColor(COLOR_INFOTEXT));
	pDC->SetBkMode(TRANSPARENT);

	pDC->DrawText(strInfo, rectText, DT_WORDBREAK);

	pDC->SelectObject(pFontOld);
	*/
}


void CCryptoToolView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if ((GetStyle() & WS_VSCROLL) == WS_VSCROLL)
	{
		SCROLLINFO scinfo = { 0 };
		int nPosMax, nWndPosOld, nWndPosNew;
		scinfo.cbSize = sizeof(SCROLLINFO);
		GetScrollInfo(SB_VERT, &scinfo, SIF_ALL);

		nPosMax = scinfo.nMax - (int)scinfo.nPage;	//������������λ��

		nWndPosOld = scinfo.nPos * scinfo.nMax / nPosMax; //�ɴ���λ�� ����nMax nPage nPos����

		switch (nSBCode)
		{
		case SB_TOP:		scinfo.nPos = 0;				break;
		case SB_BOTTOM:		scinfo.nPos = nPosMax;			break;
		case SB_LINEUP:		scinfo.nPos -= nPosMax / 5;		break;//���ͷ5�ν���
		case SB_LINEDOWN:	scinfo.nPos += nPosMax / 5;		break;
		case SB_PAGEUP:		scinfo.nPos -= nPosMax / 2;		break;//�㻬����հ�2�ν���
		case SB_PAGEDOWN:	scinfo.nPos += nPosMax / 2;		break;
		case SB_THUMBTRACK: scinfo.nPos = nPos;				break;//ֱ���϶�����
		default:
			break;
		}
		//�ƶ�������
		scinfo.fMask = SIF_POS;
		scinfo.nPos = min(max(scinfo.nPos, 0), nPosMax);
		SetScrollInfo(SB_VERT, &scinfo);

		nWndPosNew = scinfo.nPos * scinfo.nMax / nPosMax; //�´���λ��

		ScrollWindow(0, nWndPosOld - nWndPosNew);//��������

	}
	CView::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CCryptoToolView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: ˮƽ������
	if ((GetStyle() & WS_HSCROLL) == WS_HSCROLL)
	{
		SCROLLINFO scinfo = { 0 };
		int nPosMax, nWndPosOld, nWndPosNew;
		scinfo.cbSize = sizeof(SCROLLINFO);
		GetScrollInfo(SB_HORZ, &scinfo, SIF_ALL);

		nPosMax = scinfo.nMax - (int)scinfo.nPage;	//������������λ��

		nWndPosOld = scinfo.nPos * scinfo.nMax / nPosMax; //�ɴ���λ�� ����nMax nPage nPos����

		switch (nSBCode)
		{
		case SB_LEFT:		scinfo.nPos = 0;				break;
		case SB_RIGHT:		scinfo.nPos = nPosMax;			break;
		case SB_LINELEFT:	scinfo.nPos -= nPosMax / 5;		break;//���ͷ5�ν���
		case SB_LINERIGHT:	scinfo.nPos += nPosMax / 5;		break;
		case SB_PAGELEFT:		scinfo.nPos -= nPosMax / 2;		break;//�㻬����հ�2�ν���
		case SB_PAGERIGHT:	scinfo.nPos += nPosMax / 2;		break;
		case SB_THUMBTRACK: scinfo.nPos = nPos;				break;//ֱ���϶�����
		default:
			break;
		}
		//�ƶ�������
		scinfo.fMask = SIF_POS;
		scinfo.nPos = min(max(scinfo.nPos, 0), nPosMax);
		SetScrollInfo(SB_HORZ, &scinfo);

		nWndPosNew = scinfo.nPos * scinfo.nMax / nPosMax; //�´���λ��

		ScrollWindow(nWndPosOld - nWndPosNew, 0);//��������

	}

	CView::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CCryptoToolView::SelectPage(int nPageId)
{
	SwitchPage(nPageId);
}
