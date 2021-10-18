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

#pragma once

#include "OutputBar.h"
#include "CryptoToolDoc.h"
#include "CryptoToolView.h"

class CMainFrame : public CFrameWndEx
{

protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

	// Attributes
public:

	// Operations
public:

	// Overrides
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void CreateDocumentColors();

	void Add_MainPanel();
	void Add_QAT();

	void OnLink(UINT nID);



protected:  // control bar embedded members
	CMFCRibbonBar			m_wndRibbonBar;
	CMFCRibbonApplicationButton	m_MainButton;
	CMFCToolBarImages		m_PanelImages;
	CMFCRibbonStatusBar	m_wndStatusBar;
	COutputBar				m_wndOutput;

	// Document colors for demo:
	CList<COLORREF, COLORREF> m_lstMainColors;
	CList<COLORREF, COLORREF> m_lstAdditionalColors;
	CList<COLORREF, COLORREF> m_lstStandardColors;



protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnAppLook(UINT id);
	afx_msg void OnUpdateAppLook(CCmdUI* pCmdUI);
	afx_msg LRESULT OnChangeRibbonCategory(WPARAM, LPARAM);
	void SwitchPage(int nPageId);

	DECLARE_MESSAGE_MAP()

	BOOL CreateRibbonBar();

	UINT	m_nAppLook;
public:
	afx_msg void OnRibbonBtnCryptoAlgAES();
	afx_msg void OnRibbonBtnCryptoAlgDES();
};
