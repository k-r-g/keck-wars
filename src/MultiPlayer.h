/**************************************************************************
*                                                                         *
* Class          MultiPlayer                                              *
*                                                                         *
* Author:        Matthew Bazar                                            *
*                                                                         *
* Description:   Interface of the MultiPlayer class.                      *
*                                                                         *
* Modifications: Matthew Bazar     11-10-99 ALPHA PRESENTATION            *
**************************************************************************/
#if !defined(AFX_MULTIPLAYER_H__5AA54E23_927E_11D3_B3A4_00C04F29AE79__INCLUDED_)
#define AFX_MULTIPLAYER_H__5AA54E23_927E_11D3_B3A4_00C04F29AE79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// MultiPlayer dialog                                                      //
/////////////////////////////////////////////////////////////////////////////

class MultiPlayer : public CDialog
{
// Construction
public:
	MultiPlayer(CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(MultiPlayer)
	enum { IDD = IDD_MULTIPLAYER };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MultiPlayer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(MultiPlayer)
	afx_msg void OnMultiBack();
	afx_msg void OnClient();
	afx_msg void OnServer();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTIPLAYER_H__5AA54E23_927E_11D3_B3A4_00C04F29AE79__INCLUDED_)
