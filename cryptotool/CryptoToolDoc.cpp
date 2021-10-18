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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRibbonGadgetsDoc

IMPLEMENT_DYNCREATE(CCryptoToolDoc, CDocument)

BEGIN_MESSAGE_MAP(CCryptoToolDoc, CDocument)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRibbonGadgetsDoc construction/destruction

CCryptoToolDoc::CCryptoToolDoc()
	: m_bStartup(TRUE)
{
	// TODO: add one-time construction code here

}

CCryptoToolDoc::~CCryptoToolDoc()
{
}

BOOL CCryptoToolDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CRibbonGadgetsDoc serialization

void CCryptoToolDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// CRibbonGadgetsDoc diagnostics

#ifdef _DEBUG
void CCryptoToolDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCryptoToolDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRibbonGadgetsDoc commands
