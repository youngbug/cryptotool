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

#include "MainFrm.h"
#include "cryptotool_cfg.h"


#include <memory>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CMainFrame* g_MainFrame = NULL; //全局指针

const int IdShowProgress1Timer = 1;
const int IdShowProgress2Timer = 2;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)


BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_2007, ID_VIEW_APPLOOK_2007_3, OnAppLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_2007, ID_VIEW_APPLOOK_2007_3, OnUpdateAppLook)
	ON_REGISTERED_MESSAGE(AFX_WM_ON_CHANGE_RIBBON_CATEGORY, OnChangeRibbonCategory)

	//处理显示日志消息
	ON_MESSAGE(WM_SHOWLOG_MESSAGE, OnShowLogMessage)

	ON_COMMAND(ID_RIBBON_BTN_1, &CMainFrame::OnRibbonBtnCryptoAlgAES)
	ON_COMMAND(ID_BUTTON4, &CMainFrame::OnRibbonBtnCryptoAlgDES)
	ON_COMMAND(ID_RIBBON_BTN_3, &CMainFrame::OnRibbonBtnCryptoAlgSM4)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_2007);
}

void CMainFrame::CreateDocumentColors()
{
	typedef struct
	{
		COLORREF	color;
		TCHAR* szName;
	}
	ColorTableEntry;

	int i = 0;
	int nNumColours = 0;

	static ColorTableEntry colorsMain[] =
	{
		{	RGB(255, 255, 255),	_T("White, Background 1")	},
		{	RGB(0, 0, 0),			_T("Black, Text 1")			},
		{	RGB(238, 236, 225),	_T("Tan, Background 2")		},
		{	RGB(31, 73, 125),		_T("Dark Blue, Text 2")		},
		{	RGB(79, 129, 189),		_T("Blue, Accent 1")		},
		{	RGB(192, 80, 77),		_T("Red, Accent 2")			},
		{	RGB(155, 187, 89),		_T("Olive Green, Accent 3")	},
		{	RGB(128, 100, 162),	_T("Purple, Accent 4")		},
		{	RGB(75, 172, 198),		_T("Aqua, Accent 5")		},
		{	RGB(245, 150, 70),		_T("Orange, Accent 6")		}
	};

	static ColorTableEntry colorsAdditional[] =
	{
		{	RGB(242, 242, 242),	_T("White, Background 1, Darker 5%")	},
		{	RGB(127, 127, 127),	_T("Black, Text 1, Lighter 50%")		},
		{	RGB(214, 212, 202),	_T("Tan, Background 2, Darker 10%")		},
		{	RGB(210, 218, 229),	_T("Dark Blue, Text 2, Lighter 80%")	},
		{	RGB(217, 228, 240),	_T("Blue, Accent 1, Lighter 80%")		},
		{	RGB(244, 219, 218),	_T("Red, Accent 2, Lighter 80%")		},
		{	RGB(234, 241, 221),	_T("Olive Green, Accent 3, Lighter 80%")},
		{	RGB(229, 223, 235),	_T("Purple, Accent 4, Lighter 80%")		},
		{	RGB(216, 237, 242),	_T("Aqua, Accent 5, Lighter 80%")		},
		{	RGB(255, 234, 218),	_T("Orange, Accent 6, Lighter 80%")		},

		{	RGB(215, 215, 215),	_T("White, Background 1, Darker 15%")	},
		{	RGB(89, 89, 89),		_T("Black, Text 1, Lighter 35%")		},
		{	RGB(177, 176, 167),	_T("Tan, Background 2, Darker 25%")		},
		{	RGB(161, 180, 201),	_T("Dark Blue, Text 2, Lighter 60%")	},
		{	RGB(179, 202, 226),	_T("Blue, Accent 1, Lighter 60%")		},
		{	RGB(233, 184, 182),	_T("Red, Accent 2, Lighter 60%")		},
		{	RGB(213, 226, 188),	_T("Olive Green, Accent 3, Lighter 60%")},
		{	RGB(203, 191, 215),	_T("Purple, Accent 4, Lighter 60%")		},
		{	RGB(176, 220, 231),	_T("Aqua, Accent 5, Lighter 60%")		},
		{	RGB(255, 212, 181),	_T("Orange, Accent 6, Lighter 60%")		},

		{	RGB(190, 190, 190),	_T("White, Background 1, Darker 25%")	},
		{	RGB(65, 65, 65),		_T("Black, Text 1, Lighter 25%")		},
		{	RGB(118, 117, 112),	_T("Tan, Background 2, Darker 35%")		},
		{	RGB(115, 143, 175),	_T("Dark Blue, Text 2, Lighter 40%")	},
		{	RGB(143, 177, 213),	_T("Blue, Accent 1, Lighter 40%")		},
		{	RGB(222, 149, 147),	_T("Red, Accent 2, Lighter 40%")		},
		{	RGB(192, 213, 155),	_T("Olive Green, Accent 3, Lighter 40%")},
		{	RGB(177, 160, 197),	_T("Purple, Accent 4, Lighter 40%")		},
		{	RGB(137, 203, 218),	_T("Aqua, Accent 5, Lighter 40%")		},
		{	RGB(255, 191, 145),	_T("Orange, Accent 6, Lighter 40%")		},

		{	RGB(163, 163, 163),	_T("White, Background 1, Darker 35%")	},
		{	RGB(42, 42, 42),		_T("Black, Text 1, Lighter 15%")		},
		{	RGB(61, 61, 59),		_T("Tan, Background 2, Darker 50%")		},
		{	RGB(20, 57, 92),		_T("Dark Blue, Text 2, Darker 25%")		},
		{	RGB(54, 96, 139),		_T("Blue, Accent 1, Darker 25%")		},
		{	RGB(149, 63, 60),		_T("Red, Accent 2, Darker 25%")			},
		{	RGB(114, 139, 71),		_T("Olive Green, Accent 3, Darker 25%")	},
		{	RGB(97, 76, 119),		_T("Purple, Accent 4, Darker 25%")		},
		{	RGB(41, 128, 146),		_T("Aqua, Accent 5, Darker 25%")		},
		{	RGB(190, 112, 59),		_T("Orange, Accent 6, Darker 25%")		},

		{	RGB(126, 126, 126),	_T("White, Background 1, Darker 50%")	},
		{	RGB(20, 20, 20),		_T("Black, Text 1, Lighter 5%")			},
		{	RGB(29, 29, 28),		_T("Tan, Background 2, Darker 90%")		},
		{	RGB(17, 40, 64),		_T("Dark Blue, Text 2, Darker 50%")		},
		{	RGB(38, 66, 94),		_T("Blue, Accent 1, Darker 50%")		},
		{	RGB(100, 44, 43),		_T("Red, Accent 2, Darker 50%")			},
		{	RGB(77, 93, 49),		_T("Olive Green, Accent 3, Darker 50%")	},
		{	RGB(67, 53, 81),		_T("Purple, Accent 4, Darker 50%")		},
		{	RGB(31, 86, 99),		_T("Aqua, Accent 5, Darker 50%")		},
		{	RGB(126, 77, 42),		_T("Orange, Accent 6, Darker 50%")		},
	};

	static ColorTableEntry colorsStandard[] =
	{
		{	RGB(200, 15, 18),		_T("Dark Red")		},
		{	RGB(255, 20, 24),		_T("Red")			},
		{	RGB(255, 191, 40),		_T("Orange")		},
		{	RGB(255, 255, 49),		_T("Yellow")		},
		{	RGB(138, 207, 87),		_T("Light Green")	},
		{	RGB(0, 175, 84),		_T("Green")			},
		{	RGB(0, 174, 238),		_T("Light Blue")	},
		{	RGB(0, 111, 189),		_T("Blue")			},
		{	RGB(0, 36, 95),		_T("Black")			},
		{	RGB(114, 50, 157),		_T("Purple")		},
	};

	m_lstMainColors.RemoveAll();
	nNumColours = sizeof(colorsMain) / sizeof(ColorTableEntry);

	for (i = 0; i < nNumColours; i++)
	{
		m_lstMainColors.AddTail(colorsMain[i].color);
		CMFCRibbonColorButton::SetColorName(colorsMain[i].color, colorsMain[i].szName);
	};

	m_lstAdditionalColors.RemoveAll();
	nNumColours = sizeof(colorsAdditional) / sizeof(ColorTableEntry);

	for (i = 0; i < nNumColours; i++)
	{
		m_lstAdditionalColors.AddTail(colorsAdditional[i].color);
		CMFCRibbonColorButton::SetColorName(colorsAdditional[i].color, colorsAdditional[i].szName);
	};

	m_lstStandardColors.RemoveAll();
	nNumColours = sizeof(colorsStandard) / sizeof(ColorTableEntry);

	for (i = 0; i < nNumColours; i++)
	{
		m_lstStandardColors.AddTail(colorsStandard[i].color);
		CMFCRibbonColorButton::SetColorName(colorsStandard[i].color, colorsStandard[i].szName);
	};
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	OnAppLook(m_nAppLook);

	if (!CreateRibbonBar())
	{
		TRACE0("Failed to create ribbon bar\n");
		return -1;      // fail to create
	}

	//	m_wndRibbonBar.SaveToXMLFile(_T("E:\\Users\\patbr\\Documents\\Visual Studio 10\\Samples\\C++\\MFC\\Visual C++ 2008 Feature Pack\\RibbonGadgets\\res\\RibbonGadgets.mfcribbon-ms"));

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, _T("CryptoTool 加密算法、智能卡、网络安全、数字证书、密码钥匙工具"), TRUE), _T("CyrptoTool"));
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, _T("Author:赵 洋"), TRUE), _T("Author:赵 洋"));

	if (!m_wndOutput.Create(_T("Output"), this, CRect(0, 0, 150, 150),
		TRUE /* Has gripper */, ID_VIEW_OUTPUT,
		WS_CHILD | WS_VISIBLE | CBRS_BOTTOM | CBRS_FLOAT_MULTI,
		AFX_CBRS_REGULAR_TABS, AFX_CBRS_RESIZE | AFX_CBRS_AUTOHIDE))
	{
		TRACE0("Failed to create output bar\n");
		return -1;      // fail to create
	}
	m_wndOutput.AddTab(_T("Log"));
	EnableDocking(CBRS_ALIGN_ANY);
	EnableAutoHidePanes(CBRS_ALIGN_ANY);
	DockPane(&m_wndOutput);

	OnChangeRibbonCategory(0, 0);
	//
	//
	g_MainFrame = this;

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWndEx::PreCreateWindow(cs))
		return FALSE;

	cs.style &= ~FWS_ADDTOTITLE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers



