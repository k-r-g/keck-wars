/**************************************************************************
*                                                                         *
* Class          StartGame                                                *
*                                                                         *
* Author:        Matthew Bazar                                            *
*                                                                         *
* Description:   Interface of the StartGame class.                        *
*                                                                         *
* Modifications: Matthew Bazar     12-08-99 Created                       *
**************************************************************************/
#if !defined(AFX_STARTGAME_H__2B9ACEF4_A9BF_11D3_B397_00C04F29AE3F__INCLUDED_)
#define AFX_STARTGAME_H__2B9ACEF4_A9BF_11D3_B397_00C04F29AE3F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/////////////////////////////////////////////////////////////////////////////
// StartGame dialog                                                        //
/////////////////////////////////////////////////////////////////////////////
class StartGame : public CDialog
{
// Construction
public:	
	StartGame(CWnd* pParent = NULL);
// Dialog Data
	//{{AFX_DATA(StartGame)
	enum { IDD = IDD_START };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(StartGame)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(StartGame)
	afx_msg void OnSkip();
	afx_msg void OnStartNext();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STARTGAME_H__2B9ACEF4_A9BF_11D3_B397_00C04F29AE3F__INCLUDED_)
