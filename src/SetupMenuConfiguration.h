/**************************************************************************
*                                                                         *
* Class          CSetupMenuConfigurationApp                               *
*                                                                         *
* Author:        Matthew Bazar                                            *
*                                                                         *
* Description:   Interface of the CSetupMenuConfigurationApp class.       *
*                Main header file for SETUPMENUCONFIGURATION application. *
*                                                                         *
*                                                                         *
* Modifications: Matthew Bazar     11-10-99 ALPHA PRESENTATION            *
**************************************************************************/
#if !defined(AFX_SETUPMENUCONFIGURATION_H__14BE77C5_90F3_11D3_B3AE_00C04F29AE50__INCLUDED_)
#define AFX_SETUPMENUCONFIGURATION_H__14BE77C5_90F3_11D3_B3AE_00C04F29AE50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSetupMenuConfigurationApp:                                             //
// See SetupMenuConfiguration.cpp for the implementation of this class     //
/////////////////////////////////////////////////////////////////////////////
class CSetupMenuConfigurationApp : public CWinApp
{
public:

	CSetupMenuConfigurationApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetupMenuConfigurationApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSetupMenuConfigurationApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETUPMENUCONFIGURATION_H__14BE77C5_90F3_11D3_B3AE_00C04F29AE50__INCLUDED_)