void CMainFrame::OnAppLook(UINT id)
{
	CDockingManager::SetDockingMode(DT_SMART);

	m_nAppLook = id;

	CTabbedPane::m_StyleTabWnd = CMFCTabCtrl::STYLE_3D;

	switch (m_nAppLook)
	{
	case ID_VIEW_APPLOOK_2007:
	case ID_VIEW_APPLOOK_2007_1:
	case ID_VIEW_APPLOOK_2007_2:
	case ID_VIEW_APPLOOK_2007_3:
		// enable Office 2007 look:

		switch (m_nAppLook)
		{
		case ID_VIEW_APPLOOK_2007:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_2007_1:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_2007_2:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_2007_3:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		ASSERT(FALSE);
	}

	CDockingManager* pDockManager = GetDockingManager();
	if (pDockManager != NULL)
	{
		ASSERT_VALID(pDockManager);
		pDockManager->AdjustPaneFrames();
	}

	CTabbedPane::ResetTabs();

	RecalcLayout();
	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), m_nAppLook);
}

void CMainFrame::OnUpdateAppLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(m_nAppLook == pCmdUI->m_nID);
}

BOOL CMainFrame::CreateRibbonBar()
{
	if (!m_wndRibbonBar.Create(this))
	{
		return FALSE;
	}

	// Load panel images:
	m_PanelImages.SetImageSize(CSize(16, 16));
	m_PanelImages.Load(IDB_RIBBON_ICONS);

	if (!m_wndRibbonBar.LoadFromResource(IDR_RIBBON))
	{
		return FALSE;
	}

	return TRUE;
}

