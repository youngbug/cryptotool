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
	//获得CDialog尺寸


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

	//当前客户区，不含滚动条的尺寸
	CRect rcClient;
	GetClientRect(rcClient);

	//如果当前有垂直/水平滚动条 客户区宽度/高度加上垂直/水平滚动条
	if ((GetStyle() & WS_VSCROLL) == WS_VSCROLL) rcClient.right += nCxVscroll;
	if ((GetStyle() & WS_HSCROLL) == WS_HSCROLL) rcClient.bottom += nCyHscroll;

	//是否需要添加垂直滚动条
	BOOL bVscrollAdd = nLengthNeed > rcClient.Height();

	if (bVscrollAdd)
	{
		rcClient.right -= nCxVscroll; //客户区宽度减去垂直滚动条
	}
	//是否需要添加水平滚动条
	BOOL bHscrollAdd = nWidthNeed > rcClient.Width();

	if (bHscrollAdd)
	{
		rcClient.bottom -= nCyHscroll;//客户区高度减去水平滚动条
	}
	//更新水平滚动条后，再计算下是不是需要垂直滚动条
	if (bHscrollAdd && !bVscrollAdd)
	{
		bVscrollAdd = nLengthNeed > rcClient.Height();
		if (bVscrollAdd)
		{
			rcClient.right -= nCxVscroll;
		}
	}
	//更新垂直滚动条后再看看是不是需要水平滚动条
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
	//更新垂直滚动条
	scinfo.nMax = max(0, nLengthNeed - rcClient.Height());
	scinfo.nPage = scinfo.nMax * rcClient.Height() / nLengthNeed;
	SetScrollInfo(SB_VERT, &scinfo);
	//更新水平滚动条
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
	//初始化之后当前选中页面在Aes
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

	UpdateScrollInfo(rt.Width(), rt.Height());//窗口重绘时，刷新滚动条
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if ((GetStyle() & WS_VSCROLL) == WS_VSCROLL)
	{
		SCROLLINFO scinfo = { 0 };
		int nPosMax, nWndPosOld, nWndPosNew;
		scinfo.cbSize = sizeof(SCROLLINFO);
		GetScrollInfo(SB_VERT, &scinfo, SIF_ALL);

		nPosMax = scinfo.nMax - (int)scinfo.nPage;	//滚动条最大滚动位置

		nWndPosOld = scinfo.nPos * scinfo.nMax / nPosMax; //旧窗口位置 根据nMax nPage nPos计算

		switch (nSBCode)
		{
		case SB_TOP:		scinfo.nPos = 0;				break;
		case SB_BOTTOM:		scinfo.nPos = nPosMax;			break;
		case SB_LINEUP:		scinfo.nPos -= nPosMax / 5;		break;//点箭头5次结束
		case SB_LINEDOWN:	scinfo.nPos += nPosMax / 5;		break;
		case SB_PAGEUP:		scinfo.nPos -= nPosMax / 2;		break;//点滑块外空白2次结束
		case SB_PAGEDOWN:	scinfo.nPos += nPosMax / 2;		break;
		case SB_THUMBTRACK: scinfo.nPos = nPos;				break;//直接拖动滑块
		default:
			break;
		}
		//移动滚动条
		scinfo.fMask = SIF_POS;
		scinfo.nPos = min(max(scinfo.nPos, 0), nPosMax);
		SetScrollInfo(SB_VERT, &scinfo);

		nWndPosNew = scinfo.nPos * scinfo.nMax / nPosMax; //新窗口位置

		ScrollWindow(0, nWndPosOld - nWndPosNew);//滚动窗体

	}
	CView::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CCryptoToolView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 水平滚动条
	if ((GetStyle() & WS_HSCROLL) == WS_HSCROLL)
	{
		SCROLLINFO scinfo = { 0 };
		int nPosMax, nWndPosOld, nWndPosNew;
		scinfo.cbSize = sizeof(SCROLLINFO);
		GetScrollInfo(SB_HORZ, &scinfo, SIF_ALL);

		nPosMax = scinfo.nMax - (int)scinfo.nPage;	//滚动条最大滚动位置

		nWndPosOld = scinfo.nPos * scinfo.nMax / nPosMax; //旧窗口位置 根据nMax nPage nPos计算

		switch (nSBCode)
		{
		case SB_LEFT:		scinfo.nPos = 0;				break;
		case SB_RIGHT:		scinfo.nPos = nPosMax;			break;
		case SB_LINELEFT:	scinfo.nPos -= nPosMax / 5;		break;//点箭头5次结束
		case SB_LINERIGHT:	scinfo.nPos += nPosMax / 5;		break;
		case SB_PAGELEFT:		scinfo.nPos -= nPosMax / 2;		break;//点滑块外空白2次结束
		case SB_PAGERIGHT:	scinfo.nPos += nPosMax / 2;		break;
		case SB_THUMBTRACK: scinfo.nPos = nPos;				break;//直接拖动滑块
		default:
			break;
		}
		//移动滚动条
		scinfo.fMask = SIF_POS;
		scinfo.nPos = min(max(scinfo.nPos, 0), nPosMax);
		SetScrollInfo(SB_HORZ, &scinfo);

		nWndPosNew = scinfo.nPos * scinfo.nMax / nPosMax; //新窗口位置

		ScrollWindow(nWndPosOld - nWndPosNew, 0);//滚动窗体

	}

	CView::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CCryptoToolView::SelectPage(int nPageId)
{
	SwitchPage(nPageId);
}
