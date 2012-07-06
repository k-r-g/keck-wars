/**************************************************************************
*                                                                         *
* Class          Intro3                                                   *
*                                                                         *
* Author:        Matthew Bazar                                            *
*                                                                         *
* Description:   Interface of the Intro3 class.                           *
*                                                                         *
* Modifications: Matthew Bazar     12-08-99 Created                       *
**************************************************************************/
#if !defined(AFX_INTRO3_H__E8C94A89_AD3B_11D3_B3B4_00C04F29AEA5__INCLUDED_)
#define AFX_INTRO3_H__E8C94A89_AD3B_11D3_B3B4_00C04F29AEA5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/////////////////////////////////////////////////////////////////////////////
// Intro3 dialog
/////////////////////////////////////////////////////////////////////////////
class Intro3 : public CDialog
{
// Construction
public:
	Intro3(CWnd* pParent = NULL);
// Dialog Data
	//{{AFX_DATA(Intro3)
	enum { IDD = IDD_INTRO3 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Intro3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(Intro3)
	afx_msg void OnIntro3Next();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTRO3_H__E8C94A89_AD3B_11D3_B3B4_00C04F29AEA5__INCLUDED_)