void CMainFrame::Add_MainPanel()
{

}

void CMainFrame::Add_QAT()
{
	CMFCRibbonQuickAccessToolBarDefaultState qatState;
	qatState.AddCommand(ID_FILE_NEW);
	qatState.AddCommand(ID_FILE_OPEN, FALSE);
	qatState.AddCommand(ID_FILE_SAVE, FALSE);
	qatState.AddCommand(ID_FILE_SAVE_AS);
	qatState.AddCommand(ID_FILE_PRINT_DIRECT);
	qatState.AddCommand(ID_FILE_PRINT_PREVIEW, FALSE);
	m_wndRibbonBar.SetQuickAccessDefaultState(qatState);
}

void CMainFrame::OnLink(UINT nID)
{
	CArray<CMFCRibbonBaseElement*, CMFCRibbonBaseElement*> ar;
	m_wndRibbonBar.GetElementsByID(nID, ar);

	if (ar.GetSize() >= 1)
	{
		CMFCRibbonLinkCtrl* pLink = DYNAMIC_DOWNCAST(CMFCRibbonLinkCtrl, ar[0]);
		if (pLink != NULL)
		{
			if (!pLink->OpenLink())
			{
				AfxMessageBox(_T("Link clicked."));
			}
		}
	}
}


//选中Ribbon Category发生变化
LRESULT CMainFrame::OnChangeRibbonCategory(WPARAM, LPARAM)
{

	return 0;
}

void CMainFrame::SwitchPage(int nPageId)
{
	CCryptoToolView* m_pwndCryptoToolView = (CCryptoToolView*)this->GetActiveView(); //在CMainFrame获得CCryptoToolView的指针
	m_pwndCryptoToolView->SelectPage(nPageId);
}


void CMainFrame::OnRibbonBtnCryptoAlgAES()
{
	// TODO: 在此添加命令处理程序代码
	SwitchPage(PAGE_CRYPTO_ALG_AES);
	m_wndOutput.InsertLog(_T("AES"));
}


void CMainFrame::OnRibbonBtnCryptoAlgDES()
{
	SwitchPage(PAGE_CRYPTO_ALG_DES);
	m_wndOutput.InsertLog(_T("DES"));
}

LRESULT CMainFrame::OnShowLogMessage(WPARAM wparam, LPARAM lparam)
{
	if (wparam == 1)
	{
		m_wndOutput.InsertLog((LPCTSTR)lparam);
	}
	return 0;
}

void CMainFrame::OnRibbonBtnCryptoAlgSM4()
{
	// TODO: 
	SwitchPage(PAGE_CRYPTO_ALG_SM4);
	m_wndOutput.InsertLog(_T("SM4"));
}
