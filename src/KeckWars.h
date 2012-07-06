// KeckWars.h : main header file for the KECKWARS application
//

#if !defined(AFX_KECKWARS_H__98359835_9588_11D3_B390_00C04F29A509__INCLUDED_)
#define AFX_KECKWARS_H__98359835_9588_11D3_B390_00C04F29A509__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CKeckWarsApp:
// See KeckWars.cpp for the implementation of this class
//

class CKeckWarsApp : public CWinApp
{
public:
	CKeckWarsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKeckWarsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CKeckWarsApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KECKWARS_H__98359835_9588_11D3_B390_00C04F29A509__INCLUDED_)
