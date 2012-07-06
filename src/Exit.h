/**************************************************************************
*                                                                         *
* Class          Exit                                                     *
*                                                                         *
* Author:        Matthew Bazar                                            *
*                                                                         *
* Description:   Interface of the Exit class.                             *
*                                                                         *
* Modifications: Matthew Bazar     12-08-99 Created                       *
**************************************************************************/
#if !defined(AFX_EXIT_H__2B9ACEF3_A9BF_11D3_B397_00C04F29AE3F__INCLUDED_)
#define AFX_EXIT_H__2B9ACEF3_A9BF_11D3_B397_00C04F29AE3F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// Exit dialog                                                             //
/////////////////////////////////////////////////////////////////////////////
class Exit : public CDialog
{
// Construction
public:
	Exit(CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(Exit)
	enum { IDD = IDD_EXIT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Exit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(Exit)
	afx_msg void OnSkip();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXIT_H__2B9ACEF3_A9BF_11D3_B397_00C04F29AE3F__INCLUDED_)
