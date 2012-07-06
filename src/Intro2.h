/**************************************************************************
*                                                                         *
* Class          Intro2                                                   *
*                                                                         *
* Author:        Matthew Bazar                                            *
*                                                                         *
* Description:   Interface of the Intro2 class.                           *
*                                                                         *
* Modifications: Matthew Bazar     12-08-99 Created                       *
**************************************************************************/
#if !defined(AFX_INTRO2_H__E8C94A88_AD3B_11D3_B3B4_00C04F29AEA5__INCLUDED_)
#define AFX_INTRO2_H__E8C94A88_AD3B_11D3_B3B4_00C04F29AEA5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// Intro2 dialog                                                           //
/////////////////////////////////////////////////////////////////////////////
class Intro2 : public CDialog
{
// Construction
public:
	Intro2(CWnd* pParent = NULL);
// Dialog Data
	//{{AFX_DATA(Intro2)
	enum { IDD = IDD_INTRO2 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Intro2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(Intro2)
	afx_msg void OnIntro2Next();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTRO2_H__E8C94A88_AD3B_11D3_B3B4_00C04F29AEA5__INCLUDED_)
